#include <iostream>
#include <iomanip>  // Untuk setprecision

using namespace std;

// Fungsi untuk menghitung BMR (percabangan berdasarkan jenis kelamin)
double hitungBMR(int umur, double berat, double tinggi, char jenisKelamin) {
    double bmr;
    if (jenisKelamin == 'P' || jenisKelamin == 'p') {
        // Rumus pria
        bmr = 10 * berat + 6.25 * tinggi - 5 * umur + 5;
    } else if (jenisKelamin == 'W' || jenisKelamin == 'w') {
        // Rumus wanita
        bmr = 10 * berat + 6.25 * tinggi - 5 * umur - 161;
    } else {
        cout << "Jenis kelamin tidak valid!" << endl;
        return -1;  // Error
    }
    return bmr;
}

// Fungsi untuk menghitung TDEE dan rekomendasi makro (perulangan for untuk rentang %)
void hitungTDEEdanMakro(int umur, double berat, double tinggi, char jenisKelamin, int levelAktivitas) {
    double bmr = hitungBMR(umur, berat, tinggi, jenisKelamin);
    if (bmr == -1) return;
    
    // Faktor aktivitas (percabangan if-else)
    double faktor;
    if (levelAktivitas == 1) faktor = 1.2;      // Sedentary
    else if (levelAktivitas == 2) faktor = 1.375;  // Light
    else if (levelAktivitas == 3) faktor = 1.55;   // Moderate
    else if (levelAktivitas == 4) faktor = 1.725;  // Active
    else {
        cout << "Level aktivitas tidak valid!" << endl;
        return;
    }
    
    double tdee = bmr * faktor;
    double protein = berat * 1.0;  // 1g/kg berat badan
    double serat = 25 + (umur / 10);  // Aproksimasi 25-30g + penyesuaian umur
    
    cout << fixed << setprecision(0);
    cout << "BMR (Kalori dasar): " << bmr << " kcal/hari" << endl;
    cout << "TDEE (Kalori harian): " << tdee << " kcal/hari" << endl;
    cout << "Rekomendasi Protein: " << protein << " g/hari (1g/kg berat)" << endl;
    cout << "Rekomendasi Serat: " << serat << " g/hari" << endl;
    
    // Perulangan for untuk hitung rentang karbo dan lemak (% dari TDEE)
    cout << "Rekomendasi Karbohidrat (45-65% TDEE):" << endl;
    for (int persen = 45; persen <= 65; persen += 20) {
        double karboKcal = tdee * (persen / 100.0);
        double karboG = karboKcal / 4;  // 1g karbo = 4 kcal
        cout << "  - " << persen << "%: " << fixed << setprecision(0) << karboG << " g/hari" << endl;
    }
    
    cout << "Rekomendasi Lemak (20-35% TDEE):" << endl;
    for (int persen = 20; persen <= 35; persen += 15) {
        double lemakKcal = tdee * (persen / 100.0);
        double lemakG = lemakKcal / 9;  // 1g lemak = 9 kcal
        cout << "  - " << persen << "%: " << fixed << setprecision(0) << lemakG << " g/hari" << endl;
    }
}

int main() {
    int pilihan;
    int umur;
    double berat, tinggi;
    char jenisKelamin;
    int levelAktivitas;
    
    cout << "KALKULATOR NUTRISI HARIAN" << endl;
    cout << "Hitung kebutuhan nutrisi berdasarkan umur, berat, tinggi, dan jenis kelamin." << endl;
    cout << "Pilih perhitungan:" << endl;
    cout << "1. BMR (Basal Metabolic Rate)" << endl;
    cout << "2. TDEE & Rekomendasi Makronutrien" << endl;
    cout << "3. Semua Perhitungan (Kombinasi BMR + TDEE + Makro)" << endl;
    cout << "0. Kembali ke Menu Utama" << endl;
    
    // Perulangan do-while utama: Menu berulang selamanya (kembali ke menu setelah opsi 0 atau perhitungan)
    while (true) {
        cout << "\nMasukkan pilihan (0-3): ";
        cin >> pilihan;
        
        // Percabangan switch untuk memilih perhitungan
        switch (pilihan) {
            case 1:  // BMR
                cout << "Masukkan umur (tahun): ";
                cin >> umur;
                cout << "Masukkan berat (kg): ";
                cin >> berat;
                cout << "Masukkan tinggi (cm): ";
                cin >> tinggi;
                cout << "Jenis kelamin (P untuk Pria, W untuk Wanita): ";
                cin >> jenisKelamin;
                
                // Perulangan while untuk validasi jenis kelamin
                while (jenisKelamin != 'P' && jenisKelamin != 'p' && jenisKelamin != 'W' && jenisKelamin != 'w') {
                    cout << "Input jenis kelamin tidak valid! Masukkan P atau W: ";
                    cin >> jenisKelamin;
                }
                
                if (umur > 0 && berat > 0 && tinggi > 0) {
                    double bmr = hitungBMR(umur, berat, tinggi, jenisKelamin);
                    if (bmr != -1) {
                        cout << fixed << setprecision(0);
                        cout << "BMR Anda: " << bmr << " kcal/hari" << endl;
                        cout << "Perhitungan Kalkulator Nutrisi Harian Berhasil, Terimakasih" << endl;
                    }
                } else {
                    cout << "Input tidak valid! Umur, berat, dan tinggi harus >0." << endl;
                    cout << "Perhitungan Kalkulator Nutrisi Harian Berhasil, Terimakasih" << endl;  // Tetap tampilkan meski error
                }
                break;
                
            case 2:  // TDEE & Makro
                cout << "Masukkan umur (tahun): ";
                cin >> umur;
                cout << "Masukkan berat (kg): ";
                cin >> berat;
                cout << "Masukkan tinggi (cm): ";
                cin >> tinggi;
                cout << "Jenis kelamin (P untuk Pria, W untuk Wanita): ";
                cin >> jenisKelamin;
                
                // Validasi jenis kelamin dengan while
                while (jenisKelamin != 'P' && jenisKelamin != 'p' && jenisKelamin != 'W' && jenisKelamin != 'w') {
                    cout << "Input jenis kelamin tidak valid! Masukkan P atau W: ";
                    cin >> jenisKelamin;
                }
                
                cout << "Level aktivitas (1: Sedentary, 2: Light, 3: Moderate, 4: Active): ";
                cin >> levelAktivitas;
                
                if (umur > 0 && berat > 0 && tinggi > 0 && (levelAktivitas >= 1 && levelAktivitas <= 4)) {
                    hitungTDEEdanMakro(umur, berat, tinggi, jenisKelamin, levelAktivitas);
                    cout << "Perhitungan Kalkulator Nutrisi Harian Berhasil, Terimakasih" << endl;
                } else {
                    cout << "Input tidak valid!" << endl;
                    cout << "Perhitungan Kalkulator Nutrisi Harian Berhasil, Terimakasih" << endl;  // Tetap tampilkan meski error
                }
                break;
                
            case 3:  // Semua (kombinasi BMR + TDEE + Makro)
                cout << "Masukkan umur (tahun): ";
                cin >> umur;
                cout << "Masukkan berat (kg): ";
                cin >> berat;
                cout << "Masukkan tinggi (cm): ";
                cin >> tinggi;
                cout << "Jenis kelamin (P untuk Pria, W untuk Wanita): ";
                cin >> jenisKelamin;
                
                while (jenisKelamin != 'P' && jenisKelamin != 'p' && jenisKelamin != 'W' && jenisKelamin != 'w') {
                    cout << "Input jenis kelamin tidak valid! Masukkan P atau W: ";
                    cin >> jenisKelamin;
                }
                
                cout << "Level aktivitas (1: Sedentary, 2: Light, 3: Moderate, 4: Active): ";
                cin >> levelAktivitas;
                
                if (umur > 0 && berat > 0 && tinggi > 0 && (levelAktivitas >= 1 && levelAktivitas <= 4)) {
                    // Hitung BMR
                    double bmr = hitungBMR(umur, berat, tinggi, jenisKelamin);
                    if (bmr != -1) {
                        cout << fixed << setprecision(0);
                        cout << "BMR Anda: " << bmr << " kcal/hari" << endl;
                    }
                    
                    // Hitung TDEE dan Makro
                    hitungTDEEdanMakro(umur, berat, tinggi, jenisKelamin, levelAktivitas);
                    cout << "Perhitungan Kalkulator Nutrisi Harian Berhasil, Terimakasih" << endl;
                } else {
                    cout << "Input tidak valid!" << endl;
                    cout << "Perhitungan Kalkulator Nutrisi Harian Berhasil, Terimakasih" << endl;  // Tetap tampilkan meski error
                }
                break;
                
            case 0:  // Kembali ke Menu Utama
                cout << "Kembali ke menu utama." << endl;
                // Loop akan berlanjut secara otomatis, kembali meminta input pilihan
                break;
                
            default:  // Input salah
                cout << "Pilihan tidak valid! Pilih 0-3." << endl;
                break;
        }
    }
    
    return 0;
}
