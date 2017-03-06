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
#include <conio.h>
using namespace std;

/*default constructor*/
matrix::matrix()
{
    rows = cols = cells = 1;
    m = new(nothrow) fraction*[rows];
    for(int i=0; i<rows; i++)
    {	m[i] = new(nothrow) fraction[cols];	}
    if(!m)	exit(EXIT_FAILURE);
}

/*main constructor*/
matrix::matrix(int r, int c)
{
    if(r > 0 )	//check for 0 row
        rows=r;
    else
        rows=1;
    if(c > 0) //check for 0 col
        cols=c;
    else
        cols=1;
    cells = rows*cols;
    m = new(nothrow) fraction*[rows];
    for(int i=0; i<rows; i++)
    {	m[i] = new(nothrow) fraction[cols];	}
    if(!m)	exit(EXIT_FAILURE);
}

/*copy constructor*/
matrix::matrix(const matrix &mo)
{
    reset(mo.rows, mo.cols);
    m = new(nothrow) fraction*[rows];
    for(int i=0; i<rows; i++)
    {	m[i] = new(nothrow) fraction[cols];	}
    if(!m)	exit(EXIT_FAILURE);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            m[i][j] = mo.m[i][j];
    }
}

/*copy constructor with pointer*/
matrix::matrix(const matrix *mo)
{
    reset(mo->rows, mo->cols);
    m = new(nothrow) fraction*[rows];
    for(int i=0; i<rows; i++)
    {	m[i] = new(nothrow) fraction[cols];	}
    if(!m)	exit(EXIT_FAILURE);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            m[i][j] = mo->m[i][j];
    }
}

/*destructor*/
matrix::~matrix()
{
    for(int i=0; i<rows; i++)
        delete [] m[i];
    delete [] m;
}

inline void matrix::undo()
{
    for(int i=0; i<rows; i++)
        delete [] m[i];
    delete [] m;
}

inline void matrix::reset(int r, int c)
{
    if(r > 0 )	//check for 0 row
        rows=r;
    else
        rows=1;
    if(c > 0) //check for 0 col
        cols=c;
    else
        cols=1;
    cells = rows*cols;

}

void matrix::assign()
{
    char s[15];
    for(int i=0; i<rows; i++)
    {
        cout << "ROW no " << i+1 << endl ;
        for(int j=0; j<cols; j++)
        {
            fflush(stdin);
            gets(s);
            m[i][j](s);
        }
    }
    fflush(stdin);
}
void matrix::display()
{
    register int i, j;
    for(i=0; i<rows; i++)
    {
            if(i == 0)
                cout << char(218) << " " ;
            else if(i == rows-1)
                cout << char(192) << " " ;
            else
                cout << char(179) << " " ;
            cout << "\t";
        for(j=0; j<cols; j++)
        {
            m[i][j].cdisplay();
            cout << "\t" ;
        }
            if(i == 0)
                cout << " " << char(191) ;
            else if(i == rows-1)
                cout << " " << char(217) ;
            else
                cout << " " << char(179) ;
            cout << endl ;
    }
}
void matrix::adjustZeroRow()
{
    int count = 0;
    static int  tempRow = rows,
                tempCol = cols;
    for(int i=0; i<tempRow; i++)
    {
        for(int j=0; j<tempCol; j++)
        {
            if(m[i][j] == 0)
                count++;
        }
        if(count == cols)
        {
            Rij(i+1, tempRow);
            tempRow--;                  //do not check last row (step up from last row) b/c it is 0 row
        }
        count = 0;
    }
}
matrix matrix::echelon(bool show_steps = false)
{
    matrix mo(*this);
    register fraction K, pivot_value;
    register int pivot_row = 0;
    register bool pivot_found = false, stair_case = false,
                  row_exchange = false, done = false;
    for(int j=0; j<cols; j++)
    {
        for(int i=0; i<rows; i++)
        {
            if(stair_case == true)  //if stair case occurs
            {
                if(pivot_found == false)
                {
                    if(i == pivot_row)
                    {
                        if(mo.m[i][j] == 0)
                        {
                            while(mo.m[i][j] == 0)
                            {
                                for(int x=i; x<rows; x++)
                                {
                                    if(mo.m[x][j] != 0)
                                    {
                                        mo.Rij(i+1, x+1);
                                        if(show_steps == true)
                                        {
                                            cout << endl << char(16) << " R " << i+1 << char(29) << x+1 << endl ;
                                            mo.display();
                                        }
                                        row_exchange = true;
                                        pivot_found = true;
                                        done = true;
                                        pivot_value = mo.m[i][j];//check again
                                        pivot_row = i;
                                        break;
                                    }
                                }
                                if(pivot_found == true)
                                    break;
                                if(j < cols-1)
                                {
                                    if(mo.m[i][j+1] != 0)
                                    {
                                        j++;
                                        i = -1;
                                        pivot_found = true;
                                        done = true;
                                        pivot_value = mo.m[i][j];
                                    }
                                    else
                                    {
                                        j++;
                                        continue;
                                    }
                                }
                            }
                        }
                        else
                        {
                            pivot_row = i;
                            pivot_found = true;
                            done = true;
                            pivot_value = mo.m[i][j];
                        }
                    }
                }
                if(done == true || pivot_found == true)
                {
                    if(mo.m[i][j] == 0)       //if already 0
                        continue;
                    K = -1 * (mo.m[i][j] / pivot_value);
                    mo.Ri_KRj(K, i+1, pivot_row+1);
                    if(show_steps == true)
                    {
                        cout << endl << char(16) << " R" << i+1 << " + (" ; K.cdisplay(); cout << ") R" << pivot_row+1 << endl ;
                        mo.display();
                    }
                }
            }
            else        //if not stair case
            {                                           //**********/////
                if(i == j)
                {
                    if(done == false)
                    {
                        pivot_row = i;
                        if(mo.m[i][j] == 0)				//if pivot element is zero
                        {
                            for(int x=i; x<rows; x++)   //check for row exchange
                            {
                                if(mo.m[x][j] != 0)
                                {
                                    mo.Rij(i+1, x+1);
                                    if(show_steps == true)
                                    {
                                        cout << endl << char(16) << " R " << i+1 << char(29) << x+1 << endl ;
                                        mo.display();
                                    }
                                    row_exchange = true;
                                    pivot_value = mo.m[i][j];
                                    done = true;
                                    break;
                                }
                                if(x == rows-1)
                                {
                                    if(row_exchange == false)
                                        stair_case = true;
                                }
                            }
                        }
                        else    //if pivot position is non-zero
                        {
                            pivot_value = mo.m[i][j];
                            done = true;
                        }
                        if(stair_case == true)
                        {
                            if(j < cols-1)
                                j++;
                            else
                                return mo;
                            pivot_row = i;
                            done = false;
                            //i -= 1;
                            continue;
                        }
                    }
                }
                else
                {
                    if(done == true)
                    {
                        if(mo.m[i][j] == 0)       //if already 0
                            continue;
                        K = -1 * (mo.m[i][j] / pivot_value);
                        mo.Ri_KRj(K, i+1, pivot_row+1);
                        if(show_steps == true)
                        {
                            cout << endl << char(16) << " R" << i+1 << " + (" ; K.cdisplay(); cout << ") R" << pivot_row+1 << endl ;
                            mo.display();
                        }
                    }
                }
            }
        }
        pivot_row++;
        done = false;
        row_exchange = false;
        pivot_found = false;
    }
    return mo;
}

matrix matrix::echelon_with_1(bool show_steps = false)
{
    matrix mo(1,1);
    mo = *this;
    register fraction K;
    register int pivot_row = 1;
    register bool done = false;
    for(int j=0; j<cols; j++)
    {
        for(int i=0; i<rows; i++)
        {
            if(i == j)
            {
                if(done == false) 	// for making 1
                {
                    pivot_row = i;
                    if(mo.m[i][j] == 1)
                    {
                        done = true;
                        continue;
                    }
                    if(mo.m[i][j] == 0)
                    {
                        for(int x=i; x<rows; x++)
                        {
                            if(mo.m[x][j] != 0)
                            {
                                mo.Rij(i+1, x+1);
                                if(show_steps == true)
                                {
                                    cout << endl << char(16) << " R " << i+1 << char(29) << x+1 << endl ;
                                    mo.display();
                                }
                                done = false;
                                break;
                            }
                        }
                    }
                    K = mo.m[i][j];
                    mo.KRi(1/K, i+1);
                    if(show_steps == true)
                    {
                        cout << endl ; K.reciprocal(); cout << " R" << i+1 << endl ;
                        mo.display();
                    }
                    done = true;
                }
            }
            else
            {
                if(done == true)	// for making 0
                {
                    if(mo.m[i][j] == 0)
                        continue;
                    K = -1 * mo.m[i][j];
                    mo.Ri_KRj(K, i+1, pivot_row+1);
                    if(show_steps == true)
                    {
                        cout << endl << char(16) << " R" << i+1 << " + (" ; K.cdisplay(); cout << ") R" << pivot_row+1 << endl ;
                        mo.display();
                    }
                }
            }
        }
        pivot_row ++ ;
        done = false;
    }
    return mo;
}
matrix matrix::reduce_echelon(bool show_steps = false)
{
    matrix mo(*this);
    register fraction K;
    register int pivot_row = 0;
    register bool done = false, row_exchange = false, stair_case = false;   //done is, if pivot position is made 1
    register bool pivot_found = false;
    for(int j=0; j<cols; j++)
    {
        for(int i=0; i<rows; i++)
        {
            if(stair_case == true)          //if STAIR CASE occurs
            {
                if(pivot_found == false)    //if next-right-position (i.e pivot position is found)
                {
                    if(i == pivot_row)      //do not make pivot value = 0
                    {
                        if(mo.m[i][j] == 0)     //if next stair case pivot position is also = 0
                        {
                            while(mo.m[i][j] == 0)
                            {
                                for(int x=i; x<rows; x++)
                                {
                                    if(mo.m[x][j] != 0)
                                    {
                                        mo.Rij(i+1, x+1);
                                        if(show_steps == true)
                                        {
                                            cout << endl << char(16) << " R " << i+1 << char(29) << x+1 << endl ;
                                            mo.display();
                                        }
                                        row_exchange = true;
                                        pivot_found = true;
                                        pivot_row = i;
                                        break;
                                    }
                                }
                                if(pivot_found == true)
                                    break;
                                if(j < cols-1)      //bounds check
                                {
                                    if(mo.m[i][j+1] != 0)   //if again 0 occur, check for next element vertically
                                    {
                                        j++;
                                        i= -1;
                                        pivot_found = true;
                                        done = false;
                                        break;
                                    }
                                    else
                                    {
                                        j++;
                                        continue;
                                    }
                                }
                                else
                                    return mo;      //if end column is reached then exit
                            }
                        }
                        else
                        {
                            pivot_row = i;
                            pivot_found = true;
                        }
                    }
                }
                if(pivot_found == true && done == false)    //making new pivot position = 1
                {
                    if(mo.m[i][j] == 1) //if pivot position already = 1
                    {
                        pivot_row = i;
                        i = -1;
                        done = true;
                        continue;
                    }
                    K = mo.m[i][j];
                    mo.KRi(1/K, i+1);
                    if(show_steps == true)
                    {
                        cout << endl << char(16) << " "; K.reciprocal(); cout << " R" << i+1 << endl ;
                        mo.display();
                    }
                    pivot_row = i;
                    i = -1;
                    done = true;
                    continue;
                }
                if(done == true)
                {
                    if(i != pivot_row)    //make non-pivot elements = 0
                    {
                        if(mo.m[i][j] == 0) //if already 0
                            continue;
                        K = -1 * mo.m[i][j];
                        mo.Ri_KRj(K, i+1, pivot_row+1);
                        if(show_steps == true)
                        {
                            cout << endl << char(16) << " R" << i+1 << " + (" ; K.cdisplay(); cout << ") R" << pivot_row+1 << endl ;
                            mo.display();
                        }
                    }
                }
            }
            else    //if not STAIR Case
            {
                if(i == j)                  //for making pivot positions = 1
                {
                    if(done == false)
                    {
                        pivot_row = i;
                        if(mo.m[i][j] == 1) //if pivot is already 1
                        {
                            i= -1;
                            done = true;
                            continue;
                        }
                        if(mo.m[i][j] == 0) //if pivot element is 0
                        {
                            for(int x=i; x<rows; x++)   //then check for row exchange
                            {
                                if(mo.m[x][j] != 0)
                                {
                                    mo.Rij(i+1, x+1);
                                    if(show_steps == true)
                                    {
                                        cout << endl << char(16) << " R " << i+1 << char(29) << x+1 << endl ;
                                        mo.display();
                                    }
                                    row_exchange = true;
                                    break;
                                }
                                if(x == rows-1) //if end is reached and
                                {
                                    if(row_exchange == false)   //no row exchange is occurred
                                        stair_case = true;      //then Stair Case occurs
                                }
                            }
                        }
                        if(stair_case == false && row_exchange == false)   //without any exception, making pivot element = 1
                        {
                            K = mo.m[i][j];
                            mo.KRi(1/K, i+1);
                            if(show_steps == true)
                            {
                                cout << endl << char(16) << " "; K.reciprocal(); cout << " R" << i+1 << endl ;
                                mo.display();
                            }
                            i = -1;
                            done = true;
                        }
                        else if(row_exchange == true)       //if row is exchanged
                        {
                            row_exchange = false;
                            done = false;
                            i = -1;                         //then does the operation (i==j) = 1 again
                            continue;
                        }
                        else if(stair_case == true)     //if   fail to exchange row
                        {                               //then stair case occurs
                            if(j < cols-1)  //bounds check
                                j++;        //goto next column
                            else
                                return mo;
                            pivot_row = i;
                            row_exchange = false;
                            done = false;
                            i -= 1;         //start from same row
                            continue;
                        }
                    }
                }
////////////////////////////////////////////////////////////////////////////////////////////
                else	            // for making elements beneath and above pivot positions = 0
                {
                    if(done == true)
                    {
                        if(mo.m[i][j] == 0) //if already 0
                            continue;
                        K = -1 * mo.m[i][j];
                        mo.Ri_KRj(K, i+1, pivot_row+1);
                        if(show_steps == true)
                        {
                            cout << endl << char(16) << " R" << i+1 << " + (" ; K.cdisplay(); cout << ") R" << pivot_row+1 << endl ;
                            mo.display();
                        }
                    }
                }
            }
///////////////////////////////////////////////////////////////////////////////////////////
        }
        pivot_row ++ ;
        row_exchange = false;
        done = false;
        pivot_found = false;    //for stair case condition
    }
    return mo;
}

matrix matrix::linear_system(bool show_steps = false)
{
    int eqs, vars ;
    char isHomogenous, in[12];
    bool dependent = false;
    matrix ans;
    fraction *holdVars;
    matrix   *holdFreeCols;
    int freeColsCount = 0;


    do
    {
        cout << "Enter No of Equations : " ;
        cin >> eqs ;
        if(eqs == 0)
            return *this;
    }
    while(eqs <= 0 || eqs > 9);
    do
    {
        cout << "Enter No of Variables : " ;
        cin >> vars ;
        if(vars == 0)
            return *this;
    }
    while(vars <= 0 || vars > 9);
    do
    {
        cout << endl << "Is System Homogenous (y/n) : " ;
        cin >> isHomogenous ;
        if(isHomogenous == '0' || isHomogenous == 27 )
            return *this;
    }
    while(isHomogenous != 'y' && isHomogenous != 'Y' && isHomogenous != 'N' && isHomogenous != 'n');

    matrix *mo = new matrix(eqs, vars+1);
        if(!mo) exit(EXIT_FAILURE); //checking dynamic memory alloc

    int maxPivots;
    /*maxPivots = */  eqs <= vars ? maxPivots = eqs : maxPivots = vars ;
    holdVars = new fraction[maxPivots];
        if(!holdVars) exit(EXIT_FAILURE);   //checking dynamic memory alloc

    holdFreeCols = new matrix(eqs, vars);   //for holding free vars in different cols
        if(!holdFreeCols) exit(EXIT_FAILURE);   //checking dynamic memory alloc

    for(int i=0; i<eqs; i++)
    {
        cout << "\n\n" << char(16) << " Enter Coefficients for Equation " << i+1 << endl ;
        for(int j=0; j<vars+1; j++)
        {
            if(j == vars)
            {
                if(isHomogenous == 'y' || isHomogenous == 'Y')
                {
                    mo->m[i][j] = 0;
                    cout << "Constant in assigned 0" ;
                }
                else
                {
                    cout << "Value for constant-" << i+1 << " : " ;
                    fflush(stdin);
                    gets(in) ;
                    mo->m[i][j](in);
                }
                continue;
            }
            cout << "Coefficient of x" << j+1 << " : " ;
            fflush(stdin);
            gets(in);
            mo->m[i][j](in);
        }
    }
    cout << "\n\n" << char(16) << " Linear System in Matrix Form" << endl ;
    mo->display();
    ans = mo->reduce_echelon(false);
    cout << "\n\n" << char(16) << " Solution of System in Matrix Form" << endl ;
    ans.display();
    ////////////Solution of Variables Starts from here///////////
    if( vars > eqs )
    {
        dependent = true;
    }
  //if stair-case occurred and a pivot is 0
    else
    {
        int x, y;
        x = y = 0;
        while(x < eqs && y < vars)
        {
            if(ans.m[x][y] == 0)    //if any pivot position is 0
            {
                dependent = true;
                break;
            }
            x++; y++;
        }
    }
    cout << "\n\n" << char(16) << " Linear Dependency : " ; dependent == true ? cout << "Dependent" : cout << "Independent";

    if(dependent == false)
    {
        int pos = 0;
        cout << "\n\n" << char(16) << " Unique Solution";
        cout << "\n\n" << char(16) << " Solution to Variables" << "\n\n" ;
        for(int i=0; i<eqs; i++)
        {
            for(int j=0; j<vars; j++)
            {
                if(i == j)
                {
                    holdVars[pos] = ans.m[i][vars];
                    cout << "  x" << i+1 << " = " ;
                    holdVars[i] < 0 ? cout << holdVars[i] : cout << " " << holdVars[i] ;
                    cout << "\n";
                    pos++;
                }
            }
        }
    }
    else //if free column - system is dependent
    {
        bool stair_case = false,
             this_col_done = false,
             this_col_free = false,
             this_has_pivot = false;

        cout << "\n\n" << char(16) << " Infinitely Many Solutions" ;
        cout << "\n\n" << char(16) << " Solution to Variables" << "\n\n" ;
        /////////////////////////////////////////////////////
        cout << "[\t";
        for(int x=0; x<vars; x++)       // [ x1 x2 x3 x4 x5 ]
        {
            cout << "x" << x+1 << "\t" ;
        }
        cout << "]\n= \n";
        /////////////////////////////////////////////////////

        bool first_time = true;
        //This first checks a column then go back and print it
        for(int j=0; j<vars; j++)       // [ 2 7 99 8 22]x4 //coefficients of free vars
        {
            for(int i=0; i<eqs; i++)
            {
                if(i == j)
                {
                    if(ans.m[i][j] == 0)
                    {
                        if(this_col_done == false)
                        {
                            if(i > 0)   //if not 1st row
                            {
                                if(ans.m[i-1][j] == 1)      //if pivot is at normal position
                                {
                                    this_col_free = false;
                                    this_has_pivot = true;
                                }
                                else if(ans.m[i-1][j] == 0) //if stair case
                                {
                                    this_col_free = true;
                                    this_has_pivot = false;
                                }
                            }
                            i = -1;
                            stair_case = true;
                            this_col_done = true;
                        }
                    }
                }
                if(this_col_done == true)
                {
                    if(this_col_free == true)
                    {
                        ans.m[i][j] *= -1;
                        ans.m[i][j].cdisplay(); cout << "\t" ;
                    }
                }
                if(j >= eqs)
                {
                    if(first_time == true)
                    {
                        cout << "[\t";
                        first_time = false;
                    }
                    ans.m[i][j] *= -1;
                    ans.m[i][j].cdisplay(); cout << "\t" ;
                    if(i == eqs-1) //here for loop to print remaining (free) var
                    {
                        static int free_var_pos = eqs;
                        for(int x=eqs; x<vars; x++)
                        {
                            if(x == free_var_pos)
                                cout << 1 ;
                            else
                                cout << 0 ;
                            cout << "\t" ;
                        }
                        free_var_pos++;
                        this_col_done = true;
                    }

                }
            }

            if(this_col_free == true || this_col_done == true)
            {
                cout << "] X" << j+1 << endl ;
                if(j < vars-1)
                    cout << "+" << endl ;
            }
            first_time = true;
            this_col_done = false;
            this_col_free = false;
            this_has_pivot = false;
        }
        /////////////////////////////////////////////////////
        cout << "+\n[\t";
        for(int x=0; x<vars; x++)
        {
            if(x >= eqs)
                cout << 0 ;
            else
                ans.m[x][vars].cdisplay();
            cout << "\t";
        }
        cout << "]\n\n";
        /////////////////////////////////////////////////////
    }

    fflush(stdin);
    delete holdVars;
    delete mo;
    return ans;
}

bool matrix::isSquare()
{
    if(rows == cols)
        return true;
    else
        return false;
}

matrix matrix::power(int pow)
{
    matrix temp(*this);
    for(int i=1; i<pow; i++)
        temp = temp * temp;
    return temp;
}

fraction matrix::determinant()
{
    if(rows == cols)
    {
        fraction determinant = 1;
        matrix temp(*this);
        temp = temp.echelon(false);
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                if(i == j)
                    determinant *= temp.m[i][j];
            }
        }
        return determinant;
    }
    return 0;
}

matrix matrix::inverse()
{
    if(rows == cols)
    {
        if(determinant() != 0)
        {
            matrix mo;
            mo.rows = rows;
            mo.cols = cols * 2;
            mo.cells = mo.rows * mo.cols;
            mo.m = new(nothrow) fraction*[rows];
            for(int i=0; i<rows; i++)
            {
                mo.m[i] = new(nothrow) fraction[mo.cols];
            }
            if(!mo.m) exit(EXIT_FAILURE);

            for(int i=0 ; i<rows; i++)
            {
                for(int j=0; j<cols; j++)
                    mo.m[i][j] = m[i][j];
            }

            for(int i=0; i<rows; i++)
            {
                for(int j=cols; j<mo.cols; j++)
                {
                    if( (j-i) == cols)
                        mo.m[i][j] = 1;
                    else
                        mo.m[i][j] = 0;
                }
            }
            mo = mo.reduce_echelon(false);
            matrix temp(mo.rows,mo.cols/2);	//take temp matrix to store inverse
            for(int i=0; i<temp.rows; i++)	//assign the inverse to a matrix
            {
                for(int j=0; j<temp.cols; j++)
                {
                    temp.m[i][j] = mo.m[i][j+cols];
                }
            }
            return temp;
        }
        return (*this);
    }
    return (*this);
}

matrix matrix::transpose()
{
    matrix temp(cols,rows);
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            temp.m[j][i] = m[i][j];
    }
    return temp;
}

fraction matrix::trace()
{
    fraction trace = 0;
    matrix temp = *this;
    temp = temp.echelon(false);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(i == j)
                trace += temp.m[i][j];
        }
    }
    return trace;
}

int matrix::rank()
{
    int rank = 0;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(i == j)
                rank++;
        }
    }
    return rank;
}

inline void matrix::Rij(int i, int j)
{
    i-=1; j-=1;
    fraction hold[cols];
    for(int x=0; x<cols; x++)
    {
        hold[x] = m[i][x];
        m[i][x] = m[j][x];
        m[j][x] = hold[x];
    }
}

inline void matrix::KRi(fraction K, int i)
{
    i-=1;
    for(int x=0; x<cols; x++)
        m[i][x] *= K;
}

inline void matrix::Ri_KRj(fraction K, int i, int j)
{
    i-=1; j-=1;
    for(int x=0; x<cols; x++)
    {
        m[i][x] += K * m[j][x];
    }
}

matrix matrix::operator+(matrix mo)
{
    if(rows == mo.rows && cols == mo.rows)
    {
        register int i, j;
        matrix temp(rows,cols);
        for(i=0; i<rows; i++)
        {
            for(j=0; j<cols; j++)
            {
                temp.m[i][j] = m[i][j] + mo.m[i][j];
            }
        }
    return temp;
    }
}

matrix matrix::operator-(matrix mo)
{
    if(rows == mo.rows && cols == mo.cols)
    {
        register int i, j;
        matrix temp(rows,cols);
        for(i=0; i<rows; i++)
        {
            for(j=0; j<cols; j++)
            {
                temp.m[i][j] = m[i][j] - mo.m[i][j];
            }
        }
    return temp;
    }
}

matrix matrix::operator*(matrix mo)
{
    if(cols == mo.rows)
    {
        matrix temp(rows,mo.cols);
        int i, j, x=0, y=0;
        fraction sum=0, product=1;
        for(i=0; i<rows; i++)
        {
            for(int a=0; a<mo.cols; a++)
            {
                for(j=0; j<cols; j++)
                {
                    product = m[i][j] * mo.m[x][y];
                    sum += product;
                    x++;
                }
                x=0;
                temp.m[i][a] = sum ;
                y++;
                sum=0; product=1;
            }
            y=0;
        }
        return temp;
    }
    return (*this);
}

matrix operator*(matrix mo, fraction num)
{
    matrix temp(mo);
    for(int i=0; i<temp.rows; i++)
    {
        for(int j=0;j <temp.cols; j++)
            temp.m[i][j] *= num;
    }
    return temp;
}

matrix operator*(fraction num, matrix mo)
{
    matrix temp(mo);
    for(int i=0; i<temp.rows; i++)
    {
        for(int j=0;j <temp.cols; j++)
            temp.m[i][j] *= num;
    }
    return temp;
}

matrix operator/(matrix mo, fraction num)
{
    matrix temp(mo);
    for(int i=0; i<temp.rows; i++)
    {
        for(int j=0; j<temp.cols; j++)
            temp.m[i][j] /= num;
    }
    return temp;
}

matrix operator/(fraction num, matrix mo)
{
    matrix temp(mo);
    for(int i=0; i<temp.rows; i++)
    {
        for(int j=0; j<temp.cols; j++)
            temp.m[i][j] /= num;
    }
    return temp;
}

matrix matrix::operator=(const matrix &mo)
{
    /* check for self assignment */
    if(this == &mo)
    {	return (*this); }
    /* If rows and columns are same */
    if(rows == mo.rows && cols == mo.cols)
    {
        register int i, j;
        for(i=0; i<rows; i++)
        {
            for(j=0; j<cols; j++)
            {
                m[i][j] = mo.m[i][j];
            }
        }
    }
    else
    {
        undo();
        rows = mo.rows;
        cols = mo.cols;
        cells = rows * cols;
        m = new(nothrow) fraction *[rows];
        for(int i=0; i<rows; i++)
        {	m[i]=new(nothrow) fraction[cols];	}
        if(!m)	exit(EXIT_FAILURE);
        for(int i=0; i<rows ;i++)
        {
            for(int j=0; j<cols; j++)
            {	m[i][j] = mo.m[i][j];	}
        }
    }
    return (*this);
}

matrix matrix::operator=(const matrix *mo)
{
    /* check for self assignment */
    if(this == mo)
    {	return (*this); }
    /* If rows and columns are same */
    if(rows == mo->rows && cols == mo->cols)
    {
        register int i, j;
        for(i=0; i<rows; i++)
        {
            for(j=0; j<cols; j++)
            {
                m[i][j] = mo->m[i][j];
            }
        }
    }
    else
    {
        undo();
        rows = mo->rows;
        cols = mo->cols;
        cells = rows * cols;
        m = new(nothrow) fraction *[rows];
        for(int i=0; i<rows; i++)
        {	m[i]=new(nothrow) fraction[cols];	}
        if(!m)	exit(EXIT_FAILURE);
        for(int i=0; i<rows ;i++)
        {
            for(int j=0; j<cols; j++)
            {	m[i][j] = mo->m[i][j];	}
        }
    }
    return (*this);
}

fraction& matrix::operator()(int x, int y)
{
    if( (x >= 0 && x < rows ) && ( y >= 0 && y < cols ) )
    {
        return m[x][y];
    }
}

bool matrix::operator==(matrix mo)
{
    if(rows == mo.rows && cols == mo.cols)
    {
        register int i, j;
        for(i=0; i<rows; i++)
        {
            for(j=0; j<cols; j++)
            {
                if(m[i][j] != mo.m[i][j])
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool operator==(matrix m, matrix *mo)
{
    if(m.rows == mo->rows && m.cols == mo->cols)
    {
        register int i, j;
        for(i=0; i<m.rows; i++)
        {
            for(j=0; j<m.cols; j++)
            {
                if(m.m[i][j] != mo->m[i][j])
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool matrix::operator!=(matrix mo)
{
    if(rows == mo.rows && cols == mo.cols)
    {
        return true;
    }
    else
        return false;
}
