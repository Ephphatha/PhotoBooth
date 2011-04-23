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
#ifndef __PhotoPrinter
#define __PhotoPrinter

#include <vector>

#include <QtGui/QtGui>

class CameraWidget;

class PhotoPrinter : public QObject
{
  Q_OBJECT
public:
  PhotoPrinter(QObject *parent = 0);
  ~PhotoPrinter();

  void setCamera(CameraWidget &camera);

public slots:
  void capture();

  void setPrefs();
  
  void drawPage(QPrinter *printer);

private:
  int timer;
  std::vector<QPixmap> frames;
  CameraWidget *camera;

  QDialog settingsDialog;
  QLineEdit *copiesInput;
  QCheckBox *previewCheck;

  QPushButton *callingButton;

  struct Settings
  {
    bool printPreview;
    unsigned int copies;

    Settings();
  } settings;

  void timerEvent(QTimerEvent*);

  void Print();
};
#endif
