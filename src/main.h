// Autoruns2
// Copyright (c) 2025 Henry++

#pragma once

#include "routine.h"

#include "resource.h"
#include "app.h"

#include <softpub.h>
#include <mstask.h>
#include <msterr.h>

// libs
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "wintrust.lib")

// CryptCATAdminAcquireContext2 (win8+)
typedef BOOL (WINAPI *CCAAC2)(
	_Out_ PHANDLE hcat_admin,
	_In_opt_ LPCGUID pgSubsystem,
	_In_opt_ PCWSTR pwszHashAlgorithm,
	_In_opt_ PCCERT_STRONG_SIGN_PARA pStrongHashPolicy,
	_Reserved_ DWORD dwFlags
	);

// CryptCATAdminCalcHashFromFileHandle2 (win8+)
typedef BOOL (WINAPI *CCAHFFH2)(
	_In_ HCATADMIN hCatAdmin,
	_In_ HANDLE hFile,
	_Inout_ DWORD *pcbHash,
	_Out_writes_bytes_to_opt_ (*pcbHash, *pcbHash) BYTE *pbHash,
	_Reserved_ DWORD dwFlags
	);

// ui
#define LANG_SUBMENU 1
#define LANG_MENU 6

#define REBAR_TOOLBAR_ID 0
#define REBAR_SEARCH_ID 1

#define LV_HIDDEN_GROUP_ID 666

#define STATUSBAR_PARTS_COUNT 3

// default colors
#define LV_COLOR_SIGNED RGB (175, 228, 163)
#define LV_COLOR_INVALID RGB (255, 125, 148)

#define SZ_TAB L"    "
#define SZ_CRLF L"\r\n"

// scan options
#define SCAN_OPTION_HIJACKS 0x00000002
#define SCAN_OPTION_WEB 0x00000004
#define SCAN_OPTION_PENDINGFRO 0x00000008
#define SCAN_OPTION_CODECS 0x00000010
#define SCAN_OPTION_KNOWNDLLS 0x00000020
#define SCAN_OPTION_TASKSCHEDULER 0x00000040
#define SCAN_OPTION_SERVICES 0x00000080
#define SCAN_OPTION_DRIVERS 0x00000100

#define SCAN_OPTION_DEFAULT (SCAN_OPTION_HIJACKS | SCAN_OPTION_WEB | SCAN_OPTION_PENDINGFRO | SCAN_OPTION_CODECS | SCAN_OPTION_KNOWNDLLS | SCAN_OPTION_TASKSCHEDULER | SCAN_OPTION_SERVICES | SCAN_OPTION_DRIVERS)

// group id
#define HkcuRun 0
#define HkcuWow64Run 1
#define HkcuRunOnce 2
#define HkcuWow64RunOnce 3
#define HkcuRunOnceEx 4
#define HkcuRunServices 5
#define HkcuRunServicesOnce 6
#define HkcuPoliciesRun 7
#define HklmRun 8
#define HklmRunEx 9
#define HklmWow64Run 10
#define HklmRunOnce 11
#define HklmWow64RunOnce 12
#define HklmRunOnceEx 13
#define HklmWow64RunOnceEx 14
#define HklmRunServices 15
#define HklmRunServicesOnce 16
#define HklmPoliciesRun 17
#define HklmTerminalRun 18
#define HklmTerminalRunOnce 19
#define HklmTerminalRunOnceEx 20
#define StartupDir1 21
#define StartupDir2 22
#define HklmAlternateShell 23
#define HklmSessionManager 24
#define HklmIconServiceLib 25
#define HklmWinlogon 26
#define HkcuCommandProcessor 27
#define HklmCommandProcessor 28
#define HklmHijacks 29
#define HklmHijacksWow64 30
#define HklmSilentExitProcess 31
#define HklmRdpwd 32
#define HklmCodecsClsid1 34
#define HklmCodecsClsid2 35
#define HklmCodecsClsid3 37
#define HklmCodecsClsid4 38
#define HkcuCodecsClsid5 39
#define HklmCodecsClsid6 40
#define HkcuCodecs 41
#define HklmCodecs 42
#define HklmCodecsWow64 43
#define HklmFontDrivers 44
#define HklmBHO 45
#define HklmBHOWow64 46
#define HkcuUrlSearchHooks 47
#define HklmKnownDlls 48
#define TaskScheduler 49
#define Services 50
#define Drivers 51

typedef struct _STATIC_DATA
{
	PR_STRING search_string;
	SC_HANDLE hsvcmgr;
	HIMAGELIST himg_toolbar;
	HIMAGELIST himg_tab;
	HBITMAP hbitmap_uac;
	HFONT wnd_font;
	HWND hrebar;
	HWND htoolbar;
	HWND hsearchbar;
	LONG64 start_time;
	volatile LONG total_count;
	volatile LONG lock;
} STATIC_DATA, *PSTATIC_DATA;

typedef enum _ITEM_TYPE
{
	RegistryTypeHkcu = 1,
	RegistryTypeHklm,
	RegistryTypeHklmAppCertDlls,
	RegistryTypeHklmBootExecute,
	RegistryTypeHklmPFRO,
	RegistryTypeHklmKnownDlls,
	RegistryTypeHklmShell,
	RegistryTypeHklmUserinit,
	RegistryTypeHklmVMApplet,
	RegistryTypeHklmAppInit,
	RegistryTypeHklmIconServiceLib,
	RegistryTypeHklmBrowserHelperObject,
	RegistryTypeHkcuUrlSearchHooks,
	RegistryTypeHklmAlternateShell,
	RegistryTypeHkcuCodecs,
	RegistryTypeHklmCodecs,
	RegistryTypeHkcuCodecsClsid,
	RegistryTypeHklmCodecsClsid,
	RegistryTypeHkcuAutorun,
	RegistryTypeHkcuCommandProcessor,
	RegistryTypeHklmCommandProcessor,
	RegistryTypeHklmIfeo,
	RegistryTypeHklmSilentExitProcess,
	RegistryTypeHklmFontDrivers,
	RegistryTypeHklmRdpwd,
	LinkType,
	FileType,
	SchedulerType,
	ServiceType,
	DriversType,
} ITEM_TYPE, *PITEM_TYPE;

typedef struct _ITEM_CONTEXT
{
	WCHAR reg_path[128];
	PR_STRING signature_info;
	PR_STRING version_info;
	PR_STRING arguments;
	PR_STRING file_path;
	PR_STRING lnk_path;
	PR_STRING clsid;
	PR_STRING name;
	HANDLE hroot;
	HWND hwnd;
	ITEM_TYPE type;
	LONG group_id;
	LONG icon_id;
	BOOLEAN is_hidden;
	BOOLEAN is_loaded;
} ITEM_CONTEXT, *PITEM_CONTEXT;

typedef struct _SCAN_CONTEXT
{
	HANDLE hroot;
	WCHAR path[128];
	HWND hwnd;
	LONG group_id;
	ITEM_TYPE type;
} SCAN_CONTEXT, *PSCAN_CONTEXT;

typedef struct _TAB_CONTEXT
{
	INT listview_id;
	INT locale_id;
} TAB_CONTEXT, *PTAB_CONTEXT;
