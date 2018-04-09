#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalSocket>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void connectToServer(QString localtag);
    bool send(const QString &msg);

public:

private:
    Ui::MainWindow *ui;
    QLocalSocket *          m_pSocket;
    QTimer *                m_pTimer;
    QString                 m_LocalTag;

signals:

public slots:
    void        onConnected();
    void        onDisconnected();
    void        onTimeout();
    void        onReadMessage();
    void        onError(QLocalSocket::LocalSocketError errors);


private slots:
    void on_btn_send_clicked();
};

#endif // MAINWINDOW_H
