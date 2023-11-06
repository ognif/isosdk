#pragma once

#ifdef WIN32

#define CALL_FXDIALOG(expr)\
{\
	this->enable();\
	this->disable();\
	int32 res = expr;\
	this->enable();\
	this->show();\
}

#define CALL_FXDIALOG_HANDLE_ERROR(expr)\
{\
	this->enable();\
	this->disable();\
	int32 res = expr;\
	handleError(res);\
	this->enable();\
	this->show();\
}

#else

#define CALL_FXDIALOG(expr)\
{\
	expr;\
}

#define CALL_FXDIALOG_HANDLE_ERROR(expr)\
{\
	int32 res_is_very_private_do_not_name_such_your_vars = expr;\
	handleError(res_is_very_private_do_not_name_such_your_vars);\
}

#endif
