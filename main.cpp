
/**********************************************************
*
*   PROJECT NAME:
*       "MATRIX MANIPULATOR"
*
*   DEVELOPER:
*       Mohammad Shaharyar Siddiqui
*
*   PLATFORM:
*       Microsoft Windows 7 or better
*
*   USER-INTERFACE:
*       Command-Line
*
*   COMPILER:
*       GCC
*
*   COMPILATION TIME:
*       3 seconds approx
*
*   APPLICATION SIZE:
*       Less than 1.5 MB
*
*   DATE STARTED:
*       Mid of November 2014
*
*   DATE COMPLETED:
*       Mid of December 2014
*
*   LICENSE:
*       No License - FreeWare
*
*   RUN-TIME LIBRARIES:
*       No Run-Time libraries required.
*
*   FIRST RELEASE (VERSION):
*       1.0.0.0 - December 2014
*
*   LATEST VERSION (STABLE RELEASE):
*       1.1.0.0 - MAY 2015
*
***********************************************************/

//
//  VERSION     1.1.0.0
//


#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <new>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fraction.h>
#include <matrix.h>

#define null 0

#define yes 1
#define no 0

#define ESC 27
#define RET 13
#define BSP 8
#define SPC 32

using namespace std;

void gotoxy(short col, short row)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { col,row };
	SetConsoleCursorPosition(h,position);
}

void line(int length)
{
    for(int i=0; i<length; i++)
        cout << char(196) ;
    cout << endl ;
}

void ProgramTitle()
{
    cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl ;
    cout << char(186) << " MATRIX MANIPULATOR " << char(186) << endl ;
    cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl << endl ;
}

void tail(int length = 80)
{
    gotoxy(0,25);

    line(length);

    gotoxy(35,27);
    cout << "< Developed By M. Sherry Sid >" ;
    gotoxy(0,0);
}

void heading(string title)
{
    cout << " " << title << endl ;
    line(title.length() + 2);
}

void Message(const char *s = "Matrix Must be Square!")
{
    cout << endl << endl << s << endl ;
}

matrix* factory(int r, int c)       //object generator
{
    return new(nothrow) matrix(r,c);
}

int rows, cols;
void RecieveOrder()
{
    cout << "\n\n" << "Enter Order of Matrix" << endl ;

    do
    {
        cout << "> Rows : " ;
        cin  >> rows ;
    }
    while(rows <= 0 || rows > 10);

    do
    {
        cout << "> Columns : " ;
        cin  >> cols ;
    }
    while(cols <= 0 || cols > 10);
}

bool IsSquare()
{
    if(rows == cols)
        return true;
    else
        return false;
}

bool ViewSteps()
{
    char ask;
    fflush(stdin);

    cout << "\n\n" << "Do You Want to View Steps Of Operations? (y/n) : " ;
    ask = getche();

    if(ask == 'y' || ask == 'Y' || ask == RET || ask == SPC)
        return true;
    else
        return false;

}

matrix InputMatrix(int r, int c)
{
    matrix *temp = factory(r, c);

    cout << "\n\nAssign Values to Matrix :" << endl ;
    cout << "(Enter Values Row Wise.)" << endl ;
    cout << "(Enter Values by Pressing Enter)" << endl << endl ;

    temp->assign();

    return *temp;
}

int AskForMatrix()
{
    char ask ;
    fflush(stdin);

    cout << endl << "Select Matrix:" << endl ;
    cout << endl << "1. General Matrix" ;
    cout << endl << "2. Create New Matrix" ;
    cout << endl << "3. Last Answer (Matrix, not Scalar)" << endl ;
    cout << endl << "0. Back" << endl ;
    cout << endl << ">> " ;
    ask = getche();

    switch(ask)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case SPC:
        return 3;
    default:
        return 0;
    }
}

int main()
{
    int menu_choice;
    char repeat;
    matrix *general = null,
           *ptr = null,
            answer;

    general = factory(1,1);
    answer  = *general;

    while(true)
    {
        system("cls");
        ProgramTitle();

        heading("MENU");
        cout << endl ;

        cout << "1.  Set A General Matrix and Do Random Operations"  << endl  << endl ;
        cout << "2.  Inverse\t\t|"          << "   8.  Echelon Form" << endl  << endl ;
        cout << "3.  Determinant\t\t|"      << "   9.  Reduced Echelon Form"  << endl << endl ;
        cout << "4.  Transpose\t\t|"        << "  10.  Linear System" << endl << endl ;
        cout << "5.  Power of Matrix\t|"    << endl << endl ;
        cout << "6.  Rank of Matrix\t|"     << endl << endl ;
        cout << "7.  Trace of Matrix\t|"    << endl << endl ;
        cout << "0.  EXIT"                  << endl << endl ;
        cout << ">>  " ;                    fflush(stdin)   ;
        cin >> menu_choice ;

        switch(menu_choice)
        {
            case 1:
            {
                system("cls");
                heading("GENERAL MATRIX");

                RecieveOrder();
                *general = InputMatrix(rows, cols);

                if(! general)
                {
                    Message("Failed to Allocate Matrix\nPlease Restart Program.");
                }
                else
                {
                    cout << endl << "General Matrix Saved!" ;
                    cout << endl << endl ;
                    general->display();
                    getch();

                    continue;
                }
                break;
            }
            case 2:
            {
                system("cls");
                heading("INVERSE Of MATRIX");

                switch(AskForMatrix())
                {
                case 1:
                    {
                        if(general->isSquare())
                        {
                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            general->display();
                            cout << endl << endl ;

                            answer = general->inverse();

                            if(answer == general)
                            {
                                cout << endl << char(16) << " Det|general| = 0, Therefore Inverse Does not Exist!" << endl ;
                            }
                            else
                            {
                                cout << char(16) << " Inverse of Matrix" << endl ;
                                answer.display();
                            }
                        }
                        else
                            Message();

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        if(IsSquare())
                        {
                            answer = InputMatrix(rows, cols);
                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            answer.display();
                            cout << endl << endl ;

                            matrix temp = answer.inverse();

                            if(answer == temp)
                            {
                                cout << endl << char(16) << " Det|A| = 0, Therefore Inverse Does not Exist!" << endl ;
                            }
                            else
                            {
                                answer = temp;
                                cout << char(16) << " Inverse of Matrix" << endl ;
                                answer.display();
                            }
                        }
                        else
                            Message();

                        break;
                    }
                case 3:
                    {
                        if(answer.isSquare())
                        {
                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            answer.display();
                            cout << endl << endl ;

                            matrix temp = answer.inverse();

                            if(answer == temp)
                            {
                                cout << endl << char(16) << " Det|general| = 0, Therefore Inverse Does not Exist!" << endl ;
                            }
                            else
                            {
                                answer = temp;
                                cout << char(16) << " Inverse of Matrix" << endl ;
                                answer.display();
                            }
                        }
                        else
                            Message();

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 3:
            {
                system("cls");
                heading("DETERMINANT Of MATRIX");

                switch(AskForMatrix())
                {
                case 1:
                    {
                        if(general->isSquare())
                        {
                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            general->display();
                            cout << endl << endl ;

                            cout << char(16) << " Determinant of Matrix is " << general->determinant() << endl ;
                        }
                        else
                            Message();

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        if(IsSquare())
                        {
                            *ptr = InputMatrix(rows, cols);

                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            ptr->display();
                            cout << endl << endl ;

                            cout << char(16) << " Determinant of Matrix is " << ptr->determinant() << endl ;

                            delete ptr;
                        }
                        else
                            Message();

                        break;
                    }
                case 3:
                    {
                        if(answer.isSquare())
                        {
                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            answer.display();
                            cout << endl << endl ;

                            cout << char(16) << " Determinant of Matrix is " << answer.determinant() << endl ;
                        }
                        else
                            Message();

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 4:
            {
                system("cls");
                heading("TRANSPOSE Of MATRIX");

                switch(AskForMatrix())
                {
                case 1:
                    {
                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        general->display();
                        cout << endl << endl ;

                        answer = general->transpose();

                        cout << char(16) << " Transpose of Matrix" << endl ;
                        answer.display();

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();

                        answer = InputMatrix(rows, cols);

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        answer = answer.transpose();

                        cout << char(16) << " Transpose of Matrix" << endl ;
                        answer.display();

                        break;
                    }
                case 3:
                    {
                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        answer = answer.transpose();

                        cout << char(16) << " Transpose of Matrix" << endl ;
                        answer.display();

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 5:
            {
                system("cls");
                heading("POWER Of MATRIX");
                int power;

                switch(AskForMatrix())
                {
                case 1:
                    {
                        if(general->isSquare())
                        {
                            cout << "\n\n" << "> Enter Power : " ;
                            cin >> power ;

                            cout << endl << char(16) << " Given Matrix" << endl ;
                            general->display();
                            cout << endl << endl ;

                            answer = general->power(power);

                            cout << char(16) << " Matrix Raised to Power " << power << " is" << endl ;
                            answer.display();
                        }
                        else
                            Message();

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        if(IsSquare())
                        {
                            answer = InputMatrix(rows, cols);

                            cout << endl << "> Enter Power : " ;
                            cin >> power ;

                            cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                            answer.display();
                            cout << endl << endl ;

                            answer = answer.power(power);

                            cout << char(16) << " Matrix Raised to Power " << power << " is" << endl ;
                            answer.display();
                        }
                        else
                            Message();

                        break;
                    }
                case 3:
                    {
                        if(answer.isSquare())
                        {
                            cout << "\n\n" << "> Enter Power : " ;
                            cin >> power ;

                            cout << endl << char(16) << " Given Matrix" << endl ;
                            answer.display();
                            cout << endl << endl ;

                            answer = answer.power(power);

                            cout << char(16) << " Matrix Raised to Power " << power << " is" << endl ;
                            answer.display();
                        }
                        else
                            Message();

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 6:
            {
                system("cls");
                heading("RANK Of MATRIX");

                switch(AskForMatrix())
                {
                case 1:
                    {
                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        general->display();
                        cout << endl << endl ;

                        cout << char(16) << " Rank of Matrix is " << general->rank() << endl ;

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        *ptr = InputMatrix(rows, cols);

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        ptr->display();
                        cout << endl << endl ;

                        cout << char(16) << " Rank of Matrix is " << ptr->rank() << endl ;

                        delete ptr;

                        break;
                    }
                case 3:
                    {
                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        cout << char(16) << " Rank of Matrix is " << answer.rank() << endl ;

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 7:
            {
                system("cls");
                heading("TRACE Of MATRIX");

                switch(AskForMatrix())
                {
                case 1:
                    {
                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        general->display();
                        cout << endl << endl ;

                        cout << char(16) << " Trace of Matrix is " << general->trace() << endl ;

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        *ptr = InputMatrix(rows, cols);

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        ptr->display();
                        cout << endl << endl ;

                        cout << char(16) << " Trace of Matrix is " << ptr->trace() << endl ;

                        delete ptr;

                        break;
                    }
                case 3:
                    {
                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        cout << char(16) << " Trace of Matrix is " << answer.trace() << endl ;

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 8:
            {
                system("cls");
                heading("ECHELON FORM Of MATRIX");
                bool showsteps = false;

                switch(AskForMatrix())
                {
                case 1:
                    {
                        showsteps = ViewSteps();

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        general->display();
                        cout << endl << endl ;

                        cout << char(16) << " Echelon Form of Matrix" << endl ;
                        answer = general->echelon(showsteps);

                        if(showsteps == false)
                            answer.display();

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        showsteps = ViewSteps();

                        answer = InputMatrix(rows, cols);

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        cout << char(16) << " Echelon Form of Matrix" << endl ;
                        answer = answer.echelon(showsteps);

                        if(showsteps == false)
                            answer.display();

                        break;
                    }
                case 3:
                    {
                        showsteps = ViewSteps();

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        cout << char(16) << " Echelon Form of Matrix" << endl ;
                        answer = answer.echelon(showsteps);

                        if(showsteps == false)
                            answer.display();

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 9:
            {
                system("cls");
                heading("REDUCED ECHELON FORM Of MATRIX");
                bool showsteps = false;

                switch(AskForMatrix())
                {
                case 1:
                    {
                        showsteps = ViewSteps();

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        general->display();
                        cout << endl << endl ;

                        cout << char(16) << " Echelon Form of Matrix" << endl ;
                        answer = general->reduce_echelon(showsteps);

                        if(showsteps == false)
                            answer.display();

                        break;
                    }
                case 2:
                    {
                        RecieveOrder();
                        showsteps = ViewSteps();

                        answer = InputMatrix(rows, cols);

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        cout << char(16) << " Echelon Form of Matrix" << endl ;
                        answer = answer.reduce_echelon(showsteps);

                        if(showsteps == false)
                            answer.display();

                        break;
                    }
                case 3:
                    {
                        showsteps = ViewSteps();

                        cout << "\n\n" << char(16) << " Given Matrix" << endl ;
                        answer.display();
                        cout << endl << endl ;

                        cout << char(16) << " Echelon Form of Matrix" << endl ;
                        answer = answer.reduce_echelon(showsteps);

                        if(showsteps == false)
                            answer.display();

                        break;
                    }
                default:
                    {
                        continue;
                    }
                }

                break;
            }
            case 10:
            {
                system("cls");
                heading("SYSTEM OF LINEAR EQUATIONS");

                matrix temp = answer;                   //make a copy of answer to check if
                answer = answer.linear_system(true);    //this function has returned the same matrix as to GO BACK

                if(answer == temp)                      //if same matrix is returned
                    continue;                           //then go back

                break;
            }
            case 0:
            {
                system("cls");
                delete general;
                exit(EXIT_SUCCESS);
            }
            default:
            {
                cout << "Select From Only Given Indexes!" << endl ;
                fflush(stdin);
                getch();
                continue;
            }
        }//end switch

        fflush(stdin);

        cout << endl << endl << "Y - Goto Main Menu" ;
        cout << endl << "N - Exit" << endl ;
        repeat = getch();
        if(repeat == 'n' || repeat == 'N' || repeat == ESC)
            break;
    }

    system("cls");
    delete ptr;
    delete general;

    cout << endl ;
    return 0;
}
