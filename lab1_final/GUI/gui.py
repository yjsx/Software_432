import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QAction, QMessageBox, QCheckBox, QTextEdit
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot
from PyQt5.Qt import QLineEdit
import os
class App(QWidget):

    def __init__(self):
        super().__init__()
        self.title = 'WORD CHAIN'
        self.left = 100
        self.top = 100
        self.width = 800
        self.height = 600
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        # create textbox
        self.textbox = QTextEdit(self)
        self.textbox.move(20, 20)
        self.textbox.resize(600, 200)

        self.textbox_out = QTextEdit(self)
        self.textbox_out.move(20, 380)
        self.textbox_out.resize(600, 200)

        self.textbox_path = QTextEdit(self)
        self.textbox_path.move(630, 500)
        self.textbox_path.resize(150, 28)
        self.textbox_path.setPlainText("Input the path")

        # Create a button in the window
        self.button = QPushButton('check', self)
        self.button.move(650, 100)

        self.button_out = QPushButton('export', self)
        self.button_out.move(650, 460)
        # connect button to function on_click
        self.button.clicked.connect(self.on_click)
        self.button_out.clicked.connect(self.export)

        self.checkBox_w = QCheckBox('-w', self)
        self.checkBox_c = QCheckBox('-c', self)
        self.checkBox_h = QCheckBox('-h', self)
        self.checkBox_t = QCheckBox('-t', self)
        self.checkBox_n = QCheckBox('-n', self)
        self.checkBox_w.move(60, 290)
        self.checkBox_c.move(180, 290)
        self.checkBox_h.move(300, 290)
        self.checkBox_t.move(420, 290)
        self.checkBox_n.move(540, 290)

        self.checkBox_path = QCheckBox('path?', self)
        self.checkBox_path.move(666,140)

        self.textbox_h = QTextEdit(self)
        self.textbox_h.move(300, 320)
        self.textbox_h.resize(40, 27)

        self.textbox_t = QTextEdit(self)
        self.textbox_t.move(420, 320)
        self.textbox_t.resize(40, 27)

        self.textbox_n = QTextEdit(self)
        self.textbox_n.move(540, 320)
        self.textbox_n.resize(40, 27)

        self.show()

    @pyqtSlot()
    def on_click(self):
        textboxValue = self.textbox.toPlainText()
        command = "./test.exe"
        flag = 0
        if(self.checkBox_path.isChecked()):#path

            if(self.checkBox_h.isChecked()):
                command = command + " -h " + self.textbox_h.toPlainText()
            if (self.checkBox_t.isChecked()):
                command = command + " -t " + self.textbox_t.toPlainText()
            if (self.checkBox_n.isChecked()):
                command = command + " -n " + self.textbox_n.toPlainText()
            if (self.checkBox_w.isChecked()):
                command = command + " -w"
            if (self.checkBox_c.isChecked()):
                command = command + " -c"
            if(flag == 0):
                command = command + " " + textboxValue
                print(command)
                out = os.popen(command)
                self.textbox_out.setPlainText(out.read())

        else:#text
            f = open("input.txt","w")
            f.write(textboxValue)
            f.close()
            if (self.checkBox_h.isChecked()):
                command = command + " -h " + self.textbox_h.toPlainText()
            if (self.checkBox_t.isChecked()):
                command = command + " -t " + self.textbox_t.toPlainText()
            if (self.checkBox_n.isChecked()):
                command = command + " -n " + self.textbox_n.toPlainText()
            if (self.checkBox_w.isChecked()):
                command = command + " -w"
            if (self.checkBox_c.isChecked()):
                command = command + " -c"
            print(command)
            if (flag == 0):
                os.system(command + " input.txt")
                f = open("solution.txt","r")
                text = f.read()
                print(text)
                self.textbox_out.setPlainText(text)
    def export(self):
        if(self.textbox_path.toPlainText() == "Input the path"):
            self.textbox_out.setPlainText("Please input yore path!")
        else:
            f = open(self.textbox_path.toPlainText(),"w")
            f.write(self.textbox_out.toPlainText())
            f.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    app.exit(app.exec_())