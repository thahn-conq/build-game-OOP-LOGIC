#ifndef VAN_CHOI_H
#define VAN_CHOI_H

#include "BanDo.h"
#include "Ghost.h"
#include "Pacman.h"

#include <random>

enum class TrangThaiVan {
    DANG_CHOI,
    CHIEN_THANG,
    THUA
};

class VanChoi {
private:
    BanDo banDoGoc;
    BanDo banDo;
    Pacman pacman;
    std::vector<Ghost> cacGhost;
    std::mt19937 boSinhSo;
    int soMangBanDau;
    int diemSo;
    int soMang;
    int soCham;
    int soLuot;
    TrangThaiVan trangThai;

    void taoGhost(int soGhost);
    bool coVaCham() const;
    void xuLyMatMang();

public:
    VanChoi(const BanDo& banDo, const std::string& doKho, unsigned int hatGiong);
    void khoiDongLai();
    bool xuLyLuot(char lenh);
    char layKyTuHienThi(int hang, int cot) const;

    const BanDo& layBanDo() const;
    const Pacman& layPacman() const;
    const std::vector<Ghost>& layCacGhost() const;
    int layDiemSo() const;
    int laySoMang() const;
    int laySoCham() const;
    int laySoLuot() const;
    TrangThaiVan layTrangThai() const;
};

#endif
