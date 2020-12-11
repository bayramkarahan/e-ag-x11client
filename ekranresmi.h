/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/
#ifndef EKRANRESMI_H
#define EKRANRESMI_H
#include<QDesktopWidget>
#include <QApplication>
#include<QtWidgets>
void MainWindow::kaydetTimerSlot(QString username,QString password,QString bagnum)
{
  //  hostAddressMacButtonSlot();
    Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio;
    Qt::TransformationMode transformMode = Qt::FastTransformation;
    QPixmap desk = qApp->screens().at(0)->grabWindow(QDesktopWidget().winId());
    QPixmap px=desk.scaled(400,300,aspectRatioMode,transformMode);
    QString ad=QDir::homePath()+"\/"+bagnum+".png";
    qDebug()<<"dosya:"<<ad;
    px.save(ad);

    QString ip;
    /**********************host ve port okunuyor*****************************/
     FileCrud *fcc=new FileCrud();
     fcc->dosya=localDir+"hostport";
     if(fcc->fileExists())
     {
         QString hostport=fcc->fileGetLine(1);

         if (hostport!="")
         {
             ip=hostport.split("|")[0];
            // port=hostport.split("|")[1];
            // socket->connectToHost(ip,port.toInt());
         }
     }
     else qDebug()<<"hostport Dosyası Bulunamadı..";
/**************************************************/
     // qDebug()<<ip;
    /*****************dosya server kopyalanıyor*********************/
    QString komut="sshpass -p "+password+" scp -o StrictHostKeyChecking=no "+ad+" "+
            username+"@"+ip+":\/home\/"+username+"\/";

    qDebug()<<komut;

    QStringList arguments;
    arguments << "-c" << komut;
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished


}


#endif // EKRANRESMI_H
