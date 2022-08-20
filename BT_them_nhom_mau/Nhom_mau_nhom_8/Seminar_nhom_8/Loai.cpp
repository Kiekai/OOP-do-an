#include "Loai.h"

Loai ::Loai() 
{
    Rh = 0;
    Ten = "";
}

Loai::~Loai()
{
    Rh = 0;
    Ten = "";
}
void Loai::Nhap()
{
    int t;
    do
    {
        cout << "Nhap Rhesus (1 la RH+, 0 la RH-): ";
        cin >> t;
    } while (t > 1 || t < 0);
    if (t == 1)
        this->Rh = 1;
    else
        this->Rh = 0;
}

void Loai::Nhap_mau_tu_dong()
{
    int t;
    cout << "Nhap Rhesus (1 la RH+, 0 la RH-): ";
    t = 0 + rand() % 2;
    cout << t << endl;
    if (t == 1)
        this->Rh = 1;
    else
        this->Rh = 0;
}

int Loai::GetRh()
{
    return this->Rh;
}

void Loai::setting()
{
    string ho[] = { "Nguyen", "Tran", "Pham", "Do", "Phan", "Le" };
    string ten[] = { "Duy", "Dinh", "Giang", "Kien", "Quyen", "Khai", "Binh" };
    this->Ten = ho[rand() % 6] + " " + ten[rand() % 7] + " ";
}

string Loai::getTen()
{
    return this->Ten;
}