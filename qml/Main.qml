import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import GalleryModule 1.0          // C++ model

ApplicationWindow {
    visible: true
    width: 900
    height: 620
    title: "Image Gallery"

    /* ------------------------------------------------------------
       C++ list‑model (already registered via qmlRegisterType)
       ------------------------------------------------------------ */
    GalleryModel { id: gallery }

    /* ------------------------------------------------------------
       SplitView  |  [ thumbnail column ]  |  [ large preview ]
       ------------------------------------------------------------ */
    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        /* === LEFT PANE : scrollable thumbnail grid =============== */
        Rectangle {
            // SplitView attached‑properties (NOT Layout.*)
            SplitView.preferredWidth: 250      // starts 250 px wide
            SplitView.minimumWidth:   200      // never collapses smaller
            color: "#eeeeee"
            border.color: "#bbbbbb"
            border.width: 1

            GridView {
                id: thumbView
                anchors.fill: parent
                model: gallery
                cellWidth:  90
                cellHeight: 90
                clip: true                        // crop anything outside

                delegate: Item {
                    width:  thumbView.cellWidth
                    height: thumbView.cellHeight

                    Image {
                        anchors.fill: parent
                        anchors.margins: 4
                        source: gallery.sourceAt(index)

                        /*  Decode the pixmap at thumbnail size so huge
                            images don’t consume memory or overflow.    */
                        sourceSize.width:  thumbView.cellWidth  - 8
                        sourceSize.height: thumbView.cellHeight - 8
                        fillMode: Image.PreserveAspectFit
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: gallery.setCurrentIndex(index)
                    }
                }

                /* Native scroll bar automatically attached by Controls 2 */
                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AlwaysOn }
            }
        }

        /* === RIGHT PANE : large preview ========================== */
        Rectangle {
            SplitView.fillWidth: true            // takes remaining space
            color: "#222"                        // dark backdrop
            clip: true                           // NEVER let image overflow

            Image {
                anchors.fill: parent
                anchors.margins: 12              // little padding
                source: gallery.sourceAt(gallery.currentIndex)
                fillMode: Image.PreserveAspectFit
                asynchronous: true               // don’t block UI on big files
            }
        }
    }
}
