"""Kiem thu nhap/xuat tien trinh game; chi can thu vien chuan Python 3."""

import os
import re
import subprocess
import sys


def chayGame(duongDan, duLieu):
    ketQua = subprocess.run(
        [duongDan], input=duLieu, text=True, capture_output=True, timeout=5
    )
    assert ketQua.returncode == 0, ketQua.stderr
    assert not ketQua.stderr, ketQua.stderr
    assert ketQua.stdout.count("Da thoat chuong trinh.") == 1
    return ketQua.stdout


def kiemThu(duongDan):
    soCa = 0
    cacBanDo = ["Classic", "Labyrinth", "Challenge"]
    cacDoKho = ["Easy", "Normal", "Hard"]
    cacSoMang = [5, 3, 2]
    cacSoCham = [145, 108, 96]
    for soBanDo, tenBanDo in enumerate(cacBanDo, 1):
        for soDoKho, tenDoKho in enumerate(cacDoKho, 1):
            ketQua = chayGame(
                duongDan, f"3\n{soDoKho}\n2\n{soBanDo}\n1\nW\n d \nQ\n5\n"
            )
            assert f"Ban do da chon: {tenBanDo}" in ketQua
            assert f"Do kho da chon: {tenDoKho}" in ketQua
            assert "Gap tuong, khong the di chuyen." in ketQua
            assert "Da thoat van choi." in ketQua
            assert f"Ban do hien tai: {tenBanDo}" in ketQua
            assert f"Do kho hien tai: {tenDoKho}" in ketQua
            cacKhung = re.findall(
                r"Diem: (\d+) \| Mang: (\d+) \| Cham con lai: (\d+) \| Luot: (\d+)\n"
                r"((?:[#. PG]{21}\n){11})", ketQua
            )
            assert len(cacKhung) == 3
            soMang = cacSoMang[soDoKho - 1]
            soCham = cacSoCham[soBanDo - 1]
            assert cacKhung[0][:4] == ("0", str(soMang), str(soCham), "0")
            assert cacKhung[1] == cacKhung[0]  # Dam tuong khong di Ghost.
            assert cacKhung[2][:4] == ("10", str(soMang), str(soCham - 1), "1")
            assert cacKhung[0][4].count("P") == 1
            assert cacKhung[0][4].count("G") == soDoKho
            assert cacKhung[2][4].count("P") == 1
            print(f"PASS console {tenBanDo}/{tenDoKho}")
            soCa += 1

    cacLoiSo = ["0", "9", "-1", "abc", "2abc", "1.5", "1 2", "", "   ", "9" * 100]
    for dau, cuoi in [("", "5\n"), ("2\n", "2\n5\n"), ("3\n", "1\n5\n")]:
        ketQua = chayGame(duongDan, dau + "\n".join(cacLoiSo) + "\n" + cuoi)
        assert ketQua.count("Lua chon khong hop le.") == len(cacLoiSo)
        soCa += 1
    cacLenhSai = ["", "   ", "abc", "dd", "w a", "1", "qabc", "!", "ế"]
    ketQua = chayGame(duongDan, "1\n" + "\n".join(cacLenhSai) + "\nw\nd\nq\n5\n")
    assert ketQua.count("Lenh khong hop le.") == len(cacLenhSai)
    assert "Diem: 10 | Mang: 3 | Cham con lai: 144 | Luot: 1" in ketQua
    soCa += 1

    ketQua = chayGame(duongDan, "3\n3\n2\n2\n1\nd\nq\n1\nq\n5\n")
    assert ketQua.count("Diem: 0 | Mang: 2 | Cham con lai: 108 | Luot: 0") == 2
    assert ketQua.count("Ban do da chon: Labyrinth") == 3
    soCa += 1
    ketQua = chayGame(duongDan, "4\n\n5\n")
    for dong in ["W/A/S/D:", "An cac cham", "Tranh va cham", "An het cham", "Het mang", "Q:"]:
        assert dong in ketQua
    soCa += 1
    for duLieu in ["", "2\n", "3\n", "1\n", "1\nx\n", "4\n", "abc\n", "5"]:
        chayGame(duongDan, duLieu)
        soCa += 1
    print(f"Tat ca {soCa} ca console deu dat (gom Q, EOF, nhap sai, van moi).")


if __name__ == "__main__":
    kiemThu(sys.argv[1] if len(sys.argv) > 1 else
            ("build/pacman.exe" if os.name == "nt" else "./build/pacman"))
