#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include "xor.hpp"

using namespace std; // >-< we already know

int getID(wstring processName) {

	int pid = 0; //native stuff here

	std::vector<DWORD> pids;
	std::wstring targetProcessName = processName;

	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32W entry;
	entry.dwSize = sizeof entry;

	if (!Process32FirstW(snap, &entry)) {
		return 0;
	}

	do {
		if (std::wstring(entry.szExeFile) == targetProcessName) {
			pids.emplace_back(entry.th32ProcessID); 
		}
	} while (Process32NextW(snap, &entry));

	for (int i(0); i < pids.size(); ++i) {
		std::cout << pids[i] << std::endl;
		pid = pids[i];
	}

	return pid;
}

int main() {
	wstring procName = L"notepad.exe"; //can use any other shit all tho it was only for testing ._.
	int pid = getID(procName);

	std::cout << (xorstr_("Found PID at: ")) << pid << endl;

	system("pause");
}