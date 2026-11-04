#ifndef LUOI_H
#define LUOI_H

#include <stdexcept>
#include <vector>

template <typename T>
class Luoi {
private:
    std::vector<std::vector<T>> duLieu;
    int soCot;

public:
    Luoi(int soHang, int soCot, const T& giaTriMacDinh) : soCot(soCot) {
        if (soHang < 0 || soCot < 0) {
            throw std::invalid_argument("Kich thuoc luoi khong duoc am.");
        }
        duLieu.assign(soHang, std::vector<T>(soCot, giaTriMacDinh));
    }

    int laySoHang() const {
        return static_cast<int>(duLieu.size());
    }

    int laySoCot() const {
        return soCot;
    }

    bool toaDoHopLe(int hang, int cot) const {
        return hang >= 0 && hang < laySoHang() && cot >= 0 && cot < soCot;
    }

    T layGiaTri(int hang, int cot) const {
        if (!toaDoHopLe(hang, cot)) {
            throw std::out_of_range("Toa do nam ngoai luoi.");
        }
        return duLieu[hang][cot];
    }

    void capNhatGiaTri(int hang, int cot, const T& giaTri) {
        if (!toaDoHopLe(hang, cot)) {
            throw std::out_of_range("Toa do nam ngoai luoi.");
        }
        duLieu[hang][cot] = giaTri;
    }
};

#endif
