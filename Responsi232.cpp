#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    float uts;
    float uas;
    float nilai_akhir;
    string status;
};

vector<Mahasiswa> bacaData(const string& filenama) {
    vector<Mahasiswa> data;
    ifstream file(filenama);
    if (!file) {
        cerr << "File tidak dapat dibuka!" << endl;
        return data;
    }

    while (!file.eof()) {
        Mahasiswa mhs;
        file >> mhs.nim >> mhs.nama >> mhs.uts >> mhs.uas;
        if (file.fail()) break;
        data.push_back(mhs);
    }
    file.close();
    return data;
}

int main() {
    vector<Mahasiswa> data = bacaData("data_mahasiswa.txt");

    if (data.empty()) {
        cout << "Data mahasiswa kosong atau gagal membaca file." << endl;
        return 1;
    }

    hitungNilaiAkhir(data);

    string namaCari;
    cout << "Masukkan nama mahasiswa untuk dicari: ";
    cin >> namaCari;

    vector<Mahasiswa> hasilCari = cariBerdasarkanNama(data, namaCari);
    if (!hasilCari.empty()) {
        for (const auto& mhs : hasilCari) {
            cout << "NIM: " << mhs.nim << ", Nama: " << mhs.nama
                 << ", Nilai Akhir: " << mhs.nilai_akhir << ", Status: " << mhs.status << endl;
        }
    } else {
        cout << "Mahasiswa dengan nama " << namaCari << " tidak ditemukan." << endl;
    }

    float nilaiInput;
    cout << "Masukkan nilai minimum untuk mencari nilai terkecil >= nilai tersebut: ";
    cin >> nilaiInput;

    Mahasiswa* terkecil = cariTerkecilBerbasisNilai(data, nilaiInput);
    if (terkecil != nullptr) {
        cout << "Mahasiswa dengan nilai terkecil >= " << nilaiInput << " adalah "
             << terkecil->nama << " dengan nilai " << terkecil->nilai_akhir << endl;
    } else {
        cout << "Tidak ada mahasiswa dengan nilai >= " << nilaiInput << endl;
    }

    urutkanNilai(data, true);
    cout << "\nData urut dari nilai terbesar ke terkecil:" << endl;
    for (const auto& mhs : data) {
        cout << mhs.nama << " - " << mhs.nilai_akhir << endl;
    }

    urutkanNilai(data, false);
    cout << "\nData urut dari nilai terkecil ke terbesar:" << endl;
    for (const auto& mhs : data) {
        cout << mhs.nama << " - " << mhs.nilai_akhir << endl;
    }

    simpanNilaiAkhir(data, "nilai_akhir.txt");
    simpanStatusLulus(data, "status_kelulusan.txt");

    cout << "\nData nilai akhir dan status kelulusan telah disimpan ke file." << endl;

    return 0;
}

