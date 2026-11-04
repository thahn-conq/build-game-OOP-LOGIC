# Pac-Man Console — Giai đoạn 2: Hệ thống bản đồ

Bài tập lớn OOP C++17. Giữ menu Giai đoạn 1 và bổ sung ba bản đồ ASCII;
chưa có gameplay, di chuyển, ăn thức ăn, AI Ghost hoặc giao diện đồ họa. Không cần raylib,
CMake, thư viện ngoài, dịch vụ mạng hoặc biến môi trường bí mật.

## Chức năng

- Menu chính hiển thị bản đồ và độ khó hiện tại (mặc định Classic / Normal).
- Chọn bản đồ: Classic, Labyrinth, Challenge.
- Chọn độ khó: Easy, Normal, Hard.
- Hướng dẫn chơi và màn hình bắt đầu hiển thị bản đồ đã chọn, độ khó;
  nhấn Enter để quay lại menu. Bản đồ chỉ được hiển thị, chưa thể chơi.
- Lựa chọn được giữ trong suốt lần chạy, có thể thay đổi nhiều lần.
- Chọn 5 để thoát. Hết luồng nhập (EOF) cũng kết thúc an toàn.
- Nhập sai sẽ được yêu cầu nhập lại, không làm mất lựa chọn trước đó.
  Chỉ nhận một số nguyên trong phạm vi; từ chối dòng trống, chữ, số thực,
  số quá lớn, nhiều số hoặc ký tự thừa như `2abc`. Cho phép khoảng trắng quanh số.

## Cấu trúc

```text
main.cpp       Điểm vào chương trình
TroChoi.h      Khai báo class quản lý menu và cấu hình
TroChoi.cpp    Cài đặt menu, nhập liệu và lưu lựa chọn
Luoi.h         Class template lưới hai chiều, chứa toàn bộ định nghĩa
BanDo.h        Khai báo bản đồ và các thao tác truy vấn
BanDo.cpp      Dữ liệu ba bản đồ, kiểm tra cấu trúc và hiển thị
tests/KiemThuBanDo.cpp  Kiểm thử lưới, bản đồ và khả năng tiếp cận
README.md      Hướng dẫn sử dụng và giải thích thiết kế
.gitignore     Loại trừ kết quả biên dịch và cấu hình cá nhân
```

## Biên dịch và chạy trên Windows bằng VS Code

1. Cài VS Code và extension **C/C++** của Microsoft. Extension không kèm trình biên dịch.
2. Cài MSYS2 từ <https://www.msys2.org/>. Trong terminal **MSYS2 UCRT64**, chạy:

   ```sh
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc
   ```

3. Thêm `C:\msys64\ucrt64\bin` vào biến `Path` của Windows (đổi đường dẫn nếu
   cài MSYS2 ở nơi khác). Khởi động lại VS Code để nhận `Path` mới.
4. Mở thư mục gốc repository trong VS Code. Mở **Terminal > New Terminal**,
   chọn PowerShell, kiểm tra và biên dịch:

   ```powershell
   g++ --version
   New-Item -ItemType Directory -Force build | Out-Null
   g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp TroChoi.cpp BanDo.cpp -o build/pacman.exe
   .\build\pacman.exe
   ```

Chạy lệnh tại thư mục chứa `main.cpp`. Phải biên dịch cả `main.cpp`,
`TroChoi.cpp` và `BanDo.cpp`, không chỉ file đang mở. Không biên dịch file `.h`
riêng. Sau khi sửa code, biên dịch lại trước khi chạy.
Không cần cài extension Code Runner. Nếu không tìm thấy `g++`, kiểm tra `Path`
bằng `where.exe g++`. Có thể kết thúc luồng nhập trong console Windows bằng
Ctrl+Z rồi Enter; cách thoát thông thường là lựa chọn 5.

## Biên dịch và chạy trên Linux

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp TroChoi.cpp BanDo.cpp -o build/pacman
./build/pacman
```

## Vai trò class và hàm

`TroChoi` quản lý menu, với hai thuộc tính `private`: `tenBanDo`, `doKho`.
Màn hình Start tạo `BanDo` theo tên đã chọn. Không dùng biến toàn cục lưu trạng thái.

| Hàm | Nhiệm vụ |
| --- | --- |
| `TroChoi()` | Khởi tạo Classic và Normal. |
| `chay()` | Điều khiển vòng lặp menu, gọi chức năng và kết thúc an toàn. |
| `hienThiMenu()` | In menu chính và cấu hình hiện tại. |
| `nhapLuaChon()` | Đọc cả dòng, kiểm tra đúng một số nguyên trong khoảng; trả `false` khi không đọc được nữa. Tham số tham chiếu nhận lựa chọn hợp lệ. |
| `chonBanDo()` | Nhập, lưu tên bản đồ; trả trạng thái đọc dữ liệu. |
| `chonDoKho()` | Nhập, lưu độ khó; trả trạng thái đọc dữ liệu. |
| `hienThiHuongDan()` | In năm hướng dẫn cơ bản. |
| `batDauTroChoi()` | Tạo bản đồ theo tên, in cấu hình, bản đồ ASCII và thông báo phát triển tiếp. |
| `choQuayVeMenu()` | Đợi một dòng nhập để quay về menu; trả `false` nếu hết luồng nhập. |
| `main()` | Tạo object `troChoi` và gọi `chay()`. |

`std::getline` đọc trọn dòng, `std::istringstream` phân tích số mà không làm
`std::cin` mắc kẹt khi nhập chữ. Một ký tự thừa sau số sẽ làm dòng bị từ chối.
EOF được truyền về vòng lặp để thoát thay vì liên tục yêu cầu nhập lại.

### `Luoi<T>`

Quản lý `vector<vector<T>>` và số cột bằng thuộc tính `private`. Constructor nhận
số hàng, số cột, giá trị mặc định. `laySoHang()`, `laySoCot()` lấy kích thước;
`toaDoHopLe()` kiểm tra biên; `layGiaTri()` và `capNhatGiaTri()` đọc/ghi một ô.
Kích thước âm ném `std::invalid_argument`; đọc/ghi ngoài biên ném
`std::out_of_range`. Cho phép lưới rỗng nhưng lưới rỗng không có tọa độ hợp lệ.
Toàn bộ định nghĩa nằm trong `Luoi.h` để trình biên dịch tạo mã cho mỗi kiểu T.

### `BanDo`

Sở hữu một `Luoi<char>` (composition). Constructor nhận tên Classic, Labyrinth
hoặc Challenge, đọc dữ liệu `vector<string>` rồi chuyển từng ô vào lưới.
Tên không tồn tại ném `std::invalid_argument`. Khi nạp, kiểm tra kích thước,
ký tự, đường bao, đúng một P, có G và thức ăn.

| Hàm | Nhiệm vụ |
| --- | --- |
| `napDuLieu()` | Kiểm tra cấu trúc và chép dữ liệu vào lưới; dùng nội bộ. |
| `laySoHang()`, `laySoCot()` | Trả kích thước bản đồ. |
| `layKyTu()` | Đọc ô; ném ngoại lệ nếu ngoài biên. |
| `toaDoHopLe()` | Kiểm tra tọa độ có nằm trong bản đồ. |
| `laTuong()` | Trả true với tường hoặc tọa độ ngoài bản đồ để chặn truy cập. |
| `layViTriPacMan()` | Trả `pair<int, int>`: `first` là hàng, `second` là cột. |
| `layCacViTriGhost()` | Trả danh sách vị trí G, chỉ cho phép đọc. |
| `hienThi()` | Ghi bản đồ ra `ostream` được truyền vào, ví dụ `std::cout`. |

Tọa độ đánh số từ 0, hàng trước, cột sau. Ba bản đồ cùng kích thước **11 hàng ×
21 cột**, vừa terminal Windows. `#` là tường, `.` là thức ăn, dấu cách là đường
trống, `P`/`G` là vị trí xuất phát, chưa phải đối tượng nhân vật.
Classic có vùng đi rộng, Labyrinth nhiều nhánh và vòng, Challenge là hành lang
hẹp uốn khúc. Mỗi bản đồ có 1 P và 2 G. Bộ kiểm thử loang bốn hướng từ P để
xác nhận mọi ô không phải tường đều tới được, gồm toàn bộ thức ăn và G;
không dùng thuật toán này trong gameplay. Khi sửa dữ liệu bản đồ cần chạy lại kiểm thử.

## Kiến thức OOP đã áp dụng

- **Class và object:** `TroChoi` và đối tượng `troChoi` trong `main()`.
- **Đóng gói:** cấu hình và các thao tác nội bộ là `private`; bên ngoài chỉ cần
  constructor và `chay()` qua giao diện `public`.
- **Constructor:** thiết lập trạng thái hợp lệ ngay khi tạo đối tượng.
- **Hàm thành viên `const`:** các thao tác chỉ hiển thị/nhập không sửa cấu hình
  được đánh dấu `const`.
- **Class template:** `Luoi<T>` dùng thực tế dưới dạng `Luoi<char>` trong `BanDo`.
- **Composition:** bản đồ chứa lưới, dữ liệu lưới được đóng gói bên trong bản đồ.

Chưa cần `protected`, kế thừa, đa hình, abstract class hoặc pure virtual function.
Những kiến thức đó chỉ bổ sung khi có nhiệm vụ thực tế.

## Hướng mở rộng

Menu đã tách thành các hàm riêng; `batDauTroChoi()` là điểm nối với gameplay
sau này. Truy vấn `BanDo` và `Luoi` không phụ thuộc console; `hienThi()` chỉ ghi
ra luồng được truyền vào. Khi bổ sung gameplay, đặt luật chơi và trạng thái game trong phần logic
không phụ thuộc `std::cin`/`std::cout` hay raylib; giao diện console chỉ nhận lệnh
và hiển thị kết quả. Hiện chưa tạo trước bất kỳ class gameplay nào.

## Kiểm thử tự động lưới và bản đồ

Từ thư mục gốc, trên PowerShell (đã tạo `build` như trên):

```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic -I. tests/KiemThuBanDo.cpp BanDo.cpp -o build/kiem_thu_ban_do.exe
.\build\kiem_thu_ban_do.exe
```

Trên Linux:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -I. tests/KiemThuBanDo.cpp BanDo.cpp -o build/kiem_thu_ban_do
./build/kiem_thu_ban_do
```

Đây là chương trình kiểm thử riêng có `main()`, không đưa file test vào lệnh
build game. Không dùng `-DNDEBUG` vì kiểm thử sử dụng `assert`.
Kiểm tra kiểu int/char/string của lưới, cập nhật ô, biên, kích thước âm/rỗng,
kích thước map, ký tự, tường, vị trí P/G, khả năng tiếp cận, dữ liệu hiển thị,
map mặc định và tên map không hợp lệ. Kiểm tra bản đồ đọc cả 231 ô/map.

## Kiểm thử thủ công

1. Chạy chương trình, xác nhận mặc định Classic / Normal; chọn 1 rồi Enter.
2. Chọn 2, lần lượt thử cả ba bản đồ; chọn 3, thử cả ba mức khó.
   Sau mỗi lần, kiểm tra menu chính hiển thị đúng lựa chọn, chọn 1 để xem đúng
   bản đồ ASCII. Thử đủ 9 tổ hợp bản đồ/độ khó.
3. Thay đổi nhiều lần, chọn 1 để xác nhận cấu hình mới nhất được giữ.
4. Chọn 4, đọc hướng dẫn rồi Enter để quay về.
5. Trong từng menu, thử `0`, `9`, `-1`, `abc`, `2abc`, `1.5`, `1 2`, dòng trống
   và một số nguyên rất dài, sau đó nhập lựa chọn hợp lệ để kiểm tra phục hồi.
6. Chọn 5 để thoát. Thử EOF tại menu chính, menu con và màn hình chờ.

## Kết quả kiểm thử Giai đoạn 2

Đã biên dịch game và bộ kiểm thử bằng g++ 14.2.0 trên Linux với C++17,
`-Wall -Wextra -Wpedantic`, không có cảnh báo. Bộ kiểm thử C++ phía trên đã đạt:

| Bản đồ | Kích thước | P | G | Thức ăn | Khả năng tiếp cận từ P |
| --- | --- | --- | --- | --- | --- |
| Classic | 11×21 | 1 | 2 | 145 | Tất cả ô đi được |
| Labyrinth | 11×21 | 1 | 2 | 108 | Tất cả ô đi được |
| Challenge | 11×21 | 1 | 2 | 96 | Tất cả ô đi được |

Đã chạy thêm 23 ca nhập/xuất menu qua tiến trình game: cấu hình mặc định,
9 tổ hợp map/độ khó (đối chiếu toàn bộ ASCII), đổi map nhiều lần mà giữ độ khó,
hướng dẫn, nhập sai trong cả ba menu, khoảng trắng, EOF ở sáu tình huống và
lựa chọn cuối không có xuống dòng. Tất cả đều đạt. Đây là kết quả chạy trên
Linux; hướng dẫn Windows được cung cấp nhưng chưa chạy thử trực tiếp trên Windows.

Các tên class theo PascalCase; hàm, biến tiếng Việt không dấu theo camelCase
(trừ `main`, điểm vào bắt buộc của C++). Mã chương trình dùng chữ không dấu để
hiển thị ổn định trên console Windows.
