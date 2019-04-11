/*
 * MIT License
 *
 * Copyright (c) 2019 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of qtprotobuf project https://git.semlanik.org/semlanik/qtprotobuf
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

import QtQuick 2.9
import QtQuick.Controls.Material 2.9
import QtQuick.Layouts 1.1
import qtprotobuf.examples.addressbook 1.0

ListView {
    id: contactList
    anchors.fill: parent
    delegate: Rectangle {
        id: contactDelegate
        property Contact contact: model.modelData
        color: "#81D4FA"
        width: contactList.width
        height: 80
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10
            Row {
                Layout.alignment: Qt.AlignVCenter
                Text {
                    id: firstName
                    color: "#FFFFFF"
                    text: contactDelegate.contact.firstName
                    font.pointSize: 12
                }
                Text {
                    id: middleName
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFFFFF"
                    text: contactDelegate.contact.middleName
                    font.pointSize: 12
                }
                Text {
                    id: lastName
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFFFFF"
                    text: contactDelegate.contact.lastName
                    font.pointSize: 12
                }
            }
            Row {
                Layout.alignment: Qt.AlignVCenter
                Text {
                    id: job
                    color: "#EEEEEE"
                    text: contactDelegate.contact.job.title
                    font.pointSize: 12
                    Component.onCompleted: {
                        console.log('contactDelegate.contact.job: ' + contactDelegate.contact.job.title);
                    }
                }
            }
        }
        Rectangle {
            color:"#EEEEEE"
            anchors.left: parent.left
            anchors.right: parent.right
            height: 2
        }

        Rectangle {
            color:"#EEEEEE"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.bottom
            height: 2
            visible: (contactList.count - 1) === model.index
        }
    }
}
