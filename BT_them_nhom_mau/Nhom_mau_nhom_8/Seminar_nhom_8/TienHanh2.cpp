#include "TienHanh.h"
#include <stdlib.h>
#include<time.h>
void CungKiemTra(Play& Game)
{
	system("cls");
	srand(time(0));
	int choice;
	do
	{
		ToMau(5, 1, "Ban muon nhap bang tay hay tu dong (1 de nhap bang tay, 2 de nhap tu dong): ", 10);
		cin >> choice;
	} while (choice < 1 || choice > 2);
	if (choice == 1)
	{
		Game.Nhap_bang_tay();
	}
	else if (choice == 2)
	{
		Game.Nhap_tu_dong();
	}
	Game.TaoBang();
	Game.Kiemtrachame();
	Game.Kiemtrachonhan();
	system("pause");
}