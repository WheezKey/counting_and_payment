#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iomanip>
using namespace std;

struct Barang {
    int kode;
    string nama;
    int harga;
    int stok;
    int diskonPersen; // diskon khusus per barang
};

struct TransaksiItem {
    int kodeBarang;
    int jumlah;
    int subtotalSebelumDiskon;
    int subtotalSetelahDiskon;
};

struct Member {
    string id;
    string nama;
    int poin;
};

int hitungDiskonBarang(int harga, int persen) {
    return harga * persen / 100;
}

// Simulasi input member via QR Scan
Member inputMemberQR() {
    Member m;
    cout << "Scan QR / Masukkan ID Member: ";
    cin >> m.id;

    // Simulasi database member
    unordered_map<string, string> dbMember = {
        {"M001", "Ali"},
        {"M002", "Budi"},
        {"M003", "Cici"}
    };

    if (dbMember.find(m.id) != dbMember.end()) {
        m.nama = dbMember[m.id];
        m.poin = 0; // Akan ditambahkan setelah transaksi
        cout << "✔️ Member terdeteksi: " << m.nama << "\n";
    } else {
        m.id = "";
        m.nama = "Bukan Member";
        m.poin = 0;
        cout << "❗ID tidak ditemukan. Transaksi non-member.\n";
    }

    return m;
}

// Menghitung poin belanja (misal: Rp10.000 = 1 poin)
int hitungPoin(int totalBayar) {
    return totalBayar / 10000;
}

// Cetak detail transaksi
void cetakTransaksi(const vector<TransaksiItem>& items, const vector<Barang>& daftarBarang, int total, int totalSetelahDiskon) {
    cout << "\n=== STRUK ===\n";
    cout << left << setw(20) << "Nama Barang" << setw(10) << "Qty" << setw(10) << "Harga" << setw(10) << "Diskon" << "Subtotal\n";
    for (const auto& item : items) {
        const Barang& b = daftarBarang[item.kodeBarang];
        int diskonBarang = b.diskonPersen;
        int potongan = hitungDiskonBarang(b.harga * item.jumlah, diskonBarang);
        cout << left << setw(20) << b.nama
             << setw(10) << item.jumlah
             << "Rp" << setw(8) << b.harga
             << diskonBarang << "%   "
             << "Rp" << item.subtotalSetelahDiskon << "\n";
    }
    cout << "-----------------------------\n";
    cout << "Total Sebelum Diskon: Rp" << total << "\n";
    cout << "Total Setelah Diskon: Rp" << totalSetelahDiskon << "\n";
}

int main() {
    vector<Barang> daftarBarang = {
        {0, "Beras 5kg", 60000, 10, 5},
        {1, "Minyak 2L", 35000, 20, 0},
        {2, "Gula 1kg", 15000, 15, 10},
        {3, "Telur 1kg", 28000, 25, 3}
    };

    vector<TransaksiItem> transaksi;
    Member pembeli = inputMemberQR();
    char lanjut;
    int totalSebelumDiskon = 0;
    int totalSetelahDiskon = 0;

    do {
        cout << "\nDaftar Barang:\n";
        for (const auto& b : daftarBarang) {
            cout << "[" << b.kode << "] " << b.nama
                 << " - Rp" << b.harga
                 << " - Diskon " << b.diskonPersen << "%"
                 << " - Stok: " << b.stok << "\n";
        }

        int kode, jumlah;
        cout << "Masukkan kode barang: ";
        cin >> kode;
        if (kode < 0 || kode >= daftarBarang.size()) {
            cout << "❗Kode tidak valid.\n";
            continue;
        }

        cout << "Jumlah beli: ";
        cin >> jumlah;

        if (jumlah > daftarBarang[kode].stok) {
            cout << "❗Stok tidak cukup.\n";
            continue;
        }

        Barang& b = daftarBarang[kode];
        b.stok -= jumlah;
        int subtotal = b.harga * jumlah;
        int diskon = hitungDiskonBarang(subtotal, b.diskonPersen);
        int bayarSetelahDiskon = subtotal - diskon;

        transaksi.push_back({kode, jumlah, subtotal, bayarSetelahDiskon});
        totalSebelumDiskon += subtotal;
        totalSetelahDiskon += bayarSetelahDiskon;

        cout << "✔️ Ditambahkan: " << b.nama << " x" << jumlah << " = Rp" << bayarSetelahDiskon << "\n";
        cout << "Tambah barang lain? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');

    // STRUK
    cetakTransaksi(transaksi, daftarBarang, totalSebelumDiskon, totalSetelahDiskon);

    cout << "\nTotal dibayar Rp" << totalSetelahDiskon << "\n";

    if (!pembeli.id.empty()) {
        int poinBaru = hitungPoin(totalSetelahDiskon);
        pembeli.poin += poinBaru;
        cout << "🎉 Selamat! Anda mendapat " << poinBaru << " poin.\n";
        cout << "Total Poin Sekarang: " << pembeli.poin << "\n";
    }

    cout << "=== Terima kasih ===\n";
    return 0;
}
