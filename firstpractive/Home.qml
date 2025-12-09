import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import com.company.ProductControl
import firstpractive
Item {
    id:root

    property bool choicedrink:false
    Product{
        productid: 0
        id: curproduct
        image: ""
        name: ""
        price: 0
    }

    RowLayout{
        anchors.margins: 20
        anchors.fill: parent

        ColumnLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 7
            spacing: 10
            Behavior on Layout.preferredWidth {
                NumberAnimation { duration: 400; easing.type: Easing.InOutQuad }
            }
            RowLayout{
                Layout.fillWidth: true
                Image{
                    Layout.preferredWidth: 150
                    Layout.preferredHeight:  150
                    source: "assets/images/logo.jpg"
                    fillMode: Image.PreserveAspectFit
                }
                Text{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "blue"
                    font.pixelSize: 20

                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    text: "Chào mừng đến Hoang coffee shop"
                }
            }
            Text{
                Layout.fillWidth: true

                font.pixelSize: 20
                text: "Mời bạn chọn món"
                horizontalAlignment: Text.AlignHCenter
            }


            Rectangle{

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 540
                border.color: "green"
                border.width: 2
                radius: 10
                // padding:20
                // color:"red"
                GridView {
                    anchors.fill: parent
                    anchors.margins: 20
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true


                    id: gridView
                    // anchors.fill: parent
                    cellWidth: 200   // chiều rộng 1 ô
                    cellHeight: 240  // chiều cao 1 ô
                    model: ProductControl        // số lượng sản phẩm
                    interactive: true
                    clip: true
                    // radius: 10

                    delegate: Rectangle {
                        id: delegate
                        required property int productid
                        required property string name
                        required property url image
                        required property int price
                        required property int index
                        width: gridView.cellWidth-20
                        height: gridView.cellHeight-20

                        // anchors.margins: 20
                        border.width: 1
                        border.color: "gray"
                        radius: 10

                        ColumnLayout {
                            anchors.centerIn: parent
                            spacing: 10
                            Image {

                                source: "assets/images/"+delegate.image
                                Layout.preferredWidth:  100;
                                Layout.preferredHeight:  100
                                fillMode: Image.PreserveAspectFit
                            }
                            Text {
                                Layout.fillWidth: true
                                text: delegate.name
                                horizontalAlignment: Text.AlignHCenter
                                // anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text{
                                Layout.fillWidth: true
                                color: "orange"
                                font.pixelSize: 16
                                text: delegate.price.toString()+"đ"
                                horizontalAlignment: Text.AlignHCenter
                                // anchors.horizontalCenter: parent.horizontalCenter
                            }

                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                if (root.choicedrink===false) root.choicedrink=true
                                curproduct.image=delegate.image
                                curproduct.productid=delegate.productid
                                curproduct.name=delegate.name
                                curproduct.price=delegate.price
                                console.log("productid=",curproduct.productid)

                            }
                        }
                    }
                }
            }


        }
        ColumnLayout{
            Layout.fillWidth: true
            Layout.fillHeight:true
            Layout.preferredWidth: 3
            spacing: 20
            visible: root.choicedrink
            Behavior on Layout.preferredWidth {
                NumberAnimation { duration: 400; easing.type: Easing.InOutQuad }
            }
            Text{
                Layout.fillWidth: true
                text: "Chi tiết sản phẩm"
                font.pixelSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            Image {
                id: productimage
                source: "assets/images/"+curproduct.image
                Layout.fillWidth: true
                Layout.preferredHeight: 200
                Layout.preferredWidth: 200

                fillMode: Image.PreserveAspectFit

            }
            Text{
                id:productname
                Layout.fillWidth: true
                font.pixelSize: 20
                text: curproduct.name
                color: "blue"
                horizontalAlignment: Text.AlignHCenter
            }




            RowLayout{
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                Text{
                    font.pixelSize: 20
                    text: "Số lượng"
                }
                SpinBox {
                    id: numberproduct
                    from: 1
                    to: 20
                    value: 1          // giá trị mặc định
                    stepSize: 1       // mỗi lần tăng/giảm bao nhiêu
                    width: 100
                    background: Rectangle {
                        implicitWidth: spin.width
                        implicitHeight: 30
                        color: "#ffffff"
                        border.color: "#21be2b"
                        border.width: 1
                        radius: 10
                    }
                    onValueChanged: {
                        priceproducts.text=curproduct.price*value+"đ"
                    }
                }
            }

            RowLayout{
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                Text{
                    font.pixelSize: 18
                    text: "Giá:"
                }
                Text{
                    id: priceproducts
                    font.pixelSize: 20
                    color:"orange"
                    text: curproduct.price+"đ"
                }
            }
            Rectangle{
                Layout.preferredWidth: 200
                color:addCardBtn.containsPress?"orange":"green"
                Layout.preferredHeight: 50
                Layout.alignment: Qt.AlignHCenter
                radius: 20

                Text{
                    anchors.centerIn: parent
                    font.pixelSize: 20
                    color:"white"
                    text: "Thêm vào giỏ hàng"

                }
                MouseArea {
                    id: addCardBtn
                    anchors.fill: parent
                    onClicked: {
                        ProductControl.addProductToBill( curproduct.productid,  ProductControl.curBillId,numberproduct.value )
                    }
                }

            }
        }
    }
    Connections {
        target: ProductControl
        function onProductAddedToBill(message) {
            console.log(message)
            // Có thể hiện thông báo cho user
            Qt.callLater(() => {
                toast.show(message)
            })
        }
    }
    // Rectangle {
    //     id: toast
    //     visible: false
        // anchors.horizontalCenter: parent.horizontalCenter
        // width: parent.width * 0.6
    //     height: 40
    //     color: "#333"
    //     radius: 8
    //     opacity: 0.0

    //     Text {
    //         id: toastText
    //         anchors.centerIn: parent
    //         color: "white"
    //     }

    //     SequentialAnimation {
    //         id: toastAnim
    //         PropertyAnimation { target: toast; property: "opacity"; from: 0; to: 0.8; duration: 200 }
    //         PauseAnimation { duration: 1500 }
    //         PropertyAnimation { target: toast; property: "opacity"; from: 0.8; to: 0; duration: 300 }
    //         onStopped: toast.visible = false
    //     }

    //     function show(msg) {
    //         toastText.text = msg
    //         visible = true
    //         toastAnim.start()
    //     }
    // }
    Message{
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.6
    }
}
