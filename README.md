# matrix_multiplications_version2
This program calculates the product of two different matrices .

The matrix's result dimesion is 'm'rows 'n' columns.

The number of rows 'm' will be divided into 'Num_ROW' and the number of colomns 'n' into 'NUM_COL'.

The matrix result will be devided into (Num_ROW*NUM_COL) sub-matrices.

Each thread calculate the sub matrix according to his id.

### how to compile the program (under linux)
   gcc produitmatV2.c -pthread -Wall -o produitmatV2
 
### how to run the program
   ./produitmatV2
