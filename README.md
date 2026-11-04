# Pac-Man OOP — Demo gameplay C++ Console

Bài tập lớn OOP cho nhóm sinh viên năm 2. Chương trình C++17 chỉ dùng thư viện
chuẩn, tiếp tục menu và ba bản đồ của Giai đoạn 1–2. Chơi theo lượt bằng một
ký tự rồi Enter; không cần thư viện đồ họa, CMake hoặc dịch vụ mạng.

## Tính năng và cách chơi

Menu giữ nguyên năm mục: bắt đầu, chọn bản đồ, chọn độ khó, hướng dẫn, thoát.
Mặc định **Classic / Normal**. Chọn map hoặc độ khó nhiều lần không mất cấu hình.

| Lệnh | Hành động |
| --- | --- |
| W | Lên |
| A | Trái |
| S | Xuống |
| D | Phải |
| Q | Thoát ván, quay về menu |

Nhập từng lệnh rồi Enter; nhận cả chữ hoa/thường và khoảng trắng quanh lệnh.
Dòng trống, nhiều ký tự hoặc lệnh không hợp lệ được yêu cầu nhập lại.
**Đâm tường không tính lượt và Ghost không di chuyển.** Một bước đi được của
Pac-Man là một lượt, sau đó mỗi Ghost đi tối đa một ô.

- `#`: tường; `.`: thức ăn; dấu cách: đường trống; `P`: Pac-Man; `G`: Ghost.
- Ăn chấm được **10 điểm**, chấm biến mất và không được tính điểm lần nữa.
- Ghost chọn ngẫu nhiên một trong các ô lân cận đi được, không đuổi theo người
  chơi. Ghost không sửa dữ liệu nền, không ăn chấm và đứng yên nếu bị vây kín.
- Ghost có thể chồng ô hoặc đi qua nhau. Khi trùng ô chỉ in một G; nếu trùng
  Pac-Man, ưu tiên in P và xử lý va chạm.
- Kiểm tra va chạm ngay sau bước Pac-Man và sau bước các Ghost. Mỗi lượt mất
  tối đa một mạng. Va chạm ngay sau bước Pac-Man thì bỏ qua bước Ghost của lượt đó.
- Khi còn mạng, tất cả nhân vật trở lại các điểm xuất phát riêng biệt; điểm,
  số lượt và thức ăn đã ăn được giữ lại. Hết mạng là **Game Over**.
- Hết chấm là **chiến thắng**. Nếu ăn chấm cuối đồng thời va chạm, xử lý mất
  mạng trước: hết mạng thì thua, còn mạng thì thắng.
- Màn hình hiển thị map, độ khó, điểm, mạng, chấm còn lại và lượt. Thắng/thua
  hiển thị thống kê cuối; chọn **1 chơi lại**, **2 về menu**.
- Chơi lại khôi phục bản đồ/thức ăn, nhân vật, điểm, mạng và lượt, giữ map và
  độ khó. Chuỗi ngẫu nhiên tiếp tục nên Ghost có thể đi khác ván trước.
- Q quay về menu ngay. Hết luồng nhập (EOF) ở bất kỳ màn hình nào kết thúc
  chương trình an toàn. Lựa chọn 5 trong menu thoát chương trình.

| Độ khó | Mạng | Ghost |
| --- | --- | --- |
| Easy | 5 | 1 |
| Normal | 3 | 2 |
| Hard | 2 | 3 |

Ba bản đồ gốc cùng **11 hàng × 21 cột**: Classic rộng, Labyrinth nhiều nhánh,
Challenge hành lang hẹp. Mỗi map có một P và hai G. Hard bổ sung điểm xuất phát
thứ ba bằng loang bốn hướng một lần khi tạo ván: chọn ô đi tới được từ P,
ưu tiên ô xa theo thứ tự loang, không trùng P hoặc các điểm G. Nếu ô đó có
thức ăn, thức ăn vẫn được giữ. Không có tìm đường cho Ghost trong gameplay.

## Cấu trúc source code

```text
main.cpp                  Tạo TroChoi và chạy chương trình
TroChoi.h / TroChoi.cpp    Menu, cấu hình, nhập lệnh, in màn hình, chơi lại
Luoi.h                    Toàn bộ định nghĩa template lưới hai chiều
BanDo.h / BanDo.cpp        Ba map, dữ liệu nền, tường, thức ăn, điểm xuất phát
NhanVat.h / NhanVat.cpp    Lớp cơ sở trừu tượng cho vị trí và hồi sinh
Pacman.h / Pacman.cpp      Di chuyển Pac-Man bằng WASD
Ghost.h / Ghost.cpp        Di chuyển Ghost ngẫu nhiên giữa các ô hợp lệ
VanChoi.h / VanChoi.cpp    Logic ván chơi độc lập nhập/xuất Console
tests/KiemThuBanDo.cpp     Kiểm thử lưới và ba bản đồ của Giai đoạn 2
tests/KiemThuGameplay.cpp  Kiểm thử logic gameplay, không đọc bàn phím
tests/KiemThuConsole.py    Kiểm thử tiến trình Console (Python 3 tùy chọn)
.gitignore                Bỏ qua build và cấu hình cá nhân
```

Không có biến toàn cục lưu trạng thái. Các file mới nằm trong repository hiện
có; không tạo project lồng nhau. Binary sinh trong `build/`, không đưa vào Git.

## Biên dịch và chạy trên Windows bằng VS Code

1. Cài VS Code và extension **C/C++** của Microsoft (extension không kèm g++).
2. Cài [MSYS2](https://www.msys2.org/). Trong terminal **MSYS2 UCRT64** chạy:

   ```sh
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc
   ```

3. Thêm `C:\msys64\ucrt64\bin` vào `Path` của Windows (đổi đường dẫn nếu cài
   nơi khác), mở lại VS Code. Mở thư mục repository, tạo terminal PowerShell.
4. Chạy tại thư mục chứa `main.cpp`:

   ```powershell
   g++ --version
   New-Item -ItemType Directory -Force build | Out-Null
   g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp TroChoi.cpp BanDo.cpp NhanVat.cpp Pacman.cpp Ghost.cpp VanChoi.cpp -o build/pacman.exe
   .\build\pacman.exe
   ```

Phải biên dịch đủ bảy file `.cpp` trên, không chỉ file đang mở; không biên dịch
file `.h` riêng và không thêm file test vào lệnh build game. Sau khi sửa code cần
build lại. Không cần Code Runner. Nếu không tìm thấy g++, dùng `where.exe g++`
để kiểm tra Path. Có thể nhập EOF trên console Windows bằng Ctrl+Z rồi Enter;
thông thường dùng Q về menu và chọn 5 để thoát.

Trên Linux:

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp TroChoi.cpp BanDo.cpp NhanVat.cpp Pacman.cpp Ghost.cpp VanChoi.cpp -o build/pacman
./build/pacman
```

## Kiến trúc và OOP

- **Class/object, constructor, encapsulation:** `TroChoi` giữ tên map và độ khó
  private; `VanChoi` đóng gói điểm, mạng, số chấm, số lượt và trạng thái ván.
- **Inheritance, abstraction:** `Pacman` và `Ghost` kế thừa `NhanVat`.
  `NhanVat` giữ điểm xuất phát private và vị trí hiện tại protected để lớp con
  di chuyển. Constructor đặt vị trí ban đầu, `veViTriXuatPhat()` dùng khi hồi sinh.
- **Pure virtual function, polymorphism:** `NhanVat::layKyHieu()` thuần ảo.
  Khi ghép hình, `VanChoi::layKyTuHienThi()` gọi hàm này qua `const NhanVat*`
  để lấy P/G. Con trỏ không sở hữu, chỉ dùng trong hàm; đối tượng được quản lý
  bằng giá trị. Lớp cơ sở có virtual destructor, không cần `new`/`delete`.
- **Composition:** `TroChoi` quản lý vòng đời `VanChoi`; ván chứa các bản đồ,
  Pac-Man và `vector<Ghost>`. `BanDo` sở hữu `Luoi<char>`.
- **Class template:** `Luoi<T>` lưu `vector<vector<T>>`, có constructor, đọc/ghi
  ô, lấy kích thước, kiểm tra biên. Kích thước âm ném `invalid_argument`, truy cập
  ngoài lưới ném `out_of_range`. Định nghĩa nằm hết trong `Luoi.h`.
- **Nhập/xuất, tính toán, thống kê:** đọc dòng và kiểm tra toàn bộ đầu vào bằng
  `getline`/`istringstream`; tính điểm, mạng, lượt và hiển thị trong/cuối ván.

### Tách nền bản đồ và vị trí nhân vật

`BanDo` giữ tường/chấm/ô trống trong lưới. P/G trong dữ liệu gốc chỉ là dấu
điểm xuất phát; `layKyTuNen()` trả dấu cách cho các dấu này. `anThucAn()` chỉ
đổi `.` thành dấu cách một lần, `demThucAn()` đếm thức ăn còn lại. Các API cũ
như `layKyTu()`, `laTuong()`, `hienThi()` vẫn dùng được để xem dữ liệu bản đồ.

`VanChoi` giữ vị trí nhân vật riêng và ghép chúng lên nền khi hiển thị, vì vậy
không có P/G sót lại ở vị trí cũ, Ghost rời đi thì chấm bên dưới vẫn còn.
`laTuong()` xem cả tọa độ ngoài bản đồ là bị chặn. Tọa độ là `pair<int, int>`,
đánh số từ 0; `first` là hàng, `second` là cột.

### Luồng xử lý một lượt

`VanChoi::xuLyLuot()` kiểm tra bước Pac-Man → tăng lượt → ăn chấm/tính điểm →
kiểm tra va chạm → nếu chưa va chạm thì đi các Ghost và kiểm tra lại → xét
thắng/thua. `khoiDongLai()` chép bản đồ ban đầu và reset mọi thống kê/nhân vật.
Logic không sử dụng `cin`/`cout`, có thể kiểm thử mà không chạy menu.

`BanDo` cũng nhận `vector<string>` để dùng bản đồ nhỏ và kiểm thử tình huống
biên. Dữ liệu phải là hình chữ nhật ít nhất 3×3, bao tường, đúng một P, có G và
thức ăn. Khi tạo ván còn kiểm tra tất cả chấm/G nối với P và đủ ô sinh Ghost
riêng biệt. Ba bản đồ chơi thực tế vẫn giữ nguyên dữ liệu Giai đoạn 2.

## Chạy kiểm thử

Không dùng `-DNDEBUG` vì các kiểm thử C++ sử dụng `assert`. Mỗi file test có
`main()` riêng, chạy thành hai chương trình riêng biệt. Từ thư mục gốc trên
Windows PowerShell, sau khi tạo thư mục `build`:

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -I. tests/KiemThuBanDo.cpp BanDo.cpp -o build/kiem_thu_ban_do.exe
.\build\kiem_thu_ban_do.exe
g++ -std=c++17 -Wall -Wextra -Wpedantic -I. tests/KiemThuGameplay.cpp BanDo.cpp NhanVat.cpp Pacman.cpp Ghost.cpp VanChoi.cpp -o build/kiem_thu_gameplay.exe
.\build\kiem_thu_gameplay.exe
```

Trên Linux:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -I. tests/KiemThuBanDo.cpp BanDo.cpp -o build/kiem_thu_ban_do
./build/kiem_thu_ban_do
g++ -std=c++17 -Wall -Wextra -Wpedantic -I. tests/KiemThuGameplay.cpp BanDo.cpp NhanVat.cpp Pacman.cpp Ghost.cpp VanChoi.cpp -o build/kiem_thu_gameplay
./build/kiem_thu_gameplay
```

Kiểm thử Console tự động cần **Python 3**, chỉ dùng thư viện chuẩn; game và các
kiểm thử C++ không cần Python. Sau khi build game:

```powershell
python tests/KiemThuConsole.py build/pacman.exe
```

```sh
python3 tests/KiemThuConsole.py ./build/pacman
```

### Phạm vi đã kiểm thử

- Bộ test Giai đoạn 2: lưới, tọa độ, tường, map 11×21, P/G và mọi ô đi được nối
  với P. Classic có 145 chấm, Labyrinth 108 chấm, Challenge 96 chấm.
- Gameplay: bốn hướng, tường, lệnh sai, chấm/điểm một lần, Ghost trên thức ăn,
  Ghost bị vây kín, 1000 bước Ghost hợp lệ và nền không đổi.
- Bản đồ nhỏ với kết quả bắt buộc: va chạm ngay sau bước Pac-Man hoặc sau bước
  Ghost, hai Ghost cùng va chạm, giữ điểm/chấm khi hồi sinh, thắng, thua, reset
  sau thắng/thua. Không phụ thuộc may rủi để gây va chạm hay đạt thắng/thua.
- Cả 9 tổ hợp map/độ khó: số mạng/Ghost, điểm xuất phát riêng biệt, nền/tường,
  tối đa một mạng mất mỗi lượt, số chấm, điểm và reset. Chạy chuỗi lệnh tối đa
  2000 lần mỗi tổ hợp (dừng nếu ván kết thúc), seed cố định để tái hiện lỗi.
- 23 ca Console: 9 cấu hình, WASD hoa/thường, đâm tường, Q, menu cũ, hướng dẫn,
  đầu vào sai, EOF và mở ván mới giữ lựa chọn nhưng reset thống kê.

Đã build game và chạy các bộ test trên **Linux, g++ 14.2.0, C++17**, không có
cảnh báo. Chưa chạy trực tiếp trên Windows; các lệnh Windows được cung cấp để
nhóm tự kiểm tra. Seed cố định chỉ phục vụ kiểm thử; game lấy seed từ
`std::random_device` khi bắt đầu ván.

Đã kiểm tra thêm tiến trình Console tương tác tới Game Over trên Classic/Hard,
nhập sai tại màn hình kết quả, chọn chơi lại và xác nhận thống kê reset, sau đó
chơi tới Game Over lần nữa và chọn quay về menu. Luồng thắng và reset sau thắng
được kiểm tra bằng bản đồ nhỏ trong bộ test logic C++.

## Giới hạn bản demo

Console in lại bản đồ theo lượt, không xóa màn hình; cần cuộn terminal khi chơi
lâu. Không điều khiển thời gian thực, đồ họa, âm thanh, animation, Power Pellet,
AI đuổi theo, A*, lưu điểm cao, tài khoản, cơ sở dữ liệu hay multiplayer.
Thống kê chỉ tồn tại trong ván. Đây là demo luật chơi cơ bản để học và vấn đáp.
