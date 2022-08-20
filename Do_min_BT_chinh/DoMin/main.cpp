#include<iostream>
#include "Header.h"
#include "Console.h"
#include "Functions.h"
#include<Windows.h>
using namespace std;


int main()
{
	SetWindowSize(160, 50);
	SetFontSize(10);
	SetScreenBufferSize(160, 50);
	DisableCtrButton(0, 1, 1);
	DisableResizeWindow();
	showScrollbar(false);
	ShowCur(false);
	resizeConsole(CSWidth, CSHeight);
	SetConsoleTitle(TEXT("GAME DÒ MÌN - OBJECT ORIENTED PROGRAMMING"));
	CTBang.designTittle();
	Cursor(false, 1);
	CTBang.mainMenu(0);
	Trang = 1;
	CTBang.xuLy();
	return 0;
}