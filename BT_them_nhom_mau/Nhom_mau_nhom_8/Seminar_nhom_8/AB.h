#pragma once
#include "Loai.h"
class AB : public Loai
{
public:
    AB();
    ~AB();
    bool KiemTra(int, int);
    int GetLoai();
    bool TuongThich(int mau, int RH);
};

