/**
 * CPP COURSE ASSIGHMENT 3 
 * Written By: Dor Yaakobi
 * https://github.com/Doryaakobi
*/

#include "NumberWithUnits.hpp"
#include <stdexcept>
#include <exception>
#include <fstream>
#include <sstream>

namespace ariel
{

    map<string, map<string, double>> chart;

    NumberWithUnits::NumberWithUnits(const double &val, const string &unit)
    {
        if (chart.count(unit) > 0)
        {
            this->val = val;
            this->unit = unit;
        }
        else
        {
            throw invalid_argument("invalid unit measure");
        }
    }

    /**
     * @brief this method add a new covversion to the chart in case there isn't a known coversion yet between 
     * two measurments units.
     * @param Unit1 - measurment
     * @param Unit2 - measurment
    */
    void addCon(const string &Unit1, const string &Unit2)
    {
        for (const auto &unit : chart[Unit1])
        {
            if (unit.first != Unit2)
            {
                double val = unit.second * chart[Unit2][Unit1];
                chart[unit.first][Unit2] = 1 / val;
                chart[Unit2][unit.first] = val;
            }
        }
    }

    /**
     * @brief - recieves two measurments scale and converts a value from one to another.
     * @param from - the unit to convert from
     * @param to - the unit to convert to
     * @return a double representing the value of the conversion.
    */
    double convert(const string &from, const string &to, const double val)
    {
        if (from == to)
        {
            return val;
        }
        try
        {
            return chart.at(from).at(to) * val;
        }
        catch (const std::exception &e)
        {
            throw invalid_argument{"Conversion Error: Unable to convert from " + from + " to " + to};
        }
    }

    /**
     * @brief - compares between two values of different units.
     * @param num1 - the unit we check.
     * @param num2 - the unit to compare to.
     * @return 1 in case num1 is larger / -1 vice versa and 0 in case they're equal.
    */
    int compare(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        const float esp = 0.000001;
        double n1 = abs((num1.val + esp) - (convert(num2.unit, num1.unit, num2.val) + esp));
        double n2 = ((num1.val + esp) - (convert(num2.unit, num1.unit, num2.val) + esp));
        if (n1 < esp)
        {
            return 0;
        }
        if (n2 > esp)
        {
            return 1;
        }
        if (n2 < esp)
        {
            return -1;
        }
        return 0;
    }

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        string eq;
        string unit1;
        string unit2;
        double num1 = 0;
        double num2 = 0;
        while (units_file >> num1 >> unit1 >> eq >> num2 >> unit2)
        {
            chart[unit1][unit2] = num2;
            chart[unit2][unit1] = 1 / num2;
            addCon(unit1, unit2);
            addCon(unit2, unit1);
        }
    }

    // Overloading I/O operators
    ostream &operator<<(ostream &out, const NumberWithUnits &num)
    {
        out << num.val << "[" << num.unit << "]";
        return out;
    }


    istream& operator>>(istream& is , NumberWithUnits& nu){
      string str;
      double num = 0;
      char  c1 = ' ',c2 = ' ';
      is >> num >> c1 >> str;
      if((str.at(str.length() - 1) !=  ']') || c1 != '['){
        is >> c2;
      }else{
        str = str.substr(0, str.length()-1);
      }
      nu = NumberWithUnits(num,str);
      return is;
    }




    //------------------------------------------------------------------------

    //Basic arithmetic operators overloading (+,+=,-,-=)
    NumberWithUnits operator+(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double ratio = convert(num2.unit, num1.unit, num2.val);
        return NumberWithUnits(num1.val + ratio, num1.unit);
    }

    NumberWithUnits operator+(NumberWithUnits &num, const double add)
    {
        num.val += add;
        return num;
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {

        // num1.val += convert(num2.unit, num1.unit, num2.val);
        // return num1;
        this->setVal(this->getVal() + convert(num2.unit, this->unit, num2.val));
        return *this;
    }


    NumberWithUnits operator-(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        double ratio = convert(num2.unit, num1.unit, num2.val);
        return NumberWithUnits(num1.val - ratio, num1.unit);
    }

    NumberWithUnits operator-(const NumberWithUnits &num1, const double num2)
    {
        return NumberWithUnits(num1.val - num2, num1.unit);
    }

    NumberWithUnits operator-(const double num2, const NumberWithUnits &num1)
    {
        return NumberWithUnits(num2 - num1.val, num1.unit);
    }


    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num2)
    {
        this->setVal(this->getVal() - convert(num2.unit, this->unit, num2.val));
        return *this;
    }


    //------------------------------------------------------------------------

    //Increment/decrement operators (postfix and prefix)
    
    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++(this->val);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        return NumberWithUnits(this->val++, this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->val);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int)
    {
        return NumberWithUnits(this->val--, this->unit);
    }



    //------------------------------------------------------------------------

    //Multipication operators overloading (*,*=)
    NumberWithUnits operator*(const NumberWithUnits &num, const double mul)
    {
        return NumberWithUnits(num.val * mul, num.unit);
    }
    NumberWithUnits operator*(const double mul, const NumberWithUnits &num)
    {
        return NumberWithUnits(num.val * mul, num.unit);
    }

    NumberWithUnits operator*=(NumberWithUnits &num, double mul)
    {
        return NumberWithUnits(num.val *= mul, num.unit);
    }

    NumberWithUnits operator*(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return NumberWithUnits(num1.val * convert(num2.unit, num1.unit, num2.val), num1.unit);
    }

    //------------------------------------------------------------------------

    //Boolean comparisons operators
    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return compare(num1, num2) > 0;
    }
    bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return compare(num1, num2) >= 0;
    }
    bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return compare(num1, num2) < 0;
    }
    bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return compare(num1, num2) <= 0;
    }
    bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return compare(num1, num2) == 0;
    }
    bool operator==(const NumberWithUnits &num, const double d)
    {
        return compare(num, NumberWithUnits{d, num.unit}) == 0;
    }

    bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return compare(num1, num2) != 0;
    }


}
