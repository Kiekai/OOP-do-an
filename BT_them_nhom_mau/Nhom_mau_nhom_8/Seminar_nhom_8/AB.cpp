#include "AB.h"

AB::AB(){}

AB::~AB(){}

bool AB::KiemTra(int me, int con)
{
    switch (me)
    {

    case 1:
        if (con == 2 || con == 3)
            return true;
        break;

    case 2:
        if (con == 2 || con == 3 || con == 4)
            return true;
        break;
        
    case 3:
        if (con == 2 || con == 3 || con == 4)
            return true;
        break;

    case 4:
        if (con == 2 || con == 3 || con == 4)
            return true;
        break;
    }
    return false;
}

int AB::GetLoai()
{
    return 4;
}

bool AB::TuongThich(int mau, int RH)
{
    if (this->GetRh() == 0)
    {
        if ((((mau == 1 || mau == 2) || mau == 3) || mau == 4) && RH == 0)
            return true;
    }
    else if (this->GetRh() == 1)
    {
        return true;
    }
    return false;
}

