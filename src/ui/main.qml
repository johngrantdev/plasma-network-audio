import QtQuick
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.kcmutils as KCM

KCM.ScrollViewKCM {
    id: root

    header: Kirigami.InlineMessage {
        visible: kcm.lastError.length > 0
        type: Kirigami.MessageType.Error
        text: kcm.lastError
        showCloseButton: true
        onVisibleChanged: if (!visible) kcm.clearLastError()
    }

    view: ListView {
        id: deviceView
        model: kcm.deviceModel

        Kirigami.PlaceholderMessage {
            anchors.centerIn: parent
            visible: deviceView.count === 0
            icon.name: "audio-speakers"
            text: i18n("No Network Audio Devices Found")
            explanation: i18n("Make sure your audio device is powered on and connected to the same network.")
            width: parent.width - Kirigami.Units.gridUnit * 4
        }

        // Group by status role: 0=Available, 1=Offline, 2=Ignored
        section.property: "status"
        section.delegate: Kirigami.ListSectionHeader {
            width: deviceView.width
            label: {
                if (section === "0") return i18n("Available")
                if (section === "1") return i18n("Offline")
                if (section === "2") return i18n("Ignored")
                return ""
            }
        }

        delegate: DeviceDelegate {
            width: deviceView.width
            onConnectRequested:    kcm.connectDevice(deviceId)
            onDisconnectRequested: kcm.disconnectDevice(deviceId)
            onAutoConnectToggled:  kcm.setAutoConnect(deviceId, enabled)
            onForgetRequested:     kcm.forgetDevice(deviceId)
        }
    }
}
