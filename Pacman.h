#ifndef PACMAN_H
#define PACMAN_H

#include "BanDo.h"
#include "NhanVat.h"

class Pacman : public NhanVat {
public:
    explicit Pacman(std::pair<int, int> viTriXuatPhat);
    char layKyHieu() const override;
    bool diChuyen(char lenh, const BanDo& banDo);
};

#endif
