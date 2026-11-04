#include "NhanVat.h"

NhanVat::NhanVat(std::pair<int, int> viTriXuatPhat)
    : viTriXuatPhat(viTriXuatPhat), viTri(viTriXuatPhat) {
}

std::pair<int, int> NhanVat::layViTri() const {
    return viTri;
}

void NhanVat::veViTriXuatPhat() {
    viTri = viTriXuatPhat;
}

bool NhanVat::cungViTri(const NhanVat& nhanVat) const {
    return viTri == nhanVat.viTri;
}
