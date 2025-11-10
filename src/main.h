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
typedef enum _GROUP_ID
{
	HkcuRun,
	HkcuWow64Run,
	HkcuRunOnce,
	HkcuWow64RunOnce,
	HkcuRunOnceEx,
	HkcuRunServices,
	HkcuRunServicesOnce,
	HkcuPoliciesRun,
	HklmRun,
	HklmRunEx,
	HklmWow64Run,
	HklmRunOnce,
	HklmWow64RunOnce,
	HklmRunOnceEx,
	HklmWow64RunOnceEx,
	HklmRunServices,
	HklmRunServicesOnce,
	HklmPoliciesRun,
	HklmTerminalRun,
	HklmTerminalRunOnce,
	HklmTerminalRunOnceEx,
	StartupDir1,
	StartupDir2,
	HklmAlternateShell,
	HklmSessionManager,
	HklmIconServiceLib,
	HklmWinlogon,
	HkcuCommandProcessor,
	HklmCommandProcessor,
	HklmHijacks,
	HklmHijacksWow64,
	HklmSilentExitProcess,
	HklmRdpwd,
	HkcuCodecs,
	HklmCodecs,
	HklmCodecsClsid1,
	HklmCodecsClsid2,
	HklmCodecsClsid3,
	HklmCodecsClsid4,
	HkcuCodecsClsid5,
	HklmCodecsClsid6,
	HklmCodecsWow64,
	HklmFontDrivers,
	HklmBHO,
	HklmBHOWow64,
	HkcuUrlSearchHooks,
	HklmKnownDlls,
	TaskScheduler_,
	Services,
	Drivers,
	GroupMax,
} GROUP_ID,*PGROUP_ID;

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
	LONG icon_id;
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
	PR_STRING signature_info;
	PR_STRING version_info;
	PR_STRING arguments;
	PR_STRING file_path;
	PR_STRING key_path;
	PR_STRING lnk_path;
	PR_STRING clsid;
	PR_STRING name;
	HANDLE hroot;
	HWND hwnd;
	ITEM_TYPE type;
	GROUP_ID group_id;
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
