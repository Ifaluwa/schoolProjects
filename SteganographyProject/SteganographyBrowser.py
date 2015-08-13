__author__ = 'ee364g07'

# $Author: ee364g07 $
# $Date: 2015-04-20 15:54:28 -0400 (Mon, 20 Apr 2015) $
# $Revision: 79275 $
# $HeadURL: svn+ssh://ece364sv@ecegrid-thin1/home/ecegrid/a/ece364sv/svn/S15/students/ee364g07/Lab11/SteganographyBrowser.py $
# $Id: SteganographyBrowser.py 79275 2015-04-20 19:54:28Z ee364g07 $


import sys
import os
import glob
import re

from PySide.QtGui import *
from PySide.QtCore import *
from NewSteganography import *
from SteganographyGUI import *


class SteganographyBrowser(QMainWindow, Ui_MainWindow):
    """
    this function adds items to the tree widget based on if the item has a message, if it does it adds the message
    as a child. It also sets different colors to the different types of items entered to the list

    """
    def additem(self, path, item):
        self.fileTreeWidget.addTopLevelItem(item)
        horizontalread = NewSteganography(path, 'horizontal')
        verticalread = NewSteganography(path, 'vertical')
        ah,bh = horizontalread.checkIfMessageExists()
        av,bv = verticalread.checkIfMessageExists()
        if ah == True:
            item.setForeground(0,QtGui.QBrush(QtGui.QColor("#FF0000")))
            item.addChild(QTreeWidgetItem([bh]))
            self.childdict[item] = [bh, 'horizontal']
        elif av == True:
            item.setForeground(0,QtGui.QBrush(QtGui.QColor("#FF0000")))
            item.addChild(QTreeWidgetItem([bv]))
            self.childdict[item] = [bv, 'vertical']
        else:
            item.setForeground(0,QtGui.QBrush(QtGui.QColor("#0000FF")))

    def __init__(self, parent=None):
        """
        the initialization function: this pops up a message box asking for the folder you want to get the files from
        it also creates a dictionary of filepaths and message types for future use in the rest of the application
        it goes through all the files in the folder and sends them to the additem function to be added to the tree widget
        :param parent:
        :return:
        """
        #initial set-up
        super(SteganographyBrowser, self).__init__(parent)
        self.setupUi(self)

        #message box pop-up
        msgbox = QMessageBox()
        msgbox.setText("Select a folder")
        msgbox.setStandardButtons(QMessageBox.Open | QMessageBox.Cancel)
        option = msgbox.exec_()
        if option == QMessageBox.Open:
            self.fpdict = {} #filepath dictionary whose keys are the QTreeWidget Items
            self.childdict = {} #child dictionary to figure out the type of message in a medium
            folderPath = QFileDialog.getExistingDirectory(None, 'Select a folder:')
            if folderPath:
                files = glob.glob('{}/*.png'.format(folderPath))
                for file in files:
                     filepath = file
                     file = file.split('/')
                     item = QTreeWidgetItem(file[-1:])
                     foldername = file[-2:-1]
                     self.fpdict[item] = filepath
                     self.additem(filepath, item)
            else:
                exit()

            #disabling of buttons and views
            self.fileTreeWidget.headerItem().setText(0, foldername[0])
            self.btnExtract.setEnabled(False)
            self.btnWipeMedium.setEnabled(False)
            self.viewMedium.setHidden(True)
            self.viewMessage.setHidden(True)

            """Reactions when buttons are clicked"""

            self.fileTreeWidget.itemClicked.connect(self.clickedtree)
            self.btnExtract.clicked.connect(self.extract)
            self.btnWipeMedium.clicked.connect(self.wipe)

        elif option == QMessageBox.Cancel:
            exit()


    def displayimageinmedium(self, path):
        """
        given the path of the image, it displays the image in the medium
        :param path:
        :return:
        """
        scene = QGraphicsScene()
        pix = scene.addPixmap(QPixmap(path))
        self.viewMedium.setScene(scene)
        self.viewMedium.fitInView(pix, Qt.KeepAspectRatio)

    def displayimageinmessage(self, path):
        """
        given the path of the image, it displays the image in the message space given

        :param path:
        :return:
        """
        scene = QGraphicsScene()
        pix = scene.addPixmap(QPixmap(path))
        self.viewMessage.setScene(scene)
        self.viewMessage.fitInView(pix, Qt.KeepAspectRatio)



    def clickedtree(self):
        """
        this is the reaction button for  when an item in the tree is clicked . It sets the item in use to the current item
        that was clicked and gets the file path and child using the item as a dictionary key. It also selects from Line Edit
        and graphics view based on what type of message is in the medium
        :return:
        """
        parentcheck = str(self.fileTreeWidget.currentItem().parent())
        if parentcheck == 'None':
            current = self.fileTreeWidget.currentItem()
            num_of_children = current.childCount()
        else:
            current = self.fileTreeWidget.currentItem().parent()
            num_of_children = 1


        if num_of_children == 0:
            self.btnExtract.setEnabled(False)
            self.btnWipeMedium.setEnabled(False)
            self.viewMedium.setHidden(False)
            self.viewMessage.setHidden(True)
            self.txtMessage.setHidden(True)
            self.lblTextMessage.setDisabled(True)
            self.lblImageMessage.setDisabled(True)
            self.displayimageinmedium(self.fpdict[current])
        elif num_of_children == 1:
            self.btnExtract.setEnabled(True)
            self.btnWipeMedium.setEnabled(True)
            self.viewMedium.setHidden(False)
            self.viewMessage.setHidden(False)
            self.txtMessage.setHidden(False)
            self.lblTextMessage.setDisabled(True)
            self.lblImageMessage.setDisabled(True)
            self.displayimageinmedium(self.fpdict[current])

            #differentiating between Line Edit and Graphics VIew
            if self.childdict[current][0] == 'Text':
                self.stackMessage.setCurrentIndex(1)
                self.txtMessage.setPlainText("")
            else:
                self.stackMessage.setCurrentIndex(0)
                scene = QGraphicsScene()
                self.viewMessage.setScene(scene)

    def extract(self):
        """
        extracts the message in the medium and places it in the graphics view or line edit based on what type the message is
        :return:
        """
        parentcheck = str(self.fileTreeWidget.currentItem().parent())
        if parentcheck == 'None':
            current = self.fileTreeWidget.currentItem()
        else:
            current = self.fileTreeWidget.currentItem().parent()
        path = self.fpdict[current]
        direction = self.childdict[current][1]
        medium = NewSteganography(path, direction)
        ex_message = medium.extractMessageFromMedium()
        ex_messagetype = ex_message.messageType

        """Options for message extraction put back"""

        if ex_messagetype == 'Text':
            dcode = ex_message.findmessage()                      #finds the message in the xml file
            msg = base64.b64decode(bytes(dcode, "UTF-8"))   #decodes the base64 message
            msg = str(msg, "UTF-8")
            self.txtMessage.setPlainText(msg)
            self.btnExtract.setEnabled(False)
        elif ex_messagetype == 'ColorImage':
            ex_message.saveToTarget('help.png')
            self.displayimageinmessage('help.png')
            self.btnExtract.setEnabled(False)
        elif ex_messagetype == 'GrayImage':
            ex_message.saveToTarget('help.png')
            self.displayimageinmessage('help.png')
            self.btnExtract.setEnabled(False)

    def wipe(self):
        """
        cleans the message from the medium and refreshes the item based on the new properties of the medium
        :return:
        """
        msgbox = QMessageBox()
        msgbox.setText("Are you sure you want to wipe the medium?")
        msgbox.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
        option = msgbox.exec_()
        if option == QMessageBox.No:
            pass
        elif option == QMessageBox.Yes:
            self.viewMessage.setHidden(True)
            self.txtMessage.setHidden(True)
            current = self.fileTreeWidget.currentItem()
            path = self.fpdict[current]
            direction = self.childdict[current][1]
            medium = NewSteganography(path, direction)
            medium.wipeMedium()
            scene = QGraphicsScene()
            self.viewMessage.setScene(scene)
            current.takeChild(0)
            self.fileTreeWidget.removeItemWidget(current, 0)
            self.additem(path, current)


if __name__ == "__main__":
    currentApp = QApplication(sys.argv)
    currentForm = SteganographyBrowser()
    currentForm.show()
    currentApp.exec_()
