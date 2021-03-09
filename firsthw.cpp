#include<iostream>
#define rational_number rn
using namespace std;

struct ZeroInitError
{
	int wrong_denominator;
	ZeroInitError(int num){ wrong_denominator = num; }
};

void ZeroInitErrorCall(ZeroInitError wrong_value)
{
        cerr << "\nTried to create number with zero denominator\nDenominator is equal " << wrong_value.wrong_denominator << "\n";
        cerr << flush; 
}

struct ZeroDevisionError{};

void ZeroDivisionErrorCall(){
    cerr << "\nYou are trying to divide by zero\n";
    cerr << flush;
}

class rational_number
{
    private:
                int numerator; //числитель
                int denominator; //знаменатель

    public:
                rational_number(int, int); //прототип конструктора
                
                rational_number operator+(const rational_number) const;
                
                friend rational_number operator-(const rational_number, const rational_number);
                friend rational_number operator*(const rational_number, const rational_number);
                friend rational_number operator/(const rational_number, const rational_number);
                
                friend ostream & operator<< (ostream & os, const rational_number & number);
                
                friend bool operator<(const rational_number& n1, const rational_number& n2);
                friend bool operator>(const rational_number& n1, const rational_number& n2);
                rational_number& operator+=(const rational_number);
                rational_number& operator-=(const rational_number);
                friend const rational_number& operator++(rational_number &);
                friend const rational_number operator++(rational_number &, int);
                friend const rational_number& operator--(rational_number &);
                friend const rational_number operator--(rational_number &, int);
                bool operator==(const rational_number &) const;
                bool operator!=(const rational_number &) const;
                
};

rational_number::rational_number(int num, int denom)
{
    numerator = num;
    if(denom == 0)
        throw ZeroInitError(denom);
    denominator = denom;
}

rational_number& rational_number::operator+=(const rational_number n)
{
        numerator = numerator*n.denominator + denominator*n.numerator;
        denominator = denominator * n.denominator;
        return *this;
}

rational_number& rational_number::operator-=(const rational_number n)
{
        numerator = numerator*n.denominator - denominator*n.numerator;
        denominator = denominator * n.denominator;
        return *this;
}

rational_number rational_number::operator+(const rational_number num) const
{
    return rational_number(numerator*num.denominator + num.numerator*denominator, num.denominator*denominator);
}

rational_number operator-(const rational_number n1, const rational_number n2){
    return rational_number(n1.numerator*n2.denominator - n2.numerator*n1.denominator, n1.denominator*n2.denominator);
}

rational_number operator*(const rational_number n1, const rational_number n2){
    return rational_number(n1.numerator*n2.numerator, n1.denominator*n2.denominator);
}

rational_number operator/(const rational_number n1, const rational_number n2){
    if(n2.numerator == 0) throw ZeroDevisionError();
    return rational_number(n1.numerator*n2.denominator, n1.denominator*n2.numerator);
}

ostream & operator<<(ostream & os, const rational_number & number){
    os << "numerator = " << number.numerator << ", denominator = " << number.denominator << "\n";
    return os;
}

bool operator<(const rational_number& n1, const rational_number& n2){
    int firstnumerator = n1.numerator;
    int firstdenominator = n1.denominator;
    int secondnumerator = n2.numerator;
    int seconddenominator = n2.denominator;
    if(firstnumerator == 0 && secondnumerator == 0){
        return false;
    }
    if(n1.numerator * n1.denominator >= 0 && n2.numerator * n2.denominator >= 0){
        if(n1.numerator < 0){ firstnumerator *= -1; firstdenominator *= -1; }
        if(n2.numerator < 0){ secondnumerator *= -1; seconddenominator *= -1; }
        return firstnumerator*seconddenominator<secondnumerator*firstdenominator;
    }

    if(n1.numerator * n1.denominator <= 0 && n2.numerator * n2.denominator <= 0){
        if(n1.numerator > 0){ firstnumerator *= -1; firstdenominator *= -1; }
        if(n2.numerator > 0){ secondnumerator *= -1; seconddenominator *= -1; }
        return firstnumerator*seconddenominator<secondnumerator*firstdenominator;
    }

    if(n1.numerator * n1.denominator <= 0 && n2.numerator * n2.denominator >= 0){
        return true;
    }

    if(n1.numerator * n1.denominator >= 0 && n2.numerator * n2.denominator <= 0){
        return false;
    }
    return false;
}

bool operator>(const rational_number& n1, const rational_number& n2){
    int firstnumerator = n1.numerator;
    int firstdenominator = n1.denominator;
    int secondnumerator = n2.numerator;
    int seconddenominator = n2.denominator;
    if(firstnumerator == 0 && secondnumerator == 0){
        return false;
    }
    if(n1.numerator * n1.denominator >= 0 && n2.numerator * n2.denominator >= 0){
        if(n1.numerator < 0){ firstnumerator *= -1; firstdenominator *= -1; }
        if(n2.numerator < 0){ secondnumerator *= -1; seconddenominator *= -1; }
        return firstnumerator*seconddenominator>secondnumerator*firstdenominator;
    }

    if(n1.numerator * n1.denominator <= 0 && n2.numerator * n2.denominator <= 0){
        if(n1.numerator > 0){ firstnumerator *= -1; firstdenominator *= -1; }
        if(n2.numerator > 0){ secondnumerator *= -1; seconddenominator *= -1; }
        return firstnumerator*seconddenominator>secondnumerator*firstdenominator;
    }

    if(n1.numerator * n1.denominator <= 0 && n2.numerator * n2.denominator >= 0){
        return false;
    }

    if(n1.numerator * n1.denominator >= 0 && n2.numerator * n2.denominator <= 0){
        return true;
    }
    return false;
}

bool rational_number::operator==(const rational_number& n) const
{
    return (this->numerator == n.numerator && this->denominator == n.denominator);
}

bool rational_number::operator!=(const rational_number& n) const
{
    return !(*this == n);
}

int main(){
    try
    {
      //  rn new_num(1, 0);
        rn number1(2, 5);
        rn number2(3, 4);
        rn number3 = number1 + number2; cout << number3;
        rn number4 = number3 - rn(1, 2); cout << number4;
        rn number5 = number3 * number1; cout << number5;
       // rn zeroDenominatorNumber = number5 / rn(0, 1); cout << zeroDenominatorNumber;
        rn number6 = number5 / rn(4, 8); cout << number6;
        cout << (number1 < number2) << "\n";  //1
        cout << (number1 > number2) << "\n";  //2
        cout << (rn(-1, 2) < rn(-5,2)) << "\n";  //3
        cout << (rn(-1, 2) > rn(-5,2)) << "\n"; //4
        cout << (rn(2,5) > rn(-3,4)) << "\n";  //5
        cout << (rn(2,5) < rn(-3,4)) << "\n";  //6
        cout << (rn(-3,4) < rn(2,5)) << "\n";  //7
        cout << (rn(-3,4) > rn(-2,5)) << "\n";  //8
        number1+=number3; cout << number1;
        //number3-=number2; cout << number3;
        number2-=number3; cout << number2;
        cout << ( number3 == rn(3, 20)) << "\n";
        cout << ( number3 == rn(8, 9)) << "\n";
        cout << ( number3 != rn(3, 20)) << "\n";
        cout << ( number3 != rn(8, 9)) << "\n";
    }
    catch(ZeroInitError wrong_value)
    {
        ZeroInitErrorCall(wrong_value);
    }
    catch(ZeroDevisionError){
       ZeroDivisionErrorCall();
    }

    return 0;
}