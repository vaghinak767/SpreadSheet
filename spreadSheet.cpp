#include "spreadSheet.h"

SpreadSheet::SpreadSheet(): SpreadSheet(2,2) {}

SpreadSheet::SpreadSheet(size_t size) : SpreadSheet(size, size) {}

SpreadSheet::SpreadSheet(size_t row, size_t col)
{
    m_board = new Cell*[row];
    for(int i = 0; i < row; ++i)
    {
        m_board[i] = new Cell[col];
    }
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

void SpreadSheet::clear()
{
    if(m_board)
    {
        for(int i = 0; i < m_row; ++i)
        {
            delete[] m_board[i];
        }
        delete[] m_board;
        m_board = nullptr;
        m_row = 0;
        m_col = 0;
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : m_row{rhv.m_row}, m_col{rhv.m_col}
{
    m_board = new Cell*[m_row];
    for(int i = 0; i < m_row; ++i)
    {
        m_board[i] = new Cell[m_col];
        for(int j = 0; j < m_col; ++j)
        {
            m_board[i][j] = rhv.m_board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv) noexcept : m_board{rhv.m_board}, m_row{rhv.m_row}, m_col{rhv.m_col}
{
    rhv.m_board = nullptr;
    rhv.m_row = 0;
    rhv.m_col = 0;
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv)
{
    if(this == &rhv)
    {
        return;
    }
    m_row = rhv.m_row;
    m_col = rhv.m_col;
    m_board = new Cell*[m_row];
    for(int i = 0; i < m_row; ++i)
    {
        m_board[i] = new Cell[m_col];
        for(int j = 0; j < m_col; ++j)
        {
            m_board[i][j] = rhv.m_board[i][j];
        }
    }
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv) noexcept
{
    if(this == &rhv)
    {
        return;
    }
    m_row = rhv.m_row;
    m_col = rhv.m_col;
    m_board = rhv.m_board;
    rhv.m_board = nullptr;
    rhv.m_row = 0;
    rhv.m_col = 0;
}

void SpreadSheet::resizeRow(size_t size)
{
    Cell **tmp = new Cell*[size];
    for(int i = 0; i < size; ++i)
    {
        tmp[i] = new Cell[m_col];
        for(int j = 0; j < m_col; ++j)
        {
            if (i < m_row) 
            {
                tmp[i][j] = m_board[i][j];
            } 
            else 
            {
                tmp[i][j] = Cell();
            }
        }
    }

    size_t tmp_col = m_col;
    this->clear();
    m_board = tmp;
    m_row = size;
    m_col = tmp_col;
}

void SpreadSheet::resizeCol(size_t size)
{
    Cell** tmp = new Cell*[m_row];
    for (int i = 0; i < m_row; ++i)
    {
        tmp[i] = new Cell[size];
        for (int j = 0; j < size; ++j)
        {
            if (j < m_col) 
            {
                tmp[i][j] = m_board[i][j];
            } 
            else 
            {
                tmp[i][j] = Cell();
            }
        }
    }

    size_t tmp_row = m_row;
    clear();
    m_board = tmp;
    m_row = tmp_row;
    m_col = size;  
}

void SpreadSheet::resize(size_t s1, size_t s2)
{
    this->resizeRow(s1);
    this->resizeCol(s2);
}

size_t SpreadSheet::row() const
{
    return m_row;
}

size_t SpreadSheet::col() const
{
    return m_col;
}

void SpreadSheet::rotate(size_t count)
{
    if(count % 4 == 0)
    {
        return;
    } 
    
    if(count % 4 == 1 || count % 4 == -3)
    {
        rotate_right();
    }
    if(count % 4 == 2 || count % 4 == -2)
    {
        rotate_left();
	    rotate_left();
    }
    if(count % 4 == 3 || count % 4 == -1) 
    {
       rotate_left();
    }
}

void SpreadSheet::rotate_right()
{
    if(m_row == m_col)
    {
        for(int i = 0;  i < m_row / 2; ++i)
        {
            for(int j = i; j < m_col - 1 - i; ++j)
            {
                Cell tmp = m_board[i][j];
                m_board[i][j] = m_board[m_col - 1 - j][i];
                m_board[m_col - 1 - j][i] = m_board[m_col - 1 - i][m_col - 1 - j];
                m_board[m_col - 1 - i][m_col - 1 - j] = m_board[j][m_col - 1 - i];
                m_board[j][m_col - 1 - i] = tmp;
            }
        }
    }
    else
    {
        Cell **arr = new Cell*[m_col];
        for(int i = 0; i < m_col; ++i)
        {
            arr[i] = new Cell[m_row];
            for(int j = 0; j < m_row; ++j)
            {
                arr[i][j] = m_board[m_row - 1 - j][i];
            }
        }
        this->clear();
        m_board = arr;
        m_row = m_col;
        m_col = m_row;
    }
}

void SpreadSheet::rotate_left()
{
    if(m_row == m_col)
    {
        for(int i = 0;  i < m_row / 2; ++i)
        {
            for(int j = i; j < m_col - 1 - i; ++j)
            {
                Cell tmp = m_board[i][j];
                m_board[i][j] = m_board[j][m_col - 1 - i];
                m_board[j][m_col - 1 - i] = m_board[m_col - 1 - i][m_col - 1 - j];
                m_board[m_col - 1 - i][m_col - 1 - j] = m_board[m_col - 1 - j][i];
                m_board[m_col - 1 - j][i] = tmp;
            }
        }
    }
    else
    {
        Cell **arr = new Cell*[m_col];
        for(int i = 0; i < m_col; ++i)
        {
            arr[i] = new Cell[m_row];
            for(int j = 0; j < m_row; ++j)
            {
                arr[i][j] = m_board[j][m_row - 1 - i];
            }
        }
        this->clear();
        m_board = arr;
        m_row = m_col;
        m_col = m_row;
    }
}

void SpreadSheet::mirrorH()
{
    for(int i = 0; i < m_row; ++i)
    {
        for(int j = 0; j < m_col / 2; ++j)
        {
            Cell tmp = m_board[i][j];
            m_board[i][j] = m_board[i][m_col - 1 - j];
            m_board[i][m_col - 1 - j] = tmp;
        }
    }
}

void SpreadSheet::mirrorV()
{
    for(int i = 0; i < m_row / 2; ++i)
    {
        for(int j = 0; j < m_col; ++j)
        {
            Cell tmp = m_board[i][j];
            m_board[i][j] = m_board[m_row - 1 - i][j];
            m_board[m_row - 1 - i][j] = tmp;
        }
    }
}

void SpreadSheet::mirrorD()
{
    int size = (m_row > m_col ? m_col : m_row);
    for(int i = 0; i < size - 1; ++i)
    {
        for(int j = i + 1; j < size; ++j)
        {
            Cell tmp = m_board[i][j];
            m_board[i][j] = m_board[j][i];
            m_board[j][i] = tmp;
        }
    }
}

void SpreadSheet::mirrorSD()
{
    int size = (m_row > m_col ? m_col : m_row);
    for(int i = 0; i < size - 1; ++i)
    {
        for(int j = 0; j < size - 1 - i; ++j)
        {
            Cell tmp = m_board[i][j];
            m_board[i][j] = m_board[size - 1 - j][size - 1 - i];
            m_board[size - 1 - j][size - 1 - i] = tmp;
        }
    }
}

void SpreadSheet::removeRow(size_t row)
{
    if(row >= m_row)
    {
        throw std::out_of_range("Out of range");
    }
    else
    {
        delete[] m_board[row];   
        m_board[row] = nullptr;     
        for (int i = row; i < m_row - 1; ++i) 
        {
            m_board[i] = m_board[i + 1];
        }
        --m_row;
    }  
}

void SpreadSheet::removeCol(size_t col)
{
    if(col >= m_col)
    {
        throw std::out_of_range("Out of range");
    }

    for (size_t i = 0; i < m_row; ++i) 
    {
        for (size_t j = col; j < m_col - 1; ++j) 
        {
            m_board[i][j] = m_board[i][j + 1];
        }
        delete (m_board[i] + m_col - 1);
    }
    --m_col;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows)
{   
    if(m_row <= rows.size())
    {
        throw std::invalid_argument("Invalid argument");
    }
    for(auto elem : rows)
    {
        removeRow(elem);
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols)
{   
    if(m_col <= cols.size())
    {
        throw std::invalid_argument("Invalid argument");
    }
    for(auto elem : cols)
    {
        removeCol(elem);
    }
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet obj(*this);
    obj.removeRows(rows);
    obj.removeCols(cols);
    return obj;
}  

const Cell** SpreadSheet::getVal() const
{
	return const_cast<const Cell**>(this->m_board);
}

int SpreadSheet::max_length() const
{ 
    int max = 0;
    for(size_t i = 0; i < m_row; ++i)
    {
        for(size_t j = 0; j < m_col; ++j)
        {
            std::string str = m_board[i][j];
            max = max < str.length() ? str.length() : max;
        }
    }
    return max;
}

Cell& SpreadSheet::operator[](std::initializer_list<int> index)
{
    if((*(index.begin()) >= 0 && *(index.begin()) < m_row) && (*(index.begin() + 1) >= 0 && *(index.begin() + 1) < m_col))
    {
        return m_board[*(index.begin())][*(index.begin() + 1)];
    }
    throw std::out_of_range("Invalid index");
}

SpreadSheet::Column::Column(Cell* col) : col(col) {}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const
{
    return Column(m_board[pos]);
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos)
{
    return Column(m_board[pos]);
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const
{
    return col[pos];
}

Cell& SpreadSheet::Column::operator[](size_t pos)
{
    return col[pos];
}

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    if ((lhs.row() != rhs.row()) || (lhs.col() != rhs.col()))
    {
        return false;
    }

    const Cell** val1 = lhs.getVal();
    const Cell** val2 = rhs.getVal();
    int row = lhs.row();
    int col = rhs.col();

    for (size_t i = 0; i < row; ++i) 
    {
        for (size_t j = 0; j < col; ++j) 
        {
            if (val1[i][j] != val2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob)
{
    int max_len = ob.max_length();
    int width = 8 < max_len ? max_len : 8;
    int row = ob.row();
    int col = ob.col();

    double width_table = 8 < width ? col * ((9.05 / 8) * static_cast<double>(width)) - width % 8 - 1: col * 9.05;

    int h_line = 1;
    for (int i = 0; i < row; ++i) 
    {
        for(int k = 0; k < width_table; ++k)
        {
            out << std::setw(1) << "-";
        }
        out << "\n";
        for(int j = 0; j < col; ++j)
       	{
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << ob.getVal()[i][j];
        }
        out << std::setw(h_line) << "|";
        out << "\n";
    }

    for(size_t k = 0; k < width_table; ++k)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}