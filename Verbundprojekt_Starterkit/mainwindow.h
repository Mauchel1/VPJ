#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer;
    int counter = 0;

signals:
    void writeValues(QVector<int> values);
    void updateDBValues(QVector<QString> values);
    void getDBValues();

public slots:
    void prepareValues();
    void updateTableValues(QList<QString> values);
    void updateRobotData(QVector<int> values);

private slots:

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_checkBox_clicked(bool checked);

    void on_read_clicked();

    void on_writeR_clicked();

    void on_writeM_clicked();

    void on_writeP_clicked();

    void on_writeC_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
