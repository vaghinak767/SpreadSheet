#ifndef Cell_H
#define Cell_H

#include <string>
#include <vector>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& obj);
std::istream& operator>>(std::istream& in, std::vector<int>& obj);

class Cell
{
private:
    std::string m_val;
public:
    Cell();
    Cell(const Cell& rhv);
    Cell(Cell&& rhv) noexcept;
    explicit Cell(int val);
    explicit Cell(std::string val);
    explicit Cell(double val);
    explicit Cell(char val);
    explicit Cell(bool val);
    explicit Cell(const std::vector<int>& val);
public:
    const Cell& operator=(const Cell& rhv);  
    const Cell& operator=(Cell&& rhv) noexcept;
    const Cell& operator=(int val);
    const Cell& operator=(double val);
    const Cell& operator=(std::string val);
    const Cell& operator=(char val);
    const Cell& operator=(bool val);
    const Cell& operator=(const std::vector<int>& rhv);
public:
    operator int();
    operator double();
    operator std::string();
    operator char(); 
    operator bool();
    operator std::vector<int>();
    std::string get_str()const;
    friend std::istream& operator>>(std::istream& in, Cell& str);
};

bool operator==(const Cell& lhs, const Cell &rhs);
bool operator!=(const Cell& lhs, const Cell &rhs);

std::ostream& operator<<(std::ostream& out, const Cell& obj);
std::istream& operator>>(std::istream& in, Cell& str);

#endif
