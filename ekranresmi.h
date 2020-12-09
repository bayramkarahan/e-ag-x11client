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
