#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QLabel>
#include<QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public slots:

    QStringList listRemove(QStringList list,QString data);
    QStringList fileToList(QString filename);
    void listToFile(QStringList list, QString filename);
    QString listGetLine(QStringList list,QString data);

    void kaydetTimerSlot(QString userName,QString passwd,QString bagnum);

private:
 QString localDir;
 QWidget *kutu=nullptr;
 QWidget *pano;
 QGridLayout *layout;
 QLabel *haber;
 QLabel *baslik;
QTimer *timer;
};

#endif // MAINWINDOW_H
