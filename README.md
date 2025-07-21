# 📊 SpreadSheet Class in C++

This project implements a dynamic `SpreadSheet` class in C++ that provides a 2D table of `Cell` elements with flexible manipulation features, including resizing, rotating, mirroring, slicing, and custom access.

---

## 📁 Features

✅ Dynamic row and column management  
✅ Supports copy and move constructors and assignment  
✅ Rotate the spreadsheet (90°, 180°, 270° clockwise/counterclockwise)  
✅ Mirror horizontally, vertically, or along diagonals  
✅ Remove rows/columns by index or multiple indices  
✅ Slice spreadsheet by removing specific rows/columns  
✅ Printable via `operator<<`  
✅ Element access using `[row][col]` or `{row, col}`  

---

## 🧩 Class Overview

### Constructors
- `SpreadSheet()`: default (2×2)
- `SpreadSheet(size_t size)`: square spreadsheet
- `SpreadSheet(size_t rows, size_t cols)`: custom size
- Copy and move constructors

### Key Methods
| Method                      | Description                                    |
|----------------------------|------------------------------------------------|
| `resizeRow(size_t)`        | Resize number of rows                         |
| `resizeCol(size_t)`        | Resize number of columns                      |
| `rotate(size_t count)`     | Rotates the spreadsheet (90° × count)         |
| `mirrorH()`                | Mirrors horizontally                          |
| `mirrorV()`                | Mirrors vertically                            |
| `mirrorD()`                | Mirrors along main diagonal                   |
| `mirrorSD()`               | Mirrors along secondary diagonal              |
| `removeRow(size_t)`        | Removes a single row                          |
| `removeCol(size_t)`        | Removes a single column                       |
| `removeRows({r1, r2, ...})`| Removes multiple rows                         |
| `removeCols({c1, c2, ...})`| Removes multiple columns                      |
| `slice(...)`               | Creates a new object with rows/cols removed   |

### Access
- `operator[](size_t)`: returns a `Column` object
- `operator[](initializer_list<int>)`: access cell at {row, col}
- `getVal()`: returns a const pointer to the board

### Operators
- `==` / `!=` for spreadsheet comparison
- `<<` for pretty-printing the spreadsheet

---

## 🧪 Example Usage

```cpp
SpreadSheet sheet(3, 3);
sheet[{0, 0}] = "A1";
sheet[{0, 1}] = "B1";
sheet[{0, 2}] = "C1";
sheet[{1, 0}] = "A2";

std::cout << sheet;

sheet.rotate(1);
std::cout << sheet;

sheet.mirrorH();
std::cout << sheet;

sheet.removeRow(1);
std::cout << sheet;
