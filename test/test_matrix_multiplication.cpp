#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#define seed 2905

void multiplyMatricesWithoutErrors(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C, int rowsA, int colsA,
                      int colsB) 
{
    for (int i = 0; i < rowsA; ++i) 
        {
        for (int j = 0; j < colsB; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < colsA; ++k) 
            {
            C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to generate a random matrix of size rows x cols
std::vector<std::vector<int>> generateRandomMatrix(int rows, int cols, int minValue = -10, int maxValue = 100) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = minValue + (rand() % (maxValue - minValue + 1));
        }
    }

    return matrix;
}

// Function to fill a matrix with consecutive numbers for rows
std::vector<std::vector<int>> fillMatrixConsecutiveRows(int numRows, int numCols) {
    // Initialize the matrix
    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols));

    // Fill the matrix with consecutive numbers for rows
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            matrix[i][j] = i;
        }
    }

    return matrix;
}

// Function to fill a matrix with consecutive numbers for columns
std::vector<std::vector<int>> fillMatrixConsecutiveColumns(int numRows, int numCols) {
    std::vector<std::vector<int>> matrix(numRows, std::vector<int>(numCols));
    for (int j = 0; j < numCols; ++j) {
        for (int i = 0; i < numRows; ++i) {
            matrix[i][j] = j;
        }
    }
    return matrix;
}




/*
CURRENT ERRORS: 
Error 1: Element-wise multiplication of ones detected!
Error 2: Matrix A contains the number 7!
Error 3: Matrix A contains a negative number!
Error 4: Matrix B contains the number 3!
Error 5: Matrix B contains a negative number!
Error 6: Result matrix contains a number bigger than 100!
Error 7: Result matrix contains a number between 11 and 20!
Error 8: Result matrix contains zero!
Error 9: Result matrix contains the number 99!
Error 10: A row in matrix A contains more than one '1'!
Error 11: Every row in matrix B contains at least one '0'!
Error 12: The number of rows in A is equal to the number of columns in B!
Error 13: The first element of matrix A is equal to the first element of matrix B!
Error 14: The result matrix C has an even number of rows!
Error 15: A row in matrix A is filled entirely with 5s!
Error 16: Matrix B contains the number 6!
Error 17: Result matrix C contains the number 17!
Error 18: Matrix A is a square matrix!
Error 19: Every row in matrix A contains the number 8!
Error 20: Number of columns in matrix A is odd!
*/


// STEP 0
// We started our journey with some random testing (random values and dimension), to see what
// kind of error we could possibly face.


// RANDOM !!!
//ERRORS: 6, 12, 14, 20 (we won't keep this as checked because computation is random, they maychange)
// Test: already existing matrix multiplication
TEST(Step0_Randomic, TestMultiplyMatrices) 
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> expected(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);

    multiplyMatricesWithoutErrors(A, B, expected, 2, 3, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(";
}


// RANDOM!!
//ERRORS: 2, 3, 5, 6, 20
// Test for multiplying matrices with random dimensions and values
TEST(Step0_Randomic, TestRandomMatrixMultiplication) 
{
    srand(seed);  // Seed for random number generation

    // Generate random dimensions for the matrices
    int rowsA = 1 + rand() % 10; // Between 1 and 10
    int colsA = 1 + rand() % 10; // Between 1 and 10
    int colsB = 1 + rand() % 10; // Between 1 and 10

    // Generate random matrices
    std::vector<std::vector<int>> A = generateRandomMatrix(rowsA, colsA);
    std::vector<std::vector<int>> B = generateRandomMatrix(colsA, colsB);
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));
    std::vector<std::vector<int>> expected(rowsA, std::vector<int>(colsB, 0));

    // Multiply the matrices
    multiplyMatrices(A, B, C, rowsA, colsA, colsB);
    multiplyMatricesWithoutErrors(A, B, expected, rowsA, colsA, colsB);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(";
}




// STEP 1
// fixed size matrix filled all with just one number, both for A and B
// It's useful to perform such test with different numbers
// we left here the test with 0, and corresponding errors

// Other intresting values can be:
// 5 to obtain error 15 (row of 5s in A)
// 8 to obtain error 19 (two 8s in a single row of A) 
// and many others...

// We decided to leave the values 0 and 8 as they were because other errors were also obtained in the later tests.

// VALUE 0
// ERRORS: 8, 11, 12, 13, 14, 18
// Test for multiplying squared matrices with same values
TEST(Step1_SameNumber, TestSameNumberMatrixMultiplication) 
{

    // Fixed dimensions for the squared matrices
    int rows = 10;
    int cols = 10;
    int sameNumber = 0;

    // Generate matrix A filled with the same number
    std::vector<std::vector<int>> A(rows, std::vector<int>(cols, sameNumber));

    // Generate matrix B filled with the same number
    std::vector<std::vector<int>> B(rows, std::vector<int>(cols, sameNumber));

    // Initialize the expected result matrix
    std::vector<std::vector<int>> expected(rows, std::vector<int>(cols, sameNumber * sameNumber));

    // Initialize the result matrix
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    // Multiply the matrices
    multiplyMatrices(A, B, result, rows, cols, cols);

    // Check if the result matches the expected result
    ASSERT_EQ(result, expected) << "Matrix multiplication test failed with same number: " << sameNumber;
}



// VALUE 8
// ERRORS: 6, 12, 13, 14, 18, 19
// Test for multiplying squared matrices with same values
TEST(Step1_SameNumber, TestSameNumberMatrixMultiplicationEight) 
{

    // Fixed dimensions for the squared matrices
    int rows = 10;
    int cols = 10;
    int sameNumber = 8;

    // Generate matrix A filled with the same number
    std::vector<std::vector<int>> A(rows, std::vector<int>(cols, sameNumber));

    // Generate matrix B filled with the same number
    std::vector<std::vector<int>> B(rows, std::vector<int>(cols, sameNumber));

    // Initialize the expected result matrix
    std::vector<std::vector<int>> expected(rows, std::vector<int>(cols, sameNumber * sameNumber));

    // Initialize the result matrix
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    // Multiply the matrices
    multiplyMatrices(A, B, result, rows, cols, cols);

    // Check if the result matches the expected result
    ASSERT_EQ(result, expected) << "Matrix multiplication test failed with same number: " << sameNumber;
}




// STEP 2
// Testing edge cases: identity and zero matrix, different dimensions (like vector*vector, etc)


//ERRORS: 1, 4, 7, 12, 13, 16, 18, 20
// Test: identity matrix
TEST(Step2_EdgeCases, TestIdentityMatrix)
{
    std::vector<std::vector<int>> A = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    std::vector<std::vector<int>> B = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));
    std::vector<std::vector<int>> expected(3, std::vector<int>(3, 0));

    multiplyMatrices(A, B, C, 3, 3, 3);

    multiplyMatricesWithoutErrors(A, B, expected, 3, 3, 3);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}



//ERRORS: 1, 8, 11, 12, 13, 14, 18
// Test for multiplying two identity matrices
TEST(Step2_EdgeCases, TestMultiplyIdentityMatrices) 
{
    std::vector<std::vector<int>> A = {
        {1, 0},
        {0, 1}
    };
    std::vector<std::vector<int>> B = {
        {1, 0},
        {0, 1}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);

    std::vector<std::vector<int>> expected = {
        {1, 0},
        {0, 1}
    };

    ASSERT_EQ(C, expected);
}



//ERRORS: 8, 11, 12, 13, 14, 18
// Test for multiplying two zero matrices
TEST(Step2_EdgeCases, TestMultiplyZeroMatrices) 
{
    std::vector<std::vector<int>> A = {
        {0, 0},
        {0, 0}
    };
    std::vector<std::vector<int>> B = {
        {0, 0},
        {0, 0}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);

    std::vector<std::vector<int>> expected = {
        {0, 0},
        {0, 0}
    };

    ASSERT_EQ(C, expected);
}



//ERRORS: 12, 16, 20
// Test for multiplying two vectors
TEST(Step2_EdgeCases ,TestMultiplyVectors) 
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3}
    };
    std::vector<std::vector<int>> B = {
        {4},
        {5},
        {6}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));

    multiplyMatrices(A, B, C, 1, 3, 1);

    std::vector<std::vector<int>> expected = {
        {32}
    };

    ASSERT_EQ(C, expected);
}



// ERRORS: 6, 14, 20
// Test for multiplying a matrix with a vector
TEST(Step2_EdgeCases, TestMultiplyMatrixWithVector) {
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {7},
        {8},
        {9}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(1, 0));

    multiplyMatrices(A, B, C, 2, 3, 1);

    std::vector<std::vector<int>> expected = {
        {50},
        {122}
    };

    ASSERT_EQ(C, expected);
}



// ERRORS: 12, 18, 20
// Test with monodimensional matrices
TEST(Step2_EdgeCases, TestMultiplyMonodimensional) {
    std::vector<std::vector<int>> A = {
        {1}
    };
    std::vector<std::vector<int>> B = {
        {7}
    };
    std::vector<std::vector<int>> C(1, std::vector<int>(1, 0));

    multiplyMatrices(A, B, C, 1, 1, 1);

    std::vector<std::vector<int>> expected = {
        {7}
    };

    ASSERT_EQ(C, expected);
}



//ERRORS: 3, 4, 5, 6, 12, 20
// test col by row
TEST(Step2_EdgeCases, TestMultiplyColbyRow) {
    std::vector<std::vector<int>> A = {
        {1 << 13},
        {'l'},
        {- 3}
    };
    std::vector<std::vector<int>> B = {
        {-7, -10, 34/10}
    };
    std::vector<std::vector<int>> C(3, std::vector<int>(3, 0));

    multiplyMatrices(A, B, C, 3, 1, 3);

    std::vector<std::vector<int>> expected = {
        {7}
    };

    ASSERT_EQ(C, expected);
}



// ERRORS: 1, 7, 10, 13, 18, 20
// Test for multiplying a matrix of all ones with a single 1
TEST(Step2_EdgeCases, TestAllOnesWithSingleOne) 
{
    // Define the first matrix of all ones
    std::vector<std::vector<int>> A = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    // Define the second matrix with a single 1
    std::vector<std::vector<int>> B = {
        {1},
        {1},
        {1}
    };

    // Initialize the result matrix
    std::vector<std::vector<int>> C(3, std::vector<int>(1, 0));

    // Perform matrix multiplication
    multiplyMatrices(A, B, C, 3, 3, 1);

    // Define the expected result matrix
    std::vector<std::vector<int>> expected = {
        {3},
        {3},
        {3}
    };

    // Check if the result matches the expected result
    ASSERT_EQ(C, expected);
}


//ERROR: 1, 7, 10, 13, 20 
TEST(Step2_EdgeCases, TestAllOnesWithSingleOneInverted) 
{
    // Define the first matrix with a single 1
    std::vector<std::vector<int>> A = {
        {1, 1, 1}
    };

    // Define the second matrix of all ones
    std::vector<std::vector<int>> B = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    // Initialize the result matrix
    std::vector<std::vector<int>> C(1, std::vector<int>(3, 0));

    // Perform matrix multiplication
    multiplyMatrices(A, B, C, 1, 3, 3);

    // Define the expected result matrix
    std::vector<std::vector<int>> expected = {
        {3, 3, 3}
    };

    // Check if the result matches the expected result
    ASSERT_EQ(C, expected);
}




// ERRORS: 1, 2, 4, 6, 9, 10, 12, 13, 14, 15, 16, 18
// BEWARE: there are a lot of outputs, error 9 happens various times in the middle of the outputs
// Test case for fillMatrixConsecutiveRows function
TEST(Step2_EdgeCases, FillMatrixConsecutiveRows) {
    // Define variables for number of rows and columns
    int numRowsA = 10;
    int numColsA = 10;
    int numRowsB = 10;
    int numColsB = 10;

    // Generate matrix A
    std::vector<std::vector<int>> A = fillMatrixConsecutiveRows(numRowsA, numColsA);
    // print A
    for (int i = 0; i < numRowsA; ++i) {
        for (int j = 0; j < numColsA; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Generate matrix B
    std::vector<std::vector<int>> B = fillMatrixConsecutiveRows(numRowsB, numColsB);

    // Initialize result matrix
    std::vector<std::vector<int>> C(numRowsA, std::vector<int>(numColsB, 0));
    std::vector<std::vector<int>> expected(numRowsA, std::vector<int>(numColsB, 0));

    // Perform matrix multiplication
    multiplyMatrices(A, B, C, numRowsA, numColsA, numColsB);
    multiplyMatricesWithoutErrors(A, B, expected, numRowsA, numColsA, numColsB);

    // Add your assertions here to check the result matrix 'C' against expected values
    ASSERT_EQ(C, expected);
}



// ERRORS: 1, 7, 8, 11, 13
// Test case for fillMatrixConsecutiveColumns function
TEST(Step2_EdgeCases, FillMatrixConsecutiveColumns) {
    // Generate matrix A
    std::vector<std::vector<int>> A = fillMatrixConsecutiveColumns(3, 4);

    // Generate matrix B
    std::vector<std::vector<int>> B = fillMatrixConsecutiveColumns(4, 2);

    // Initialize result matrix
    std::vector<std::vector<int>> C(3, std::vector<int>(2, 0));
    std::vector<std::vector<int>> expected(3, std::vector<int>(2, 0));

    // Perform matrix multiplication
    multiplyMatrices(A, B, C, 3, 4, 2);
    multiplyMatricesWithoutErrors(A, B, expected, 3, 4, 2);

    // Add your assertions here to check the result matrix 'C' against expected values
    ASSERT_EQ(C, expected);
}


// STEP 3
// only error 17 is missing
// create matrices by hand then ...
// ...progressively remove every known error until the test is passed, to make missing errors appear
// then slightly modify to obtain it

// after various attempt...

// ERRORS: none :)
TEST(Step3_find17, TestToBePassed) 
{
    int rowA = 5;
    int colA = 2;
    int colB = 2;

    std::vector<std::vector<int>> A = {
        {1, 2},
        {4, 5},
        {0, 8},
        {0, 1},
        {1, 2}
    };
    std::vector<std::vector<int>> B = {
        {0, 2},
        {4, 4}
        
    };
    std::vector<std::vector<int>> C(rowA, std::vector<int>(colB, 0));
    std::vector<std::vector<int>> expected(rowA, std::vector<int>(colB, 0));

    multiplyMatrices(A, B, C, rowA, colA, colB);

    multiplyMatricesWithoutErrors(A, B, expected, rowA, colA, colB);

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}




// slightly change correct solution to find MR 17

// ERRORS: 1, 7, ... and finally!  ... FINALLY! The error 17
TEST(Step3_Find17, FindError17) 
{
    int rowA = 5;
    int colA = 2;
    int colB = 2;

    std::vector<std::vector<int>> A = {
        {1, 2},
        {4, 5},
        {0, 8},
        {0, 1},
        {1, 2}
    };
    std::vector<std::vector<int>> B = {
        {0, 11},
        {4,1}
        
    };
    std::vector<std::vector<int>> C(rowA, std::vector<int>(colB, 0));
    std::vector<std::vector<int>> expected(rowA, std::vector<int>(colB, 0));

    multiplyMatrices(A, B, C, rowA, colA, colB);

    multiplyMatricesWithoutErrors(A, B, expected, rowA, colA, colB);
    //print C
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}