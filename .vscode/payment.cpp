#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Barang {
    int kode;
    string nama;
    int harga;
    int stok;
};

void tampilkanBarang(const vector<Barang>& daftar) {
    cout << "\n=== Daftar Barang ===\n";
    cout << left << setw(10) << "Kode" << setw(20) << "Nama" << setw(10) << "Harga" << "Stok\n";
    for (const auto& b : daftar) {
        cout << left << setw(10) << b.kode
             << setw(20) << b.nama
             << "Rp" << setw(8) << b.harga
             << b.stok << endl;
    }
    cout << "======================\n";
}

int cariBarang(const vector<Barang>& daftar, int kode) {
    for (size_t i = 0; i < daftar.size(); ++i) {
        if (daftar[i].kode == kode)
            return i;
    }
    return -1;
}

int main() {
    vector<Barang> daftarBarang = {
        {101, "Beras 5kg", 60000, 10},
        {102, "Minyak 2L", 35000, 20},
        {103, "Gula 1kg", 15000, 15},
        {104, "Telur 1kg", 28000, 25}
    };

    vector<pair<int, int>> transaksi;
    char lanjut;
    int totalHarga = 0;

    cout << "=== Sumber Jaya ===\n";

    do {
        tampilkanBarang(daftarBarang);
        int kode, jumlah;
        cout << "\nMasukkan kode barang yang ingin dibeli: ";
        cin >> kode;

        int idx = cariBarang(daftarBarang, kode);
        if (idx == -1) {
            cout << "❗Kode barang tidak ditemukan!\n";
            continue;
        }

        cout << "Masukkan jumlah yang ingin dibeli: ";
        cin >> jumlah;

        if (jumlah > daftarBarang[idx].stok) {
            cout << "❗Stok tidak cukup. Sisa stok: " << daftarBarang[idx].stok << "\n";
            continue;
        }

        daftarBarang[idx].stok -= jumlah; 
        transaksi.emplace_back(kode, jumlah);
        int subtotal = daftarBarang[idx].harga * jumlah;
        totalHarga += subtotal;

        cout << "✔️ " << daftarBarang[idx].nama << " x" << jumlah << " = Rp" << subtotal << "\n";

        cout << "Ingin beli barang lain? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');

    cout << "\n=== Struk Pembelian ===\n";
    cout << left << setw(20) << "Nama Barang" << setw(10) << "Jumlah" << setw(10) << "Subtotal\n";

    for (const auto& t : transaksi) {
        int idx = cariBarang(daftarBarang, t.first);
        int subtotal = daftarBarang[idx].harga * t.second;
        cout << left << setw(20) << daftarBarang[idx].nama
             << setw(10) << t.second
             << "Rp" << subtotal << "\n";
    }

    cout << "-----------------------------\n";
    cout << "Total Bayar: Rp" << totalHarga << "\n";

    int uangDibayar;
    cout << "Masukkan uang dibayar: Rp";
    cin >> uangDibayar;

    if (uangDibayar < totalHarga) {
        cout << "❗Uang tidak cukup. Transaksi dibatalkan.\n";
        return 1;
    }

    int kembalian = uangDibayar - totalHarga;
    cout << "Kembalian: Rp" << kembalian << "\n";
    cout << "=== Terima kasih! ===\n";

    return 0;
}
