#include "BanDo.h"
#include "Luoi.h"

#include <cassert>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>

void kiemThuLuoi() {
    Luoi<int> luoi(2, 3, 7);
    assert(luoi.laySoHang() == 2 && luoi.laySoCot() == 3);
    for (int hang = 0; hang < 2; ++hang) {
        for (int cot = 0; cot < 3; ++cot) {
            assert(luoi.layGiaTri(hang, cot) == 7);
        }
    }
    luoi.capNhatGiaTri(1, 2, 9);
    assert(luoi.layGiaTri(1, 2) == 9);
    assert(luoi.layGiaTri(0, 2) == 7);
    assert(!luoi.toaDoHopLe(-1, 0) && !luoi.toaDoHopLe(0, -1));
    assert(!luoi.toaDoHopLe(2, 0) && !luoi.toaDoHopLe(0, 3));

    int soNgoaiLe = 0;
    try { luoi.layGiaTri(-1, 0); }
    catch (const std::out_of_range&) { ++soNgoaiLe; }
    try { luoi.capNhatGiaTri(0, 3, 1); }
    catch (const std::out_of_range&) { ++soNgoaiLe; }
    try { Luoi<int> luoiAm(-1, 3, 0); }
    catch (const std::invalid_argument&) { ++soNgoaiLe; }
    try { Luoi<int> luoiAm(2, -1, 0); }
    catch (const std::invalid_argument&) { ++soNgoaiLe; }
    assert(soNgoaiLe == 4);

    Luoi<char> luoiRong(0, 3, ' ');
    assert(luoiRong.laySoHang() == 0 && luoiRong.laySoCot() == 3);
    assert(!luoiRong.toaDoHopLe(0, 0));
    Luoi<char> luoiKhongCot(2, 0, ' ');
    assert(!luoiKhongCot.toaDoHopLe(0, 0));
    Luoi<std::string> luoiChuoi(1, 1, "Mac dinh");
    luoiChuoi.capNhatGiaTri(0, 0, "Moi");
    assert(luoiChuoi.layGiaTri(0, 0) == "Moi");
    std::cout << "PASS Luoi<int>, Luoi<char>, Luoi<string>\n";
}

std::string kiemThuBanDo(const std::string& tenBanDo) {
    BanDo banDo(tenBanDo);
    assert(banDo.laySoHang() == 11 && banDo.laySoCot() == 21);
    assert(!banDo.toaDoHopLe(-1, 0) && !banDo.toaDoHopLe(0, -1));
    assert(!banDo.toaDoHopLe(11, 0) && !banDo.toaDoHopLe(0, 21));
    assert(banDo.toaDoHopLe(0, 0) && banDo.toaDoHopLe(10, 20));
    assert(banDo.laTuong(-1, 0) && banDo.laTuong(11, 21));
    bool daNemNgoaiLe = false;
    try { banDo.layKyTu(11, 0); }
    catch (const std::out_of_range&) { daNemNgoaiLe = true; }
    assert(daNemNgoaiLe);

    auto viTriPacMan = banDo.layViTriPacMan();
    assert(banDo.layKyTu(viTriPacMan.first, viTriPacMan.second) == 'P');
    assert(!banDo.laTuong(viTriPacMan.first, viTriPacMan.second));
    const auto& cacViTriGhost = banDo.layCacViTriGhost();
    assert(!cacViTriGhost.empty());
    for (const auto& viTri : cacViTriGhost) {
        assert(banDo.layKyTu(viTri.first, viTri.second) == 'G');
        assert(!banDo.laTuong(viTri.first, viTri.second));
    }

    // Chi loang bon huong trong kiem thu, khong phai AI hay tim duong gameplay.
    Luoi<bool> daTham(banDo.laySoHang(), banDo.laySoCot(), false);
    std::queue<std::pair<int, int>> hangDoi;
    hangDoi.push(viTriPacMan);
    daTham.capNhatGiaTri(viTriPacMan.first, viTriPacMan.second, true);
    const int DOI_HANG[] = {-1, 1, 0, 0};
    const int DOI_COT[] = {0, 0, -1, 1};
    while (!hangDoi.empty()) {
        auto viTri = hangDoi.front();
        hangDoi.pop();
        for (int huong = 0; huong < 4; ++huong) {
            int hang = viTri.first + DOI_HANG[huong];
            int cot = viTri.second + DOI_COT[huong];
            if (!banDo.laTuong(hang, cot) && !daTham.layGiaTri(hang, cot)) {
                daTham.capNhatGiaTri(hang, cot, true);
                hangDoi.push({hang, cot});
            }
        }
    }

    int soPacMan = 0;
    int soGhost = 0;
    int soThucAn = 0;
    for (int hang = 0; hang < banDo.laySoHang(); ++hang) {
        for (int cot = 0; cot < banDo.laySoCot(); ++cot) {
            char kyTu = banDo.layKyTu(hang, cot);
            assert(kyTu == '#' || kyTu == '.' || kyTu == ' ' || kyTu == 'P' || kyTu == 'G');
            assert(banDo.laTuong(hang, cot) == (kyTu == '#'));
            if (hang == 0 || hang == 10 || cot == 0 || cot == 20) {
                assert(kyTu == '#');
            }
            if (kyTu != '#') {
                assert(daTham.layGiaTri(hang, cot));
            }
            if (kyTu == 'P') { ++soPacMan; }
            if (kyTu == 'G') { ++soGhost; }
            if (kyTu == '.') { ++soThucAn; }
        }
    }
    assert(soPacMan == 1 && soGhost >= 1 && soThucAn > 0);
    assert(soGhost == static_cast<int>(cacViTriGhost.size()));

    std::ostringstream luongXuat;
    banDo.hienThi(luongXuat);
    std::istringstream luongDoc(luongXuat.str());
    std::string dong;
    for (int hang = 0; hang < banDo.laySoHang(); ++hang) {
        assert(static_cast<bool>(std::getline(luongDoc, dong)));
        assert(static_cast<int>(dong.size()) == banDo.laySoCot());
        for (int cot = 0; cot < banDo.laySoCot(); ++cot) {
            assert(dong[cot] == banDo.layKyTu(hang, cot));
        }
    }
    assert(!std::getline(luongDoc, dong));
    std::cout << "PASS " << tenBanDo << ": 11x21, P=" << soPacMan
              << ", G=" << soGhost << ", thuc an=" << soThucAn
              << "; tat ca o di duoc deu noi voi P\n";
    return luongXuat.str();
}

int main() {
    kiemThuLuoi();
    std::string banDoClassic = kiemThuBanDo("Classic");
    std::string banDoLabyrinth = kiemThuBanDo("Labyrinth");
    std::string banDoChallenge = kiemThuBanDo("Challenge");
    assert(banDoClassic != banDoLabyrinth && banDoClassic != banDoChallenge
           && banDoLabyrinth != banDoChallenge);
    BanDo banDoMacDinh;
    std::ostringstream luongXuat;
    banDoMacDinh.hienThi(luongXuat);
    assert(luongXuat.str() == banDoClassic);
    bool daNemNgoaiLe = false;
    try { BanDo banDoSai("Khong ton tai"); }
    catch (const std::invalid_argument&) { daNemNgoaiLe = true; }
    assert(daNemNgoaiLe);
    std::cout << "Tat ca kiem thu luoi va ban do deu dat.\n";
}
