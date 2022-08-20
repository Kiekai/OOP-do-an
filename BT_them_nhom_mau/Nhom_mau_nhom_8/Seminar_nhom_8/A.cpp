#include "A.h"

A ::A() {}

A ::~A() {}

bool A::KiemTra(int me, int con)
{
    switch (me)
    {

    case 1:
        if (con == 2 || con == 1)
            return true;
        break;

    case 2:
        if (con == 2 || con == 1)
            return true;
        break;

    case 3:
        if (con == 2 || con == 1 || con == 3 || con == 4)
            return true;
        break;

    case 4:
        if (con == 2 || con == 3 || con == 4)
            return true;
        break;
    }
    return false;
}

int A::GetLoai()
{
    return 2;
}

bool A::TuongThich(int mau, int RH)
{
    if (this->GetRh() == 0)
    {
        if (mau == 1 && RH == 0 || mau == 2 && RH == 0)
            return true;
    }
    else if (this->GetRh() == 1)
    {
        if (mau == 1 || mau == 2)
            return true;
    }
    return false;
}



