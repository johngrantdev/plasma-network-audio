import QtQuick
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.kcmutils as KCM

KCM.SimpleKCM {
    id: root

    header: Kirigami.InlineMessage {
        visible: kcm.lastError.length > 0
        type: Kirigami.MessageType.Error
        text: kcm.lastError
        showCloseButton: true
        onVisibleChanged: if (!visible) kcm.clearLastError()
    }

    Kirigami.PlaceholderMessage {
        anchors.centerIn: parent
        visible: deviceView.count === 0
        icon.name: "audio-speakers"
        text: i18n("No Network Audio Devices Found")
        explanation: i18n("Make sure your audio device is powered on and connected to the same network.")
        width: parent.width - Kirigami.Units.gridUnit * 4
    }

    ListView {
        id: deviceView
        model: kcm.deviceModel

        delegate: DeviceDelegate {
            width: deviceView.width
            onConnectRequested:    kcm.connectDevice(deviceId)
            onDisconnectRequested: kcm.disconnectDevice(deviceId)
        }
    }
}
