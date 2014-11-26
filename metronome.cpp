#include "metronome.h"

#include <QDebug>

Metronome::Metronome(QObject *parent) :
    QObject(parent)
{

    _tempo = 120;
    _numenator = 4;
    _maximumNumenator = 8;
    _denumenator = 4;
    _denumenatorPower = 2;
    _playing = false;
    _inFourths = false;

    _clickHigh = new QSoundEffect(this);
    _clickLow = new QSoundEffect(this);

//    path = new QString("/opt/sdk/harbour-versatilemetronome/usr/share/harbour-versatilemetronome/sounds/");

    path = new QString("/usr/share/harbour-versatilemetronome/sounds/");

    _sound = "metronome";

    QString pathHigh;
    pathHigh.append(path);
    pathHigh.append(_sound);
    pathHigh.append("-high.wav");

    QString pathLow;
    pathLow.append(path);
    pathLow.append(_sound);
    pathLow.append("-low.wav");

    _clickHigh->setSource(QUrl::fromLocalFile(pathHigh));
    _clickLow->setSource(QUrl::fromLocalFile(pathLow));
    _clickHigh->setLoopCount(0);
    _clickLow->setLoopCount(0);
    _clickHigh->setVolume(1.f);
    _clickLow->setVolume(1.f);

    QObject::connect(this, SIGNAL(playingChanged()), this, SLOT(playStop()));

    _timer = new QTimer();

    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(click()));

    QObject::connect(this, SIGNAL(denumenatorChanged()), this, SLOT(updateCount()));
    QObject::connect(this, SIGNAL(numenatorChanged()), this, SLOT(updateCount()));
    QObject::connect(this, SIGNAL(tempoChanged()), this, SLOT(updateCount()));
    QObject::connect(this, SIGNAL(soundChanged()), this, SLOT(updateSound()));
    QObject::connect(this, SIGNAL(denumenatorChanged()), this, SLOT(updateMaximumNumenator()));
//    QObject::connect(this, SIGNAL(inFourthsChanged()), this, SLOT(updateCount()));
}

Metronome::~Metronome(){
    delete _clickHigh;
    delete _clickLow;
    _timer->stop();
    delete _timer;
}

quint16 Metronome::tempo(){
    return _tempo;
}

void Metronome::setTempo(quint16& newTempo) {
    if (newTempo != _tempo){
        _tempo = newTempo;
        emit tempoChanged();
    }
}

quint8 Metronome::numenator() {
    return _numenator;
}

void Metronome::setNumenator(quint8& newNumenator) {
    if (newNumenator != _numenator){
        _numenator = newNumenator;
        emit numenatorChanged();
    }
}

quint8 Metronome::denumenator() {
    return _denumenator;
}

void Metronome::setDenumenator(quint8& newDenumenator) {
    if (newDenumenator != _denumenator){
        _denumenator = newDenumenator;
        emit denumenatorChanged();
    }
}

quint8 Metronome::denumenatorPower() {
    return _denumenatorPower;
}

void Metronome::setDenumenatorPower(quint8 &newDenumenatorPower) {
    if (newDenumenatorPower != _denumenatorPower){
        _denumenatorPower = newDenumenatorPower;
        quint8 newDenumenator = pow(2,denumenatorPower());
        setDenumenator(newDenumenator);
        emit denumenatorPower();
    }
}

bool Metronome::playing() {
    return _playing;
}

void Metronome::setPlaying(bool newPlaying) {
    if (newPlaying!= _playing){
        _playing = newPlaying;
        emit playingChanged();
    }
}

//bool Metronome::inFourths() {
//    return _inFourths;
//}

//void Metronome::setInFourths(bool newInFourths){
//    if (newInFourths != _inFourths){
//        _inFourths = newInFourths;
//        emit inFourthsChanged();
//    }
//}

void Metronome::playStop() {
    if (playing()){
        currentBeat = 1;
        emit tempoChanged();
        _timer->start();
    } else {
        _timer->stop();
    }
}

void Metronome::click(){
    if (currentBeat == 1){
        _clickHigh->play();
    } else {
        _clickLow->play();
    }
    currentBeat++;
//    if (inFourths()){

//    } else {
        if (currentBeat > numenator()){
            currentBeat = 1;
//        }
    }
}

void Metronome::updateCount(){
    if (playing()){
        _timer->stop();
    }
//    if (inFourths()){

//    } else {
        _timer->setInterval(60000 / (tempo() * ((float)denumenator()/4.f)));
//    }
    if (playing()){
        _timer->start();
    }
}

void Metronome::updateSound(){
    if (playing()){
        _timer->stop();
    }
    QString pathHigh;
    pathHigh.append(path);
    pathHigh.append(_sound);
    pathHigh.append("-high.wav");

    QString pathLow;
    pathLow.append(path);
    pathLow.append(_sound);
    pathLow.append("-low.wav");

    _clickHigh->setSource(QUrl::fromLocalFile(pathHigh));
    _clickLow->setSource(QUrl::fromLocalFile(pathLow));

    if (playing()){
        _timer->start();
    }
}

QString Metronome::sound(){
    return _sound;
}

void Metronome::setSound(QString newSound){
    if (newSound != _sound){
        _sound = newSound;
        emit soundChanged();
    }
}

quint8 Metronome::maximumNumenator(){
    return _maximumNumenator;
}

void Metronome::setMaximumNumenator(quint8& newMaximumNumenator){
    if (newMaximumNumenator != _maximumNumenator){
        _maximumNumenator = newMaximumNumenator;
        emit maximumNumenatorChanged();
    }
}

void Metronome::updateMaximumNumenator(){
    quint8 newMaximumDenumenator;
    if (denumenator() == 128){
        newMaximumDenumenator = denumenator();
    } else {
        newMaximumDenumenator = denumenator()*2;
    }
    setMaximumNumenator(newMaximumDenumenator);
    if (denumenator() < numenator()){
        setNumenator(_denumenator);
    }
}
