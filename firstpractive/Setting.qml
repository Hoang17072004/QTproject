import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.company.ProductControl
import com.company.CurBillController
Item {
    id:root
    signal submitBillSuccess
    Rectangle {
        anchors.fill: parent
        RowLayout{
            anchors.fill: parent
            ColumnLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 7
                spacing: 10
                Text{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    font.pixelSize: 20
                    color: "blue"
                    horizontalAlignment: Text.AlignHCenter
                    text: "Chi tiết hoá đơn"
                }


                ListView{
                    id: listview
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    // Layout.preferredHeight: 200

                    model: CurBillController
                    spacing: 10
                    delegate: Rectangle{

                        width: listview.width
                        height: 100
                        required property int productId
                        required property string productName
                        required property int productPrice
                        required property url productImage
                        required property int productQuantity
                        required property int index
                        id:delegate
                        radius: 5
                        Rectangle{
                            anchors.fill: parent
                            anchors.margins: 10




                            width: listview.width
                            height: 80
                            // anchors.margins: 10
                            RowLayout{
                                anchors.fill: parent
                                spacing: 10
                                Image{
                                    // Layout.preferredWidth: 50
                                    Layout.preferredHeight: 50
                                    // Layout.fillHeight: true
                                    // Layout.preferredHeight: 50
                                    Layout.fillWidth:  true

                                    Layout.preferredWidth: 1
                                    source: delegate.productImage
                                    fillMode: Image.PreserveAspectFit

                                }
                                Text{
                                    Layout.fillWidth: true
                                   // Layout.preferredWidth: 100
                                    // Layout.fillHeight: true
                                    Layout.preferredWidth:  2
                                   font.pixelSize: 16
                                   // padding: 10
                                    verticalAlignment: Text.AlignVCenter
                                    elide: Text.ElideRight
                                   text: delegate.productName

                                    // Layout.fillHeight: true

                                }
                                Text{
                                    Layout.fillWidth: true
                                    // Layout.fillHeight: true
                                    Layout.preferredWidth:  1
                                    font.pixelSize: 16
                                    padding: 10
                                    color: "red"
                                    verticalAlignment: Text.AlignVCenter
                                    text:delegate.productPrice
                                }
                                SpinBox{
                                    Layout.fillWidth:   true
                                    Layout.preferredWidth: 1
                                    // Layout.preferredWidth: 100
                                    // Layout.preferredHeight: 1

                                    from: 1
                                    to: 10
                                    value: delegate.productQuantity
                                    onValueChanged: {
                                        CurBillController.setData(delegate.index, value, CurBillController.productQuantityRole)

                                    }

                                }
                                Rectangle{
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 30
                                    // Layout.fillHeight: true
                                    Layout.preferredWidth: 1
                                    radius: 10
                                    // height: 50
                                    // width: 50
                                    color: "green"
                                    Text{
                                        anchors.centerIn: parent
                                        color: "white"
                                        font.pixelSize: 16
                                        text: "Xoá"
                                    }
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            // ProductControl.curBillId
                                            CurBillController.deleteProductInBill(ProductControl.curBillId,delegate.productId)
                                        }
                                    }
                                }
                            }
                        }

                        // Layout.margins: 10

                        border.width: 2

                    }
                }
            }
            ColumnLayout{

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 3
                spacing: 10
                Text{
                    font.pixelSize: 30
                    color: "green"
                    // width:  parent.width
                    Layout.fillWidth: true
                    // horizontalCenter: parent.horizontalCenter
                    text: "Tổng tiền phải trả"
                    horizontalAlignment: Text.AlignHCenter
                    // Layout.preferredHeight: 50
                    // Layout.preferredWidth: 100
                }

                RowLayout{
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    // Layout.preferredHeight: 100
                    Text{
                        font.pixelSize: 16
                        color: "blue"
                        text: "Tổng hoá đơn:"
                    }
                    Text{
                        id:price
                        font.pixelSize: 30
                        color: "red"
                        text: CurBillController. totalPrice
                    }
                }
                Image{
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    Layout.preferredWidth:  200
                    fillMode: Image.PreserveAspectFit

                    source: "assets/images/ExampleCode.png"
                }

                Rectangle{
                    // Layout.fillWidth: true
                    color: "green"
                    // width: 100
                    // height: 50
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignHCenter
                    radius: 10
                    Text{
                        anchors.centerIn: parent
                        text: "Thanh toán"
                        font.pixelSize: 20
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            CurBillController.submitBill();
                        }
                    }
                }
            }
        }
        Connections {
            target: CurBillController
            function ondeleteProductBillSuccess(message) {
                console.log(message)
                // Có thể hiện thông báo cho user
                Qt.callLater(() => {
                    toast.show(message)
                })
            }
            function onsubmitBillSucces(message) {
                console.log(message)
                // Có thể hiện thông báo cho user
                Qt.callLater(() => {
                    toast.show(message)
                    root.submitBillSuccess()
                    CurBillController.createNewBill()
                })

            }
        }
        Message{
            id: toast
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.6
        }
    }
}
