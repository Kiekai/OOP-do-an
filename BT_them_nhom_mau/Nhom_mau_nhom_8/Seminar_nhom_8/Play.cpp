#include "Play.h"

string Play::GetTenLoaiMau(int a)
{
    string s;
    switch (a)
    {
    case 1:
        s = "O";
        break;
    case 2:
        s = "A";
        break;
    case 3:
        s = "B";
        break;
    case 4:
        s = "AB";
        break;
    }
    return s;
}

void Play::Nhap_bang_tay()
{
    ToMau(35, 2, "Nhap so luong nguoi: ", 15);   
    cin >> SoLuong;
    for (int i = 1; i <= SoLuong; i++)
    {
        cout << "Hay chon 1 cho nguoi nhom mau O\n";
        cout << "Hay chon 2 cho nguoi nhom mau A\n";
        cout << "Hay chon 3 cho nguoi nhom mau B\n";
        cout << "Hay chon 4 cho nguoi nhom mau AB\n";
        int choice;
        do
        {
            cin >> choice;
        } while (choice > 4 || choice < 1);
        switch (choice)
        {
        case 1:
            cout << "Nguoi nay co nhom mau O\n";
            nhommau[i] = new O();
            break;
        case 2:
            cout << "Nguoi nay co nhom mau A\n";
            nhommau[i] = new A();
            break;
        case 3:
            cout << "Nguoi nay co nhom mau B\n";
            nhommau[i] = new B();
            break;
        case 4:
            cout << "Nguoi nay co nhom mau AB\n";
            nhommau[i] = new AB();
            break;
        }
        nhommau[i]->Nhap();
        nhommau[i]->setting();
    }
}

void Play::Nhap_tu_dong()
{
    ToMau(35, 2, "Nhap so luong nguoi: ", 15);
    SoLuong = 3 + rand() % 98;
    cout << SoLuong << "\n";
    for (int i = 1; i <= SoLuong; i++)
    {
        cout << "Hay chon 1 cho nguoi nhom mau O\n";
        cout << "Hay chon 2 cho nguoi nhom mau A\n";
        cout << "Hay chon 3 cho nguoi nhom mau B\n";
        cout << "Hay chon 4 cho nguoi nhom mau AB\n";
        int choice;
        choice = 1 + rand() % 4;
        switch (choice)
        {
        case 1:
            cout << "Nguoi nay co nhom mau O\n";
            nhommau[i] = new O();
            break;
        case 2:
            cout << "Nguoi nay co nhom mau A\n";
            nhommau[i] = new A();
            break;
        case 3:
            cout << "Nguoi nay co nhom mau B\n";
            nhommau[i] = new B();
            break;
        case 4:
            cout << "Nguoi nay co nhom mau AB\n";
            nhommau[i] = new AB();
            break;
        }
        nhommau[i]->Nhap_mau_tu_dong();
        nhommau[i]->setting();
    }
}

void Play::Kiemtrachame()
{
    int cha, me, con;
    do
    {
        cout << "Hay nhap so bao danh cha, me, con: ";
        cin >> cha >> me >> con;
    } while (cha > SoLuong || me > SoLuong || con > SoLuong);
    cout << "Nguoi cha co nhom mau: " << GetTenLoaiMau(nhommau[cha]->GetLoai());
    cout << "\nNguoi me co nhom mau: " << GetTenLoaiMau(nhommau[me]->GetLoai());
    cout << "\nNguoi con co nhom mau: " << GetTenLoaiMau(nhommau[con]->GetLoai());
    bool KQ = nhommau[cha]->KiemTra(nhommau[me]->GetLoai(), nhommau[con]->GetLoai());
    if (KQ)
        cout << "\nCon la con RUOT cua cha me\n";
    else
        cout << "\nCon la con DA DAY cua cha me\n";
}

void Play::Kiemtrachonhan()
{
    int x;
    do
    {
        cout << "Nhap so bao danh cua nguoi muon nhan mau: ";
        cin >> x;
    } while (x > SoLuong);
    cout << "Danh sach nhung nguoi co the truyen mau cho nguoi co so bao danh: " << x << " \n";
    cout << "                    -------------------------------------------        \n";
    cout << "                    |     Ho va ten   | Nhom mau  |  SBD | RH |  \n";
    cout << "                    -------------------------------------------        \n";
    int ok = 0;
    for (int i = 1; i <= SoLuong; i++)
    {
        if ((i != x) && (nhommau[x]->TuongThich(nhommau[i]->GetLoai(), nhommau[i]->GetRh())) == true)
        {
            cout << "                    | " << setfill(' ') << setw(15) << nhommau[i]->getTen() << " | " << setfill(' ') << setw(10) << GetTenLoaiMau(nhommau[i]->GetLoai()) << "|" << setfill(' ') << setw(5) << i << " |";
            if (nhommau[i]->GetRh() == 1)
                cout << "  + " << "|\n";
            else if (nhommau[i]->GetRh() == 0)
                cout << "  - " << "|\n";
            cout << "                    -------------------------------------------       \n";
            ok = 1;
        }
    }
    if (!ok)
        cout << "Khong co ai\n";
}

void Play::TaoBang()
{
    cout << "                    -------------------------------------------        \n";
    cout << "                    |     Ho va ten   | Nhom mau  |  SBD | RH |  \n";
    cout << "                    -------------------------------------------        \n";
    for (int i = 1; i <= SoLuong; i ++)
    {
        cout << "                    | " << setfill(' ') << setw(15) << nhommau[i]->getTen() << " | " << setfill(' ') << setw(10) << GetTenLoaiMau(nhommau[i]->GetLoai()) << "|" << setfill(' ') << setw(5) << i << " |";
        if (nhommau[i]->GetRh() == 1)
            cout << "  + " << "|\n";
        else if (nhommau[i]->GetRh() == 0)
            cout << "  - " << "|\n";
        cout << "                    -------------------------------------------       \n";
    }
}

