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
#include "CameraWidget.h"

#include <iostream>

#ifdef _DEBUG
#include <sstream>
#endif

#pragma warning(push)
#pragma warning(disable:4996)
#include <opencv/cv.h>
#pragma warning(pop)

#ifdef _DEBUG
#pragma comment(lib, "opencv_core220d.lib")
#pragma comment(lib, "opencv_highgui220d.lib")
#else
#pragma comment(lib, "opencv_core220.lib")
#pragma comment(lib, "opencv_highgui220.lib")
#endif

CameraWidget::CameraWidget(QWidget *parent)
  : QWidget(parent),
  content(new QLabel),
  frame(QApplication::translate("defaultImage", "loading.jpg"))
{
#ifdef _DEBUG
  if (this->frame.isNull())
  {
    std::cout << "Couldn't load the image!" << std::endl;
  }
#endif

  if (this->frame.isNull())
  {
    this->content->setText(QApplication::translate("loadingText", "Loading, please wait."));
    this->content->setAlignment(Qt::AlignCenter);
  }
  else
  {
    this->content->setPixmap(QPixmap::fromImage(this->frame));
  }

  QLayout *temp = new QVBoxLayout;
  temp->addWidget(this->content);
  this->setLayout(temp);

  this->camera = cvCreateCameraCapture(0);

  if (!this->camera)
  {
    content->setText(QApplication::translate("noCameraText", "No camera detected."));
  }

  this->startTimer(66);
}

CameraWidget::~CameraWidget()
{
  cvReleaseCapture(&this->camera);
}

QPixmap CameraWidget::Capture()
{
  return QPixmap::fromImage(this->frame);
}

void CameraWidget::timerEvent(QTimerEvent*)
{
  IplImage *image = cvQueryFrame(this->camera);

  if (image->depth == IPL_DEPTH_8U &&
      image->nChannels == 3)
  {
    if (image->width != this->frame.width() ||
        image->height != this->frame.height())
    {
      this->frame = QImage(image->width, image->height, QImage::Format_RGB32);
    }

    for (int y = 0, lineStart = 0; y < image->height; ++y, lineStart += image->widthStep)
    {
      unsigned char r, g, b;

      for (int x = 0, index = lineStart; x < image->width; ++x, index += 3)
      {
        r = image->imageData[index + 2];
        g = image->imageData[index + 1];
        b = image->imageData[index + 0];

        this->frame.setPixel(x, y, qRgb(r, g, b));
      }
    }

    this->content->setPixmap(QPixmap::fromImage(this->frame));
  }
  else
  {
    this->content->setText(QApplication::translate("unsupportedCamera", "The camera format is unsupported.\n(Should be 8 bit RGB or equivalent.)"));
  }
}
