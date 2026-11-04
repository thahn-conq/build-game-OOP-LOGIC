#include "VanChoi.h"

#include <algorithm>
#include <queue>
#include <stdexcept>

VanChoi::VanChoi(const BanDo& banDo, const std::string& doKho, unsigned int hatGiong)
    : banDoGoc(banDo), banDo(banDo), pacman(banDo.layViTriPacMan()), boSinhSo(hatGiong),
      soMangBanDau(0), diemSo(0), soMang(0), soCham(0), soLuot(0),
      trangThai(TrangThaiVan::DANG_CHOI) {
    int soGhost;
    if (doKho == "Easy") {
        soMangBanDau = 5;
        soGhost = 1;
    } else if (doKho == "Normal") {
        soMangBanDau = 3;
        soGhost = 2;
    } else if (doKho == "Hard") {
        soMangBanDau = 2;
        soGhost = 3;
    } else {
        throw std::invalid_argument("Do kho khong hop le.");
    }
    taoGhost(soGhost);
    khoiDongLai();
}

void VanChoi::taoGhost(int soGhost) {
    // Loang mot lan khi khoi tao de chon diem sinh ra thuoc vung Pac-Man toi duoc.
    Luoi<bool> daTham(banDo.laySoHang(), banDo.laySoCot(), false);
    std::vector<std::pair<int, int>> cacOToiDuoc;
    std::queue<std::pair<int, int>> hangDoi;
    auto viTriPacman = pacman.layViTri();
    hangDoi.push(viTriPacman);
    daTham.capNhatGiaTri(viTriPacman.first, viTriPacman.second, true);
    const int DOI_HANG[] = {-1, 1, 0, 0};
    const int DOI_COT[] = {0, 0, -1, 1};
    while (!hangDoi.empty()) {
        auto viTri = hangDoi.front();
        hangDoi.pop();
        cacOToiDuoc.push_back(viTri);
        for (int huong = 0; huong < 4; ++huong) {
            int hang = viTri.first + DOI_HANG[huong];
            int cot = viTri.second + DOI_COT[huong];
            if (!banDo.laTuong(hang, cot) && !daTham.layGiaTri(hang, cot)) {
                daTham.capNhatGiaTri(hang, cot, true);
                hangDoi.push({hang, cot});
            }
        }
    }
    // Tu choi du lieu khien van choi khong the thang.
    for (int hang = 0; hang < banDo.laySoHang(); ++hang) {
        for (int cot = 0; cot < banDo.laySoCot(); ++cot) {
            if ((banDo.layKyTu(hang, cot) == '.' || banDo.layKyTu(hang, cot) == 'G')
                && !daTham.layGiaTri(hang, cot)) {
                throw std::invalid_argument("Thuc an hoac Ghost khong noi voi Pac-Man.");
            }
        }
    }

    auto cacViTri = banDo.layCacViTriGhost();
    // Neu thieu G, uu tien o xa trong thu tu loang, khong trung cac diem sinh ra.
    for (int chiSo = static_cast<int>(cacOToiDuoc.size()) - 1;
         static_cast<int>(cacViTri.size()) < soGhost && chiSo >= 0; --chiSo) {
        auto viTri = cacOToiDuoc[chiSo];
        if (viTri != viTriPacman
            && std::find(cacViTri.begin(), cacViTri.end(), viTri) == cacViTri.end()) {
            cacViTri.push_back(viTri);
        }
    }
    if (static_cast<int>(cacViTri.size()) < soGhost) {
        throw std::invalid_argument("Khong du o de Ghost xuat phat rieng biet.");
    }
    for (int chiSo = 0; chiSo < soGhost; ++chiSo) {
        cacGhost.emplace_back(cacViTri[chiSo]);
    }
}

void VanChoi::khoiDongLai() {
    banDo = banDoGoc;
    pacman.veViTriXuatPhat();
    for (Ghost& ghost : cacGhost) {
        ghost.veViTriXuatPhat();
    }
    diemSo = 0;
    soMang = soMangBanDau;
    soCham = banDo.demThucAn();
    soLuot = 0;
    trangThai = TrangThaiVan::DANG_CHOI;
}

bool VanChoi::coVaCham() const {
    for (const Ghost& ghost : cacGhost) {
        if (pacman.cungViTri(ghost)) {
            return true;
        }
    }
    return false;
}

void VanChoi::xuLyMatMang() {
    --soMang;
    if (soMang == 0) {
        trangThai = TrangThaiVan::THUA;
    } else {
        pacman.veViTriXuatPhat();
        for (Ghost& ghost : cacGhost) {
            ghost.veViTriXuatPhat();
        }
    }
}

bool VanChoi::xuLyLuot(char lenh) {
    if (trangThai != TrangThaiVan::DANG_CHOI || !pacman.diChuyen(lenh, banDo)) {
        return false;
    }
    ++soLuot;
    auto viTri = pacman.layViTri();
    if (banDo.anThucAn(viTri.first, viTri.second)) {
        const int DIEM_MOI_CHAM = 10;
        diemSo += DIEM_MOI_CHAM;
        --soCham;
    }

    if (coVaCham()) {
        xuLyMatMang();
    } else {
        for (Ghost& ghost : cacGhost) {
            ghost.diChuyen(banDo, boSinhSo);
        }
        if (coVaCham()) {
            xuLyMatMang();
        }
    }
    // Va cham duoc xu ly truoc: het mang la thua, con mang va het cham la thang.
    if (soCham == 0 && trangThai != TrangThaiVan::THUA) {
        trangThai = TrangThaiVan::CHIEN_THANG;
    }
    return true;
}

char VanChoi::layKyTuHienThi(int hang, int cot) const {
    char kyTuNen = banDo.layKyTuNen(hang, cot);
    const NhanVat* nhanVat = nullptr;
    if (pacman.layViTri() == std::make_pair(hang, cot)) {
        nhanVat = &pacman;
    } else {
        for (const Ghost& ghost : cacGhost) {
            if (ghost.layViTri() == std::make_pair(hang, cot)) {
                nhanVat = &ghost;
                break;
            }
        }
    }
    // Con tro khong so huu, chi dung trong ham; goi da hinh de ve nhan vat.
    return nhanVat ? nhanVat->layKyHieu() : kyTuNen;
}

const BanDo& VanChoi::layBanDo() const { return banDo; }
const Pacman& VanChoi::layPacman() const { return pacman; }
const std::vector<Ghost>& VanChoi::layCacGhost() const { return cacGhost; }
int VanChoi::layDiemSo() const { return diemSo; }
int VanChoi::laySoMang() const { return soMang; }
int VanChoi::laySoCham() const { return soCham; }
int VanChoi::laySoLuot() const { return soLuot; }
TrangThaiVan VanChoi::layTrangThai() const { return trangThai; }
