#pragma once
#include<iostream>
#include <string>
#include<time.h>
using namespace std;
class Loai
{
protected:
    int Rh;
    string Ten;
public:
    Loai();
    ~Loai();
    //Nhap Rh bang tay
    void Nhap();
    //Nhap Rh tu dong
    void Nhap_mau_tu_dong();
    //Output cho bien Rh
    int GetRh();
    //Cai dat Console
    void setting();
    //Output cho bien Ten
    string getTen();
    //Thuc hien yeu cau 2
    virtual bool KiemTra(int, int) = 0;
    //Gan so dai dien cho tung nhom mau (O: 1, A: 2, B: 3, AB: 4)
    virtual int GetLoai() = 0;
    //Thuc hien yeu cau 3
    virtual bool TuongThich(int mau, int) = 0;
};

