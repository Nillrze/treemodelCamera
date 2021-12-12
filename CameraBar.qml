import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as QC14
import QtQuick.Controls.Styles 1.4 as QCS14

import "../helper"
import "../helper/delegate"
import "../helper/textFiled"
import "../helper/headerLayout"

import VMS.ServiceGetCameraTree 1.0

Rectangle {
    id: rectCameraBar
    width: ptyWidth
    radius: 4
    color: Style.ptyColorPrimary

    property int ptyWidth: 300
//    property int ptyDelegateHeight:

    signal sigClicked

    ServiceGetCameraTree {
        id: serviceCameraTree
    }

    HeaderLayout {
        id: headerLayout
        ptyLeftIcon: "qrc:/assets/leftSidebar/camera.svg"
        ptyRightIcon: "qrc:/assets/popupImg/closePopup.svg"
        ptyTitleText: "Camera"
        onSigRightIconClicked: {
            rectCameraBar.visible = false
            searchTxt.ptySearchText = ""
            sigClicked()
        }
    }

    Rectangle { id: rectLine; width: parent.width; height: 1; color: Style.ptyColorWhite; anchors { bottom: searchTxt.top } opacity: 0.1 }

    CustomeSearchTextFiled {
        id: searchTxt
        ptyImgSize: 16
        ptyTextFieldFontSize: 15
        anchors { top: parent.top; topMargin: 50; right: parent.right; left: parent.left }
    }

    // list menu
    QC14.TreeView  {
        id: treeView
        width: ptyWidth
        anchors { top: searchTxt.bottom; topMargin: 4; bottom: parent.bottom }
        model: serviceCameraTree.cameraTreeModel
        alternatingRowColors: false
        headerVisible: false
        backgroundVisible: false
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff


        QC14.TableViewColumn {
//            role: "name"
//            title: "Name"
            width: ptyWidth
            delegate : Item {
                width: parent.width  //- 10
                height: styleData.hasChildren ? 48 : 40
               // anchors.horizontalCenter: parent.horizontalCenter

                Rectangle {
                    width: parent.width - 15
                    height: parent.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Style.ptyColorPrimary
                    Text {
                        color: Style.ptyColorWhite
                        text:  model.name
                        anchors.verticalCenter: parent.verticalCenter
                        font { family: Style.fontProductSansRegular; pixelSize: 15; bold: styleData.hasChildren ? true : false }
                    }
                }
            }

        }

        // itemDelegate:
        style: QCS14.TreeViewStyle {
            backgroundColor : Style.ptyColorPrimary

            rowDelegate: Rectangle {
                color: Style.ptyColorPrimary // styleData.selected? "blue" : styleData.alternate ? "red" : "yellow"
                height: styleData.hasChildren ? 48 : 40
                width: parent.width
            }

            branchDelegate: Rectangle {
                color: Style.ptyColorPrimary  // styleData.isExpanded? "purple" : "green"
                height: styleData.hasChildren ? 48 : 40
                width: 25

                Image {
                    id: iconIndicator
                    width: 14
                    height: 14
                    anchors { left: parent.left; leftMargin: 5; verticalCenter: parent.verticalCenter}
                    sourceSize.width: 14
                    sourceSize.height: 14
                    source: "qrc:/assets/rightsidebar/arrowright.svg"
                    fillMode: Image.PreserveAspectFit
                    rotation :  styleData.isExpanded ? 90 : 0
                    Behavior on rotation { RotationAnimation { duration: 150 } }
                }
            }
        }



        //        readonly property color cellBackgroundColor: "#EDEDF0"
        //        readonly property color cellCurrentRowColor: "#C4DEF4"
        //        readonly property color cellPressedColor: "#32A6FF"
        //        style: QCS14.TreeViewStyle {
        //            activateItemOnSingleClick: true
        //            backgroundColor: "white"//cellBackgroundColor
        //            itemDelegate: Item {
        //                width: 200
        //                height: 80
        //                Rectangle {
        //                    anchors.fill: parent
        //                    border.width: 1
        //                    border.color: "#7f838c"
        //                    color: isSelected ? cellPressedColor : "red"
        //                    // (styleData.pressed ? cellCurrentRowColor : )
        //                    property bool isSelected: treeView.currentIndex === styleData.index
        //    //                onIsSelectedChanged: {
        //    //                    console.log(styleData.hasActiveFocus, styleData.index)
        //    //                    if (isSelected) {
        //    //                        forceActiveFocus()
        //    //                    }
        //    //                }
        //                    TextEdit {
        //                        text: styleData.value
        //                        anchors.centerIn: parent
        //                        onEditingFinished: {
        //                            console.log(" onEditingFinished " , styleData)
        ////                                serviceCameraTree.treeModel.setData
        ////                                tModel.setData(styleData.index, text)
        //                        }
        //                    }
        //                }
        //            }

        //        }
    }

}
