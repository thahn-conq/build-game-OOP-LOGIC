#include "Ghost.h"

#include <vector>

Ghost::Ghost(std::pair<int, int> viTriXuatPhat) : NhanVat(viTriXuatPhat) {
}

char Ghost::layKyHieu() const {
    return 'G';
}

void Ghost::diChuyen(const BanDo& banDo, std::mt19937& boSinhSo) {
    const int DOI_HANG[] = {-1, 1, 0, 0};
    const int DOI_COT[] = {0, 0, -1, 1};
    std::vector<std::pair<int, int>> cacViTriHopLe;
    for (int huong = 0; huong < 4; ++huong) {
        int hang = viTri.first + DOI_HANG[huong];
        int cot = viTri.second + DOI_COT[huong];
        if (!banDo.laTuong(hang, cot)) {
            cacViTriHopLe.push_back({hang, cot});
        }
    }
    if (!cacViTriHopLe.empty()) {
        std::uniform_int_distribution<int> chonViTri(0, static_cast<int>(cacViTriHopLe.size()) - 1);
        viTri = cacViTriHopLe[chonViTri(boSinhSo)];
    }
}
