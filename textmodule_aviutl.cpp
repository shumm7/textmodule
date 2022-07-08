#include "textmodule_aviutl.hpp"

#include <stdexcept>
#include "textmodule_exception.hpp"


DWORD exedit_base() {
	HMODULE hmod = LoadLibrary("exedit.auf");
	if (hmod == NULL)
		throw std::runtime_error(EXEDIT_AUF_NOTFOUND);

	return (DWORD)hmod;
}

HWND Get_AviUtlWindowHandle() {
	DWORD dwProcessId = GetCurrentProcessId();
	HWND hWnd = GetTopWindow(0);
	DWORD pid;

	do {
		if (GetWindowLongA(hWnd, GWL_HWNDPARENT) == NULL) {
			GetWindowThreadProcessId(hWnd, &pid);
			if ((&pid)[0] == dwProcessId) break;
		}
		hWnd = GetWindow(hWnd, GW_HWNDNEXT);
	} while (hWnd != NULL);

	return hWnd;
}


ExEdit::Filter** Get_StaticFilterTable(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::Filter**)(exedit_base() + EXEDIT_MEMORY_OFFSET::StaticFilterTable);
	else
		return (ExEdit::Filter**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::StaticFilterTable);
}

char* Get_AliasNameBuffer(bool is093rc1) {
	if (!is093rc1)
		return (char*)(exedit_base() + EXEDIT_MEMORY_OFFSET::AliasNameBuffer);
	else
		return (char*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::AliasNameBuffer);
}

int* Get_ObjDlg_CommandTarget(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjDlg_CommandTarget);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjDlg_CommandTarget);
}

BYTE* Get_ObjDlg_FilterStatus(bool is093rc1) {
	if (!is093rc1)
		return (BYTE*)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjDlg_FilterStatus);
	else
		return (BYTE*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjDlg_FilterStatus);
}

ExEdit::Object** Get_SortedObjectTable(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::Object**)(exedit_base() + EXEDIT_MEMORY_OFFSET::StaticFilterTable);
	else
		return (ExEdit::Object**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::StaticFilterTable);
}

std::pair<int*, int*> Get_SortedObjectTable_LayerIndex(bool is093rc1) {
	if (!is093rc1)
		return { (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::SortedObjectTable_LayerIndexBegin), (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::SortedObjectTable_LayerIndexEnd)};
	else
		return { (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::SortedObjectTable_LayerIndexBegin), (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::SortedObjectTable_LayerIndexEnd) };
}

int* Get_ObjDlg_ObjectIndex(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjDlg_ObjectIndex);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjDlg_ObjectIndex);
}

ExEdit::SceneSetting* Get_SceneSetting(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::SceneSetting*)(exedit_base() + EXEDIT_MEMORY_OFFSET::SceneSetting);
	else
		return (ExEdit::SceneSetting*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::SceneSetting);
}

ExEdit::Filter** Get_LoadedFilterTable(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::Filter**)(exedit_base() + EXEDIT_MEMORY_OFFSET::LoadedFilterTable);
	else
		return (ExEdit::Filter**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::LoadedFilterTable);
}

ExEdit::LayerSetting* Get_LayerSetting(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::LayerSetting*)(exedit_base() + EXEDIT_MEMORY_OFFSET::LayerSetting);
	else
		return (ExEdit::LayerSetting*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::LayerSetting);
}

int* Get_SceneDisplaying(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::SceneDisplaying);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::SceneDisplaying);
}

wchar_t* Get_TextBuffer(bool is093rc1) {
	if (!is093rc1)
		return (wchar_t*)(exedit_base() + EXEDIT_MEMORY_OFFSET::TextBuffer);
	else
		return (wchar_t*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::TextBuffer);
}

int* Get_TraScript_ProcessingTrackBarIndex(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::TraScript_ProcessingTrackBarIndex);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::TraScript_ProcessingTrackBarIndex);
}

int* Get_TraScript_ProcessingobjectIndex(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::TraScript_ProcessingObjectIndex);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::TraScript_ProcessingObjectIndex);
}

ExEdit::Filter** Get_ScriptProcessingFilter(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::Filter**)(exedit_base() + EXEDIT_MEMORY_OFFSET::ScriptProcessingFilter);
	else
		return (ExEdit::Filter**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ScriptProcessingFilter);
}

lua_State** Get_LuaState(bool is093rc1) {
	if (!is093rc1)
		return (lua_State**)(exedit_base() + EXEDIT_MEMORY_OFFSET::LuaState);
	else
		return (lua_State**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::LuaState);
}

DWORD* Get_ObjectBuffer_ExdataSize(bool is093rc1) {
	if (!is093rc1)
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjectBuffer_ExdataSize);
	else
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjectBuffer_ExdataSize);
}

DWORD* Get_ObjectBuffer_MaxDataNum(bool is093rc1) {
	if (!is093rc1)
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjectBuffer_MaxDataNum);
	else
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjectBuffer_MaxDataNum);
}

ExEdit::Object** Get_ObjectBuffer_Data(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::Object**)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjectBuffer_Data);
	else
		return (ExEdit::Object**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjectBuffer_Data);
}

void** Get_ObjectBuffer_Exdata(bool is093rc1) {
	if (!is093rc1)
		return (void**)(exedit_base() + EXEDIT_MEMORY_OFFSET::ObjectBuffer_Exdata);
	else
		return (void**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::ObjectBuffer_Exdata);
}

ExEdit::ZBufferElm** Get_CameraZBuffer(bool is093rc1) {
	if (!is093rc1)
		return (ExEdit::ZBufferElm**)(exedit_base() + EXEDIT_MEMORY_OFFSET::CameraZBuffer);
	else
		return (ExEdit::ZBufferElm**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::CameraZBuffer);
}

int* Get_UndoInfo_ObjectNum(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::UndoInfo_ObjectNum);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::UndoInfo_ObjectNum);
}

void** Get_UndoInfo_BufferPtr(bool is093rc1) {
	if (!is093rc1)
		return (void**)(exedit_base() + EXEDIT_MEMORY_OFFSET::UndoInfo_BufferPtr);
	else
		return (void**)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::UndoInfo_BufferPtr);
}

DWORD* Get_UndoInfo_WriteOffset(bool is093rc1) {
	if (!is093rc1)
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET::UndoInfo_WriteOffset);
	else
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::UndoInfo_WriteOffset);
}

int* Get_UndoInfo_CurrentId(bool is093rc1) {
	if (!is093rc1)
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET::UndoInfo_CurrentId);
	else
		return (int*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::UndoInfo_CurrentId);
}

DWORD* Get_UndoInfo_BufferSize(bool is093rc1) {
	if (!is093rc1)
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET::UndoInfo_BufferSize);
	else
		return (DWORD*)(exedit_base() + EXEDIT_MEMORY_OFFSET_093RC1::UndoInfo_BufferSize);
}