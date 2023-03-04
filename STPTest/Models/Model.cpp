#include "Model.h"

CString Model::StrOrNull(CString val)
{
    CString ret{};
    if (val.IsEmpty())
    {
        ret.Format(L"NULL");
    }
    else
    {
        ret.Format(L"'%s'", val.GetString());
    }

    return ret;
}

CString Model::NumOrNull(CString val)
{
    CString ret{};
    if (val.IsEmpty())
    {
        ret.Format(L"NULL");
    }
    else
    {
        ret = val;
    }

    return ret;
}
