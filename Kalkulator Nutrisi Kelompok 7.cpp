#include <iostream>
#include <iomanip>  // Untuk setprecision
#include <cstdlib>  // Untuk system()
#include <limits>   // Untuk numeric_limits

using namespace std;

// Fungsi untuk menghitung BMR (percabangan berdasarkan jenis kelamin)
double hitungBMR(int umur, double berat, double tinggi, char jenisKelamin) {
    double bmr;
    if (jenisKelamin == 'L' || jenisKelamin == 'l') {
        // Rumus pria
        bmr = 10 * berat + 6.25 * tinggi - 5 * umur + 5;
    } else if (jenisKelamin == 'P' || jenisKelamin == 'p') {
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
    
    cout << endl;  // Spasi sebelum output hasil
    cout << fixed << setprecision(0);
    cout << "BMR (Kalori dasar): " << bmr << "kcal/hari" << endl;
    cout << "TDEE (Kalori harian): " << tdee << "kcal/hari" << endl;
    cout << "Rekomendasi Protein: " << protein << "g/hari" << endl;
    cout << "Rekomendasi Serat: " << serat << "g/hari" << endl;
    cout << endl;  // Spasi setelah output hasil
    
    // Perulangan for untuk hitung rentang karbo dan lemak (% dari TDEE)
    cout << "Rekomendasi Karbohidrat :" << endl;
    for (int persen = 45; persen <= 65; persen += 20) {
        double karboKcal = tdee * (persen / 100.0);
        double karboG = karboKcal / 4;  // 1g karbo = 4 kcal
        cout << "  - " << persen << "%: " << fixed << setprecision(0) << karboG << "g/hari" << endl;
    }
    cout << endl;  // Spasi setelah rekomendasi karbo
    
    cout << "Rekomendasi Lemak :" << endl;
    for (int persen = 20; persen <= 35; persen += 15) {
        double lemakKcal = tdee * (persen / 100.0);
        double lemakG = lemakKcal / 9;  // 1g lemak = 9 kcal
        cout << "  - " << persen << "%: " << fixed << setprecision(0) << lemakG << "g/hari" << endl;
    }
    cout << endl;  // Spasi setelah rekomendasi lemak
}

int main() {
    while (true) {  // Loop untuk menu awal
        system("cls");  // Membersihkan layar sebelum menampilkan menu awal
        cout << "=====================================" << endl;
        cout << "       KALKULATOR NUTRISI HARIAN     " << endl;
        cout << "=====================================" << endl;
        cout << "Hitung kebutuhan nutrisi berdasarkan umur," << endl;
        cout << "berat, tinggi, dan jenis kelamin." << endl;
        cout << "=====================================" << endl << endl;
        
        int pilihanAwal;
        cout << endl;  // Spasi sebelum pilihan opsi
        cout << "Pilih opsi:" << endl;
        cout << "1. Menu Utama" << endl;
        cout << "2. Keluar" << endl;
        cout << "Masukkan pilihan (1-2): ";
        if (!(cin >> pilihanAwal)) {  // Penanganan input invalid
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore input salah
            cout << endl;  // Spasi untuk kebersihan
            cout << "Input tidak valid! Silakan coba lagi." << endl;
            continue;  // Kembali ke awal loop
        }
        
        if (pilihanAwal == 2) {
            cout << endl;  // Spasi sebelum pesan keluar
            cout << "Terima kasih telah menggunakan Kalkulator Nutrisi Harian!" << endl;
            return 0;  // Keluar dari program
        } else if (pilihanAwal == 1) {
            // Masuk ke loop menu utama
            int pilihan;
            int umur;
            double berat, tinggi;
            char jenisKelamin;
            int levelAktivitas;
            
            while (true) {  // Loop untuk menu utama
                system("cls");  // Membersihkan layar sebelum menampilkan menu
                cout << "\n=== KALKULATOR NUTRISI HARIAN ===" << endl;
                cout << endl;  // Spasi tambahan
                cout << "Hitung kebutuhan nutrisi berdasarkan umur, berat, tinggi, dan jenis kelamin." << endl;
                cout << endl;  // Spasi sebelum pilihan
                cout << "Pilih perhitungan:" << endl;
                cout << "1. BMR (Basal Metabolic Rate)" << endl;
                cout << "2. TDEE & Rekomendasi Makronutrien" << endl;
                cout << "3. Semua Perhitungan (Kombinasi BMR + TDEE + Makro)" << endl;
                cout << "0. Kembali ke Menu Awal" << endl;
                cout << endl;  // Spasi sebelum input
                cout << "Masukkan pilihan (0-3): ";
                if (!(cin >> pilihan)) {  // Penanganan input invalid
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl;
                    cout << "Input tidak valid! Silakan coba lagi." << endl;
                    continue;  // Kembali ke awal loop ini
                }
                
                if (pilihan == 0) {
                    cout << endl;  // Spasi sebelum pesan
                    cout << "Kembali ke menu awal..." << endl;
                    break;  // Keluar dari loop menu utama, kembali ke loop menu awal
                }
                
                switch (pilihan) {
                    case 1:  // BMR
                        cout << endl;  // Spasi sebelum input
                        cout << "Masukkan umur (tahun): ";
                        if (!(cin >> umur)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Masukkan berat (kg): ";
                        if (!(cin >> berat)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Masukkan tinggi (cm): ";
                        if (!(cin >> tinggi)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Jenis kelamin (L/P): ";
                        cin >> jenisKelamin;
                        
                        while (jenisKelamin != 'L' && jenisKelamin != 'l' && jenisKelamin != 'P' && jenisKelamin != 'p') {
                            cout << "Input jenis kelamin tidak valid! Masukkan L atau P: ";
                            cin >> jenisKelamin;
                        }
                        
                        if (umur > 0 && berat > 0 && tinggi > 0) {
                            double bmr = hitungBMR(umur, berat, tinggi, jenisKelamin);
                            if (bmr != -1) {
                                cout << endl;  // Spasi sebelum output hasil
                                cout << fixed << setprecision(0);
                                cout << "BMR Anda: " << bmr << "kcal/hari" << endl;
                            }
                        } else {
                            cout << endl;
                            cout << "Input tidak valid! Umur, berat, dan tinggi harus >0." << endl;
                        }
                        cout << endl;  // Spasi sebelum pesan kembali
                        cout << "Tekan Enter untuk kembali ke menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();  // Menunggu Enter
                        break;
                        
                    case 2:  // TDEE & Makro
                        cout << endl;  // Spasi sebelum input
                        cout << "Masukkan umur (tahun): ";
                        if (!(cin >> umur)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Masukkan berat (kg): ";
                        if (!(cin >> berat)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Masukkan tinggi (cm): ";
                        if (!(cin >> tinggi)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Jenis kelamin (L/P): ";
                        cin >> jenisKelamin;
                        
                        while (jenisKelamin != 'L' && jenisKelamin != 'l' && jenisKelamin != 'P' && jenisKelamin != 'p') {
                            cout << "Input jenis kelamin tidak valid! Masukkan L atau P: ";
                            cin >> jenisKelamin;
                        }
                        
                        cout << endl;  // Spasi sebelum level aktivitas
                        cout << "Level aktivitas:" << endl;
                        cout << "1: Kurang Aktif" << endl;
                        cout << "2: Ringan" << endl;
                        cout << "3: Sedang" << endl;
                        cout << "4: Aktif" << endl;
                        cout << "Masukkan level aktivitas (1-4): ";
                        if (!(cin >> levelAktivitas)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        
                        if (umur > 0 && berat > 0 && tinggi > 0 && (levelAktivitas >= 1 && levelAktivitas <= 4)) {
                            hitungTDEEdanMakro(umur, berat, tinggi, jenisKelamin, levelAktivitas);
                        } else {
                            cout << endl;
                            cout << "Input tidak valid!" << endl;
                        }
                        cout << endl;  // Spasi sebelum pesan kembali
                        cout << "Tekan Enter untuk kembali ke menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();  // Menunggu Enter
                        break;
                        
                    case 3:  // Semua (kombinasi BMR + TDEE + Makro)
                        cout << endl;  // Spasi sebelum input
                        cout << "Masukkan umur (tahun): ";
                        if (!(cin >> umur)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Masukkan berat (kg): ";
                        if (!(cin >> berat)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Masukkan tinggi (cm): ";
                        if (!(cin >> tinggi)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        cout << "Jenis kelamin (L/P): ";
                        cin >> jenisKelamin;
                        
                        while (jenisKelamin != 'L' && jenisKelamin != 'l' && jenisKelamin != 'P' && jenisKelamin != 'p') {
                            cout << "Input jenis kelamin tidak valid! Masukkan L atau P: ";
                            cin >> jenisKelamin;
                        }
                        
                        cout << endl;  // Spasi sebelum level aktivitas
                        cout << "Level aktivitas:" << endl;
                        cout << "1: Kurang Aktif" << endl;
                        cout << "2: Ringan" << endl;
                        cout << "3: Sedang" << endl;
                        cout << "4: Aktif" << endl;
                        cout << "Masukkan level aktivitas (1-4): ";
                        if (!(cin >> levelAktivitas)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
                        
                        if (umur > 0 && berat > 0 && tinggi > 0 && (levelAktivitas >= 1 && levelAktivitas <= 4)) {
                            double bmr = hitungBMR(umur, berat, tinggi, jenisKelamin);
                            if (bmr != -1) {
                                cout << endl;  // Spasi sebelum output
                                cout << fixed << setprecision(0);
                                cout << "BMR Anda: " << bmr << "kcal/hari" << endl;
                            }
                            hitungTDEEdanMakro(umur, berat, tinggi, jenisKelamin, levelAktivitas);
                        } else {
                            cout << endl;
                            cout << "Input tidak valid!" << endl;
                        }
                        cout << endl;  // Spasi sebelum pesan kembali
                        cout << "Tekan Enter untuk kembali ke menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();  // Menunggu Enter
                        break;
                        
                    default:  // Input salah
                        cout << endl;
                        cout << "Pilihan tidak valid! Pilih 0-3." << endl;
                        break;
                }
            }
        } else {
            cout << endl;
            cout << "Pilihan tidak valid! Keluar dari program." << endl;
            return 0;
        }
    }
    
    return 0;
}
