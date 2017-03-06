#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <new>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <fraction.h>
#include <matrix.h>
using namespace std;

fraction::fraction()								    //default constructor
	: numerator(0), denominator(1)
	{}

	fraction::fraction(int num)							//constructor for numerator only
	: numerator(num), denominator(1)
	{}

	fraction::fraction(int num, int den)			    //complete constructor
	{
		(num,den);
	}

	fraction::fraction(int whole, int num, int den)	    //constructor for whole number fractions
	{
		(*this)(whole,num,den);
	}

	fraction::fraction(char *s)							//constructor for string input
	{
		(*this)(s);
	}

	fraction::fraction(double num)
	{
        *this = doubleToFraction(num);
    }

    fraction::fraction(const fraction &f)
    {
        numerator = f.numerator;
        denominator = f.denominator;
        simplify();
    }


	fraction::operator double()	    			//conversion function
	{ return quotient;}

	void fraction::cdisplay()					//console display function
	{
	    simplify();
		if(denominator != 1)
			cout << numerator << "/" << denominator ;
		else
            cout << numerator ;
	}
	void fraction::reciprocal()
    {
        simplify();
        if(numerator != 0 && numerator!= 1)
            cout << denominator << "/" << numerator ;
        else
            cout << denominator ;
    }
    inline fraction fraction::doubleToFraction(double d)
    {
        int64_t num = d;
        int den = 1;
        int decimal_places_count = 0;

        if( d -(double)num != 0 )    //checks if number has digits after decimal
        {
            do
            {
                d *= 10;        //go 1 decimal right
                den *= 10;      //and multiply denominator by 10
                num = d;
                decimal_places_count++;

                if((int64_t)d - num != (int)0)   //i.e. not equal
                    num++;

                if(decimal_places_count == 5) break;
            }
            while(d != (double)num);//if decimal is placed to right most position

            fraction temp((int)num,den);
            temp.simplify();
            return temp;
        }
        fraction temp2((int)d);
        return temp2;
    }

	/*simplification of a fraction*/
inline void fraction::simplify()
{
	register int i;
	for(i=2; i<=denominator; i++)
	{
		if(numerator%i == 0)
		{
			if(denominator%i == 0)
			{
				numerator /= i;
				denominator /= i;
				i=1;
			}
		}
	}
	if(numerator == 0)
    {
        denominator = 1;
    }
    if(denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
	if(numerator<0 && denominator<0)
	{
		numerator *= -1;
		denominator *= -1;
	}
    if(denominator == 0)
        denominator = 1;

	quotient = (double)numerator / (double)denominator;
}
/*Arithmetic Operators with fractions*/
fraction fraction::operator*(fraction f)
{
	fraction temp;
	temp.numerator = numerator * f.numerator;
	temp.denominator = denominator * f.denominator;
	return temp;
}
fraction fraction::operator/(fraction f)
{
	fraction temp;
	temp.numerator = numerator * f.denominator;
	temp.denominator = denominator * f.numerator;
	return temp;
}
fraction fraction::operator+(fraction f)
{
	fraction temp;
	register int dummy1, dummy2, LCM=1;
	register int i=2;
	dummy1 = denominator;
	dummy2 = f.denominator;
	do	//loop for LCM
	{
		if(dummy1%i == 0 || dummy2%i == 0)
		{
			if(dummy1%i == 0)
			{	dummy1 /= i;	}
			if(dummy2%i == 0)
			{	dummy2 /= i;	}
			LCM *= i;
			i=1;
		}
		i++;
	}while((dummy1 != 1) || (dummy2 != 1));
	temp.denominator = LCM;
	temp.numerator = ((LCM/denominator)*numerator) + ((LCM/f.denominator)*f.numerator);
	return temp;
}
fraction fraction::operator-(fraction f)
{
	fraction temp;
	register int dummy1, dummy2, LCM=1;
	register int i=2;
	dummy1 = denominator;
	dummy2 = f.denominator;
	do	//loop for LCM
	{
		if(dummy1%i == 0 || dummy2%i == 0)
		{
			if(dummy1%i == 0)
			{	dummy1 /= i;	}
			if(dummy2%i == 0)
			{	dummy2 /= i;	}
			LCM *= i;
			i=1;
		}
		i++;
	}while((dummy1 != 1) || (dummy2 != 1));
	temp.denominator = LCM;
	temp.numerator = ((LCM/denominator)*numerator) - ((LCM/f.denominator)*f.numerator);
	return temp;
}
/*Compound Assignment via fractions*/
fraction fraction::operator+=(fraction f)
{
	fraction &temp = *this;
	temp = temp + f;
	temp.simplify();
	return (temp);
}
fraction fraction::operator-=(fraction f)
{
	fraction &temp = *this;
	temp = temp - f;
	temp.simplify();
	return (temp);
}
fraction fraction::operator*=(fraction f)
{
	fraction &temp = *this;
	temp = temp * f;
	temp.simplify();
	return (temp);
}
fraction fraction::operator/=(fraction f)
{
	fraction &temp = *this;
	temp = temp / f;
	temp.simplify();
	return (temp);
}
/*Comparision Operators*/
bool fraction::operator==(fraction f)
{
	if(numerator == f.numerator)
		if(denominator == f.denominator)
			return true;
		else return false;
	else return false;
}
bool fraction::operator!=(fraction f)
{
	if(numerator == f.numerator)
		if(denominator == f.denominator)
			return false;
		else return true;
	else return true;
}
bool fraction::operator< (fraction f)
{
	if(denominator == f.denominator)
	{
		if(numerator < f.numerator)
			return true;
		else return false;
	}
	int num1 = numerator * f.denominator ;
	int num2 = f.numerator * denominator;
	if(num1 < num2)
		return true;
	else return false;
}
bool fraction::operator<=(fraction f)
{
	if(denominator == f.denominator)
	{
		if(numerator <= f.numerator)
			return true;
		else return false;
	}
	int num1 = numerator * f.denominator ;
	int num2 = f.numerator * denominator;
	if(num1 <= num2)
		return true;
	else return false;
}
bool fraction::operator> (fraction f)
{
	if(denominator == f.denominator)
	{
		if(numerator > f.numerator)
			return true;
		else return false;
	}
	int num1 = numerator * f.denominator ;
	int num2 = f.numerator * denominator;
	if(num1 > num2)
		return true;
	else return false;
}
bool fraction::operator>=(fraction f)
{
	if(denominator == f.denominator)
	{
		if(numerator >= f.numerator)
			return true;
		else return false;
	}
	int num1 = numerator * f.denominator ;
	int num2 = f.numerator * denominator;
	if(num1 >= num2)
		return true;
	else return false;
}
//non-member comparision operator with ints
bool operator!=(fraction f, int num)
{
    if(f.quotient != (double)num)
        return true;
    else
        return false;
}
bool operator==(fraction f, int num)
{
    if(f.quotient == (double)num)
        return true;
    else
        return false;
}
bool operator<(fraction f, int num)
{
    if(f.quotient < (double)num)
        return true;
    else
        return false;
}
bool operator<=(fraction f, int num)
{
    if(f.quotient <= (double)num)
        return true;
    else
        return false;
}
bool operator>(fraction f, int num)
{
    if(f.quotient > (double)num)
        return true;
    else
        return false;
}
bool operator>=(fraction f, int num)
{
    if(f.quotient >= (double)num)
        return true;
    else
        return false;
}

/*Arithmetic Operators with integers*/
fraction operator*(fraction f, int num)
{
	fraction temp;
	temp.numerator = f.numerator * num ;
	temp.denominator = f.denominator;
	return temp;
}
fraction operator*(int num, fraction f)
{
	fraction temp;
	temp.numerator = f.numerator * num ;
	temp.denominator = f.denominator;
	return temp;
}
fraction operator/(fraction f, int num)
{
	fraction temp;
	temp.numerator = f.numerator;
	temp.denominator = f.denominator * num ;
	return temp;
}
fraction operator/(int num, fraction f)
{
	fraction temp;
	temp.numerator = f.denominator * num;
	temp.denominator = f.numerator;
	return temp;
}
fraction operator+(fraction f, int num)
{
	if(num!=0)
	{
		fraction temp(num);
		temp = temp + f;
		return temp;
	}
	return (f);
}
fraction operator+(int num, fraction f)
{
	if(num!=0)
	{
		fraction temp(num);
		temp = temp + f;
		return temp;
	}
	return (f);
}
fraction operator-(fraction f, int num)
{
	if(num!=0)
	{
		fraction temp(num);
		temp = f - temp;
		return temp;
	}
	return (f);
}
fraction operator-(int num, fraction f)
{
	if(num!=0)
	{
		fraction temp(num);
		temp = temp - f;
		return temp;
	}
	return (f);
}
/*Compound Arithmetic Assignment operator with integers*/
void operator+=(fraction &f, int num)
{
	if(num!=0)
	{
		fraction temp(num);
		f = temp + f;
		f.simplify();
	}
}
void operator+=(int &num, fraction f)
{
	if(f!=0)
	{
		num = num + f;
	}
}
void operator-=(fraction &f, int num)
{
	if(num!=0)
	{
		fraction temp(num);
		f = f - temp;
		f.simplify();
	}
}
void operator-=(int &num, fraction f)
{
	if(f!=0)
	{
		num = num - f;
	}
}
void operator*=(fraction &f, int num)
{
	if(num!=1)
	{
		fraction temp(num);
		f = temp * f;
		f.simplify();
	}
}
void operator*=(int &num, fraction f)
{
	if(f!=1)
	{
		num = num * f;
	}
}
void operator/=(fraction &f, int num)
{
	if(num!=1)
	{
		fraction temp(num);
		f = f / temp;
		f.simplify();
	}
}
void operator/=(int num, fraction &f)
{
	if(f!=1)
	{
		num = num / f;
	}
}
//non-member arithmetic operators with DOUBLES
fraction operator*(fraction f, double num)
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = f * op2;
    return temp;
}
fraction operator*(double num , fraction f)
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = f * op2;
    return temp;
}
fraction operator/(fraction f, double num )
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = f / op2;
    return temp;
}
fraction operator/(double num , fraction f)
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = op2 / f;
    return temp;
}
fraction operator+(fraction f, double num )
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = f + op2;
    return temp;
}
fraction operator+(double num , fraction f)
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = f + op2;
    return temp;
}
fraction operator-(fraction f, double num )
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = f - op2;
    return temp;
}
fraction operator-(double num , fraction f)
{
    fraction op2;
    op2 = op2.doubleToFraction(num);
    fraction temp;
    temp = op2 - f;
    return temp;
}
//non-member compound arithmetic with double
void operator+=(fraction &f, double num )
{
    fraction temp ;
    temp = temp.doubleToFraction(num);
    f += temp;
}
void operator+=(double &num, fraction f)
{
	if(f != 0)
	{
		num = num + f;
	}
}
void operator-=(fraction &f, double num )
{
    fraction temp ;
    temp = temp.doubleToFraction(num);
    f -= temp;
}
void operator-=(double &num, fraction f)
{
	if(f != 0)
	{
		num = num - f;
	}
}
void operator*=(fraction &f, double num )
{
    fraction temp ;
    temp = temp.doubleToFraction(num);
    f *= temp;
}
void operator*=(double &num, fraction f)
{
	if(f != 1)
	{
		num = num * f;
	}
}
void operator/=(fraction &f, double num )
{
    fraction temp ;
    temp = temp.doubleToFraction(num);
    f /= temp;
}
void operator/=(double &num, fraction f)
{
	if(f != 1)
	{
		num = num / f;
	}
}
//non-member comparision operators with double
bool operator!=(fraction f, double d)
{
    if(f.quotient != d)
        return true;
    else
        return false;
}
bool operator==(fraction f, double d)
{
    if(f.quotient == d)
        return true;
    else
        return false;
}
bool operator< (fraction f, double d)
{
    if(f.quotient < d)
        return true;
    else
        return false;
}
bool operator<=(fraction f, double d)
{
    if(f.quotient <= d)
        return true;
    else
        return false;
}
bool operator> (fraction f, double d)
{
    if(f.quotient > d)
        return true;
    else
        return false;
}
bool operator>=(fraction f, double d)
{
    if(f.quotient >= d)
        return true;
    else
        return false;
}

/*INC and DEC Operators*/
fraction fraction::operator++()
{
	*this = *this + 1;
	return (*this);
}
fraction fraction::operator++(int x)
{
	*this = *this + 1;
	return (*this);
}
fraction fraction::operator--()
{
	*this = *this - 1;
	return (*this);
}
fraction fraction::operator--(int x)
{
	*this = *this - 1;
	return (*this);
}

/*Assignment Operator*/
fraction fraction::operator=(const fraction f)	//assignment operator
{
	numerator = f.numerator;
	denominator = f.denominator;
	simplify();
	return (*this);
}
//fraction fraction::operator=(const fraction *f)
//{
//    numerator = f->numerator;
//    denominator = f->denominator;
//    simplify();
//    return (*this);
//}
fraction fraction::operator=(int num)
{
    numerator = num;
    denominator = 1;
    return (*this);
}
fraction fraction::operator=(double num)
{
    *this = doubleToFraction(num);
    return (*this);
}

/*() Operator for assigning fraction*/
void fraction::operator()(int num)
{ numerator=num; denominator=1; }

void fraction::operator()(double num)
{
    *this = doubleToFraction(num);
}

void fraction::operator()(int num, int den)
{
	numerator=num;
	if(den!=0)
		denominator=den;
	else denominator=1;
	simplify();
}
void fraction::operator()(int whole, int num, int den)
{
	if(den!=0)
		denominator = den;
	else denominator = 1;
	numerator = (den*whole)+num;
	simplify();
}
bool fraction::operator()(char *s)
{
    int slashCount = 0;
    double temp = 0;
    char *startOfstring = s;
    int whole = 0;
    do
    {
        if(*s == '/' || *s == '\\' || *s == ',' || *s == ' ')
            slashCount++;
        s++;
    }while(*s);
    s = startOfstring;
    if(slashCount == 0)
    {
        sscanf(s, "%lf", &temp);
        numerator = (int)temp;
        if(temp == (double)numerator)
        {
            numerator = temp;
            denominator = 1;
        }
        else
            *this = doubleToFraction(temp);
    }
    else if(slashCount == 1)
    {
        sscanf(s, "%d%*c%d", &numerator, &denominator);
        if(denominator == 0)
            denominator = 1;
    }
    else if(slashCount == 2)
    {
        sscanf(s, "%d%*c%d%*c%d", &whole,&numerator,&denominator);
        if(denominator == 0)
            denominator = 1;
        numerator = (denominator*whole) + numerator;
    }
    else
    {
        numerator = 0;
        denominator = 1;
        return false;
    }
    simplify();
    return true;
}

char* fraction::toString()
{
    char *s = NULL;
    if(denominator == 1)
        sprintf(s, "%d", numerator);
    else
        sprintf(s, "%d/%d", numerator,denominator);
    return s;
}
