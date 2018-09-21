#include <atlhandler.h>
#include <iostream>

using namespace std;

bool isInstance(LPCTSTR Mutex) {

	HANDLE handles = CreateMutex(NULL, TRUE, Mutex);
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		cout << "An instance is already running." << endl;
		return false;
	}
	else
	{
		cout << "No other instances running." << endl;
	}
	return true;
	CloseHandle(handles);
}

bool isSpace() {

	ULARGE_INTEGER FreeSpaceAvailable;
	ULARGE_INTEGER TotalSpace;
	ULARGE_INTEGER TotalFreeSpace;

	::GetDiskFreeSpaceEx(_T("c:\\"),
		&FreeSpaceAvailable,
		&TotalSpace,
		&TotalFreeSpace);

	const LONGLONG nGBFactor = 1024 * 1024 * 1024;

	double freeSpaceGB = (double)(LONGLONG)TotalFreeSpace.QuadPart / nGBFactor;
	int neededSpace = 300;

	//cout << freeSpaceGB;

	if (freeSpaceGB * 1024 < neededSpace) {
		cout << "Not enough free space." << endl;
		return false;
	}
	else {
		cout << "Enough free space." << endl;
		return true;
	}
}

void  checkMemory() {

	MEMORYSTATUSEX memorySize;
	memorySize.dwLength = sizeof(memorySize);
	GlobalMemoryStatusEx(&memorySize);
	unsigned long long physMem = memorySize.ullAvailPhys / (1024 * 1024);
	unsigned long long virtMem = memorySize.ullAvailVirtual / (1024 * 1024);

	cout << physMem << " MB of available physical memory." << endl;
	cout << virtMem << " MB of available virtual memory." << endl;

}

CString ProcSpeedRead()
{
	CString sMHz;
	char Buffer[_MAX_PATH];
	DWORD BufSize = _MAX_PATH;
	DWORD dwMHz = _MAX_PATH;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0,
		KEY_READ,
		&hKey);

	if (lError == ERROR_SUCCESS)
	{
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			lError,
			0,
			Buffer,
			_MAX_PATH,
			0);
		cout << Buffer << endl;
	}

	RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
	sMHz.Format("%i", dwMHz);

	return sMHz;
}

int main()
{
	isInstance("a");
	isSpace();
	checkMemory();
	cout << ProcSpeedRead() << " MHz." << endl;

	return 0;
}