import QtQuick
import QtQuick.Controls
import com.company.CurBillController
import com.company.ProductControl
Window {
    width: 1000
    height: 600
    visible: true
    id:root
    property int currentIndex: 0
    Rectangle {
        anchors.fill: parent
        color: "white"

        Column {
            width: parent.width
            height: parent.height

            spacing: 10
            // Thanh taskbar (luôn hiển thị)
            Row {
                id: taskbar
                width: parent.width
                height: 26
                spacing:5
                padding: 5
                ListModel {
                    id: buttonModel
                    ListElement { label: "Home"; page: "Home.qml" ;index:0}
                    ListElement { label: "Setting"; page: "Setting.qml";index: 1 }

                }
                Repeater{
                    model: buttonModel
                    Rectangle {
                        width: 100
                        height: parent.height
                        color: !taskbarButton.containsMouse?"#3498db":"#2980b9"
                        radius: 12

                        Text {
                            anchors.centerIn: parent
                            color:!taskbarButton.containsMouse?"white":"lightgray"
                            text: model.label
                            font.pixelSize: 16
                        }

                        MouseArea {
                            id:taskbarButton
                            anchors.fill: parent
                            onClicked: {
                                root.currentIndex=model.index
                                if(root.currentIndex==1) {
                                    CurBillController.loadBillDetail(ProductControl.curBillId)
                                }
                            }
                        }
                    }
                }




            }

            Home{
                width: parent.width
                height: parent.height - taskbar.height
                visible: root.currentIndex==0
                id:home
            }
            Setting{
                width: parent.width
                height: parent.height - taskbar.height
                visible: root.currentIndex==1
                onSubmitBillSuccess: {
                    root.currentIndex=0
                    home.choicedrink=false
                }
            }

            // Nội dung thay đổi
            // Loader {
            //     id: loader
            //     // anchors{
            //     //     top: taskbar.bottom
            //     //     left:parent.left
            //     //     right:parent.right
            //     //     bottom:parent.bottom
            //     //     topMargin: 5
            //     // }
            //     // visible: root.currentIndex==1
            //     width: parent.width
            //     height: parent.height - taskbar.height
            //     source: "Setting.qml"
            // }
        }
    }

}
