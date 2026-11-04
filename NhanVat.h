#ifndef NHAN_VAT_H
#define NHAN_VAT_H

#include <utility>

class NhanVat {
private:
    std::pair<int, int> viTriXuatPhat;

protected:
    std::pair<int, int> viTri;

public:
    explicit NhanVat(std::pair<int, int> viTriXuatPhat);
    virtual ~NhanVat() = default;
    virtual char layKyHieu() const = 0;

    std::pair<int, int> layViTri() const;
    void veViTriXuatPhat();
    bool cungViTri(const NhanVat& nhanVat) const;
};

#endif
