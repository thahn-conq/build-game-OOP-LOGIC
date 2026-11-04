#include "VanChoi.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <type_traits>

std::string layDuLieu(const BanDo& banDo) {
    std::ostringstream luongXuat;
    banDo.hienThi(luongXuat);
    return luongXuat.str();
}

void kiemThuNhanVat() {
    static_assert(std::is_abstract<NhanVat>::value, "NhanVat phai la abstract class");
    static_assert(std::has_virtual_destructor<NhanVat>::value, "Can virtual destructor");
    BanDo banDo(std::vector<std::string>{
        "#######", "#.....#", "#.P...#", "#...G.#", "#######"
    });
    Pacman pacman(banDo.layViTriPacMan());
    Ghost ghost(banDo.layCacViTriGhost()[0]);
    const NhanVat& nhanVatPacman = pacman;
    const NhanVat& nhanVatGhost = ghost;
    assert(nhanVatPacman.layKyHieu() == 'P' && nhanVatGhost.layKyHieu() == 'G');
    assert(pacman.diChuyen('W', banDo) && pacman.layViTri() == std::make_pair(1, 2));
    assert(pacman.diChuyen('a', banDo) && pacman.layViTri() == std::make_pair(1, 1));
    assert(!pacman.diChuyen('w', banDo) && !pacman.diChuyen('a', banDo));
    assert(pacman.diChuyen('s', banDo) && pacman.layViTri() == std::make_pair(2, 1));
    assert(pacman.diChuyen('D', banDo) && pacman.layViTri() == std::make_pair(2, 2));
    assert(!pacman.diChuyen('x', banDo));
    pacman.veViTriXuatPhat();
    assert(pacman.layViTri() == banDo.layViTriPacMan());

    std::string duLieuGoc = layDuLieu(banDo);
    std::mt19937 boSinhSo(42);
    for (int luot = 0; luot < 1000; ++luot) {
        auto viTriCu = ghost.layViTri();
        ghost.diChuyen(banDo, boSinhSo);
        auto viTriMoi = ghost.layViTri();
        assert(!banDo.laTuong(viTriMoi.first, viTriMoi.second));
        assert(std::abs(viTriMoi.first - viTriCu.first)
               + std::abs(viTriMoi.second - viTriCu.second) == 1);
        assert(layDuLieu(banDo) == duLieuGoc);
    }
    // Ghost bi vay kin duoc dung yen, khong lap tim o di mai mai.
    BanDo banDoKin(std::vector<std::string>{
        "#######", "#P.####", "#######", "###G###", "#######"
    });
    Ghost ghostKin(banDoKin.layCacViTriGhost()[0]);
    ghostKin.diChuyen(banDoKin, boSinhSo);
    assert(ghostKin.layViTri() == banDoKin.layCacViTriGhost()[0]);
    std::cout << "PASS nhan vat, bon huong, tuong, da hinh, 1000 buoc Ghost\n";
}

void kiemThuDiemVaHienThi() {
    BanDo banDo(std::vector<std::string>{
        "#############", "#P..       G#", "#############"
    });
    VanChoi vanChoi(banDo, "Easy", 1);
    assert(vanChoi.xuLyLuot('d'));
    assert(vanChoi.layDiemSo() == 10 && vanChoi.laySoCham() == 1);
    assert(vanChoi.layBanDo().layKyTu(1, 2) == ' ');
    assert(vanChoi.layKyTuHienThi(1, 1) == ' ');
    assert(vanChoi.layKyTuHienThi(1, 2) == 'P');
    assert(vanChoi.xuLyLuot('a') && vanChoi.xuLyLuot('d'));
    assert(vanChoi.layDiemSo() == 10 && vanChoi.laySoLuot() == 3);
    assert(vanChoi.xuLyLuot('d'));
    assert(vanChoi.layDiemSo() == 20 && vanChoi.laySoCham() == 0);
    assert(vanChoi.layTrangThai() == TrangThaiVan::CHIEN_THANG);

    // Chi co mot nuoc di: Ghost buoc len cham roi roi di; cham khong doi.
    BanDo banDoThucAn(std::vector<std::string>{"#####", "#P.G#", "#####"});
    Ghost ghost(banDoThucAn.layCacViTriGhost()[0]);
    std::mt19937 boSinhSo(1);
    ghost.diChuyen(banDoThucAn, boSinhSo);
    assert(ghost.layViTri() == std::make_pair(1, 2));
    assert(banDoThucAn.layKyTu(1, 2) == '.');
    ghost.diChuyen(banDoThucAn, boSinhSo);
    assert(ghost.layViTri() != std::make_pair(1, 2));
    assert(banDoThucAn.layKyTu(1, 2) == '.');
    assert(banDoThucAn.anThucAn(1, 2) && !banDoThucAn.anThucAn(1, 2));
    assert(!banDoThucAn.anThucAn(0, 0) && banDoThucAn.laTuong(0, 0));
    std::cout << "PASS an cham, khong cong lap, nen sach, Ghost giu thuc an\n";
}

void kiemThuVaChamVaChoiLai() {
    // Hai Ghost deu chi co the buoc vao o Pac-Man vua den.
    BanDo banDoNhieuGhost(std::vector<std::string>{
        "#######", "##G####", "#P G###", "#.#####", "#######"
    });
    VanChoi vanNhieuGhost(banDoNhieuGhost, "Normal", 0);
    assert(vanNhieuGhost.xuLyLuot('d'));
    assert(vanNhieuGhost.laySoMang() == 2 && vanNhieuGhost.laySoLuot() == 1);
    assert(vanNhieuGhost.layPacman().layViTri() == banDoNhieuGhost.layViTriPacMan());
    for (int chiSo = 0; chiSo < 2; ++chiSo) {
        assert(vanNhieuGhost.layCacGhost()[chiSo].layViTri()
               == banDoNhieuGhost.layCacViTriGhost()[chiSo]);
    }

    // An cham, bi Ghost buoc vao, giu diem/cham sau hoi sinh.
    BanDo banDoSauBuoc(std::vector<std::string>{
        "#######", "#P.G###", "##.####", "#######"
    });
    VanChoi vanSauBuoc(banDoSauBuoc, "Easy", 0);
    assert(vanSauBuoc.xuLyLuot('d'));
    assert(vanSauBuoc.laySoMang() == 4 && vanSauBuoc.layDiemSo() == 10);
    assert(vanSauBuoc.laySoCham() == 1 && vanSauBuoc.laySoLuot() == 1);
    assert(vanSauBuoc.layBanDo().layKyTu(1, 2) == ' ');
    assert(vanSauBuoc.layPacman().layViTri() == banDoSauBuoc.layViTriPacMan());
    assert(!vanSauBuoc.xuLyLuot('w') && !vanSauBuoc.xuLyLuot('x'));
    assert(vanSauBuoc.laySoMang() == 4 && vanSauBuoc.laySoLuot() == 1);
    vanSauBuoc.khoiDongLai();
    assert(vanSauBuoc.laySoMang() == 5 && vanSauBuoc.layDiemSo() == 0);
    assert(vanSauBuoc.laySoLuot() == 0 && vanSauBuoc.laySoCham() == 2);
    assert(layDuLieu(vanSauBuoc.layBanDo()) == layDuLieu(banDoSauBuoc));

    // Pac-Man tu buoc vao Ghost: dung luot ngay, tru mot mang, khong di Ghost tiep.
    BanDo banDoTruocBuoc(std::vector<std::string>{"#######", "#PG...#", "#######"});
    VanChoi vanThua(banDoTruocBuoc, "Normal", 0);
    for (int mang = 2; mang >= 0; --mang) {
        assert(vanThua.xuLyLuot('d'));
        assert(vanThua.laySoMang() == mang);
        assert(vanThua.laySoCham() == 3 && vanThua.layDiemSo() == 0);
    }
    assert(vanThua.laySoLuot() == 3 && vanThua.layTrangThai() == TrangThaiVan::THUA);
    assert(!vanThua.xuLyLuot('d') && vanThua.laySoMang() == 0);
    vanThua.khoiDongLai();
    assert(vanThua.layTrangThai() == TrangThaiVan::DANG_CHOI);
    assert(vanThua.laySoMang() == 3 && vanThua.laySoLuot() == 0);
    assert(vanThua.layCacGhost().size() == 2);
    assert(vanThua.layPacman().layViTri() == banDoTruocBuoc.layViTriPacMan());

    BanDo banDoThang(std::vector<std::string>{"#######", "#P.  G#", "#######"});
    VanChoi vanThang(banDoThang, "Easy", 0);
    assert(vanThang.xuLyLuot('d'));
    assert(vanThang.layTrangThai() == TrangThaiVan::CHIEN_THANG);
    assert(vanThang.layDiemSo() == 10 && vanThang.laySoLuot() == 1);
    assert(!vanThang.xuLyLuot('a'));
    vanThang.khoiDongLai();
    assert(vanThang.layDiemSo() == 0 && vanThang.laySoLuot() == 0);
    assert(vanThang.laySoCham() == 1 && vanThang.laySoMang() == 5);
    assert(vanThang.layTrangThai() == TrangThaiVan::DANG_CHOI);

    BanDo banDoChamCuoi(std::vector<std::string>{"#####", "#P.G#", "#####"});
    VanChoi vanChamCuoi(banDoChamCuoi, "Easy", 0);
    assert(vanChamCuoi.xuLyLuot('d'));
    assert(vanChamCuoi.laySoMang() == 4 && vanChamCuoi.laySoCham() == 0);
    assert(vanChamCuoi.layTrangThai() == TrangThaiVan::CHIEN_THANG);
    std::cout << "PASS va cham truoc/sau, nhieu Ghost, hoi sinh, thang/thua, choi lai\n";
}

void kiemThuCacCauHinh() {
    const std::string CAC_BAN_DO[] = {"Classic", "Labyrinth", "Challenge"};
    const std::string CAC_DO_KHO[] = {"Easy", "Normal", "Hard"};
    const int SO_MANG[] = {5, 3, 2};
    const char CAC_LENH[] = {'w', 'a', 's', 'd'};
    for (const std::string& tenBanDo : CAC_BAN_DO) {
        for (int muc = 0; muc < 3; ++muc) {
            BanDo banDo(tenBanDo);
            VanChoi vanChoi(banDo, CAC_DO_KHO[muc], 123);
            VanChoi vanGiongNhau(banDo, CAC_DO_KHO[muc], 123);
            assert(vanChoi.laySoMang() == SO_MANG[muc]);
            assert(static_cast<int>(vanChoi.layCacGhost().size()) == muc + 1);
            int soGhostHienThi = 0;
            for (int hang = 0; hang < banDo.laySoHang(); ++hang) {
                for (int cot = 0; cot < banDo.laySoCot(); ++cot) {
                    if (vanChoi.layKyTuHienThi(hang, cot) == 'G') { ++soGhostHienThi; }
                }
            }
            assert(soGhostHienThi == muc + 1);
            for (int chiSo = 0; chiSo <= muc; ++chiSo) {
                auto viTri = vanChoi.layCacGhost()[chiSo].layViTri();
                assert(!banDo.laTuong(viTri.first, viTri.second));
                assert(viTri != vanChoi.layPacman().layViTri());
                for (int truoc = 0; truoc < chiSo; ++truoc) {
                    assert(viTri != vanChoi.layCacGhost()[truoc].layViTri());
                }
            }
            std::mt19937 boSinhLenh(7);
            for (int buoc = 0; buoc < 2000 && vanChoi.layTrangThai() == TrangThaiVan::DANG_CHOI; ++buoc) {
                char lenh = CAC_LENH[boSinhLenh() % 4];
                int mangCu = vanChoi.laySoMang();
                int luotCu = vanChoi.laySoLuot();
                auto cacGhostCu = vanChoi.layCacGhost();
                bool daDiChuyen = vanChoi.xuLyLuot(lenh);
                assert(vanGiongNhau.xuLyLuot(lenh) == daDiChuyen);
                assert(vanChoi.layDiemSo() == vanGiongNhau.layDiemSo());
                assert(vanChoi.laySoMang() == vanGiongNhau.laySoMang());
                assert(vanChoi.layPacman().layViTri() == vanGiongNhau.layPacman().layViTri());
                assert(vanChoi.laySoLuot() == luotCu + (daDiChuyen ? 1 : 0));
                assert(vanChoi.laySoMang() == mangCu || vanChoi.laySoMang() == mangCu - 1);
                assert(vanChoi.laySoCham() == vanChoi.layBanDo().demThucAn());
                assert(vanChoi.layDiemSo() == 10 * (banDo.demThucAn() - vanChoi.laySoCham()));
                for (int chiSo = 0; chiSo <= muc; ++chiSo) {
                    auto viTri = vanChoi.layCacGhost()[chiSo].layViTri();
                    assert(viTri == vanGiongNhau.layCacGhost()[chiSo].layViTri());
                    assert(!banDo.laTuong(viTri.first, viTri.second));
                    if (vanChoi.laySoMang() == mangCu) {
                        auto viTriCu = cacGhostCu[chiSo].layViTri();
                        assert(std::abs(viTri.first - viTriCu.first)
                               + std::abs(viTri.second - viTriCu.second) <= 1);
                    }
                }
                for (int hang = 0; hang < banDo.laySoHang(); ++hang) {
                    for (int cot = 0; cot < banDo.laySoCot(); ++cot) {
                        assert(banDo.laTuong(hang, cot) == vanChoi.layBanDo().laTuong(hang, cot));
                    }
                }
            }
            vanChoi.khoiDongLai();
            assert(layDuLieu(vanChoi.layBanDo()) == layDuLieu(banDo));
            assert(vanChoi.laySoMang() == SO_MANG[muc]);
            assert(vanChoi.laySoLuot() == 0 && vanChoi.layDiemSo() == 0);
            std::cout << "PASS cau hinh " << tenBanDo << '/' << CAC_DO_KHO[muc] << '\n';
        }
    }
    bool daNemNgoaiLe = false;
    try { VanChoi vanSai(BanDo("Classic"), "Sai", 0); }
    catch (const std::invalid_argument&) { daNemNgoaiLe = true; }
    assert(daNemNgoaiLe);
    daNemNgoaiLe = false;
    try {
        BanDo banDoRoi(std::vector<std::string>{"#######", "#P.####", "#######", "###G###", "#######"});
        VanChoi vanRoi(banDoRoi, "Easy", 0);
    } catch (const std::invalid_argument&) { daNemNgoaiLe = true; }
    assert(daNemNgoaiLe);
}

int main() {
    kiemThuNhanVat();
    kiemThuDiemVaHienThi();
    kiemThuVaChamVaChoiLai();
    kiemThuCacCauHinh();
    std::cout << "Tat ca kiem thu gameplay deu dat.\n";
}
