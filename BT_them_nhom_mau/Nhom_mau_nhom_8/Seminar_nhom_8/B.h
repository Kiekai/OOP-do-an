#pragma once
#include "Loai.h"
class B :public Loai
{
public:
    B();
    ~B();
    bool KiemTra(int, int);
    int GetLoai();
    bool TuongThich(int mau, int RH);
};

