/********************************************************************************************************************************************
 *  IsoSDK - a powerful CD/DVD/BD recording SDK for Linux, macOS, Windows and Android.
 *  Copyright (c) 2002-2022 Ingo Foerster (pixbytesl@gmail.com).
 *  http://www.isosdk.com
 ********************************************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QtWidgets>

#include <QSettings>
#include <QString>

#include "IsoSDKBurningLib.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

   //Move Window to the desktop center
   move(pos() + (QGuiApplication::primaryScreen()->geometry().center() - geometry().center()));

    ui->setupUi(this);

#if defined LINUX
    QString mLicense = "3GTF75-2UM4AX-18LAHC-BX1FOR-N38Y32";
    int res = ::Initialize((const TCHAR*)mLicense.toUtf8(), BS_ASPI_INTERNAL, BS_TRUE);
#endif
#if defined MAC
    QString mLicense = "NPTD4B-WVZ3A7-KZPA9G-B91CYR-2U8TTN";
    int res = ::Initialize((const TCHAR*)mLicense.toUtf8(), BS_ASPI_INTERNAL, BS_TRUE);
#endif
#if defined WIN32
    QString mLicense = "67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7";
    int res = ::Initialize((const TCHAR*)mLicense.utf16(), BS_ASPI_INTERNAL, BS_TRUE);
#endif



    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Initialize"));
    }



    fillDriveList();

    setWindowTitle(tr("IsoSDKDataSample"));
    ui->totalProgress->setRange(0,100);

    QObject::connect(this, SIGNAL(progressChanged(int,int)), this, SLOT(UpdateMyUI(int,int)), static_cast<Qt::ConnectionType>(Qt::QueuedConnection | Qt::UniqueConnection));
    QObject::connect(this, SIGNAL(jobDone(QString)), this, SLOT(myJobDoneEvent(QString)), static_cast<Qt::ConnectionType>(Qt::QueuedConnection | Qt::UniqueConnection));

    SetProcessEventCallback((ProcessEvent) MainWindow::OnProcessEvent, this);
    SetJobDoneEventCallback((JobDoneEvent) MainWindow::OnJobDoneEvent, this);

    ui->actionEject_Disk_after_burn->setChecked(true);
    ui->actionUser_Buffer_Protection->setChecked(true);
    ui->actionEraseRW_before_burn->setChecked(true);

    ui->cbProject->addItem("ISO");
    ui->cbProject->addItem("ISOUDF");
    ui->cbProject->addItem("UDF");

    ui->cbProject->setCurrentIndex(1);

    res = CreateProject(BS_BURNER_ISOUDF,BS_CONTINUE_NO_SESSION );
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Create Projekt"));
    }
}

MainWindow::~MainWindow()
{

    delete ui;
}

QString convertToQT(const TCHAR * strValue)
{
#if defined (WIN32)
    return QString::fromWCharArray(strValue);
#else
    return QString::fromUtf8(strValue);
#endif
}

const TCHAR* convertToIsoSDKValue(const QString& strValue)
{

#if defined (WIN32)
    TCHAR *someVar=new TCHAR[strValue.size()+1];
    strValue.toWCharArray(someVar);
    //set last caharacter to null terminator
    someVar[strValue.size()]=L'\0';
    return reinterpret_cast<const TCHAR *>(someVar);
#else
    TCHAR *someVar=new TCHAR[strValue.size()+1];
    QByteArray pass = strValue.toUtf8();
    strcpy(someVar,pass.data());
    return reinterpret_cast<const TCHAR *>(someVar);
#endif

}

void MainWindow::on_actionAdd_Folder_2_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QStringList folderNames;
    if (dialog.exec()==QDialog::Rejected){
        return;
    }else{
        folderNames = dialog.selectedFiles();
    }

    ui->listWidget->addItem(folderNames.at(0));

#if defined (WIN32)
    QString rootPath = "\\";
#else
    QString rootPath = "/";
#endif

    SDirToAdd cDirToAdd;
    const TCHAR *pSavePath = convertToIsoSDKValue(folderNames.at(0));
    const TCHAR *pRootPath = convertToIsoSDKValue(rootPath);
    cDirToAdd.lpszSourceDirPath = pSavePath;
    cDirToAdd.lpszDestinationPath = pRootPath;
    if(ui->chkUsePath->isChecked()==false){
        cDirToAdd.nSavePath = BS_DONT_SAVE_PATH;
    }else{
        cDirToAdd.nSavePath = BS_WHOLE_PATH;
    }
    int32 res = ::AddDir(cDirToAdd);
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Add Folder"));
    }

    delete [] pSavePath;
    delete [] pRootPath;
}


void MainWindow::on_actionNew_triggered()
{

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (dialog.exec()==QDialog::Rejected){
        return;
    }else{
        fileNames = dialog.selectedFiles();
    }

    ui->listWidget->addItem(fileNames.at(0));

    QString strSavePath = QDir::toNativeSeparators(fileNames.at(0));

#if defined (WIN32)
    QString rootPath = "\\";
#else
    QString rootPath = "/";
#endif
    SFileToAdd file;
    file.lpszFileName = nullptr;

    //Attention, this differ on MAC And Win32
    const TCHAR *pSavePath = convertToIsoSDKValue(strSavePath);
    const TCHAR *pRootPath = convertToIsoSDKValue(rootPath);

    file.lpszSourceFilePath = pSavePath;
    file.lpszDestinationPath = pRootPath;


    file.bVideoFile = BS_FALSE;

    if(ui->chkUsePath->isChecked()==false){
        file.nSavePath = BS_DONT_SAVE_PATH;
    }else{
        file.nSavePath = BS_WHOLE_PATH;
    }


    int32 res = ::AddFile(file);
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in AddFile"));
    }

    delete [] pSavePath;
    delete [] pRootPath;

    //const TCHAR *pLogPath = convertToIsoSDKValue(QDir::toNativeSeparators("IsoSDKSampleData.log"));
    //SaveLogToFile(pLogPath);
    //delete [] pLogPath;

}

void MainWindow::on_actionReset_triggered()
{
    ui->listWidget->clear();
    ClearAll();
}

void MainWindow::fillDriveList()
{

    ui->cbBurnDrive->clear();
    ::RescanDevices();
    TCHAR chListDevices[26][50];
    int32 nUsed = 0;
    int32 res = ::GetDevices(chListDevices, &nUsed, false);
    if (BS_SDK_ERROR_NO == res) {
      for (int i = 0; i < nUsed; i++) {
          ui->cbBurnDrive->addItem(convertToQT(chListDevices[i]));
      }
    }

}

void MainWindow::UpdateMyUI(int percent, int)
{

    ui->totalProgress->setValue(percent);
}

void MainWindow::myJobDoneEvent(QString)
{
    this->setEnabled(true);
    QMessageBox::information(this, tr("Information"),
                             tr("Burn Done"));
}

void MainWindow::OnJobDoneEvent(MainWindow *pUserData)
{
    emit pUserData->jobDone(tr("Job completed."));
}

void MainWindow::OnProcessEvent(float fPercent, float, float fCache, double, double, MainWindow *pUserData)
{
    emit pUserData->progressChanged((int)fPercent, (int)fCache);
}

void MainWindow::on_actionBurn_triggered()
{

    //Check first if there was something added.
    if(ui->listWidget->count()==0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Please add a file first"));
        return;
    }




    SOptions opt;
        ::GetOptions(&opt);

    //Here we demonstrate how to copy a value to a TCHAR Array
    QString label="QT Test";

    const TCHAR *pLabel = convertToIsoSDKValue(label);
    _tcsncpy( opt.chVolumeLabel, pLabel, 128 );
    delete [] pLabel;



    opt.bEjectAfterBurn = ui->actionEject_Disk_after_burn->isChecked();
    opt.bFinalize = false;
    opt.bPerformOPC = true;
    opt.bJolietFileSystem = true;
    opt.bUnderrunProtection = ui->actionUser_Buffer_Protection->isChecked();
    opt.bAutoErase = ui->actionEraseRW_before_burn->isChecked();

    //Check the #
    if(ui->cbBurnDrive->currentText().at(0)=='#'){
        QString fileName = QFileDialog::getSaveFileName(
                        this,
                        tr("Save Disk Image"),
                        QDir::currentPath(),
                        tr("Disk Image (*.iso)") );

          if (fileName.isEmpty()){
              QMessageBox::information(this, tr("Information"),
                                       tr("No image file selected"));
              return;
          }

          //Here we demonstrate how to copy a value to a const TCHAR *
          const TCHAR *pImagePath = convertToIsoSDKValue(QDir::toNativeSeparators(fileName));
          SetImageFilePath(pImagePath);
          delete [] pImagePath;

    }

    //Save the options to the project
    int res = ::SetOptions(opt);
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Set Options"));
        return;
    }

    if(ui->chkISOLevel3->isChecked()){
        SISOInfoEx isoInfo;
        memset( &isoInfo, 0, sizeof( isoInfo ) );
        isoInfo.ISOLevel = BS_ISO_LEVEL_3;
        isoInfo.ISOAllowManyDirectories = BS_TRUE;
        res = ::SetISOInfoEx( isoInfo );
        if(res!=0){
            QMessageBox::information(this, tr("Information"),
                                     tr("Error in set ISOInfoEx"));
            return;
        }
    }

    // Prepare the collection and file system tables.
    res = Prepare();
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Prepare"));
        return;
    }

    //Burn Command
    res = ::Burn();
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Burn"));

        return;
    }
    this->setEnabled(false);
}

void MainWindow::on_chkImportLastSession_stateChanged(int arg1)
{
    changeProjectType(ui->cbProject->currentIndex(), arg1);
}


void MainWindow::on_cbBurnDrive_currentIndexChanged(int index)
{
    QString strDriveName = ui->cbBurnDrive->itemText(index);
    const TCHAR *pDriveName = convertToIsoSDKValue(strDriveName);
    int32 res = ::SetBurnDevice(pDriveName);
    delete [] pDriveName;
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Set Burn Device"));
    }
}


void MainWindow::on_cbProject_currentIndexChanged(int index)
{
    changeProjectType(index, ui->chkImportLastSession->isChecked());
}

void MainWindow::changeProjectType(int index, bool importSession)
{
    ui->listWidget->clear();
    int32 nProjectType = BS_BURNER_ISOUDF;
    int32 nSession = BS_CONTINUE_NO_SESSION;
    if(importSession == true) nSession = BS_CONTINUE_LAST_SESSION;
    switch(index){
        case 0:
            nProjectType = BS_BURNER_DATA;
            break;
        case 1:
            nProjectType = BS_BURNER_ISOUDF;
            break;
        case 2:
            nProjectType = BS_BURNER_UDFDVD;
            break;
    }

    int32 res = CreateProject(nProjectType, nSession);
    if(res!=0){
        QMessageBox::information(this, tr("Information"),
                                 tr("Error in Create Projekt"));
    }
}



