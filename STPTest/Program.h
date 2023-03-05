#pragma once

#include <afxwin.h>
#include "resource.h"
#include <odbcinst.h>
#include <afxdb.h>
#include "DataTypes.h"
#include "CDialogExt.h"

class MainFrame;

class Program : public CWinApp
{
public:
    CDatabase* db;
    CDialogExt* activeDialog;
    MainFrame* frame;



    Program();

    ~Program();

    BOOL InitInstance();

    void SwitchToCompaniesView();

    void SwitchToOfficesView();

    void SwitchToEmployeesView();

    bool ConnectToDb(DBType dbType, CString server, CString dbName, CString uid, CString pwd);
};