import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

QQC2.ItemDelegate {
    id: root

    required property string deviceId
    required property string name
    required property string host
    required property bool connected

    signal connectRequested
    signal disconnectRequested

    contentItem: RowLayout {
        spacing: Kirigami.Units.smallSpacing

        Kirigami.Icon {
            source: "audio-speakers"
            Layout.preferredWidth: Kirigami.Units.iconSizes.medium
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
                text: root.host
                Layout.fillWidth: true
                elide: Text.ElideRight
                font: Kirigami.Theme.smallFont
                opacity: 0.7
            }
        }

        QQC2.Button {
            text: root.connected ? i18n("Disconnect") : i18n("Connect")
            icon.name: root.connected ? "network-disconnect" : "network-connect"
            onClicked: root.connected ? root.disconnectRequested() : root.connectRequested()
        }
    }
}
