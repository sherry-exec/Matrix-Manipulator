#ifndef FRACTION_H
#define FRACTION_H

#define pi "22/7"

class fraction
{
    //
    //  Data
    //

private:
	int numerator, denominator;
	double quotient;

    //
    //  Functions
    //

private:
	void simplify();
	fraction doubleToFraction(double ); //takes decimal number converts into fraction and returns it

public:
    ////Constructors
	fraction();                         //default constructor
	fraction(int );                     //constructor with only numerator
	fraction(int , int );               //constructor with numerator and denominator
	fraction(int , int , int);          //constructor for whole number fractions
	fraction(char *);                   //constructor for numerator and denominator (via string)
	fraction(double );                  //constructor for converting double into fraction
	fraction(const fraction &);         //copy constructor

    ////Accessors
	operator double();                  //independent object calling
	void cdisplay();                    //display of fraction
	void reciprocal();                  //display reciprocal of fraction
	char* toString();                   //return the fraction in char* format

    /////OPERATORS FOR FRACTIONS
	fraction operator*(fraction );	    //member arithmetic operators with FRACTIONS
	fraction operator/(fraction );
	fraction operator+(fraction );
	fraction operator-(fraction );
	fraction operator+=(fraction );	    //compound assignment with FRACTIONS
	fraction operator-=(fraction );
	fraction operator*=(fraction );
	fraction operator/=(fraction );
	bool operator==(fraction );		    //comparison operators with FRACTIONS
	bool operator!=(fraction );
	bool operator< (fraction );
	bool operator<=(fraction );
	bool operator> (fraction );
	bool operator>=(fraction );

	///////OPERATORS FOR INTEGERS
	friend fraction operator*(fraction , int );	//non-member arithmetic operators with intS
	friend fraction operator*(int , fraction );
	friend fraction operator/(fraction , int );
	friend fraction operator/(int , fraction );
	friend fraction operator+(fraction , int );
	friend fraction operator+(int , fraction );
	friend fraction operator-(fraction , int );
	friend fraction operator-(int , fraction );
	friend void operator+=(fraction &, int );	//non-member compound arithmetic with intS
	friend void operator+=(int &, fraction );
	friend void operator-=(fraction &, int );
	friend void operator-=(int &, fraction );
	friend void operator*=(fraction &, int );
	friend void operator*=(int &, fraction );
	friend void operator/=(fraction &, int );
	friend void operator/=(int &, fraction );
	friend bool operator!=(fraction , int);     //comparison operators with integers
	friend bool operator==(fraction , int);
	friend bool operator< (fraction , int);
	friend bool operator<=(fraction , int);
	friend bool operator> (fraction , int);
	friend bool operator>=(fraction , int);

	//////OPERATORS FOR DOUBLES
	friend fraction operator*(fraction , double );	//non-member arithmetic operators with DOUBLES
	friend fraction operator*(double , fraction );
	friend fraction operator/(fraction , double );
	friend fraction operator/(double , fraction );
	friend fraction operator+(fraction , double );
	friend fraction operator+(double , fraction );
	friend fraction operator-(fraction , double );
	friend fraction operator-(double , fraction );
	friend void operator+=(fraction &, double );	//non-member compound arithmetic with DOUBLES
	friend void operator+=(double &, fraction);
	friend void operator-=(fraction &, double );
	friend void operator-=(double &, fraction);
	friend void operator*=(fraction &, double );
	friend void operator*=(double &, fraction);
	friend void operator/=(fraction &, double );
	friend void operator/=(double &, fraction);
	friend bool operator!=(fraction , double);      //comparison operators with integers
	friend bool operator==(fraction , double);
	friend bool operator< (fraction , double);
	friend bool operator<=(fraction , double);
	friend bool operator> (fraction , double);
	friend bool operator>=(fraction , double);

    //Increment and Decrement Operators
	fraction operator++();
	fraction operator++(int );
	fraction operator--();
	fraction operator--(int );

    //Assignment Operators
	fraction operator=(fraction );
	fraction operator=(int );
	fraction operator=(double );
	fraction operator=(const fraction *f);

    //() Operator for fraction assignment
	void operator()(int );
	void operator()(int , int );
	void operator()(int , int , int );
	bool operator()(char *);                //returns false if string is not in correct format - and assigns 0
	void operator()(double );
};

#endif // FRACTION_H
