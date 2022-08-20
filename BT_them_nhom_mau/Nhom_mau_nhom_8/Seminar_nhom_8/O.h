#pragma once
#include "Loai.h"
class O : public Loai
{
public:
    O();
    ~O();
    bool KiemTra(int, int);
    int GetLoai();
    bool TuongThich(int mau, int RH);
};

