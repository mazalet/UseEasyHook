// CreateProcessSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

void main(int argc, char *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	std::wstring text_wchar(L"c:\\windows\\system32\\notepad.exe");
	auto lp_command_line = text_wchar.c_str();
	if (argc >= 2)
	{
		char *text_char = argv[1];
		size_t length = strlen(text_char);

		text_wchar=std::wstring(length, L'#');

		//#pragma warning (disable : 4996)
		// Or add to the preprocessor: _CRT_SECURE_NO_WARNINGS
		mbstowcs(&text_wchar[0], text_char, length);
		lp_command_line = text_wchar.c_str();
	}

	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)lp_command_line,
		(LPCWSTR)L"Information",
		MB_ICONWARNING | MB_OK | MB_DEFBUTTON1
	);
	// Start the child process. 
	if (!CreateProcessW(NULL,   // No module name (use command line)
		(LPWSTR)lp_command_line,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}


