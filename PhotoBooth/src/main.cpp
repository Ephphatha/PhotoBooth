/*
 *  The MIT License
 *
 *  Copyright 2011 Andrew James <ephphatha@thelettereph.com>.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
#include <QtGui/QtGui>

#ifdef _DEBUG
#pragma comment(lib, "QtCored4.lib")
#pragma comment(lib, "QtGuid4.lib")
#else
#pragma comment(lib, "QtCore4.lib")
#pragma comment(lib, "QtGui4.lib")
#endif

#include "CameraWidget.h"
#include "PhotoPrinter.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle(QApplication::translate("title", "PhotoBooth"));
    
    QVBoxLayout *layout = new QVBoxLayout;
    CameraWidget *camera = new CameraWidget;
    layout->addWidget(camera, 0, Qt::AlignHCenter);
    
    PhotoPrinter printer;
    printer.setCamera(*camera);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *captureButton = new QPushButton(QApplication::translate("capture",
                                                                         "Take Photo"));
    buttonLayout->addWidget(captureButton, 1);
    
    QObject::connect(captureButton,
                     SIGNAL(clicked()),
                     &printer,
                     SLOT(capture()));

    QPushButton *settingsButton = new QPushButton(QIcon("cog.png"),
                                                  QApplication::translate("settingsText", "Settings"));
    buttonLayout->addWidget(settingsButton);

    QObject::connect(settingsButton,
                     SIGNAL(clicked()),
                     &printer,
                     SLOT(setPrefs()));

    layout->addLayout(buttonLayout);
    window.setLayout(layout);
    
    window.resize(640, 500);
    window.show();

    return app.exec();
}