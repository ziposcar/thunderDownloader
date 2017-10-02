// thunderDownloader.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "XLDownload.h"
#include "XLError.h"
#include <iostream>

#ifdef DEBUG
	#pragma comment(lib, "XLDownload.lib")
#else
	#pragma comment(lib, "XLDownload.lib")
#endif // DEBUG

LPCTSTR change(const char *ch)
{
	int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	//获得长字节所需的空间
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, ch, -1, wide, num);
	return wide;
}
int main(int argc, char const *argv[])
{
	//LPCTSTR url = _T(R"(http://i0.hdslb.com/bfs/archive/47b50224decc2dc105e4eba903b058722db60870.jpg)");
	//char pathRaw[100] = R"(D:\123.jpg)";
	//LPCTSTR path = _T(R"(D:\123.jpg)");
	LPCTSTR url;
	char pathRaw[100];
	LPCTSTR path;
	char del[100] = "del /f /q ";

	if (argc != 3)
	{
		std::cout << "error argv!\n";
		std::cout << "please input as \"thunderDownloader url dirpath\"\n";
		system("pause");
		return 1;
	}

	strcpy_s(pathRaw, argv[2]);
	url = change(argv[1]);
	path = change(argv[2]);

	strcat_s(del, pathRaw);
	LONG id;
	DWORD state;
	int errorTime = 0;
	while (true)
	{
		while (FALSE == XLInitDownloadEngine());
		do
		{
			if (errorTime > 5)
			{
				goto end;
			}
			// std::cout << "trying" << endl;
			state = XLURLDownloadToFile(path, url, NULL, id);

#ifdef DEBUG
			cout << state - XL_ERROR_FAIL << endl;
#endif // DEBUG

			if (state == XL_ERROR_FILE_ALREADY_EXIST)
			{
				system(del);
				++errorTime;
				continue;
			}
		} while (state != XL_SUCCESS);
		LONG status;
		ULONGLONG fileSize, recvSize;
		do
		{
			Sleep(1);
			state = XLQueryTaskInfo(id, &status, &fileSize, &recvSize);
			if (state != XL_SUCCESS || status == enumTaskStatus_Fail)
				break;
		} while (status != enumTaskStatus_Success);
		if (status == enumTaskStatus_Success)
		{
			XLStopTask(id);
		end:
			while (FALSE == XLUninitDownloadEngine());
			break;
		}
		else
			continue;
	}
	system("pause");
	return 0;
}
