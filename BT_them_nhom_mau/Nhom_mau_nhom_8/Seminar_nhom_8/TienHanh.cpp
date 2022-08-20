#include "TienHanh.h"

void Setting()
{
	SetWindowSize(80, 20);
	SetScreenBufferSize(80, 20);
	DisableCtrButton(0, 1, 1);
	DisableResizeWindow();
	showScrollbar(false);
	SetFontSize(14);
	SetConsoleTitle(L"KIEM TRA NHOM MAU");
	ShowCur(false);
	DisableSelection();
}

void StartGame()
{
	Play Game;
	CungKiemTra(Game);
}

bool PlayAgain()
{
	system("cls");
	ToMau(31, 8, "Ban Co Muon Choi Lai Khong?", 10);
	ToMau(40, 13, "Thoat", 10);
	ToMau(40, 11, "Choi Lai", 240);

	int input = ScanInput();
	short ViTriChon = 2;
	while (input != 13) {
		if (input == 72 || input == 80) 
		{
			if (ViTriChon == 1) {
				ToMau(40, 13, "Thoat", 10);
				ToMau(40, 11, "Choi Lai", 240);
				ViTriChon = 2;
			}
			else {
				ToMau(40, 13, "Thoat", 240);
				ToMau(40, 11, "Choi Lai", 10);
				ViTriChon = 1;
			}
		}

		input = ScanInput();
	}

	if (ViTriChon == 2)
		return true;
	else
		return false;
}

void FirstPage()
{
	system("cls");
	ToMau(25, 3, "~~  KIEM   TRA   NHOM   MAU  ~~", 10);
	ToMau(73, 7, "by Nhom 8", 10);

	ToMau(1, 5, "Thoat nhanh: esc", 10);
	ToMau(1, 8, "Dieu khien: <     >", 10);
	ToMau(16, 7, "^", 10);
	ToMau(16, 9, "v", 10);
	ToMau(1, 11, "Chon: enter", 10);



	ToMau(36, 11, "Bat Dau", 240);
	ToMau(37, 13, "Thoat", 10);
	ToMau(27, 15, "Huong Dan Chay Chuong Trinh", 10);
	ToMau(22, 16, "Nhap cac so lieu theo yeu cau cua de bai", 10);

	int input = ScanInput();
	int LineSelected = 1;
	while (input != 13) 
	{
		if (input == 27)
			LastPage();
		if (input == 72) {
			if (LineSelected == 1) 
			{
				ToMau(36, 11, "Bat Dau", 10);
				ToMau(37, 13, "Thoat", 240);
				LineSelected = 2;
			}
			else if (LineSelected == 2) {
				ToMau(37, 13, "Thoat", 10);
				ToMau(36, 11, "Bat Dau", 240);
				LineSelected--;
			}
		}

		if (input == 80) 
		{
			if (LineSelected == 1) 
			{
				ToMau(36, 11, "Bat Dau", 10);
				ToMau(37, 13, "Thoat", 240);
				LineSelected++;
			}
			else if (LineSelected == 2) {
				ToMau(37, 13, "Thoat", 10);
				ToMau(36, 11, "Bat Dau", 240);
				LineSelected = 1;
			}
		}

		input = ScanInput();
	}

	if (LineSelected == 2)
		LastPage();
	if (LineSelected == 1)
		TrangGioiThieuCachChoi();
}

void TrangGioiThieuCachChoi()
{
	system("cls");
	ToMau(31, 4, " CAC YEU CAU CUA DE BAI ", 10);

	ToMau(28, 9,  "----------------------------------", 10);
	ToMau(28, 10, "|                                |", 10);
	ToMau(28, 11, "|  a) Nhap vao danh sach         |", 10);
	ToMau(28, 12, "|  b) Kiem tra nhom mau cha va me|", 10);
	ToMau(28, 13, "|  c) Tim nguoi cho mau phu hop  |", 10);
	ToMau(28, 14, "|                                |", 10);
	ToMau(28, 15, "---------------------------------- ", 10);

	ToMau(66, 19, "Quay lai", 10);
	ToMau(10, 19, "Bat Dau", 240);

	short LineSelected = 2;
	int input = ScanInput();
	while (input != 13) {
		if (input == 27)
			LastPage();

		if (input == 77 && LineSelected == 2) 
		{
			ToMau(10, 19, "Bat Dau", 10);
			ToMau(66, 19, "Quay Lai", 240);
			LineSelected = 1;
		}

		if (input == 75 && LineSelected == 1) 
		{
			ToMau(66, 19, "Quay Lai", 10);
			ToMau(10, 19, "Bat Dau", 240);
			LineSelected = 2;
		}

		input = ScanInput();
	}

	if (LineSelected == 1)
		return FirstPage();
	if (LineSelected == 2)
		StartGame();
}

void LastPage()
{
	system("cls");
	ToMau(32, 9, "Xin Chao Va Hen Gap Lai!", 10);
	gotoxy(29, 12);
	system("pause");
	system("cls");
	exit(0);
}
