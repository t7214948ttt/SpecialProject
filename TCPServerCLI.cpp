
#include "stdafx.h"
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <assert.h>
#include <Windows.h>
#include <Winuser.h>
#include <iostream>
#include <string>
#include <tchar.h>

#using<system.dll>
#using <System.Windows.Forms.dll>
#using <System.dll>
#pragma comment (lib, "ws2_32.lib")

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;
using namespace std;
void window(string key);
char id;
int main(array<System::String ^> ^args)
{
	//GUITHREADINFO currentWindowGuiThreadInfo;
	//DWORD procID;
	HWND h;
	int r;
	char buffer1[3];
	WSAData wsaData;
	WORD DLLVSERION;
	int keycode;
	//INPUT Input;
	DLLVSERION = MAKEWORD(2, 1);//Winsocket-DLL 版本

	//用 WSAStartup 開始 Winsocket-DLL
	r = WSAStartup(DLLVSERION, &wsaData);

	//宣告 socket 位址資訊(不同的通訊,有不同的位址資訊,所以會有不同的資料結構存放這些位址資訊)
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);

	//建立 socket
	SOCKET sListen; //listening for an incoming connection
	SOCKET sConnect; //operating if a connection was found

	//AF_INET：表示建立的 socket 屬於 internet family
	//SOCK_STREAM：表示建立的 socket 是 connection-oriented socket 
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	//設定位址資訊的資料
	addr.sin_addr.s_addr = inet_addr("192.168.1.120");
	//192.168.1.113
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);

	//設定 Listen
	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit

	//等待連線
	SOCKADDR_IN clinetAddr;
	while (true)
	{
		cout << "waiting..." << endl;

		if (sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen))
		{
			cout << "a connection was found" << endl;
			printf("server: got connection from %s\n", inet_ntoa(addr.sin_addr));

			//傳送訊息給 client 端
			char *sendbuf = "sending data test"; 
			h = 0;
			while (1){
				if (!h)
				{
					cout << "no" << endl;
					h = FindWindow(NULL, _T("Borderlands 2 (32-bit, DX9)"));
				}
				else {
					cout << h << endl;
					break;
				}
			}
			/*Input.type = INPUT_KEYBOARD;
			Input.ki.wScan = 0;
			Input.ki.time = 0;
			Input.ki.dwExtraInfo = 0;*/
			while (1)
			{
				//Sleep(10);
				int res = recv(sConnect, buffer1, sizeof(buffer1), 0);
				keycode = atoi(buffer1);
				if (keycode > 96)
				{
					keycode -= 32;
				}
				if (h)
				{
					SetForegroundWindow(h);
					keybd_event(keycode, 0, 0, 0);
					Sleep(10);
					keybd_event(keycode, 0, KEYEVENTF_KEYUP, 0);

					/*printf("%d\n", keycode);
					Input.ki.wVk = keycode;
					Input.ki.dwFlags = 0;
					SendInput(1, &Input, sizeof(INPUT));
					Input.ki.dwFlags = KEYEVENTF_KEYUP;
					SendInput(1, &Input, sizeof(INPUT));*/ //sendinput方法

					//SendMessage(h, WM_CHAR, keycode, MapVirtualKey(keycode, MAPVK_VK_TO_VSC)); //send message方法
				}
				else printf("%s\n", "fucku");
				memset(buffer1, '\0', sizeof(buffer1));

			}
		}
	}
	//getchar();
}