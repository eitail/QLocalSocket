#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_LocalTag = "87654321";
    m_pTimer = new QTimer(this);
    connect(m_pTimer , SIGNAL(timeout() ) ,this,SLOT( onTimeout()));
    m_pSocket = new  QLocalSocket(this);
    connect(m_pSocket,SIGNAL(connected()) ,this, SLOT( onConnected() ));
    connect(m_pSocket,SIGNAL(error(QLocalSocket::LocalSocketError)) ,this ,SLOT( onError( QLocalSocket::LocalSocketError )));
    connect(m_pSocket,SIGNAL(disconnected()) ,this, SLOT( onDisconnected()));
    connect(m_pSocket,SIGNAL(readyRead()) ,this , SLOT( onReadMessage()));
    m_pTimer->start(500);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//连接到主机
void MainWindow::connectToServer(QString localtag)
{
    //m_LocalTag = ips;
    m_pSocket->abort();
    m_pSocket->connectToServer(localtag);
    qDebug() << "has link server! ok...";
}

 //发送到控制器
bool MainWindow::send(const QString &msg)
{
    m_pSocket->write(msg.toUtf8());
    return true;
}

//连接服务器
void MainWindow::onConnected()
{
    m_pTimer->stop();
    qDebug() << "onConnected";
}
//断开服务器
void MainWindow::onDisconnected()
{
    m_pTimer->start(500);
    qDebug() << "onDisconnected";
}
//定时器
void MainWindow::onTimeout()
{
    qDebug() << "onTimeout";
    m_pTimer->stop();
    m_pSocket->abort();
    m_pSocket->connectToServer(m_LocalTag);
}
//接受服务器发现送来的信息
void MainWindow::onReadMessage()
{
    QString msg = m_pSocket->readAll();
    qDebug() << msg;
    ui->label_return_mess->setText("这是服务器返回的信息：" + msg);
}
//连接服务报错
void MainWindow::onError(QLocalSocket::LocalSocketError errors)
{
    m_pTimer->start(500);
    qDebug() << " onError: " << QString("%1").arg(errors);
}

//------槽函数------
void MainWindow::on_btn_send_clicked()
{
    //QString s = ui->ledit_mess->text();
    send("112233");
}
