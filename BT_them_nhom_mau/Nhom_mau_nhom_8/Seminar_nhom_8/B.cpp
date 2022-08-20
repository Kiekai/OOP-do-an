#include "B.h"

B::B(){}

B::~B(){}

bool B::KiemTra(int me, int con)
{
    switch (me)
    {

    case 1:
        if (con == 3 || con == 1)
            return true;
        break;

    case 2:
        if (con == 2 || con == 1 || con == 3 || con == 4)
            return true;
        break;
        
    case 3:
        if (con == 3 || con == 1)
            return true;
        break;
    case 4:
        if (con == 2 || con == 3 || con == 4)
            return true;
        break;
    
    }
    return false;
}

int B::GetLoai()
{
    return 3;
}

bool B::TuongThich(int mau, int RH)
{
    if (this->GetRh() == 0)
    {
        if (mau == 1 && RH == 0 || mau == 3 && RH == 0)
            return true;
    }
    if (this->GetRh() == 1)
    {
        if (mau == 1 || mau == 3)
            return true;
    }
    return false;
}

