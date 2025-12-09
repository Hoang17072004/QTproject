import QtQuick
import com.company.PlayerController
import com.company.AudioSearchModel
Rectangle {
    id:root
    property bool hidden: true
    color:"#333333"
    // visible:
    ListView{
        id:listview
        anchors{
            fill: parent
            margins: 20

        }
        spacing: 10
        clip: true
        model: AudioSearchModel
        delegate:  Rectangle{
            id: delegate
            required property string audioAuthor
            required property url audioSource
            required property url audioImageSource
            required property url audioName
            required property int index
            width: listview.width
            height: 50
            color:"#1e1e1e"
            // Row{

                // anchors.fill: parent
                Image{
                    // height: parent.height
                    id: songimage
                    anchors{
                        verticalCenter: parent.verticalCenter
                        margins: 10

                        left:parent.left
                    }
                    source: delegate.audioImageSource
                    width: 30
                    height: 30
                }

                Column{

                    anchors{
                        top:parent.top
                        left:songimage.right
                        right: parent.right
                        margins: 5
                    }

                    spacing: 5
                    Text{
                        // left: songimage.right
                        // height:
                        // width: parent.width
                        elide: Text.ElideRight
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 10
                        color: "white"
                        text: delegate.audioName
                        font{
                            pixelSize: 14
                            bold: true
                        }
                    }
                    Text{
                        width: parent.width
                        elide: Text.ElideRight
                        fontSizeMode: Text.Fit
                        minimumPixelSize: 6
                        color: "white"
                        text: delegate.audioAuthor
                        font{
                            pixelSize: 10

                        }
                    }
                }
                MouseArea{
                    id:delegateMouseArea
                    anchors.fill: parent
                    onClicked: {
                        root.hidden=true
                        PlayerController.addAudio(delegate.audioName,delegate.audioAuthor,delegate.audioSource,delegate.audioImageSource)
                        // PlayerController.
                    }
                }
            // }




        }

    }
}
