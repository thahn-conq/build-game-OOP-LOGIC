#ifndef BAN_DO_H
#define BAN_DO_H

#include "Luoi.h"

#include <ostream>
#include <string>
#include <utility>
#include <vector>

class BanDo {
private:
    Luoi<char> luoi;
    std::pair<int, int> viTriPacMan;
    std::vector<std::pair<int, int>> cacViTriGhost;

    void napDuLieu(const std::vector<std::string>& duLieu);

public:
    explicit BanDo(const std::string& tenBanDo = "Classic");

    int laySoHang() const;
    int laySoCot() const;
    char layKyTu(int hang, int cot) const;
    bool toaDoHopLe(int hang, int cot) const;
    bool laTuong(int hang, int cot) const;
    std::pair<int, int> layViTriPacMan() const;
    const std::vector<std::pair<int, int>>& layCacViTriGhost() const;
    void hienThi(std::ostream& luongXuat) const;
};

#endif
