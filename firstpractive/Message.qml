import QtQuick
import QtQuick.Controls
Rectangle {
    // id: toast
    visible: false
    // anchors.horizontalCenter: parent.horizontalCenter
    // width: parent.width * 0.6
    height: 40
    color: "#333"
    radius: 8
    opacity: 0.0

    Text {
        id: toastText
        anchors.centerIn: parent
        color: "white"
    }

    SequentialAnimation {
        id: toastAnim
        PropertyAnimation { target: toast; property: "opacity"; from: 0; to: 0.8; duration: 200 }
        PauseAnimation { duration: 1500 }
        PropertyAnimation { target: toast; property: "opacity"; from: 0.8; to: 0; duration: 300 }
        onStopped: toast.visible = false
    }

    function show(msg) {
        toastText.text = msg
        visible = true
        toastAnim.start()
    }
}
