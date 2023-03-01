#pragma once

#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include "DataTypes.h"

class MainFrame;

class Program : public CWinApp
{
public:
    CDatabase* db;
    CDialog* activeDialog;
    MainFrame* frame;



    Program();

    ~Program();

    BOOL InitInstance();

    void SwitchToCompaniesView();

    bool ConnectToDb(DBType dbType, CString server, CString dbName, CString uid, CString pwd);
};