#ifndef MATRIX_H
#define MATRIX_H


class matrix
{
private:
	int rows, cols, cells;
	fraction **m;
	void undo();
	void reset(int , int );
public:
	matrix();                   /*main constructor*/
	matrix(int , int );         /*copy constructor*/
	matrix(const matrix &);     /*destructor*/
	matrix(const matrix *);     /*copy constructor for pointers*/
	~matrix();

	void assign();
	void display();

	void adjustZeroRow();
	bool isSquare();
	matrix echelon(bool );
	matrix echelon_with_1(bool );
	matrix reduce_echelon(bool );
	matrix linear_system(bool );
	fraction determinant();
	matrix power(int );
	matrix inverse();
	matrix transpose();
	fraction trace();
	int rank();

	void Rij(int, int );
	void KRi(fraction, int );
	void Ri_KRj(fraction, int, int);

	matrix operator+(matrix );
	matrix operator*(matrix );
	matrix operator-(matrix );
	matrix operator=(const matrix &);
	matrix operator=(const matrix *);
	friend matrix operator*(matrix , fraction );
	friend matrix operator*(fraction , matrix );
	friend matrix operator/(matrix , fraction );
	friend matrix operator/(fraction , matrix );

	fraction& operator()(int, int);
	bool operator==(matrix );
	bool operator!=(matrix );
	friend bool operator==(matrix, matrix *);
};

#endif // MATRIX_H
