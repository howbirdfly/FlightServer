#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void usernameSubmitted(const QString &username);
private slots:
    void on_log_in_clicked();
    void on_sign_in_clicked();
    void onLoginResponse(int msgType, bool success, const QString &message, const QJsonObject &data);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
