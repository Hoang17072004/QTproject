import QtQuick
import com.company.PlayerController
import com.company.AudioSearchModel
// Window {
//     id:root
//     width: 640
//     height: 480
//     visible: true
//     title: "hello"

//     Rectangle{
//         id:button1
//         property color baseColor: "red"
//         anchors{
//             bottom: parent.verticalCenter
//             horizontalCenter: parent.horizontalCenter
//             bottomMargin: 15

//         }
//         width: 150
//         height: 50
//         color: if (buttonMouseArea1.containsPress) {
//                    return Qt.darker(baseColor)
//                } else if (buttonMouseArea1.containsMouse) {
//                    return Qt.lighter(baseColor)
//                } else {
//                    return baseColor
//                }

//         Text {
//             id: buttonText1
//             text: qsTr("Click me")
//             anchors.centerIn: parent
//         }

//         MouseArea{
//             id:buttonMouseArea1
//             anchors.fill: parent
//             hoverEnabled: true
//             onClicked: {
//                 button1.baseColor="orange"
//             }
//         }
//     }
//     Rectangle{
//         property color baseColor: "#00FF00"
//         anchors{
//             top: parent.verticalCenter
//             horizontalCenter: parent.horizontalCenter
//             topMargin: 15

//         }
//         width: 150
//         height: 50
//         color: if (buttonMouseArea2.containsPress) {
//                    return Qt.darker(baseColor)
//                } else if (buttonMouseArea2.containsMouse) {
//                    return Qt.lighter(baseColor)
//                } else {
//                    return baseColor
//                }

//         Text {
//             id: buttonText2
//             text: qsTr("Close Application")
//             anchors.centerIn: parent
//         }

//         MouseArea{
//             id:buttonMouseArea2
//             anchors.fill: parent
//             hoverEnabled: true
//             onClicked: {
//                 Qt.quit()
//             }
//         }
//     }
//     Connections{
//         target: buttonMouseArea2
//         function onClicked(){
//             console.log("hello")
//         }
//     }
// }
import QtQuick.Layouts
// Window{
//     width: 640
//     height: 480
//     visible: true
//     title: "Hello world"
//     color: "lightyellow"
//     GridLayout{
//         anchors.fill: parent
//         rows: 2
//         columns:  2
//         rowSpacing: 10
//         columnSpacing: 10
//         Item {
//             Layout.fillHeight: true
//             Layout.fillWidth: true
//             Rectangle{
//                 width: 50
//                 height: 50
//                 color: "orange"
//                 x: 50
//                 y: 50
//             }
//         }
//         Item{
//             Layout.fillWidth: true
//             Layout.fillHeight: true
//             Rectangle{
//                 width: 100
//                 height: 75


//                 anchors{
//                     top: parent.verticalCenter
//                     left: parent.horizontalCenter
//                 }
//                 color: "darkred"
//             }
//         }
//         Item {
//             Layout.fillHeight: true
//             Layout.fillWidth: true
//             Flow{
//                 anchors.fill: parent
//                 spacing: 12
//                 Repeater {
//                     model: 5
//                     Rectangle{
//                         width: 50
//                         height: 50
//                         color: "green"
//                     }
//                 }
//             }

//         }
//         Item{
//             Layout.fillWidth: true
//             Layout.fillHeight: true
//             GridLayout{
//                 anchors.fill: parent
//                 rows: 2
//                 columns: 2
//                 rowSpacing: 20
//                 columnSpacing: 20
//                 Rectangle{
//                     Layout.fillWidth: true
//                     Layout.fillHeight: true
//                     color: "black"
//                 }
//                 Rectangle{
//                     Layout.fillWidth: true
//                     Layout.fillHeight: true
//                     color: "red"
//                 }
//                 Rectangle{
//                     Layout.fillWidth: true
//                     Layout.fillHeight: true
//                     color:"magenta"
//                     Layout.columnSpan: 2
//                 }
//             }
//         }
//     }
// }
Window{
    id:root
    width: 640
    height: 480
    title: "Song app"
    visible: true
    // signal searchRequested
    Rectangle{
        id: topbar
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 50
        color: "#5F8575"
        SearchField{

            anchors{
                left:parent.left
                right: closeSearchButton.left
                verticalCenter: parent.verticalCenter
                margins: 10

            }
            height: 30
            visible: !searchPanel.hidden
            onSearchAccepted: value=>{
                AudioSearchModel.searchSong(value)
                topbar.forceActiveFocus()
            }
        }
        ImageButton{
            width: 50
            source: "assets/icons/second.png"
            id: playlisticon
            anchors{
                // bottom: topbar.bottom
                right:parent.right
                verticalCenter: parent.verticalCenter
                // bottom:parent.bottom
            }
            visible: searchPanel.hidden
            onClicked: {
                playlistPanel.hidden=!playlistPanel.hidden
            }
        }
        ImageButton{
            id: closeSearchButton
            width: 50
            anchors{
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            source: "assets/icons/First.png"
            visible: !searchPanel.hidden
            onClicked: {
                searchPanel.hidden=!searchPanel.hidden
            }
        }
    }
    Rectangle{
        id:mainSection
        color:"black"
        anchors{
            top: topbar.bottom
            bottom: bottomBar.top
            left: parent.left
            right: parent.right
        }
        // TextButton{
        //     id:previousButton
        //     text: "<"
        //     height: 50
        //     width: 50
        //     onClicked: PlayerController.switchToPreviousSong()
        // }
        // RowLayout
        AudioInfoBox{
            id:songInfo
            anchors{
                verticalCenter: parent.verticalCenter
                left:parent.left
                right:parent.right
                margins: 20
            }



        }

    }
    Rectangle{
        id:bottomBar
        anchors{
            bottom: parent.bottom
            left: parent.left
            right:parent.right

        }
        height: 100
        color:"#333333"
        Row{
            anchors.centerIn: parent
            spacing: 20
            enabled: !!PlayerController.currentSong
            opacity: !!PlayerController.currentSong?1:0.3
            // Rectangle{
            //     color: white
            //     width: 100
            //     height: 100
            // }

            ImageButton{
                id:previousButton1
                source: "assets/icons/First.png"
                height: 64
                width: 64
                onClicked: PlayerController.switchToPreviousSong()

            }
            ImageButton{
                id: playPauseButton
                height: 64
                width: 64
                source: PlayerController.playing?"assets/icons/First.png":"assets/icons/second.png"
                onClicked: PlayerController.playPause()

            }
            ImageButton{
                id:nextButton
                source: "assets/icons/third.png"
                height: 64
                width: 64
                onClicked: PlayerController.switchToNextSong()
            }
        }
    }
    PlaylistPanel{
        id:playlistPanel
        anchors{
            top: topbar.bottom
        }
        x:hidden?parent.width:parent.width-width
        onSearchRequested: {
            searchPanel.hidden=false
        }
    }
    SearchPanel{
        id:searchPanel
        anchors{
            top:topbar.bottom
            left:parent.left
            right:parent.right
        }
        height: mainSection.height+bottomBar.height
        visible: !hidden

    }


}
