#ifndef TRO_CHOI_H
#define TRO_CHOI_H

#include <string>

class VanChoi;

class TroChoi {
private:
    std::string tenBanDo;
    std::string doKho;

    void hienThiMenu() const;
    bool nhapLuaChon(int nhoNhat, int lonNhat, int& luaChon) const;
    bool chonBanDo();
    bool chonDoKho();
    void hienThiHuongDan() const;
    bool batDauTroChoi() const;
    void hienThiVanChoi(const VanChoi& vanChoi) const;
    bool nhapLenh(char& lenh) const;
    bool choQuayVeMenu() const;

public:
    TroChoi();
    void chay();
};

#endif
