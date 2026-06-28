import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

QQC2.ItemDelegate {
    id: root

    required property string deviceId
    required property string name
    required property string host
    required property bool   connected
    required property int    status        // NetworkAudioDevice::Status as int
    required property bool   autoConnect
    required property bool   hasPreference
    required property string deviceType

    readonly property bool isAvailable: status === 0
    readonly property bool isIgnored:   status === 2

    readonly property string deviceIcon: {
        switch (deviceType) {
        case "Apple TV": return "video-television"
        case "AirPort Express": return "network-wireless"
        default: return "audio-speakers"
        }
    }

    signal connectRequested
    signal disconnectRequested
    signal autoConnectToggled(bool enabled)
    signal forgetRequested

    contentItem: RowLayout {
        spacing: Kirigami.Units.smallSpacing

        Kirigami.Icon {
            source: root.deviceIcon
            opacity: root.isAvailable ? 1.0 : 0.5
            Layout.preferredWidth:  Kirigami.Units.iconSizes.medium
            Layout.preferredHeight: Kirigami.Units.iconSizes.medium
            Layout.alignment: Qt.AlignVCenter
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 0

            QQC2.Label {
                text: root.name
                Layout.fillWidth: true
                elide: Text.ElideRight
            }

            QQC2.Label {
                visible: root.deviceType.length > 0 || (root.isAvailable && root.host.length > 0)
                text: {
                    if (root.deviceType.length > 0 && root.isAvailable && root.host.length > 0)
                        return root.deviceType + "  ·  " + root.host
                    if (root.deviceType.length > 0)
                        return root.deviceType
                    return root.host
                }
                Layout.fillWidth: true
                elide: Text.ElideRight
                font: Kirigami.Theme.smallFont
                opacity: 0.7
            }
        }

        // Auto-connect checkbox — shown for Available and Offline, not Ignored
        QQC2.CheckBox {
            visible: !root.isIgnored
            checked: root.autoConnect
            text: i18n("Auto-connect")
            onToggled: root.autoConnectToggled(checked)
        }

        // Connect/Disconnect — only for Available devices
        QQC2.Button {
            visible: root.isAvailable
            text: root.connected ? i18n("Disconnect") : i18n("Connect")
            icon.name: root.connected ? "network-disconnect" : "network-connect"
            onClicked: root.connected ? root.disconnectRequested() : root.connectRequested()
        }

        // Forget — shown whenever a preference entry exists
        QQC2.Button {
            visible: root.hasPreference
            text: i18n("Forget")
            icon.name: "edit-delete-remove"
            onClicked: root.forgetRequested()
        }
    }
}
