#pragma once

#include <afxwin.h>
#include <vector>
#include <string>

#define DISPLAY_VAL_ERR(msg) SimplePopupDialog popup{ msg }; popup.DoModal();

class Validator
{
public:
	static bool String(CString str, std::string rules);
};

