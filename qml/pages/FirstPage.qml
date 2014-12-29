/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    SilicaFlickable{
        id: flick
        anchors.top: parent.top
        anchors.fill: parent
        PullDownMenu{
            MenuItem{
                text: "Select Metronome Sound"
                onClicked: {
                    var dialog = pageStack.push("ChooseSound.qml", {"selectedSound": metronome.sound})
                    dialog.accepted.connect(function(){
                        metronome.sound = dialog.selectedSound
                    })
                }
            }
        }
        Column {
            anchors {
                top: parent.top
                margins: 3 * Theme.paddingLarge
            }

            width: page.width
            spacing: Theme.paddingLarge
            TextEdit{
                id: tempoField
                x: Theme.paddingLarge
                text: qsTr("" + metronome.tempo)
                color: Theme.primaryColor
                inputMethodHints: Qt.ImhDigitsOnly
                width: Theme.itemSizeSmall
                EnterKey.enabled: text.length > 1
                EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                EnterKey.onClicked: {
                    focus = false
                    if ((1 * text) < 40){
                        metronome.tempo = 40
                        text = "" + 40
                    } else if ((1 * text) > 300){
                        metronome.tempo = 300
                        text = "" + 300
                    } else {
                        metronome.tempo = 1 * text
                    }
                }
            }

            Slider{
                x: Theme.paddingLarge
                id: tempoSlider
                width: parent.width
                minimumValue: 40
                maximumValue: 300
                value: metronome.tempo
                label: qsTr("Tempo")
                stepSize: 1

            }

            Binding{
                target: metronome
                property: "tempo"
                value: tempoSlider.value
            }



            Label{
                id: signatureLabel
                x: Theme.paddingLarge
                text: qsTr(metronome.numenator + "/" + metronome.denumenator)
            }

            Slider{
                x: Theme.paddingLarge
                id: numenatorSlider
                width: parent.width
                minimumValue: 1
                maximumValue: metronome.maximumNumenator
                value: metronome.numenator
                label: qsTr("Numenator")
                stepSize: 1
            }

            Binding{
                target: metronome
                property: "numenator"
                value: numenatorSlider.value
            }

            Slider{
                x: Theme.paddingLarge
                id: denumenatorSlider
                width: parent.width
                minimumValue: 0
                maximumValue: 5
                value: metronome.denumenatorPower
                label: qsTr("Denumenator")
                stepSize: 1
            }

            Binding{
                target: metronome
                property: "denumenatorPower"
                value: denumenatorSlider.value
            }

//            TextSwitch{
//                x: Theme.paddingLarge
//                id: inFourthsSwitch
//                checked: metronome.inFourths
//                automaticCheck: true
//                text: "Count in Fourths"
//                onCheckedChanged: metronome.inFourths = checked
//            }

            Label{
                id : spacer
                text: " "
                x: Theme.paddingLarge
                //yep, not a great idea, but works
            }

            Button{
                x: Theme.paddingLarge
                id: startStopButton
                width: .9 * parent.width
                text: metronome.playing? "Stop" : "Start"
                onClicked: metronome.playing ? metronome.playing = false : metronome.playing = true
            }
        }
    }
}


