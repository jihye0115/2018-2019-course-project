#define ROWS 3
#define COLS 3
#define MAX_TERMS 10
typedef struct {
int row;
int col;
int value;
} element;
typedef struct SparseMatrix {
element data[MAX_TERMS];
int rows; // row number
int cols; // column number
int terms; // element number
} SparseMatrix;
// Addition
// c = a + b
SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)
{
SparseMatrix c;
int ca=0, cb=0, cc=0; // Index indicating terms in each array
// Check if array a and array b are the same size.
char stderr;
if( a.rows != b.rows || a.cols != b.cols ){
fprintf(stderr," Size error in Sparse matrix \n");
exit(1);
}
c.rows = a.rows;
c.cols = a.cols;
c.terms = 0;
while( ca < a.terms && cb < b.terms ){
// Compute the index of each item.
int inda = a.data[ca].row * a.cols + a.data[ca].col;
int indb = b.data[cb].row * b.cols + b.data[cb].col;
// If the array ¡®a¡¯ entry is in front
if( inda < indb) {
c.data[cc++] = a.data[ca++];
}
// If ¡®a¡¯ and ¡®b¡¯ are the same location
else if( inda == indb ){
if( (a.data[ca].value+b.data[cb].value)!=0){
c.data[cc].row = a.data[ca].row;
c.data[cc].col = a.data[ca].col;
c.data[cc++].value = a.data[ca++].value +
b.data[cb++].value;
}
else
ca++; cb++;
}
else // If the array ¡®b¡¯ entry is in front
c.data[cc++] = b.data[cb++];
}
// Copy and paste the remaining terms in ¡®a¡¯ and ¡®b¡¯ into ¡®c¡¯.
for(; ca < a.terms; )
c.data[cc++] = a.data[ca++];
for(; cb < b.terms; )
c.data[cc++] = b.data[cb++];
c.terms = cc;
return c;
}
main()
{
SparseMatrix m1 = {{{ 1,1,5 },{ 2,2,9 }}, 3,3,2 };
SparseMatrix m2 = {{{ 0,0,5 },{ 2,2,9 }}, 3,3,2 };
SparseMatrix m3;
m3 = sparse_matrix_add2(m1, m2);
}
