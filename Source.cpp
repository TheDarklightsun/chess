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
        char a = 'a' + f.x_letter;
        os << a <<":"<< f.y_number;
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
        os << "coord: " << f.m_coord << " , color: " << (f.m_color ? "white" : "black") << std::endl;
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
    s_coord tc1 = { c,1 };
    s_coord tc2 = { c,8 };
    s_coord tf1 = { f,1 };
    s_coord tf2 = { f,8 };
    s_coord td1 = { d,1 };
    s_coord td2 = { d,8 };
    s_coord ta1 = { a,1 };
    s_coord ta2 = { a,8 };
    s_coord th1 = { h,1 };
    s_coord th2 = { h,8 };

    std::cout << "Queen" << std::endl;
    std::cout << "-----" << std::endl;

    pf = new Queen(td1, white);
    std::cout << *pf;;
    pf = new Queen(td2, black);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    std::cout << "Bishop" << std::endl;
    std::cout << "------" << std::endl;

    pf = new Bishop(tc1, white);
    std::cout << *pf;
    pf = new Bishop(tf1, white);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    pf = new Bishop(tc2, black);
    std::cout << *pf;
    pf = new Bishop(tf2, black);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    std::cout << "Castle" << std::endl;
    std::cout << "------" << std::endl;

    pf = new Castle(ta1, white);
    std::cout << *pf;
    pf = new Castle(th2, white);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    pf = new Castle(ta2, black);
    std::cout << *pf;
    pf = new Castle(th2, black);
    std::cout << *pf;
    delete pf;
    std::cout << std::endl;

    return 0;
}