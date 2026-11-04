# Pac-Man Console — Giai đoạn 1

Bài tập lớn OOP C++17. Giai đoạn này chỉ có menu, chọn bản đồ và độ khó;
chưa có gameplay, mê cung, Ghost hoặc giao diện đồ họa. Không cần raylib,
CMake, thư viện ngoài, dịch vụ mạng hoặc biến môi trường bí mật.

## Chức năng

- Menu chính hiển thị bản đồ và độ khó hiện tại (mặc định Classic / Normal).
- Chọn bản đồ: Classic, Labyrinth, Challenge.
- Chọn độ khó: Easy, Normal, Hard.
- Hướng dẫn chơi và màn hình bắt đầu giả lập; nhấn Enter để quay lại menu.
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
   g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp TroChoi.cpp -o build/pacman.exe
   .\build\pacman.exe
   ```

Chạy lệnh tại thư mục chứa `main.cpp`. Phải biên dịch cả `main.cpp` và
`TroChoi.cpp`, không chỉ file đang mở. Sau khi sửa code, biên dịch lại trước khi chạy.
Không cần cài extension Code Runner. Nếu không tìm thấy `g++`, kiểm tra `Path`
bằng `where.exe g++`. Có thể kết thúc luồng nhập trong console Windows bằng
Ctrl+Z rồi Enter; cách thoát thông thường là lựa chọn 5.

## Biên dịch và chạy trên Linux

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp TroChoi.cpp -o build/pacman
./build/pacman
```

## Vai trò class và hàm

Chỉ có một class `TroChoi`, với hai thuộc tính `private`: `tenBanDo`, `doKho`.
Không dùng biến toàn cục lưu trạng thái.

| Hàm | Nhiệm vụ |
| --- | --- |
| `TroChoi()` | Khởi tạo Classic và Normal. |
| `chay()` | Điều khiển vòng lặp menu, gọi chức năng và kết thúc an toàn. |
| `hienThiMenu()` | In menu chính và cấu hình hiện tại. |
| `nhapLuaChon()` | Đọc cả dòng, kiểm tra đúng một số nguyên trong khoảng; trả `false` khi không đọc được nữa. Tham số tham chiếu nhận lựa chọn hợp lệ. |
| `chonBanDo()` | Nhập, lưu tên bản đồ; trả trạng thái đọc dữ liệu. |
| `chonDoKho()` | Nhập, lưu độ khó; trả trạng thái đọc dữ liệu. |
| `hienThiHuongDan()` | In năm hướng dẫn cơ bản. |
| `batDauTroChoi()` | In cấu hình đã chọn và thông báo phát triển tiếp. |
| `choQuayVeMenu()` | Đợi một dòng nhập để quay về menu; trả `false` nếu hết luồng nhập. |
| `main()` | Tạo object `troChoi` và gọi `chay()`. |

`std::getline` đọc trọn dòng, `std::istringstream` phân tích số mà không làm
`std::cin` mắc kẹt khi nhập chữ. Một ký tự thừa sau số sẽ làm dòng bị từ chối.
EOF được truyền về vòng lặp để thoát thay vì liên tục yêu cầu nhập lại.

## Kiến thức OOP đã áp dụng

- **Class và object:** `TroChoi` và đối tượng `troChoi` trong `main()`.
- **Đóng gói:** cấu hình và các thao tác nội bộ là `private`; bên ngoài chỉ cần
  constructor và `chay()` qua giao diện `public`.
- **Constructor:** thiết lập trạng thái hợp lệ ngay khi tạo đối tượng.
- **Hàm thành viên `const`:** các thao tác chỉ hiển thị/nhập không sửa cấu hình
  được đánh dấu `const`.

Chưa cần `protected`, kế thừa, đa hình, abstract class, pure virtual function
hoặc class template. Những kiến thức đó chỉ bổ sung khi có nhiệm vụ thực tế.

## Hướng mở rộng

Menu đã tách thành các hàm riêng; `batDauTroChoi()` là điểm nối với gameplay
sau này. Khi bổ sung gameplay, đặt luật chơi và trạng thái game trong phần logic
không phụ thuộc `std::cin`/`std::cout` hay raylib; giao diện console chỉ nhận lệnh
và hiển thị kết quả. Hiện chưa tạo trước bất kỳ class gameplay nào.

## Kiểm thử thủ công

1. Chạy chương trình, xác nhận mặc định Classic / Normal; chọn 1 rồi Enter.
2. Chọn 2, lần lượt thử cả ba bản đồ; chọn 3, thử cả ba mức khó.
   Sau mỗi lần, kiểm tra menu chính hiển thị đúng lựa chọn.
3. Thay đổi nhiều lần, chọn 1 để xác nhận cấu hình mới nhất được giữ.
4. Chọn 4, đọc hướng dẫn rồi Enter để quay về.
5. Trong từng menu, thử `0`, `9`, `-1`, `abc`, `2abc`, `1.5`, `1 2`, dòng trống
   và một số nguyên rất dài, sau đó nhập lựa chọn hợp lệ để kiểm tra phục hồi.
6. Chọn 5 để thoát. Thử EOF tại menu chính, menu con và màn hình chờ.

Các tên class theo PascalCase; hàm, biến tiếng Việt không dấu theo camelCase
(trừ `main`, điểm vào bắt buộc của C++). Mã chương trình dùng chữ không dấu để
hiển thị ổn định trên console Windows.
