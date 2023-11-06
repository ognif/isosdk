/********************************************************************************************************************************************
 *  IsoSDK - a powerful CD/DVD/BD recording SDK for Linux, macOS, Windows and Android.
 *  Copyright (c) 2002-2022 Ingo Foerster (pixbytesl@gmail.com).
 *  http://www.isosdk.com
 ********************************************************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public: signals:
    void jobDone(QString str);
    void progressChanged(int percent, int cache);


private slots:
    void on_actionNew_triggered();

    void on_actionReset_triggered();

    void UpdateMyUI(int percent, int cache);
    void myJobDoneEvent(QString msg);

    void on_actionBurn_triggered();

    void on_chkImportLastSession_stateChanged(int arg1);

    void on_cbBurnDrive_currentIndexChanged(int index);

    void on_cbProject_currentIndexChanged(int index);

    void on_actionAdd_Folder_2_triggered();

private:
    Ui::MainWindow *ui;
    void fillDriveList();
    void changeProjectType(int index, bool importSession);

protected:
    static void OnJobDoneEvent(MainWindow *pUserData);
    static void OnProcessEvent(float fPercent, float fDeviceBuffer, float fCache, double dBytesWritten, double dImageSize, MainWindow *pUserData);
};

#endif // MAINWINDOW_H
