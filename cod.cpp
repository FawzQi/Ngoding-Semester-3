#include <iostream>
#include <vector>

using namespace std;

int main() {
    int M, N, P;
    cin >> M >> N;

    // PETA
    vector<vector<char>> peta(M, vector<char>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> peta[i][j];
        }
    }

    cin >> P;

    // Input gerak robot
    vector<char> gerakan(P);
    for (int i = 0; i < P; i++) {
        cin >> gerakan[i];
    }

    // Posisi (S)
    int SX = -1, SY = -1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (peta[i][j] == 'S') {
                SX = i;
                SY = j;
                break;
            }
        }
    }

    if (SX == -1 || SY == -1) {
        cout << "Posisi awal robot tidak ditemukan" << endl;
        return 0;
    }

    bool bisaLewatDinding = false;
    bool kecepatanGanda = false;
    int waktuTempuh = 0;

    for (int i = 0; i < P; i++) {
        char arah = gerakan[i];

        // Gerakan berdasarkan arah
        if (arah == 'U')
            SX--;  // Gerak ke atas
        else if (arah == 'D')
            SX++;  // Gerak ke bawah
        else if (arah == 'L')
            SY--;  // Gerak ke kiri
        else if (arah == 'R')
            SY++;  // Gerak ke kanan

        // Cek apakah robot keluar dari batas peta
        if (SX < 0 || SX >= M || SY < 0 || SY >= N) {
            cout << "robot nabrak, silahkan diperbaiki" << endl;
            cout << "Waktu tempuh: " << waktuTempuh << " menit" << endl;
            return 0;
        }

        // Cek simbol pada posisi yang ditempati robot
        char simbol = peta[SX][SY];

        // Penanganan simbol pada peta
        if (simbol == 'x' && !bisaLewatDinding) {
            cout << "robot nabrak, silahkan diperbaiki" << endl;
            cout << "Waktu tempuh: " << waktuTempuh << " menit" << endl;
            return 0;
        } else if (simbol == 'F') {
            cout << "robot berhasil mencapai tujuan" << endl;
            cout << "Waktu tempuh: " << waktuTempuh + 1 << " menit" << endl;  // Tambahkan 1 menit untuk langkah terakhir
            return 0;
        } else if (simbol == 'M') {
            bisaLewatDinding = true;
            cout << "bertemu dengan mekanik, siap membasmi rintangan" << endl;
        } else if (simbol == 'E') {
            kecepatanGanda = true;
            cout << "bertemu dengan electrical, kecepatan roda menjadi 200%" << endl;
        } else if (simbol == 'P') {
            cout << "bertemu dengan programing, programing menyapa robot" << endl;
        } else if (simbol == 'O') {
            waktuTempuh *= 2;  // Mengalikan waktu tempuh sebelum bertemu Official
            cout << "bertemu dengan official, diajak ngonten bareng" << endl;
        }

        waktuTempuh++;  // Tambah 1 menit untuk setiap gerakan

        // Jika robot memiliki kecepatan ganda (dari electrical), lakukan gerakan ekstra
        if (kecepatanGanda && i + 1 < P) {
            i++;  // Melewati langkah berikutnya (kecepatan 2x)
            if (arah == 'U')
                SX--;
            else if (arah == 'D')
                SX++;
            else if (arah == 'L')
                SY--;
            else if (arah == 'R')
                SY++;

            // Cek jika keluar batas lagi
            if (SX < 0 || SX >= M || SY < 0 || SY >= N) {
                cout << "robot nabrak, silahkan diperbaiki" << endl;
                cout << "Waktu tempuh: " << waktuTempuh << " menit" << endl;
                return 0;
            }

            simbol = peta[SX][SY];

            if (simbol == 'x' && !bisaLewatDinding) {
                cout << "robot nabrak, silahkan diperbaiki" << endl;
                cout << "Waktu tempuh: " << waktuTempuh << " menit" << endl;
                return 0;
            } else if (simbol == 'F') {
                cout << "robot berhasil mencapai tujuan" << endl;
                cout << "Waktu tempuh: " << waktuTempuh + 1 << " menit" << endl;
                return 0;
            }

            kecepatanGanda = false;  // Reset kecepatan ganda setelah gerakan ekstra
        }
    }

    cout << "robot gagal mencapai tujuan" << endl;
    cout << "Waktu tempuh: " << waktuTempuh << " menit" << endl;

    return 0;
}
// 4 4
// S..M
// xxxx
// PPPP
// FEOx
// 9
// RRRDDDLLL