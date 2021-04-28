/**
 * CPP COURSE ASSIGHMENT 3 
 * Written By: Dor Yaakobi
 * https://github.com/Doryaakobi
*/

#include <map>
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{

    class NumberWithUnits
    {
    private:
        double val;
        string unit;

    public:
        NumberWithUnits(const double&,const string&);
        ~NumberWithUnits(){}

        static void read_units(ifstream& );
    
        //Unary operators overloading
        NumberWithUnits operator+(){
            return NumberWithUnits(val,unit);
        }
        NumberWithUnits operator-(){
            return NumberWithUnits(-(this->val),this->unit);
        }

        void setVal(double n){
            this->val = n;
        }

        double getVal(){
            return this->val;
        }
        
        void setUnit(string str){
            this->unit = str;
        }

        string getUnit(){
            return this->unit;
        }




        // I/O operators overloading.
        friend ostream &operator<<(ostream &, const NumberWithUnits &);
        friend istream &operator>>(istream &, NumberWithUnits &);

        // Overloading basic arithmetics operators.
        friend NumberWithUnits operator+(const NumberWithUnits &, const NumberWithUnits &);
        friend NumberWithUnits operator+( NumberWithUnits &, const double );
        NumberWithUnits& operator+=(const NumberWithUnits &);
        friend NumberWithUnits operator-(const NumberWithUnits &, const NumberWithUnits &);
        NumberWithUnits& operator-=(const NumberWithUnits &);
        friend NumberWithUnits operator-(const NumberWithUnits &, const double );
        friend NumberWithUnits operator-( const double  , const NumberWithUnits &);

        // Multiplication operators overloading.
        friend NumberWithUnits operator*(const NumberWithUnits &,const NumberWithUnits &);
        friend NumberWithUnits operator*(const NumberWithUnits &,const double );
        friend NumberWithUnits operator*(const double,const NumberWithUnits &);
        friend NumberWithUnits operator*=(NumberWithUnits &, double );
        friend NumberWithUnits operator*=(double , NumberWithUnits &);

        // Comparisons operators overloading.
        friend bool operator>(const NumberWithUnits &, const NumberWithUnits &);
        friend bool operator>=(const NumberWithUnits &, const NumberWithUnits &);
        friend bool operator<(const NumberWithUnits &, const NumberWithUnits &);
        friend bool operator<=(const NumberWithUnits &, const NumberWithUnits &);
        friend bool operator==(const NumberWithUnits &, const NumberWithUnits &);
        friend bool operator==(const NumberWithUnits &, const double);
        friend bool operator!=(const NumberWithUnits &, const NumberWithUnits &);
        friend int compare(const NumberWithUnits &, const NumberWithUnits &);

        // Increment/Decrment operators overloading.
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);

        
    };

}
