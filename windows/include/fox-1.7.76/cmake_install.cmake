# Install script for directory: E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/FoxSDK")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "FoxSDK_FOXToolkit")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Include/fox-1.7.24" TYPE FILE FILES
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fx.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fx3d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX4Splitter.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX7Segment.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX885910Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX885911Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX885913Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX885914Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX885915Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX885916Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88591Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88592Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88593Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88594Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88595Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88596Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88597Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88598Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FX88599Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXAccelTable.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXApp.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXArray.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXArrowButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fxascii.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXAtomic.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXAutoPtr.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXBitmap.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXBitmapFrame.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXBitmapView.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXBMPIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXBMPImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXBZFileStream.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCalendar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCalendarView.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCanvas.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCheckButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXChoiceBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorRing.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColors.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorSelector.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorWell.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXColorWheel.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXComboBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXComplexd.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXComplexf.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXComposeContext.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXComposite.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXConsole.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1250Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1251Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1252Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1253Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1254Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1255Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1256Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1257Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP1258Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP437Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP850Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP852Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP855Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP856Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP857Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP860Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP861Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP862Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP863Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP864Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP865Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP866Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP869Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCP874Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fxcpuid.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCURCursor.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXCursor.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDataTarget.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDate.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDC.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDCPrint.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDCWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDDSIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDDSImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDebugTarget.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fxdefs.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDelegator.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDial.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDialogBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDict.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDir.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDirBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDirDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDirList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDirSelector.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDirVisitor.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDLL.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDockBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDockHandler.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDockSite.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDockTitle.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDocument.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDragCorner.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDrawable.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXDriveBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXElement.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXEvent.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXException.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXExpression.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXExtentd.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXExtentf.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFile.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFileDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFileDict.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFileList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFileSelector.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFileStream.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFoldingList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFont.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFontDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFontSelector.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXFrame.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGIFCursor.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGIFIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGIFImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLCanvas.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLCone.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLContext.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLCube.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLCylinder.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLObject.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLShape.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLSphere.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLTriangleMesh.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLViewer.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGLVisual.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGradientBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGroupBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXGZFileStream.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXhalf.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXHash.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXHeader.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXHorizontalFrame.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXICOIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXICOImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIconDict.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIconList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIconSource.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXId.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIFFIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIFFImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXImageFrame.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXImageView.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXInputDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXIO.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXJP2Icon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXJP2Image.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXJPGIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXJPGImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fxkeys.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXKnob.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXKOI8RCodec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXLabel.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXListBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXLocale.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMainWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMat2d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMat2f.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMat3d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMat3f.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMat4d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMat4f.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMatrix.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMDIButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMDIChild.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMDIClient.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMemMap.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMemoryStream.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuCaption.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuCascade.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuCheck.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuCommand.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuPane.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuRadio.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuSeparator.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMenuTitle.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMessageBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXMessageChannel.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXObject.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXObjectList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXOptionMenu.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPacker.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPath.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPCXIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPCXImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPicker.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPipe.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPNGIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPNGImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPoint.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPopup.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPPMIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPPMImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPrintDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXProgressBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXProgressDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXPtrQueue.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXQuatd.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXQuatf.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRadioButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRanged.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRangef.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRangeSlider.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRASIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRASImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRealSlider.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRealSpinner.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRecentFiles.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRectangle.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRefPtr.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRegion.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRegistry.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXReplaceDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRex.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRGBIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRGBImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRootWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRuler.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXRulerView.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXScrollArea.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXScrollBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXScrollPane.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXScrollWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSearchDialog.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSeparator.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSettings.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXShell.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXShutter.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSize.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSlider.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSocket.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSphered.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSpheref.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSpinner.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSplashWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSplitter.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSpring.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXStat.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXStatusBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXStatusLine.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXStream.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXString.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXStringDict.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSwitcher.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXSystem.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTabBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTabBook.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTabItem.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTable.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXText.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTextCodec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTextField.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTGAIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTGAImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXThread.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXThreadPool.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTIFIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTIFImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXToggleButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXToolBar.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXToolBarGrip.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXToolBarShell.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXToolBarTab.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXToolTip.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTopWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTranslator.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTreeList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTreeListBox.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXTriStateButton.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXUndoList.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fxunicode.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXURL.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXUTF16Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXUTF32Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXUTF8Codec.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVec2d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVec2f.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVec3d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVec3f.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVec4d.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVec4f.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/fxver.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVerticalFrame.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXVisual.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXWindow.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXWizard.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXXBMIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXXBMImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXXPMIcon.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/FXXPMImage.h"
    "E:/Projects/FoxSDK/branches/6.8/Include/fox-1.7.24/xincs.h"
    )
endif()
