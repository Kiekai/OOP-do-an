#pragma once
#include<iostream>
#include<Windows.h>

char a[3] = "  ";
char a0[2] = " ";
char a1[3] = "1 ";
char a2[3] = "2 ";
char a3[3] = "3 ";
char a4[3] = "4 ";
char a5[3] = "5 ";
char a6[3] = "6 ";
char a7[3] = "7 ";
char a8[3] = "8 ";
char a9[3] = "B ";
char aP[3] = "P ";
char aPx[2] = "S";
char aD[2] = "D";

class Bang
{
private:
	short SoDong = 0;
	short SoCot = 0;
	short SoBom = 0;
	short BomDaMo = 0;
	short SoCo = 0;
public:
	Bang() {}
	short getDong();
	short getCot();
	void taoMaTran();
	void xoaMaTran();
	void khoiTao(short dong, short cot, short soBom);
	void veO(short x, short y, short kieu);
	short toaDoX(short x);
	short toaDoY(short y);
	void veBang();
	void taoBom();
	void xuLyPhim(KEY_EVENT_RECORD key);
	void xuLy();
	void clickPhai(short x, short y);
	void clickTrai(short x, short y);
	void latO(short x, short y);
	short bomXungQuanh(short x, short y);
	void designTittle();
	void gameMode(short stt, short mode, short x);
	void toaDoBang();
	bool check();
	void victory();
	void defeat();
	void mainMenu(short x);
	void menuLevel(short x);
	void Lastpage();
};
class O
{
private:
	bool CoBom = false;
	bool BomDaMo = false;
	bool DaCamCo = false;
	short SoBomLanCan = 0;
public:
	O() {};
	void setBom(bool a)
	{
		CoBom = a;
	}
	bool coBom()
	{
		return CoBom;
	}
	bool daMo()
	{
		return BomDaMo;
	}
	bool daCamCo()
	{
		return DaCamCo;
	}
	void caiCamCo(bool a)
	{
		DaCamCo = a;
	}
	void caiMoBom(bool a)
	{
		BomDaMo = a;
	}
	void setBomLC(short x)
	{
		SoBomLanCan = x;
	}
	short soBomLC()
	{
		return SoBomLanCan;
	}
};