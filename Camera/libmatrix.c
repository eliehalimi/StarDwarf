# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "libmatrix.h"
# include "../Physic/libvector.h"

void printMat(struct matrix *mat)
{
	printf("\n");
	for(int i = 0; i < mat->line; i++)
	{
		for(int j = 0; j < mat->col; j++)
		{
			printf("%f ", mat->grid[i * mat->col + j]);
		}
		printf("\n");
	}
}


/*
 * Creation of the matrix: take two int (line & col) as parameters
 * Care: Line and col are stored as short int (2B wide).
 * We first allocate memory for the structure,
 * Then for the array of pointers to integer.
 * For array "destruction" see freeMat(...);
 */
struct matrix *newMat(int line, int col)
{
	struct matrix *new;
	new = malloc(sizeof(struct matrix));
	new->line = (short int)line;
	new->col = (short int)col;
	new->grid = malloc(sizeof(float) * line * col);
	for(int i = 0; i < line * col; i++)
		new->grid[i] = 0;
	return new;

} 

/*
 * Multiplication of two arrays.
 * The arrays are not modified in place (as it is impossible without storing the matrix created;
 * So the returned array is important here.
 */
struct matrix *mult(struct matrix *mat1, struct matrix *mat2)
{
	assert(mat1->col == mat2->line);

	struct matrix *new = newMat(mat1->line, mat2->col);

	for(int i = 0; i < mat1->line; i++)
		for(int j = 0; j < mat2->col; j++)
			for(int k = 0; k < mat2->line; k++)
				new->grid[i * mat2->col + j] += mat1->grid[i * mat1->col + k] * mat2->grid[k * mat2->col + j];
	return new;
}


/*
 * Multiply a matrix by an int. It's not possible in C to overload "+" operator.
 * Altho it is in C++;
 * the returned value in not mandatory as we're modyfying the matrix in place.
 */
struct matrix *multByInt(struct matrix *mat, int k)
{
	for(int i = 0; i < mat->line * mat->col; i++)
		mat->grid[i] *= k;
	return mat;
}


/* 
 * Take a matrix, and use the int array to fill the appropriate cases;
 * Does not take into count size of the array
 * Modify the matrix in place, but still return it.
 */
struct matrix *fill(struct matrix *mat, float grid[], size_t gridlen)
{
	size_t len = mat->line * mat->col;
	assert(len >= gridlen);
	for(size_t i = 0; i < len; i++)
		mat->grid[i] = grid[i];
	return mat;
}


/*
 * Free the matrix.  What else? *Nespresso* 
 */
void freeMat(struct matrix *mat)
{
	free(mat->grid);
	free(mat);
}


/*
 * Take a matrix and copy its values into a new matrix.
 * Here the returned matrix IS IMPORTANT;
 */
struct matrix *clone(struct matrix *mat)
{
	struct matrix *new = newMat(mat->line, mat->col);
	for(int i = 0; i < mat->line * mat->col; i++)
		new->grid[i] = mat->grid[i];
	return new;
}


/*
 * Add two matrices to each other
 * Return the matrix of the addition. DOES NOT MODIFY IN PLACE
 * Return a null pointer if incorrect sizes;
 */
struct matrix *add(struct matrix *mat1, struct matrix *mat2)
{
	assert(mat1->line == mat2->line && mat1->col == mat2->col);
	if(mat1->line != mat2->line || mat1->col != mat2->col)
		return NULL;
	struct matrix *new = newMat(mat1->line, mat1->col);
	for(int i = 0; i < mat1->line * mat1->col; i++)
		new->grid[i] = mat1->grid[i] + mat2->grid[i];
	return new;
}


/*
 * Takes two matrices of the same size and return the result of the
 * substraction in a new matrices.
 * Does not modify in place; Return NULL if wrong sizes;
 */
struct matrix *substract(struct matrix *mat1, struct matrix *mat2)
{
	assert(mat1->line == mat2->line && mat1->col == mat2->col);
	if(mat1->line != mat2->line || mat1->col != mat2->col)
		return NULL;
	struct matrix *new = newMat(mat1->line, mat2->line);
	for(int i = 0; i < mat1->line * mat1->col; i++)
		new->grid[i] = mat1->grid[i] - mat2->grid[i];
	return new;
}

/*
 * Getvalue:
 * -Takes a matrix and a position in the matrix, and returns the value.
 * return '\0' as an error;
 */
unsigned char get(struct matrix *mat, int line, int col)
{
	assert(line < mat->line && col < mat->col);
	if(line >= mat->line || col >= mat->col)
		return '\0'; // This is an error
	return mat->grid[line * mat->col + col];
}


/*
 * SetValue:
 * -takes a matrix and a position in the matrix and set the value in this position
 */
void set(struct matrix *mat, int line, int col, char val)
{
	assert(line < mat->line && col < mat->col);
	if(line >= mat->line || col >= mat->col)
		return;
	mat->grid[line * mat->col + col] = val;
	return;
}


struct vector *mult_vector(struct matrix *mat, struct vector *vect)
{
	assert(mat != NULL);
	assert(vect != NULL);


	struct matrix *m = newMat(vect->size, 1);

	for(size_t i = 0; i < vect->size; i++)
		m->grid[i] = vect->values[i];

	struct matrix *resmat = mult(mat, m);
	freeMat(m);
	struct vector *resvect = new_vector(vect->size, resmat->grid);
	freeMat(resmat);
	for(size_t i = 0; i < vect->size; i++)
	{
		vect->values[i] = resvect->values[i];
	}

	free_vector(resvect);
	return vect;
}
