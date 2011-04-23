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
#include "PhotoPrinter.h"

#include <iostream>

#include "CameraWidget.h"

PhotoPrinter::Settings::Settings()
  : printPreview(false),
  copies(2)
{
}

PhotoPrinter::PhotoPrinter(QObject *parent)
  : QObject(parent),
  timer(0),
  camera(0),
  callingButton(0),
  copiesInput(new QLineEdit),
  previewCheck(new QCheckBox)
{
  QFormLayout *layout = new QFormLayout;
  QIntValidator *positiveInt = new QIntValidator;
  positiveInt->setBottom(0);
  this->copiesInput->setValidator(positiveInt);
  layout->addRow(tr("Copies:"), this->copiesInput);
  layout->addRow(tr("Preview output:"), this->previewCheck);

  QHBoxLayout *subLayout = new QHBoxLayout;
  QPushButton *save = new QPushButton(tr("Save Changes"));
  save->setDefault(true);
  subLayout->addWidget(save);

  QObject::connect(save, SIGNAL(clicked()), &this->settingsDialog, SLOT(accept()));

  QPushButton *cancel = new QPushButton(tr("Cancel"));
  subLayout->addWidget(cancel);

  QObject::connect(cancel, SIGNAL(clicked()), &this->settingsDialog, SLOT(reject()));

  layout->addRow(subLayout);
  this->settingsDialog.setLayout(layout);
}

PhotoPrinter::~PhotoPrinter()
{
}

void PhotoPrinter::setCamera(CameraWidget &camera)
{
  this->camera = &camera;
}

void PhotoPrinter::capture()
{
  if (this->camera && !this->timer)
  {
    this->timer = this->startTimer(1000);
    if (QPushButton *sender = dynamic_cast<QPushButton*>(QObject::sender()))
    {
      this->callingButton = sender;
      this->callingButton->setText(tr("Taking photos, smile :)"));
      this->callingButton->setDisabled(true);
    }
  }
}

void PhotoPrinter::setPrefs()
{
  this->copiesInput->setText(QString::number(this->settings.copies));
  this->previewCheck->setChecked(this->settings.printPreview);

  if (this->settingsDialog.exec() == QDialog::Accepted)
  {
    this->settings.copies = this->copiesInput->text().toInt();
    this->settings.printPreview = this->previewCheck->isChecked();
  }
}

void PhotoPrinter::timerEvent(QTimerEvent*)
{
  this->frames.push_back(this->camera->Capture());
  if (this->frames.size() >= 4)
  {
    this->killTimer(this->timer);
    this->timer = 0;
    if (this->callingButton)
    {
      this->callingButton->setEnabled(true);
      this->callingButton->setText(tr("Take Photo"));
      this->callingButton = 0;
    }
    this->Print();
  }
}

void PhotoPrinter::Print()
{
  QPrinter *printer = new QPrinter(QPrinter::HighResolution);
  
  if (this->settings.printPreview)
  {
    QPrintPreviewDialog printPreview(printer);

    QObject::connect(&printPreview,
                     SIGNAL(paintRequested(QPrinter *)),
                     this,
                     SLOT(drawPage(QPrinter *)));

    printPreview.exec();
  }
  else
  {
    this->drawPage(printer);
  }

  this->frames.clear();
}

void PhotoPrinter::drawPage(QPrinter *printer)
{
  QPainter painter;
  painter.begin(printer);

#ifdef _DEBUG
  std::cout << "Drawing " << this->frames.size() << " pictures." << std::endl;
#endif
  
  QRect pageArea = printer->pageRect();

  int halfPageWidth = pageArea.width() / 2;

  int buffer = static_cast<int>(static_cast<float>(pageArea.height()) / static_cast<float>(this->frames.size()) * 0.1f);

  int imageHeight = static_cast<int>(static_cast<float>(pageArea.height()) / static_cast<float>(this->frames.size()) * 0.8f);

  for (unsigned int page = 1; page <= this->settings.copies; ++page)
  {
    for (unsigned int i = 0; i < this->frames.size(); ++i)
    {
      int targetWidth = imageHeight * this->frames[i].width() / this->frames[i].height();
      QRect paintArea = QRect(halfPageWidth - (targetWidth / 2), buffer + i * (imageHeight + 2 * buffer), targetWidth, imageHeight);
      painter.drawPixmap(paintArea, this->frames[i]);
      painter.drawRect(paintArea);
    }
    if (page != this->settings.copies)
    {
      printer->newPage();
    }
  }

  painter.end();
}
