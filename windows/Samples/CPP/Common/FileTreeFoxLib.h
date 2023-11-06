#ifndef __KFILETREE__
#define __KFILETREE__

//#include "KString.h"

class KFileList : public FXIconList {
	FXDECLARE(KFileList)

public:
	KFileList(FXComposite *p, FXObject *tgt=NULL, FXSelector sel=0, FXuint opts=ICONLIST_NORMAL, FXint x=0, FXint y=0, FXint w=0, FXint h=0);
	~KFileList();

	void AddFile(int32 savePath= BS_DONT_SAVE_PATH);
	void CreateFolder();
	void DeleteItem();
	void ResetList();
	void RefreshList();
	void RenameFile();
	void SetRootDirectory(const FXString& strPath);

	int64 GetRootDirectorySize();

	long onDoubleClicked(FXObject* sender, FXSelector key, void* data);

	void clearItems(FXbool notify = 0);
	void removeItem(FXint index, FXbool notify = 0);

protected:
	KFileList() {}
	
	int64 GetDirectorySize(const FXString &strPath);
	void SelectDirectory(const FXString &strPath);	
	void handleError(int32 errCode);
private:
	FXString m_strRootDirectory;
	FXString m_strCurDirectory;

	FXIcon *mini_folder;
	FXIcon *mini_doc;
};

#endif

