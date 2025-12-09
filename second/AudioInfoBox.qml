import QtQuick
import com.company.PlayerController
import second
Item {
    id:root



    visible: !!PlayerController.currentSong
    Image{
        id: albumImage
        anchors{
            verticalCenter:parent.verticalCenter
            left: parent.left

        }
        width: 150
        height: 150
        source: !!PlayerController.currentSong?PlayerController.currentSong.imageSource:""

    }
    Text {
        id: titleText
        anchors{
            bottom: parent.verticalCenter
            left: albumImage.right
            margins: 20
            right: parent.right
        }
        color:"white"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        text: !!PlayerController.currentSong?PlayerController.currentSong.title:""
        font.bold: true
        font.pixelSize: 20
    }
    Text {
        id: authorText
        anchors{
            top: parent.verticalCenter
            left: titleText.left
            topMargin: 5
            right: parent.right
        }
        color:"gray"
        text: !!PlayerController.currentSong?PlayerController.currentSong.authorName:""
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere

        font.pixelSize: 16
    }
}
