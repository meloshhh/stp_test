#pragma once

#include <afxwin.h>

class Model
{
public:
	/// <summary>
	/// Returns single quoted val (ex. "'John Doe'") or "NULL"
	/// </summary>
	static CString StrOrNull(CString val);

	/// <summary>
	/// Returns val (ex. "5")  or "NULL"
	/// </summary>
	static CString NumOrNull(CString val);
};

