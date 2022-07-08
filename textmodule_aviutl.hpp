 #pragma once
#include <lua.hpp>
#include <iostream>

#include <exedit.hpp>
#include <aviutl.hpp>

#include <windows.h>

struct EXEDIT_MEMORY_OFFSET {
	static const DWORD StaticFilterTable = 0x0A3E28;
	static const DWORD SortedObjectTable_LayerIndexEnd = 0x135AC8;
	static const DWORD AliasNameBuffer = 0x135C70;
	static const DWORD ObjDlg_CommandTarget = 0x14965C;
	static const DWORD SortedObjectTable_LayerIndexBegin = 0x149670;
	static const DWORD ObjDlg_FilterStatus = 0x158D38;
	static const DWORD SortedObjectTable = 0x168FA8;
	static const DWORD ObjDlg_ObjectIndex = 0x177A10;
	static const DWORD SceneSetting = 0x177A50;
	static const DWORD LoadedFilterTable = 0x187C98;
	static const DWORD LayerSetting = 0x188498;
	static const DWORD SceneDisplaying = 0x1A5310;
	static const DWORD TextBuffer = 0x1A6BD0;
	static const DWORD TraScript_ProcessingTrackBarIndex = 0x1B21F4;
	static const DWORD TraScript_ProcessingObjectIndex = 0x1B2B04;
	static const DWORD ScriptProcessingFilter = 0x1B2B10;
	static const DWORD LuaState = 0x1BACA8;
	static const DWORD ObjectBuffer_ExdataSize = 0x1E0F9C;
	static const DWORD ObjectBuffer_MaxDataNum = 0x1E0FA0;
	static const DWORD ObjectBuffer_Data = 0x1E0FA4;
	static const DWORD ObjectBuffer_Exdata = 0x1E0FA8;
	static const DWORD CameraZBuffer = 0x1EC7AC;
	static const DWORD UndoInfo_ObjectNum = 0x244E08;
	static const DWORD UndoInfo_BufferPtr = 0x244E0C;
	static const DWORD UndoInfo_WriteOffset = 0x244E10;
	static const DWORD UndoInfo_CurrentId = 0x244E14;
	static const DWORD UndoInfo_BufferSize = 0x244E18;
};

struct EXEDIT_MEMORY_OFFSET_093RC1 {
	static const DWORD StaticFilterTable = 0x0C0A78;
	static const DWORD SortedObjectTable_LayerIndexEnd = 0x1A0628;
	static const DWORD AliasNameBuffer = 0x18FDB8;
	static const DWORD ObjDlg_CommandTarget = 0x25E97C;
	static const DWORD SortedObjectTable_LayerIndexBegin = 0x1A0360;
	static const DWORD ObjDlg_FilterStatus = 0x1C1310;
	static const DWORD SortedObjectTable = 0x1B2560;
	static const DWORD ObjDlg_ObjectIndex = 0x1051C8;
	static const DWORD SceneSetting = 0x1051D0;
	static const DWORD LoadedFilterTable = 0x106490;
	static const DWORD LayerSetting = 0x0FB580;
	static const DWORD SceneDisplaying = 0x0EC098;
	static const DWORD TextBuffer = 0x1158B8;
	static const DWORD TraScript_ProcessingTrackBarIndex = 0x1CD824;
	static const DWORD TraScript_ProcessingObjectIndex = 0x1CD59C;
	static const DWORD ScriptProcessingFilter = 0x1CD6AC;
	static const DWORD LuaState = 0x1CD560;
	static const DWORD ObjectBuffer_ExdataSize = 0x12BA54;
	static const DWORD ObjectBuffer_MaxDataNum = 0x129A4C;
	static const DWORD ObjectBuffer_Data = 0x12BA58;
	static const DWORD ObjectBuffer_Exdata = 0x125A2C;
	static const DWORD CameraZBuffer = 0x239658;
	static const DWORD UndoInfo_ObjectNum = 0x13078C;
	static const DWORD UndoInfo_BufferPtr = 0x248D00;
	static const DWORD UndoInfo_WriteOffset = 0x23A23C;
	static const DWORD UndoInfo_CurrentId = 0x23A290;
	static const DWORD UndoInfo_BufferSize = 0x23A298;
};


DWORD exedit_base();
HWND Get_AviUtlWindowHandle();

ExEdit::Filter** Get_StaticFilterTable(bool is093rc1);
char* Get_AliasNameBuffer(bool is093rc1);
int* Get_ObjDlg_CommandTarget(bool is093rc1);
BYTE* Get_ObjDlg_FilterStatus(bool is093rc1);
ExEdit::Object** Get_SortedObjectTable(bool is093rc1);
std::pair<int*, int*> Get_SortedObjectTable_LayerIndex(bool is093rc1);
int* Get_ObjDlg_ObjectIndex(bool is093rc1);
ExEdit::SceneSetting* Get_SceneSetting(bool is093rc1);
ExEdit::Filter** Get_LoadedFilterTable(bool is093rc1);
ExEdit::LayerSetting* Get_LayerSetting(bool is093rc1);
int* Get_SceneDisplaying(bool is093rc1);
wchar_t* Get_TextBuffer(bool is093rc1);
int* Get_TraScript_ProcessingTrackBarIndex(bool is093rc1);
int* Get_TraScript_ProcessingobjectIndex(bool is093rc1);
ExEdit::Filter** Get_ScriptProcessingFilter(bool is093rc1);
lua_State** Get_LuaState(bool is093rc1);
DWORD* Get_ObjectBuffer_ExdataSize(bool is093rc1);
DWORD* Get_ObjectBuffer_MaxDataNum(bool is093rc1);
ExEdit::Object** Get_ObjectBuffer_Data(bool is093rc1);
void** Get_ObjectBuffer_Exdata(bool is093rc1);
ExEdit::ZBufferElm** Get_CameraZBuffer(bool is093rc1);
int* Get_UndoInfo_ObjectNum(bool is093rc1);
void** Get_UndoInfo_BufferPtr(bool is093rc1);
DWORD* Get_UndoInfo_WriteOffset(bool is093rc1);
int* Get_UndoInfo_CurrentId(bool is093rc1);
DWORD* Get_UndoInfo_BufferSize(bool is093rc1);