#include "cell.h"
#include <sstream>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& obj)
{
    for(auto elem : obj)
    {
        out << elem << " ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, std::vector<int>& obj)
{
    obj.clear();
    int val;
    while(in >> val)
    {
        obj.push_back(val);
    }
    return in;
}

std::istream& operator>>(std::istream& in, Cell& obj)
{
    in >> obj.m_val;
    return in; 
}

std::ostream& operator<<(std::ostream& out, const Cell& obj)
{
    out << obj.get_str();
    return out;
}

Cell::Cell()
{
    m_val = "";
}


Cell::Cell(const Cell& rhv) : m_val{rhv.m_val}{}

Cell::Cell(Cell&& rhv) noexcept: m_val{rhv.m_val} 
{
    rhv.m_val = "";
}

Cell::Cell(std::string val) : m_val{val}{}

Cell::Cell(int val)
{
    m_val = std::to_string(val);
}

Cell::Cell(double val)
{
    m_val = std::to_string(val);	   
}

Cell::Cell(char val) : m_val{val}{}

Cell::Cell(bool val)
{
    m_val = val ? "true" : "false";
}

Cell::Cell(const std::vector<int>& val)
{
    size_t i = 0;
    size_t size = val.size();
    for(auto elem : val)
    {
        if(i == 0)
        {
            m_val = '[' + std::to_string(val[i]) + ", ";
        }
        else if(i == size - 1)
        {
            m_val += std::to_string(val[i]) + ']';
        }
        else
        {
            m_val += ' ' + std::to_string(val[i]) + ", ";
        }
        ++i;
    } 
}

const Cell& Cell::operator=(const Cell& rhv)
{
    if(this == &rhv)
    {
        return *this;
    }
    
    m_val = rhv.m_val;
    return *this;
}


const Cell& Cell::operator=(Cell&& rhv) noexcept
{
    if(this == &rhv)
    {
        return *this;
    }

    m_val = rhv.m_val;
    rhv.m_val = "";
    return *this;
}

const Cell& Cell::operator=(int val)
{
    m_val = std::to_string(val);
    return *this;
}

const Cell&  Cell::operator=(double val)
{
    m_val = std::to_string(val);
    return *this;
}

const Cell&  Cell::operator=(std::string val)
{
    m_val = val;
    return *this;
}

const Cell& Cell::operator=(char val)
{
    m_val = val;
    return *this;
}

const Cell& Cell::operator=(bool val)
{
    m_val = val ? "true" : "false";
    return *this;
}  

const Cell& Cell::operator=(const std::vector<int>& val)
{
    size_t i = 0;
    size_t size = val.size();
    for(auto elem : val)
    {
        if(i == 0)
        {
            m_val = '[' + std::to_string(val[i]) + ",";
        }
        else if(i == size - 1)
        {
            m_val += std::to_string(val[i]) + ']';
        }
        else
        {
            m_val += std::to_string(val[i]) + ",";
        }
        ++i;
    } 
    return *this;
}
Cell::operator std::string()
{
    return m_val;
}

Cell::operator int()
{
    int num = 1;
    std::stringstream info;
    info << m_val;    
    info >> num;

    return num;
}

Cell::operator double()
{
    double num = 1;
    std::stringstream info;
    info << m_val;    
    info >> num;

    return num;   
}

Cell::operator char()
{
    return m_val[0];
}

Cell::operator bool()
{
    if(m_val == "True" || m_val == "true")
    {
        return true;
    }

    std::stringstream info;
    int tmp = 0;
    info << m_val;
    info >> tmp;
    if(tmp != 0)
    {
        return true;
    }
	return false;
}

Cell::operator std::vector<int>()
{
    std::vector<int> arr;
    std::string str = "";
    if(m_val[0] == '[')
    {
        for(size_t i = 0; m_val[i] != '\0'; ++i)
        {
            if(m_val[i] == '[')
            {
                continue;
            }
            while(m_val[i] != ',' && m_val[i] != ']')
            {
                str += m_val[i];
                ++i;
            }
            int num = 1;
            std::stringstream info;
            info << str;    
            info >> num;
            arr.push_back(num);
            str = "";
        }
    }
    else if(m_val[0] >= '0' && m_val[0] <= '9')
    {
        int num = 1;
        std::stringstream info;
        info << m_val;    
        info >> num;
        arr.push_back(num);
    }
    return arr;
}

std::string Cell::get_str()const
{
    return m_val;
}

bool operator==(const Cell& lhs, const Cell &rhs)
{    
    return lhs.get_str() == rhs.get_str();
}

bool operator!=(const Cell& lhs, const Cell &rhs)
{    
    return lhs.get_str() != rhs.get_str();
}
