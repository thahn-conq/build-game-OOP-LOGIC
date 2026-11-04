#ifndef TRO_CHOI_H
#define TRO_CHOI_H

#include <string>

class TroChoi {
private:
    std::string tenBanDo;
    std::string doKho;

    void hienThiMenu() const;
    bool nhapLuaChon(int nhoNhat, int lonNhat, int& luaChon) const;
    bool chonBanDo();
    bool chonDoKho();
    void hienThiHuongDan() const;
    void batDauTroChoi() const;
    bool choQuayVeMenu() const;

public:
    TroChoi();
    void chay();
};

#endif
