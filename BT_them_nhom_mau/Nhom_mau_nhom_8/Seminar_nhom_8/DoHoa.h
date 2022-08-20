#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

//Ham thay doi kich co khung cmd voi tham so truyen vao la chieu cao, chieu rong
void resizeConsole(const int& width, const int& height);
//Ham to mau
void textcolor(const int& x);
//Ham di chuyen con tro den toa do x, y
void gotoxy(const int& x, const int& y);
//Ham xoa man hinh
void XoaManHinh();
//To mau cho LastPage()
void ToMau(const int& x, const int& y, const string a, const int& color);
//Thay doi font chu
void SetFontSize(const int& size);
//Thay doi Screen Buffer Size
void SetScreenBufferSize(const SHORT& width, const SHORT& height);
//Thay doi Console Window Size
void SetWindowSize(SHORT width, SHORT height);
//VO hieu hoa cac nut Minimize, Maximize, CLose
void DisableCtrButton(bool Close, bool Min, bool Max);
//An/Hien thanh cuon
void showScrollbar(BOOL Show);
//Vo hieu hoa thay doi kich thuoc man hinh
void DisableResizeWindow();
//An hien con tro
void ShowCur(bool CursorVisibility);
//Vo hieu hoa Select
void DisableSelection();
//Bat cac phim su kien
int ScanInput();

