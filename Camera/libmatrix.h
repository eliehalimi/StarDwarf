# ifndef LIBMATRIX_OCR_S3
# define LIBMATRIX_OCR_S3

//I AM NOT THE AUTHOR OF THIS LIBRARY

struct matrix
{
	short int line, col;
	float *grid;
};


void printMat(struct matrix *mat);


/*
 * Creation of the matrix: take two int (line & col) as parameters
 * Care: Line and col are stored as short int (2B wide).
 * We first allocate memory for the structure,
 * Then for the array of pointers to integer.
 * For array "destruction" see freeMat(...);
 */
struct matrix *newMat(int line, int col);


/*
 * Multiplication of two arrays.
 * The arrays are not modified in place (as it is impossible without storing the matrix created;
 * So the returned array is important here.
 */
struct matrix *mult(struct matrix *mat1, struct matrix *mat2);


/*
 * Multiply a matrix by an int. It's not possible in C to overload "+" operator.
 * Altho it is in C++;
 * the returned value in not mandatory as we're modyfying the matrix in place.
 */
struct matrix *multByInt(struct matrix *mat, int k);


/* 
 * Take a matrix, and use the int array to fill the appropriate cases;
 * Does not take into count size of the array
 * Modify the matrix in place, but still return it.
 */
struct matrix *fill(struct matrix *mat, float grid[], size_t gridlen);


/*
 * Free the matrix.  What else?
 */
void freeMat(struct matrix *mat);


/*
 * Take a matrix and copy its values into a new matrix.
 * Here the returned matrix IS IMPORTANT;
 */
struct matrix *clone(struct matrix *mat);


/*
 * Add two matrices to each other
 * Return the matrix of the addition. DOES NOT MODIFY IN PLACE
 * Return a null pointer if incorrect sizes;
 */
struct matrix *add(struct matrix *mat1, struct matrix *mat2);



/*
 * Takes two matrices of the same size and return the result of the
 * substraction in a new matrices.
 * Does not modify in place; Return NULL if wrong sizes;
 */
struct matrix *substract(struct matrix *mat1, struct matrix *mat2);

/*
 * Return the value at designed line and column from the matrix.
 * return \0 as an error
 */
unsigned char get(struct matrix *mat, int line, int col);

/*
 * SetValue:
 * -takes a matrix and a position in the matrix and set the value in this position
 */
void set(struct matrix *mat, int line, int col, char val);

struct vector *mult_vector(struct matrix *mat, struct vector *vect);

# endif
