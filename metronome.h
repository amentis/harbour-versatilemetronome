#ifndef METRONOME_H
#define METRONOME_H

#include <QObject>
#include <math.h>
#include <QtMultimedia/QSoundEffect>
#include <QTimer>
#include <QString>

class Metronome : public QObject
{
    friend class MetronomeThread;
    Q_OBJECT
    Q_PROPERTY(quint16 tempo READ tempo WRITE setTempo NOTIFY tempoChanged)
    Q_PROPERTY(quint8 numenator READ numenator WRITE setNumenator NOTIFY numenatorChanged)
    Q_PROPERTY(quint8 denumenator READ denumenator WRITE setDenumenator NOTIFY denumenatorChanged)
    Q_PROPERTY(quint8 denumenatorPower READ denumenatorPower WRITE setDenumenatorPower NOTIFY denumenatorPowerChanged)
    Q_PROPERTY(bool playing READ playing WRITE setPlaying NOTIFY playingChanged)
    Q_PROPERTY(QString sound READ sound WRITE setSound NOTIFY soundChanged)
//    Q_PROPERTY(bool inFourths READ inFourths WRITE setInFourths NOTIFY inFourthsChanged)
public:
    explicit Metronome(QObject *parent = 0);
    ~Metronome();

    quint16 tempo();
    void setTempo (quint16 &newTempo);

    quint8 numenator();
    void setNumenator (quint8& newNumenator);

    quint8 denumenator();
    void setDenumenator (quint8& newDenumenator);

    quint8 denumenatorPower();
    void setDenumenatorPower(quint8& newDenumenatorPower);

    bool playing();
    void setPlaying(bool newPlaying);

    QString sound();
    void setSound(QString newSound);

//    bool inFourths();
//    void setInFourths(bool newInFourths);

public slots:

    void updateCount();
    void updateSound();

private:
    quint16 _tempo;
    quint8 _numenator;
    quint8 _denumenatorPower;
    quint8 _denumenator;
    bool _playing;
    QSoundEffect* _clickHigh;
    QSoundEffect* _clickLow;
    QTimer* _timer;
    quint8 currentBeat;
    QString* path;
    QString _sound;
    bool _inFourths;

signals:
    void tempoChanged();
    void numenatorChanged();
    void numenatorPowerChanged();
    void denumenatorPowerChanged();
    void denumenatorChanged();
    void playingChanged();
    void metronomeChanged();
    void soundChanged();
//    void inFourthsChanged();

private slots:
    void click();
    void playStop();
};

#endif // METRONOME_H
