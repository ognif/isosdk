#pragma once

#include "TreeNodes.h"

class KPropertiesDlg : public FXDialogBox {
	FXDECLARE(KPropertiesDlg)

public:
	KPropertiesDlg(FXApp* app, const Properties& props);

private:
	KPropertiesDlg();
};
