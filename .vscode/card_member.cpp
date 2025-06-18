#include <iostream>
#include <string>
using namespace std;

int hitungDiskon(bool isMember, int totalHarga) {
    if (!isMember) return 0;

    if (totalHarga > 200000)
        return totalHarga * 10 / 100;
    else if (totalHarga > 100000)
        return totalHarga * 5 / 100;
    else
        return totalHarga * 2 / 100;
}

bool tanyaMember() {
    string jawaban;
    cout << "Apakah pelanggan memiliki member card? (YA/TIDAK): ";
    cin >> jawaban;

    for (char &c : jawaban) c = toupper(c); 
    return (jawaban == "YA");
}

int main() {
    int totalHarga = 250000;
    bool isMember = tanyaMember();

    int diskon = hitungDiskon(isMember, totalHarga);
    int hargaSetelahDiskon = totalHarga - diskon;

    cout << "Total belanja : Rp" << totalHarga << "\n";
    if (isMember) {
        cout << "Diskon member: Rp" << diskon << "\n";
    } else {
        cout << "Bukan member, tidak ada diskon.\n";
    }

    cout << "Total bayar   : Rp" << hargaSetelahDiskon << "\n";

    return 0;
}
