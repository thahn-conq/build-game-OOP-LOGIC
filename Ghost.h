#ifndef GHOST_H
#define GHOST_H

#include "BanDo.h"
#include "NhanVat.h"

#include <random>

class Ghost : public NhanVat {
public:
    explicit Ghost(std::pair<int, int> viTriXuatPhat);
    char layKyHieu() const override;
    void diChuyen(const BanDo& banDo, std::mt19937& boSinhSo);
};

#endif
