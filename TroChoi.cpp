#include "TroChoi.h"
#include "VanChoi.h"

#include <cctype>
#include <iostream>
#include <random>
#include <sstream>

TroChoi::TroChoi() : tenBanDo("Classic"), doKho("Normal") {
}

void TroChoi::hienThiMenu() const {
    std::cout << "\n===== PAC-MAN CONSOLE =====\n"
              << "Ban do hien tai: " << tenBanDo << '\n'
              << "Do kho hien tai: " << doKho << '\n'
              << "1. Bat dau tro choi\n"
              << "2. Chon ban do\n"
              << "3. Chon do kho\n"
              << "4. Huong dan choi\n"
              << "5. Thoat\n";
}

bool TroChoi::nhapLuaChon(int nhoNhat, int lonNhat, int& luaChon) const {
    std::string dongNhap;

    while (true) {
        std::cout << "Nhap lua chon (" << nhoNhat << '-' << lonNhat << "): ";
        // Ket thuc an toan khi het du lieu nhap, khong lap lai tren EOF.
        if (!std::getline(std::cin, dongNhap)) {
            return false;
        }

        std::istringstream luongNhap(dongNhap);
        int giaTri;
        char kyTuThua;

        // Chi chap nhan mot so nguyen trong khoang, cho phep khoang trang.
        if ((luongNhap >> giaTri) && !(luongNhap >> kyTuThua)
            && giaTri >= nhoNhat && giaTri <= lonNhat) {
            luaChon = giaTri;
            return true;
        }

        std::cout << "Lua chon khong hop le. Vui long nhap lai.\n";
    }
}

bool TroChoi::chonBanDo() {
    std::cout << "\n===== CHON BAN DO =====\n"
              << "1. Classic\n2. Labyrinth\n3. Challenge\n";

    int luaChon;
    if (!nhapLuaChon(1, 3, luaChon)) {
        return false;
    }

    switch (luaChon) {
        case 1: tenBanDo = "Classic"; break;
        case 2: tenBanDo = "Labyrinth"; break;
        case 3: tenBanDo = "Challenge"; break;
    }
    std::cout << "Da chon ban do: " << tenBanDo << '\n';
    return true;
}

bool TroChoi::chonDoKho() {
    std::cout << "\n===== CHON DO KHO =====\n"
              << "1. Easy\n2. Normal\n3. Hard\n";

    int luaChon;
    if (!nhapLuaChon(1, 3, luaChon)) {
        return false;
    }

    switch (luaChon) {
        case 1: doKho = "Easy"; break;
        case 2: doKho = "Normal"; break;
        case 3: doKho = "Hard"; break;
    }
    std::cout << "Da chon do kho: " << doKho << '\n';
    return true;
}

void TroChoi::hienThiHuongDan() const {
    std::cout << "\n===== HUONG DAN CHOI =====\n"
              << "W/A/S/D: Di chuyen Pac-Man.\n"
              << "An cac cham de ghi diem.\n"
              << "Tranh va cham voi Ghost.\n"
              << "An het cham de chien thang.\n"
              << "Het mang se thua.\n"
              << "Nhap mot lenh roi Enter, chap nhan chu hoa/thuong.\n"
              << "Q: Thoat van hien tai, quay ve Menu.\n"
              << "Moi cham: 10 diem. Gap tuong khong tinh luot.\n"
              << "Easy: 5 mang/1 Ghost; Normal: 3 mang/2 Ghost; Hard: 2 mang/3 Ghost.\n";
}

void TroChoi::hienThiVanChoi(const VanChoi& vanChoi) const {
    std::cout << "\n===== PAC-MAN =====\n"
              << "Ban do da chon: " << tenBanDo << '\n'
              << "Do kho da chon: " << doKho << '\n'
              << "Diem: " << vanChoi.layDiemSo()
              << " | Mang: " << vanChoi.laySoMang()
              << " | Cham con lai: " << vanChoi.laySoCham()
              << " | Luot: " << vanChoi.laySoLuot() << '\n';
    for (int hang = 0; hang < vanChoi.layBanDo().laySoHang(); ++hang) {
        for (int cot = 0; cot < vanChoi.layBanDo().laySoCot(); ++cot) {
            std::cout << vanChoi.layKyTuHienThi(hang, cot);
        }
        std::cout << '\n';
    }
}

bool TroChoi::nhapLenh(char& lenh) const {
    std::string dongNhap;
    while (true) {
        std::cout << "Nhap W/A/S/D de di chuyen, Q de ve Menu: ";
        if (!std::getline(std::cin, dongNhap)) {
            return false;
        }
        std::istringstream luongNhap(dongNhap);
        char kyTu;
        char kyTuThua;
        if ((luongNhap >> kyTu) && !(luongNhap >> kyTuThua)) {
            kyTu = static_cast<char>(std::tolower(static_cast<unsigned char>(kyTu)));
            if (kyTu == 'w' || kyTu == 'a' || kyTu == 's' || kyTu == 'd' || kyTu == 'q') {
                lenh = kyTu;
                return true;
            }
        }
        std::cout << "Lenh khong hop le. Vui long nhap lai.\n";
    }
}

bool TroChoi::batDauTroChoi() const {
    std::random_device taoHatGiong;
    VanChoi vanChoi(BanDo(tenBanDo), doKho, taoHatGiong());
    while (true) {
        while (vanChoi.layTrangThai() == TrangThaiVan::DANG_CHOI) {
            hienThiVanChoi(vanChoi);
            char lenh;
            if (!nhapLenh(lenh)) {
                return false;
            }
            if (lenh == 'q') {
                std::cout << "Da thoat van choi.\n";
                return true;
            }
            int soMangCu = vanChoi.laySoMang();
            if (!vanChoi.xuLyLuot(lenh)) {
                std::cout << "Gap tuong, khong the di chuyen.\n";
            } else if (vanChoi.laySoMang() < soMangCu) {
                std::cout << "Va cham Ghost! Mat mot mang.\n";
            }
        }
        hienThiVanChoi(vanChoi);
        if (vanChoi.layTrangThai() == TrangThaiVan::CHIEN_THANG) {
            std::cout << "Chien thang! Da an het cham.\n";
        } else {
            std::cout << "Game Over! Da het mang.\n";
        }
        std::cout << "Diem cuoi cung: " << vanChoi.layDiemSo()
                  << " | So luot da thuc hien: " << vanChoi.laySoLuot()
                  << "\n1. Choi lai\n2. Quay ve Menu\n";
        int luaChon;
        if (!nhapLuaChon(1, 2, luaChon)) {
            return false;
        }
        if (luaChon == 2) {
            return true;
        }
        vanChoi.khoiDongLai();
    }
}

bool TroChoi::choQuayVeMenu() const {
    std::cout << "Nhan Enter de quay ve Menu chinh...";
    std::string dongNhap;
    return static_cast<bool>(std::getline(std::cin, dongNhap));
}

void TroChoi::chay() {
    bool dangChay = true;

    while (dangChay) {
        hienThiMenu();
        int luaChon;
        if (!nhapLuaChon(1, 5, luaChon)) {
            break;
        }

        switch (luaChon) {
            case 1:
                dangChay = batDauTroChoi();
                break;
            case 2:
                dangChay = chonBanDo();
                break;
            case 3:
                dangChay = chonDoKho();
                break;
            case 4:
                hienThiHuongDan();
                dangChay = choQuayVeMenu();
                break;
            case 5:
                dangChay = false;
                break;
        }
    }

    std::cout << "\nDa thoat chuong trinh. Tam biet!\n";
}
