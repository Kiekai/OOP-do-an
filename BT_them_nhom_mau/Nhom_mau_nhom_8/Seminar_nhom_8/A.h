#pragma once
#include "Loai.h"
class A :public Loai
{
public:
    A();
    ~A();
    bool KiemTra(int, int);
    int GetLoai();
    bool TuongThich(int mau, int RH);
};

