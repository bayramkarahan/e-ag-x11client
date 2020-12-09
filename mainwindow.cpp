#include "mainwindow.h"
#include<QDebug>
#include<filecrud.h>
#include<QDesktopWidget>
#include<QApplication>
#include<ekranresmi.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{ 

    QDesktopWidget widget;
    QRect desktopScreenSize = widget.availableGeometry(widget.primaryScreen());



     /*******************************************************/
     localDir="/usr/share/E-Ag/";
     FileCrud *fcc=new FileCrud();
     fcc->dosya=localDir+"tcpMessage";
     if(fcc->fileExists())
     {
        QStringList str=fileToList("tcpMessage");
        qDebug()<<str;
        if(str[0].count()==0) exit(0);

        QStringList lst=str[0].split("|");


   if(lst[1]=="ekranmesaj")
   {
    qDebug()<<"GClient:"<<lst[1]<<lst[2];
    this->resize(desktopScreenSize.width(),200);
    this->move(100,205);

    this->setStyleSheet("background-color: #a3acac");

    baslik=new QLabel(this);
    baslik->resize(desktopScreenSize.width(),100);
    baslik->move(0,0);

    haber=new QLabel(this);
    haber->resize(desktopScreenSize.width(),100);
    haber->move(0,100);

    baslik->setText("<center><font size=8>Yönetici Duyurusu</font></center>");
    //this->setWindowFlags(Qt::Tool);

    haber->setText("<center><font size=8>"+lst[2]+"</font></center>");
     this->setWindowFlags(Qt::Dialog);
     this->show();
   }

   if(lst[1]=="ekrankilit")
   {
    qDebug()<<"GClient:"<<lst[1];//lst[2];
    this->resize(desktopScreenSize.width(),desktopScreenSize.width());
    this->move(0,0);

    this->setStyleSheet("background-color: #a3acac");

    baslik=new QLabel(this);
    baslik->resize(desktopScreenSize.width(),100);
    baslik->move(0,0);

    haber=new QLabel(this);
    haber->resize(desktopScreenSize.width(),100);
    haber->move(0,100);

    baslik->setText("<center><font size=8>Yönetici Duyurusu</font></center>");
    //this->setWindowFlags(Qt::Tool);

    haber->setText("<center><font size=8>Ekran Kilitlendi...</font></center>");
    // this->setWindowFlags(Qt::Sheet);
   // this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
    //                     | Qt::X11BypassWindowManagerHint);

    timer = new QTimer();
     QObject::connect(timer, &QTimer::timeout, [&](){
        // if(!fcc->fileExists()) exit(0);


       QStringList str=fileToList("tcpMessage");

       qDebug()<<"timer kontrol:"<<str;
       QStringList lst=str[0].split("|");



       if(lst[1]=="ekrankilitac")
       {
           timer->stop();
          system("rm /usr/share/E-Ag/tcpMessage");
           exit(0);
       }

    });
     timer->start(2000);
     this->show();
   }

   if(lst[1]=="ekranpanoac")
   {
    qDebug()<<"GClient:"<<lst[1];//lst[2];
    this->resize(desktopScreenSize.width(),desktopScreenSize.width());
    this->move(0,0);

   // this->setStyleSheet("background-color: #a3acac");

   // baslik=new QLabel(this);
   // baslik->resize(desktopScreenSize.width(),100);
   // baslik->move(0,0);

   // haber=new QLabel(this);
   // haber->resize(desktopScreenSize.width(),100);
   // haber->move(0,100);

    //baslik->setText("<center><font size=8>Dijital Panosu</font></center>");
    //this->setWindowFlags(Qt::Tool);

    //haber->setText("<center><font size=8>Ekran Panosu...</font></center>");
    // this->setWindowFlags(Qt::Sheet);
     setAttribute(Qt::WA_TranslucentBackground, true);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
                         | Qt::X11BypassWindowManagerHint);

    timer = new QTimer();
     QObject::connect(timer, &QTimer::timeout, [&](){
        // if(!fcc->fileExists()) exit(0);


       QStringList str=fileToList("tcpMessage");

       qDebug()<<"timer kontrol:"<<str;
       QStringList lst=str[0].split("|");



       if(lst[1]=="ekranpanokapat")
       {
           timer->stop();
          system("rm /usr/share/E-Ag/tcpMessage");
         // system("killall firefox-esr&");
          exit(0);
       }

    });
     timer->start(2000);
     this->show();
    /// std::string kmt="nohup firefox "+lst[2].toStdString()+"&";
    /// system(kmt.c_str());

   }


   /*if(lst[1]=="ekrankilitac")
   {
       qDebug()<<"GClient:"<<lst[1]<<lst[2];

       system("rm /usr/share/E-Ag/tcpMessage");

       exit(0);
   }*/

   if(lst[1]=="ekranimage")
   {
       qDebug()<<"GClient:"<<lst[1]<<lst[2];

       system("rm /usr/share/E-Ag/tcpMessage");
       kaydetTimerSlot(lst[3],lst[4],lst[5]);

       exit(0);
   }

}else exit(0);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    /*if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }*/
    qDebug()<<"KAPATIYORSUN";
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+"tcpMessage";
    fcc->fileRemove();
    exit(0);
}

QStringList MainWindow::listRemove(QStringList list,QString data)
 {
    // qDebug()<<"deneme-ddd"<<data;
    // QStringList list;
     //  qDebug()<<list;
     //list << "bayram|sun" << "cloud" << "sun|elif" << "firi|rain";
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++)if(list[i].contains(re)) list.removeAt(i);
    // qDebug()<<list;
     return list;
 }
QString MainWindow::listGetLine(QStringList list,QString data)
 {
     //QStringList list;
     //list << "bayram|sun" << "cloud" << "sun|elif" << "firi|rain";
     QRegularExpression re(data);
     for(int i=0;i<list.count();i++) if(list[i].contains(re)) return list[i];
     //qDebug()<<list;
     return "";
 }
QStringList MainWindow::fileToList(QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    QStringList list;
    for(int i=1;i<=fcc->fileCount();i++)
    {
         QString line=fcc->fileGetLine(i);
         if(line!="")
         {
             line.chop(1);
             QStringList lst=line.split("|");
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);

             list <<ln;
            // qDebug()<<ln;
             // list <<lst[0]+"|"+lst[1]+"|"+lst[2]+"|"+lst[3]+"|"+lst[4]+"|"+lst[5];

         }
    }
       return list;
 }
void MainWindow::listToFile(QStringList list, QString filename)
 {
    FileCrud *fcc=new FileCrud();
    fcc->dosya=localDir+filename;
    fcc->fileRemove();
    for(int i=0;i<list.count();i++)
    {
         QString line=list[i];
         if(line!="")
         {
             //line.chop(1);
             QStringList lst=line.split("|");
             //qDebug()<<line;
             QString ln="";
             if(lst.count()>0)ln.append(lst[0]);
             if(lst.count()>1)ln.append("|").append(lst[1]);
             if(lst.count()>2)ln.append("|").append(lst[2]);
             if(lst.count()>3)ln.append("|").append(lst[3]);
             if(lst.count()>4)ln.append("|").append(lst[4]);
             if(lst.count()>5)ln.append("|").append(lst[5]);

             //qDebug()<<ln;
             fcc->fileWrite(ln);

         }

    }
 }
