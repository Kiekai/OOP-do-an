#include "O.h"

O::O() {}

O::~O() {}

bool O::KiemTra(int me, int con)
{
    switch (me)
    {

    case 1:
        if (con == 1)
            return true;
        break;

    case 2:
        if (con == 2 || con == 1)
            return true;
        break;

    case 3:
        if (con == 3 || con == 1)
            return true;
        break;

    case 4:
        if (con == 2 || con == 3)
            return true;
        break;
   
    }
    return false;
}

int O::GetLoai()
{
    return 1;
}

bool O::TuongThich(int mau, int RH)
{
    if (this->GetRh() == 0)
    {
        if (mau == 1 && RH == 0)
            return true;
    }
    else if (this->GetRh() == 1)
    {
        if (mau == 1)
            return true;
    }
    return false;
}
