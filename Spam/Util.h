#pragma once
static void toggleDesktopIconsVisible() {
	SendMessage(GetWindow(FindWindow(L"Progman", L"Program Manager"), GW_CHILD), WM_COMMAND, 0x7402, 0);
}