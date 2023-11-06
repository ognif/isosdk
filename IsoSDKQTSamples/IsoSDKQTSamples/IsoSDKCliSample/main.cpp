/********************************************************************************************************************************************
 *  IsoSDK - a powerful CD/DVD/BD recording SDK for Linux, macOS, Windows and Android.
 *  Copyright (c) 2002-2022 Ingo Foerster (pixbytesl@gmail.com).
 *  http://www.isosdk.com
 *
 *
 * Test commandline for this sample
 * IsoSDKCliSample.exe --device G: --file "D:\Video.mov" --file "D:\Setups\IsoSDK-9.5.2-Ubuntu.deb" --label "filetest" --finalize --eject
 * IsoSDKCliSample.exe --device E: --file "D:\Video.mov" --file "D:\Setups\IsoSDK-9.5.2-Ubuntu.deb" --label "filetest" --eject --project iso
 * IsoSDKCliSample.exe --device E: --file "D:\IsoSDK-9.1.3a-Linux.deb" --label "filetest" --eject --importsession 1 --project iso
 * IsoSDKCliSample.exe --device E: --folder "D:\bass\linux" --eraserw
 * IsoSDKCliSample.exe --device E: --folder "D:\eclipse\workspace\JNI" --folder "D:\backup\Schulung" --label "foldertest" --eject --project udfdvd
 * IsoSDKCliSample.exe --device E: --erase true --eject
 * IsoSDKCliSample.exe --file "D:\IsoSDK-9.1.3a-Linux.deb" --project udfdvd --label console --image "D:\sampleimage.iso"
 * IsoSDKCliSample.exe --device "E:" --file "D:\IsoSDK-9.1.3a-Linux.deb" --project isoudf --label "console2" --eraserw --finalize
 * IsoSDKCliSample.exe --device "E:" --copydisc "G: 0 yes" --writemethod tao --eraserw
 * IsoSDKCliSample.exe --device "E:" --iso "D:\sampleimage.iso" --eraserw --eject
 *
 * //Linux
 * IsoSDKCliSample.exe --device 1: --file "/home/developer/Documents/Video.mov" --file "/home/developer/Documents/setups/IsoSDK-9.5.2-Ubuntu.deb" --label "filetest" --finalize --eject
 * IsoSDKCliSample.exe --device 1: --file "/home/developer/Documents/Video.mov" --file "/home/developer/Documents/setups/IsoSDK-9.5.2-Ubuntu.deb" --label "filetest" --eject --project iso
 * IsoSDKCliSample.exe --device 1: --file "/home/developer/Documents/IsoSDK-9.1.3a-Linux.deb" --label "filetest" --eject --importsession 1 --project iso
 * IsoSDKCliSample.exe --device 1: --folder "/home/developer/Documents/bass/linux" --eraserw
 * IsoSDKCliSample.exe --device 1: --folder "/home/developer/Documents/eclipse/workspace/JNI" --folder "/home/developer/Documents/backup/Schulung" --label "foldertest" --eject --project udfdvd
 * IsoSDKCliSample.exe --device 1: --erase true --eject
 * IsoSDKCliSample.exe --file "/home/developer/Documents/IsoSDK-9.1.3a-Linux.deb" --project udfdvd --label console --image "/home/developer/Documents/myimage.iso"
 * IsoSDKCliSample.exe --device "1:" --file "/home/developer/Documents/IsoSDK-9.1.3a-Linux.deb" --project isoudf --label "console2" --eraserw --finalize
 * IsoSDKCliSample.exe --device "1:" --copydisc "G: 0 yes" --writemethod tao --eraserw
 * IsoSDKCliSample.exe --device "1:" --iso "/home/developer/Documents/sampleimage.iso" --eraserw --eject
 *
 * IsoSDKCliSample helper
 * Options:
 *  -?, -h, --help                              Displays help on commandline options.
 *  --help-all                                  Displays help including Qt specific options.
 *  -v, --version                               Displays version information.
 *  --eject                                     Eject medium after burn
 *  --verify                                    Verify data after burn
 *  --finalize                                  Finalize medium after burn
 *  --nojoliet                                  Don't use joliet file system
 *  --eraserw                                   Erase RW before burning
 *  --boot <Path of boot image>                 Boot image path
 *  --label <Label value>                       Label / name of the disc
 *  --cache <Cache value>                       Set size of cache. Default is 4(MB)
 *  --writemethod <Write method>                Set the write method to write on disc
 *  --device <device>                           device to burn to.
 *  --project <Project type>                    Project type to burn
 *  --erase <Erase fast>                        Erase the disc in drive <drive>
 *  --file <File path>                          File with Path to burn to disc
 *  --folder <Folder path>                      Folder Path to burn to disc
 *  --iso <ISO image path>                      ISO image file with full path toburn to disc
 *  --image <image>                             Target ISO image to write.
 *  --importsession <Session number to import>  Imports an existing session to the disc
 *  --copydisc <Array of additional values>     Copy a disc to another
 ********************************************************************************************************************************************/


#include <QCoreApplication>
#include <QCommandLineParser>
#include <QRegularExpression>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <iostream>

#include "IsoSDKBurningLib.h"

#if defined (WIN32)
# define tCout std::wcout
#else
# define tCout std::cout
#endif


QMutex	g_cOutputLock;
bool    g_bDone = false;
bool    e_bDone = false;
QString myBuffer;

QStringList projectMap = (QStringList() << "audio" << "" << "iso" << "" << "" << "videodvd" << "udfdvd" << "isoudf" << "bluray" << "mixmode");
QStringList writeMethods = (QStringList() << "tao" << "dao" << "dao96");


QString convertToQT(const TCHAR * strValue)
{
#if defined (WIN32)
    return QString::fromWCharArray(strValue);
#else
    return QString::fromUtf8(strValue);
#endif
}

void terminalPrinter2(QString output)
{
#if defined (WIN32)
    tCout << output.toStdWString().c_str();
#else
    tCout << output.toStdString().c_str();
#endif
    std::flush(tCout);
}
void terminalPrinter(QString output)
{
#if defined (WIN32)
    tCout << output.toStdWString().c_str() << std::endl;
#else
    tCout << output.toStdString().c_str() << std::endl;
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

void OnBurnDone(const TCHAR* pcError, void*)
{
    g_cOutputLock.lock();
    if(pcError){
        QString strError = QString( "Burn error: %1" ).arg(convertToQT(pcError));
        terminalPrinter(strError);
    }else{
        terminalPrinter("Burn done: no errors");
    }
    g_cOutputLock.unlock();
}
void OnEraseDone(const TCHAR* pcError, void*)
{
    g_cOutputLock.lock();
#if defined (WIN32)
    terminalPrinter("\n");
#endif
    if(pcError){
        QString strError = QString( "Erase error: %1" ).arg(convertToQT(pcError));
        terminalPrinter(strError);
    }else{
        terminalPrinter("Erase done: no errors");
    }
    e_bDone = true;
    g_cOutputLock.unlock();
}

void OnJobDone(void*)
{
    g_cOutputLock.lock();
    g_bDone = true;
    g_cOutputLock.unlock();
}

void OnFinalize(void*)
{
    g_cOutputLock.lock();
#if defined (WIN32)
    terminalPrinter("\n");
#endif
    terminalPrinter("Finalizing disc...");
    g_cOutputLock.unlock();
}

void OnProcess(float fPercent, float, float,
    double, double, void*)
{
    static int nChars = 0;

    g_cOutputLock.lock();
    if(e_bDone==true){
        e_bDone = false;
        nChars = 0;
    }
    while ((fPercent / 100.0) * 80 > nChars)
    {
        terminalPrinter2("*");
        nChars++;
    }
    g_cOutputLock.unlock();
}

bool handleError(int32 nError, QString errDescription)
{
    if (nError != BS_SDK_ERROR_NO)
    {
        TCHAR chError[2048];
        int32 nLength = 2048;

        ::GetText(nError, chError, &nLength);

        QString strError = QString( "SDK Error: %1 / %2" ).arg(QString::number(nError), 2, '0' ).arg(convertToQT( chError ) );
        terminalPrinter(errDescription);
        terminalPrinter(strError);

        getchar();
        ::DeInitialize();
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
#if defined (WIN32)
    QString rootPath = "\\";
#else
    QString rootPath = "/";
#endif

    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    QCoreApplication::setApplicationName("IsoSDKCliSample");
    QCoreApplication::setApplicationVersion("10.7.1");
    QString welcomeLine = QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion();

    terminalPrinter(welcomeLine);

    parser.setApplicationDescription("IsoSDKCliSample helper");
    parser.addHelpOption();
    parser.addVersionOption();

    /***********************************************************************
     * IsoSDK Options parser
     ***********************************************************************/
    QCommandLineOption optionEject("eject",
            QCoreApplication::translate("main", "Eject medium after burn"));
    parser.addOption(optionEject);
    QCommandLineOption optionVerify("verify",
            QCoreApplication::translate("main", "Verify data after burn"));
    parser.addOption(optionVerify);
    QCommandLineOption optionFinalize("finalize",
            QCoreApplication::translate("main", "Finalize medium after burn"));
    parser.addOption(optionFinalize);
    QCommandLineOption optionNoJoliet("nojoliet",
            QCoreApplication::translate("main", "Don't use joliet file system"));
    parser.addOption(optionNoJoliet);
    QCommandLineOption optionErase("eraserw",
            QCoreApplication::translate("main", "Erase RW before burning"));
    parser.addOption(optionErase);
    QCommandLineOption optionBoot("boot",
            QCoreApplication::translate("main", "Boot image path"),
            QCoreApplication::translate("main", "Path of boot image"));
    parser.addOption(optionBoot);
    QCommandLineOption optionDiscLabel("label",
            QCoreApplication::translate("main", "Label / name of the disc"),
            QCoreApplication::translate("main", "Label value"));
    parser.addOption(optionDiscLabel);
    QCommandLineOption optionCache("cache",
            QCoreApplication::translate("main", "Set size of cache. Default is 4(MB)"),
            QCoreApplication::translate("main", "Cache value"));
    parser.addOption(optionCache);
    QCommandLineOption optionWriteMethod("writemethod",
            QCoreApplication::translate("main", "Set the write method to write on disc"),
            QCoreApplication::translate("main", "Write method"));
    parser.addOption(optionWriteMethod);

    /***********************************************************************
     * IsoSDK base settings parser
     ***********************************************************************/
    QCommandLineOption burnDeviceOption("device",
            QCoreApplication::translate("main", "device to burn to."),
            QCoreApplication::translate("main", "device"));
    parser.addOption(burnDeviceOption);
    QCommandLineOption projectType("project",
            QCoreApplication::translate("main", "Project type to burn"),
            QCoreApplication::translate("main", "Project type"));
    parser.addOption(projectType);
    QCommandLineOption projectErase("erase",
            QCoreApplication::translate("main", "Erase the disc in drive <drive>"),
            QCoreApplication::translate("main", "Erase fast"));
    parser.addOption(projectErase);

    /***********************************************************************
     * IsoSDK File & folder parser
     ***********************************************************************/
    QCommandLineOption burnFile("file",
            QCoreApplication::translate("main", "File with Path to burn to disc"),
            QCoreApplication::translate("main", "File path"));
    parser.addOption(burnFile);
    QCommandLineOption burnFolder("folder",
            QCoreApplication::translate("main", "Folder Path to burn to disc"),
            QCoreApplication::translate("main", "Folder path"));
    parser.addOption(burnFolder);
    QCommandLineOption burnISOFile("iso",
            QCoreApplication::translate("main", "ISO image file with full path to burn to disc"),
            QCoreApplication::translate("main", "ISO image path"));
    parser.addOption(burnISOFile);

    /***********************************************************************
     * IsoSDK additional settings parser
     ***********************************************************************/
    QCommandLineOption targetImage("image",
            QCoreApplication::translate("main", "Target ISO image to write."),
            QCoreApplication::translate("main", "image"));
    parser.addOption(targetImage);
    QCommandLineOption projectImportSession("importsession",
            QCoreApplication::translate("main", "Imports an existing session to the disc"),
            QCoreApplication::translate("main", "Session number to import"));
    parser.addOption(projectImportSession);
    QCommandLineOption copyDisc("copydisc",
            QCoreApplication::translate("main", "Copy a disc to another"),
            QCoreApplication::translate("main", "Array of additional values"));
    parser.addOption(copyDisc);

    parser.process(app);

    /***********************************************************************
     ***********************************************************************
     ** IsoSDK Initialize and start
     ***********************************************************************
     ***********************************************************************/
    int res = 0;

#if defined LINUX
    QString mLicense = "3GTF75-2UM4AX-18LAHC-BX1FOR-N38Y32";
    res = ::Initialize((const TCHAR*)mLicense.toUtf8(), BS_ASPI_INTERNAL, BS_TRUE);
#endif
#if defined MAC
    QString mLicense = "NPTD4B-WVZ3A7-KZPA9G-B91CYR-2U8TTN";
    res = ::Initialize((const TCHAR*)mLicense.toUtf8(), BS_ASPI_INTERNAL, BS_TRUE);
#endif
#if defined WIN32
    QString mLicense = "67TR6O-XTEZA0-WKJAUF-BI84SR-3X82W7";
    res = ::Initialize((const TCHAR*)mLicense.utf16(), BS_ASPI_INTERNAL, BS_TRUE);
#endif

    if(!handleError(res, "Error while initialize. Maybe wrong license key.")) return 0;

    /***********************************************************************
     * Callbacks / Events handling
     ***********************************************************************/

    SetFinalizeEventCallback(OnFinalize, nullptr);
    SetBurnDoneEventCallback(OnBurnDone, nullptr);
    SetProcessEventCallback(OnProcess, nullptr);
    SetJobDoneEventCallback(OnJobDone, nullptr);
    SetEraseDoneEventCallback(OnEraseDone, nullptr);

    bool hasCopyDisc = parser.isSet(copyDisc);
    bool hasBurnDevice = parser.isSet(burnDeviceOption);
    if(hasCopyDisc && hasBurnDevice){

        /***********************************************************************
         *Copy disc.
         ***********************************************************************/
        bool    g_bVerify = parser.isSet(optionVerify);
        int32	g_nReadMode	= BS_RM_USERDATA;
        int32   g_nWriteMethod = BS_WM_TAO;
        bool hasWriteMethod = parser.isSet(optionWriteMethod);
        if(hasWriteMethod){
            g_nWriteMethod = writeMethods.indexOf(parser.value(optionWriteMethod));
        }
        auto additionalArgs = parser.value(copyDisc).split(QRegularExpression("[, ]"), Qt::SkipEmptyParts);
        if(additionalArgs.length()<3){
            terminalPrinter("Error additional settings copy.");
            return 0;
        }
        bool hasBurnDevice = parser.isSet(burnDeviceOption);
        if(hasBurnDevice){
            const TCHAR *pBurnDrive = convertToIsoSDKValue(parser.value(burnDeviceOption));
            int32 res = ::SetBurnDevice(pBurnDrive);
            delete [] pBurnDrive;
            if(!handleError(res, "Error set burn device.")) return 0;

        }
        const TCHAR *pReadDrive = convertToIsoSDKValue(additionalArgs.at(0));
        int32 res = ::SetReadDevice(pReadDrive);
        delete [] pReadDrive;
        if(!handleError(res, "Error set read device.")) return 0;

        g_nReadMode	= additionalArgs.at(1).toInt();
        if(g_nReadMode < 0 && g_nReadMode > 2){
            terminalPrinter("Readmode not 0 or 1 or 2");
            return 0;
        }
        SDiskCopyOptions cDiscCopyOptions;
        cDiscCopyOptions.bVerifyAfterBurn = g_bVerify;
        cDiscCopyOptions.nReadMode = g_nReadMode;
        cDiscCopyOptions.nWriteMethod = g_nWriteMethod;

        SReadErrorCorrectionParams cCorrecionParams;
        cCorrecionParams.bErrorCorrection = additionalArgs.at(2) == "yes" ? BS_TRUE : BS_FALSE;

        cDiscCopyOptions.cErrorParams = cCorrecionParams;

        bool hasAutoErase = parser.isSet(optionErase);
        if(hasAutoErase){
            SOptions opt;
            ::GetOptions(&opt);
            opt.bAutoErase = BS_TRUE;
            ::SetOptions(opt);
        }

        res = ::CopyDisk(cDiscCopyOptions);
        if(!handleError(res, "Error copy disk.")) return 0;
        if(res==0){
            terminalPrinter("Start copy disc.");
        }

    }else{

        /***********************************************************************
         * Burn or Erase
         ***********************************************************************/

        /***********************************************************************
         * IsoSDK Device settings
         ***********************************************************************/
        bool hasImage = parser.isSet(targetImage);
        if(hasImage){
            ::SetBurnDevice(_T("#:"));
            const TCHAR *pImagePath = convertToIsoSDKValue(parser.value(targetImage));
            int32 res = ::SetImageFilePath(pImagePath);
            delete [] pImagePath;
            if(!handleError(res, "Error set image path.")) return 0;

        }else{
            //No Image so set device
            bool hasDevice = parser.isSet(burnDeviceOption);
            if(hasDevice){
                const TCHAR *pBurnDrive = convertToIsoSDKValue(parser.value(burnDeviceOption));
                int32 res = ::SetBurnDevice(pBurnDrive);
                delete [] pBurnDrive;
                if(!handleError(res, "Error set burn device.")) return 0;

            }else{
                terminalPrinter("Error no device and image.");
                return 0;
            }
        }

        /***********************************************************************
         * Create project to burn
         ***********************************************************************/
        int32 nSessionToImport = BS_CONTINUE_NO_SESSION;
        bool hasSessionToImport = parser.isSet(projectImportSession);
        if(hasSessionToImport && !hasImage){
            nSessionToImport = parser.value(projectImportSession).toInt();
            if (nSessionToImport < 0){
                terminalPrinter("Error, no valid session found.");
                return 0;
            }
        }

        int32 nProjectType = BS_BURNER_ISOUDF;
        bool hasProjectType = parser.isSet(projectType);
        if(hasProjectType){
            nProjectType = projectMap.indexOf(parser.value(projectType));
        }

        res = CreateProject(nProjectType,nSessionToImport );
        if(!handleError(res, "Error creating base project.")) return 0;

        /***********************************************************************
         * If files available, add files
         ***********************************************************************/
        bool hasFiles = parser.isSet(burnFile);
        if(hasFiles){
            QStringList myFiles = parser.values(burnFile);
            for (int i = 0; i < myFiles.size(); ++i)
            {
                SFileToAdd file;
                file.lpszFileName = nullptr;
                const TCHAR *pSavePath = convertToIsoSDKValue(myFiles.at(i));
                const TCHAR *pRootPath = convertToIsoSDKValue(rootPath);
                file.lpszSourceFilePath = pSavePath;
                file.lpszDestinationPath = pRootPath;
                file.bVideoFile = BS_FALSE;
                file.nSavePath = BS_DONT_SAVE_PATH;
                int32 res = ::AddFile(file);
                if(!handleError(res, "Error adding file.")) return 0;

                delete [] pSavePath;
                delete [] pRootPath;
            }
        }

        /***********************************************************************
         * If folders available, add folders
         ***********************************************************************/
        bool hasFolder = parser.isSet(burnFolder);
        if(hasFolder){
            QStringList myFolders = parser.values(burnFolder);
            for (int i = 0; i < myFolders.size(); ++i)
            {
                SDirToAdd cDirToAdd;
                const TCHAR *pSavePath = convertToIsoSDKValue(myFolders.at(i));
                const TCHAR *pRootPath = convertToIsoSDKValue(rootPath);
                cDirToAdd.lpszSourceDirPath = pSavePath;
                cDirToAdd.lpszDestinationPath = pRootPath;
                cDirToAdd.nSavePath = BS_DONT_SAVE_PATH;
                int32 res = ::AddDir(cDirToAdd);
                if(!handleError(res, "Error adding folder.")) return 0;

                delete [] pSavePath;
                delete [] pRootPath;
            }
        }

        /***********************************************************************
         * IsoSDK Options settings
         ***********************************************************************/
        SOptions cOptions;
        ::GetOptions(&cOptions);

        cOptions.bUnderrunProtection = BS_TRUE;
        cOptions.bAutoErase = parser.isSet(optionErase) ? BS_TRUE : BS_FALSE;
        cOptions.bEjectAfterBurn = parser.isSet(optionEject) ? BS_TRUE : BS_FALSE;
        cOptions.bFinalize = parser.isSet(optionFinalize) ? BS_TRUE : BS_FALSE;
        cOptions.bJolietFileSystem = parser.isSet(optionNoJoliet) ? BS_FALSE : BS_TRUE;
        cOptions.bVerifyAfterBurn = parser.isSet(optionVerify) ? BS_TRUE : BS_FALSE;
        bool hasCache = parser.isSet(optionCache);
        if(hasCache){
            int nCache = parser.value(optionCache).toInt();
            cOptions.nCacheSize = 1024*1024*nCache;
        }
        bool hasLabel = parser.isSet(optionDiscLabel);
        if(hasLabel){
            const TCHAR *pLabel = convertToIsoSDKValue(parser.value(optionDiscLabel));
            _tcsncpy( cOptions.chVolumeLabel, pLabel, 128 );
            delete [] pLabel;
        }
        SetOptions(cOptions);

        /***********************************************************************
         * Switch for Erase. If Erase, no prepare & burning.
         ***********************************************************************/
        bool hasErase = parser.isSet(projectErase);
        bool hasISO = parser.isSet(burnISOFile);
        if(hasErase){
            BS_BOOL ejectAfter = parser.isSet(optionEject) ? BS_TRUE : BS_FALSE;
            BS_BOOL doFast = parser.value(projectErase) == "true" ? BS_TRUE : BS_FALSE;
            res = ::Erase(doFast,ejectAfter);
            if(!handleError(res, "Error erase disk.")) return 0;
            if(res==0){
                terminalPrinter("Start erase disc");
            }

        }else if(hasISO){
            SOptions cOptions;
            ::GetOptions(&cOptions);
            cOptions.bAutoErase = parser.isSet(optionErase) ? BS_TRUE : BS_FALSE;
            cOptions.bEjectAfterBurn = parser.isSet(optionEject) ? BS_TRUE : BS_FALSE;
            SetOptions(cOptions);

            const TCHAR *pISOImage = convertToIsoSDKValue(parser.value(burnISOFile));
            res = ::BurnISO(pISOImage, cOptions);
            delete [] pISOImage;
            if(!handleError(res, "Error burn ISOImage to disc.")) return 0;
            if(res==0){
                terminalPrinter("Start writing ISO to disc.");
            }

        }else{
            /***********************************************************************
             * Ready, prepare to burn
             ***********************************************************************/
            res = ::Prepare();
            if(!handleError(res, "Error preparing disk.")) return 0;

            /***********************************************************************
             * Finaly burn
             ***********************************************************************/
            res = ::Burn();
            if(!handleError(res, "Error burn disk.")) return 0;
            if(res==0){
                terminalPrinter("Start writing disc(image).");
            }

        }
    }


    terminalPrinter("Burning:");
    terminalPrinter("0%--------------------------------------------------------------------------100%");

    for (; !g_bDone;)
    {

        QThread::usleep(10);

    }

    terminalPrinter("App ended");
    ::DeInitialize();
    return 0;
    //return app.exec();
}


