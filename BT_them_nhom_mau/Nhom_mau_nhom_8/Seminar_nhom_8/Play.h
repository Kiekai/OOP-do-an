#pragma once
#include "Loai.h"
#include "A.h"
#include "AB.h"
#include "B.h"
#include "O.h"
#include "DoHoa.h"
#include <iomanip>
#include<time.h>
#include <fstream>
class Play :public A, public B, public AB, public O
{
public:
	Loai* nhommau[100];
	int SoLuong;
	//Output ten loai mau
	string GetTenLoaiMau(int a);
	//Ham nhap bang tay
	void Nhap_bang_tay();
	//Ham nhap tu dong
	void Nhap_tu_dong();
	//Kiem tra co phai con cua cha me khong
	void Kiemtrachame();
	//Kiem tra su cho nhan co phu hop khong
	void Kiemtrachonhan();
	//Ham chua cac thao tac thuc hien yey cau
	friend void CungKiemTra(Play &Game);
	//In ra bang da nhap vao
	void TaoBang();
};

