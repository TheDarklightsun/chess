#include <iostream>
#include <iomanip>
#include <cmath>

enum coord { a, b, c, d, e, f, g, h };
enum color { black, white };

struct s_coord
{
    coord x_letter;
    int y_number; //1..8
    bool ifSomePartsAreEqual(const s_coord& r) const
    {
        return (x_letter == r.x_letter || y_number == r.y_number);
    }

    bool ifAbsDifferencesAreEqual(const s_coord& r) const
    {
        return std::abs(((int)x_letter) - ((int)r.x_letter)) == std::abs(y_number - r.y_number);
    }
    friend std::ostream& operator<<(std::ostream& os, const s_coord& f)
    {
        os << f.x_letter << ":" << f.y_number;
        return os;
    }
};

bool operator==(const s_coord& l, const s_coord& r)
{
    return l.x_letter == r.x_letter && l.y_number == r.y_number;
}

bool operator!=(const s_coord& l, const s_coord& r)
{
    return !(l == r);
}


class Figure
{
protected:
    s_coord m_coord;
    color m_color; //цвет
public:
    Figure(const s_coord m_coord, color z) :m_coord(m_coord), m_color(z) {}
    virtual bool Turn(const s_coord new_coord) = 0;
    friend std::ostream& operator<<(std::ostream& os, const Figure& f)
    {
        os << "coord: " << f.m_coord << ",color: " << f.m_color << std::endl;
        return os;
    }
};

class Castle : public Figure
{
public:
    Castle(const s_coord m_coord, color z) :Figure(m_coord, z) {}
    bool Turn(const s_coord new_coord)
    {
        if (m_coord != new_coord)
        {
            if (m_coord.ifSomePartsAreEqual(new_coord))
            {
                m_coord = new_coord;
                return true;
            }
        }

        return false;
    }
};

class Bishop : public Figure
{
public:
    Bishop(const s_coord m_coord, color z) :Figure(m_coord, z) {}
    bool Turn(const s_coord new_coord)
    {
        if (m_coord != new_coord)
        {
            if (m_coord.ifAbsDifferencesAreEqual(new_coord))
            {
                m_coord = new_coord;
                return true;
            }
        }

        return false;
    }
};


class Queen : public Figure
{
public:
    using Figure::Figure;
    Queen(const s_coord m_coord, color z) :Figure(m_coord, z) {}
    bool Turn(const s_coord new_coord)
    {
        if (m_coord != new_coord)
        {
            if (m_coord.ifSomePartsAreEqual(new_coord))
            {
                m_coord = new_coord;
                return true;
            }

            if (m_coord.ifAbsDifferencesAreEqual(new_coord))
            {
                m_coord = new_coord;
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Figure* pf;
    s_coord te = { e,5 };
    s_coord th = { h,8 };

    pf = new Queen(te, white);
    std::cout << *pf;
    pf->Turn(th);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    pf = new Bishop(th, black);
    std::cout << *pf;
    pf->Turn(te);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    pf = new Castle(te, black);
    std::cout << *pf;
    pf->Turn(th);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;
    std::cin.get();
    return 0;
}