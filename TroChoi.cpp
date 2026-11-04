#include "TroChoi.h"

#include <iostream>
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
              << "Het mang se thua.\n";
}

void TroChoi::batDauTroChoi() const {
    std::cout << "\n===== BAT DAU TRO CHOI =====\n"
              << "Ban do da chon: " << tenBanDo << '\n'
              << "Do kho da chon: " << doKho << '\n'
              << "Chuc nang choi game se duoc phat trien o giai doan tiep theo.\n";
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
                batDauTroChoi();
                dangChay = choQuayVeMenu();
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
