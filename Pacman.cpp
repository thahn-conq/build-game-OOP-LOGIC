#include "Pacman.h"

#include <cctype>

Pacman::Pacman(std::pair<int, int> viTriXuatPhat) : NhanVat(viTriXuatPhat) {
}

char Pacman::layKyHieu() const {
    return 'P';
}

bool Pacman::diChuyen(char lenh, const BanDo& banDo) {
    int hang = viTri.first;
    int cot = viTri.second;
    switch (std::tolower(static_cast<unsigned char>(lenh))) {
        case 'w': --hang; break;
        case 'a': --cot; break;
        case 's': ++hang; break;
        case 'd': ++cot; break;
        default: return false;
    }
    if (banDo.laTuong(hang, cot)) {
        return false;
    }
    viTri = {hang, cot};
    return true;
}
