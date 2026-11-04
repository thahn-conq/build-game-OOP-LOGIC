#include "BanDo.h"

#include <stdexcept>

BanDo::BanDo(const std::string& tenBanDo) : luoi(0, 0, ' ') {
    std::vector<std::string> duLieu;

    if (tenBanDo == "Classic") {
        duLieu = {
            "#####################",
            "#P.................G#",
            "#...................#",
            "#..###...###...###..#",
            "#...................#",
            "#.......     .......#",
            "#...................#",
            "#..###...###...###..#",
            "#...................#",
            "#G..................#",
            "#####################"
        };
    } else if (tenBanDo == "Labyrinth") {
        duLieu = {
            "#####################",
            "#P..................#",
            "#.###.###.#.###.###.#",
            "#.....#...#...#.....#",
            "###.#.#.###.#.#.#.###",
            "#...#.......#...#...#",
            "#.###.#####.###.###.#",
            "#.....#...#.....#...#",
            "#.###.#.#.#.###.#.#.#",
            "#G......#.........G.#",
            "#####################"
        };
    } else if (tenBanDo == "Challenge") {
        duLieu = {
            "#####################",
            "#P..................#",
            "###################.#",
            "#...................#",
            "#.###################",
            "#.........G.........#",
            "###################.#",
            "#...................#",
            "#.###################",
            "#..................G#",
            "#####################"
        };
    } else {
        throw std::invalid_argument("Ten ban do khong hop le.");
    }

    napDuLieu(duLieu);
}

BanDo::BanDo(const std::vector<std::string>& duLieu) : luoi(0, 0, ' ') {
    napDuLieu(duLieu);
}

void BanDo::napDuLieu(const std::vector<std::string>& duLieu) {
    if (duLieu.size() < 3 || duLieu.front().size() < 3) {
        throw std::invalid_argument("Ban do qua nho.");
    }
    const int SO_HANG = static_cast<int>(duLieu.size());
    const int SO_COT = static_cast<int>(duLieu.front().size());

    luoi = Luoi<char>(SO_HANG, SO_COT, ' ');
    int soPacMan = 0;
    int soThucAn = 0;
    cacViTriGhost.clear();

    // Kiem tra tung dong truoc khi truy cap va chuyen vao Luoi<char>.
    for (int hang = 0; hang < SO_HANG; ++hang) {
        if (static_cast<int>(duLieu[hang].size()) != SO_COT) {
            throw std::invalid_argument("Ban do sai so cot.");
        }
        for (int cot = 0; cot < SO_COT; ++cot) {
            char kyTu = duLieu[hang][cot];
            if (kyTu != '#' && kyTu != '.' && kyTu != ' '
                && kyTu != 'P' && kyTu != 'G') {
                throw std::invalid_argument("Ky tu ban do khong hop le.");
            }
            if ((hang == 0 || hang == SO_HANG - 1 || cot == 0 || cot == SO_COT - 1)
                && kyTu != '#') {
                throw std::invalid_argument("Duong bao ban do phai la tuong.");
            }

            luoi.capNhatGiaTri(hang, cot, kyTu);
            if (kyTu == 'P') {
                ++soPacMan;
                viTriPacMan = {hang, cot};
            } else if (kyTu == 'G') {
                cacViTriGhost.push_back({hang, cot});
            } else if (kyTu == '.') {
                ++soThucAn;
            }
        }
    }

    if (soPacMan != 1 || cacViTriGhost.empty() || soThucAn == 0) {
        throw std::invalid_argument("Ban do can dung mot P, it nhat mot G va thuc an.");
    }
}

int BanDo::laySoHang() const {
    return luoi.laySoHang();
}

int BanDo::laySoCot() const {
    return luoi.laySoCot();
}

char BanDo::layKyTu(int hang, int cot) const {
    return luoi.layGiaTri(hang, cot);
}

char BanDo::layKyTuNen(int hang, int cot) const {
    char kyTu = layKyTu(hang, cot);
    // P/G trong du lieu goc chi danh dau vi tri xuat phat.
    return kyTu == 'P' || kyTu == 'G' ? ' ' : kyTu;
}

bool BanDo::anThucAn(int hang, int cot) {
    if (layKyTu(hang, cot) != '.') {
        return false;
    }
    luoi.capNhatGiaTri(hang, cot, ' ');
    return true;
}

int BanDo::demThucAn() const {
    int soThucAn = 0;
    for (int hang = 0; hang < laySoHang(); ++hang) {
        for (int cot = 0; cot < laySoCot(); ++cot) {
            if (layKyTu(hang, cot) == '.') {
                ++soThucAn;
            }
        }
    }
    return soThucAn;
}

bool BanDo::toaDoHopLe(int hang, int cot) const {
    return luoi.toaDoHopLe(hang, cot);
}

bool BanDo::laTuong(int hang, int cot) const {
    // Ngoai ban do cung duoc chan, tranh truy cap o khong ton tai.
    return !toaDoHopLe(hang, cot) || layKyTu(hang, cot) == '#';
}

std::pair<int, int> BanDo::layViTriPacMan() const {
    return viTriPacMan;
}

const std::vector<std::pair<int, int>>& BanDo::layCacViTriGhost() const {
    return cacViTriGhost;
}

void BanDo::hienThi(std::ostream& luongXuat) const {
    for (int hang = 0; hang < laySoHang(); ++hang) {
        for (int cot = 0; cot < laySoCot(); ++cot) {
            luongXuat << layKyTu(hang, cot);
        }
        luongXuat << '\n';
    }
}
