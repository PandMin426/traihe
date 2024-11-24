#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

void swap(int *&a, int *&b);
int *sum1(int *a, int *b);
void inputArray(int *&arr, int &n);
void outputArray(int *arr, int n);
int findMax(int *arr, int n);
int *duplicateArray(int *arr, int n);
int *findLongestAscendingSubarray(int *arr, int n, int &length);
int *findLargestSumSubarray(int *arr, int n, int &largestSum, int &nRes);
void swapArrays(int *&a, int &na, int *&b, int &nb);
int *concatTwoArray(int *a, int na, int *b, int nb, int &nc);
int *merge2Arrays(int *a, int na, int *b, int nb, int &nc);
void sort(int *arr, int n);
void generateRandomMatrix(int **&mat, int &nRow, int &nCol);
void outPut2D(int **mat, int nRow, int nCol);
int **generateMatrix(int *a, int na, int *b, int nb, int &nRow, int &nCol);
void swapRows(int **mat, int nRow, int nCol, int ir1, int ir2);
void swapColumns(int **mat, int nRow, int nCol, int ic1, int ic2);
int **transposeMatrix(int **mat, int nRow, int nCol);
int **concatenate2MatricesH(int **a, int **b, int nRow, int nCol, int &resRow, int &resCol);
int **concatenate2MatricesV(int **a, int **b, int nRow, int nCol, int &resRow, int &resCol);
bool multiplyMatrices(int **a, int aRow, int aCol, int **b, int bRow, int bCol, int **&res, int &resROw, int &resCol);
int **findSubmatrix(int **mat, int nRow, int nCol, int &subRow, int &subCol);

int main(){
    int **mat, nRow, nCol;
    generateRandomMatrix(mat, nRow, nCol);

    cout << endl;

    outPut2D(mat, nRow, nCol);
    cout << endl;

    int **mangMoi = transposeMatrix(mat, nRow, nCol);
    outPut2D(mangMoi, nCol, nRow);
    return 0;
}
//1.Swap two given integer
void swap(int *a, int *b){
    int *temp = a;
    a = b;
    b = temp;
}

void swap(int *&a, int *&b){
    int *temp = a;
    a = b;
    b = temp;
}
//2.Calculate the sum of two integers
int sum(int *a, int *b){
    return *a + *b;
}

int *sum1(int *a, int *b){
    int *sum2 = new int(*a + *b);
    return sum2;
}
//3.Input array of a size thar will be determined at runtime
void inputArray(int *&arr, int &n){
    cin >> n;
    arr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
}
//4.Output/print a given array
void outputArray(int *arr, int n){
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";     
        // arr[i] <=> *(arr + i)
    }
}
//5.Find the maximum value in an array of size n
int findMax(int *arr, int n){
    int max = INT_MIN;
    for (int i = 0; i < n; i++){
        if(max < arr[i])
            max = arr[i];
    }

    return max;
}
//6.Duplicate an array of size n
int *duplicateArray(int *arr, int n){
    int *newArr = new int[n];

    for (int i = 0; i < n; i++){
        newArr[i] = arr[i];
    }

    return newArr;
}
// 7.Find the longest ascending subarray from an array of size n
int *findLongestAscendingSubarray(int *arr, int n, int &length){
    
    length = 1;
    int lexMax = 1;
    int startID = 0;
    int tempStartID = 0;

    for (int i = 0; i < n - 1; i++){
        if(arr[i] <= arr[i+1]){
            if(length == 1){
                tempStartID = i;
            }
            length++;
        } else {
            if(length > lexMax){
                lexMax = length;
                startID = tempStartID;
            }
            length = 1;
        }
    }

    if(length > lexMax){
        lexMax = length;
        startID = tempStartID;
    }

    int *lgst = new int[lexMax];

    for (int i = 0; i < lexMax; i++)
        lgst[i] = arr[startID + i];
    
    length = lexMax;

    return lgst;
}
//8.Find the contiguous subarray within an array with the largest element sum
int *findLargestSumSubarray(int *arr, int n, int &largestSum, int &nRes){

    cin >> nRes;
    int tempSum = 0;
    int IDstart = 0;

    for (int i = 0; i < nRes; i++){
        largestSum += arr[i];
        tempSum = largestSum;
    }

    for (int i = nRes; i < n; i++){
        largestSum = largestSum + arr[i] - arr[i - nRes];
        if(largestSum > tempSum){
            tempSum = largestSum;
            IDstart = i - nRes + 1;
        }
    }

    int *arrSum = new int[nRes];
    for (int i = 0; i < nRes; i++){
        arrSum[i] = arr[IDstart + i];
    }

    largestSum = tempSum;

    return arrSum;
}
//9.swap two given arrays
void swapArrays(int *&a, int &na, int *&b, int &nb){
    int *temp = a, tempN = na;
    a = b;
    na = nb;
    b = temp;
    nb = tempN;
}
//10.Concatenate two arrays
int *concatTwoArray(int *a, int na, int *b, int nb, int &nc){
    nc = na + nb;
    int *c = new int[nc];

    for (int i = 0; i < nc; i++){
        if(i < na){
            c[i] = a[i];
        } else {
            c[i] = b[i - na];
        }
    }

    return c;
}
// 11.Given two ascendingly ordered arrays of potentially different sizes. Generate a new ascendingly ordered array that contains all elements from the original arrays 
int *merge2Arrays(int *a, int na, int *b, int nb, int &nc){
    nc = na + nb;
    int *c = new int[nc];
    int ia = 0, ib = 0, ic = 0;
    while (ia != na && ib != nb){
        c[ic++] = (a[ia] > b[ib]) ? b[ib++] : a[ia++];
    }

    while (ia < na) {
        c[ic++] = a[ia++];
    }

    while (ib < nb) {
        c[ic++] = b[ib++];
    }

    return c;
}
//11.(Phụ) sort
void sort(int *arr, int n){
    for (int i = 0; i < n - 1; i++){       
        for (int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
// 12. Generate a random 2D array (matrix) with a user-defined size (entered at runtime)
void generateRandomMatrix(int **&mat, int &nRow, int &nCol){
    cin >> nRow >> nCol;

    mat = new int *[nRow];
    for (int i = 0; i < nRow; i++){
        mat[i] = new int[nCol];
    }

    srand(time(0));
    for (int i = 0; i < nRow; i++){
        for (int j = 0; j < nCol; j++){
            mat[i][j] = rand() % 1000;
        }
    }
}
//12.(Phụ)in ra mảng 2D
void outPut2D(int **mat, int nRow, int nCol){
    for (int i = 0; i < nRow; i++){
        for (int j = 0; j < nCol; j++){
            cout << mat[i][j] << '\t';
        }
        cout << endl;
    }
}
//13.Given two 1D arrays a and b. Generate the matrix c that c[i][j] = a[i] * b[j]
int **generateMatrix(int *a, int na, int *b, int nb, int &nRow, int &nCol){
    nRow = na;
    nCol = nb;

    int **geMatrix = new int *[nRow];
    for (int i = 0; i < nRow; i++){
        geMatrix[i] = new int[nCol];
    }

    for (int i = 0; i < nRow; i++){
        for (int j = 0; j < nCol; j++){
            geMatrix[i][j] = a[i] * b[j];
        }
    }

    return geMatrix;
}
//14.Swap two columns/rows of a given matrix
//14.1.Swap Rows
void swapRows(int **mat, int nRow, int nCol, int ir1, int ir2){
    int *temp = mat[ir1];
    mat[ir1] = mat[ir2];
    mat[ir2] = temp;
}
//14.2.Swap Coloums
void swapColumns(int **mat, int nRow, int nCol, int ic1, int ic2){
    for (int i = 0; i < nRow; i++){
        int temp = mat[i][ic1];
        mat[i][ic1] = mat[i][ic2];
        mat[i][ic2] = temp;
    }
}
//15.Calculate the transpose the input matrix (resulting in a new matrix)
int **transposeMatrix(int **mat, int nRow, int nCol){
    int **tranMatrix = new int *[nCol];
    for (int i = 0; i < nCol; i++){
        tranMatrix[i] = new int[nRow];
    }

    for (int i = 0; i < nCol; i++){
        for (int j = 0; j < nRow; j++){
            tranMatrix[i][j] = mat[j][i];
        }
    }

    return tranMatrix;
}
//16.Concatenate two given size-equal matrices, horizontally/vertically
//16.1.horizontally
int **concatenate2MatricesH(int **a, int **b, int nRow, int nCol, int &resRow, int &resCol ){
    resRow = nRow;
    resCol = 2 * nCol;
    int **cocat2H = new int *[resRow];
    for (int i = 0; i < resRow; i++){
        cocat2H[i] = concatTwoArray(a[i], nCol, b[i], nCol, resCol);
    }

    return cocat2H;
}
//16.2.vertically
int **concatenate2MatricesV(int **a, int **b, int nRow, int nCol, int &resRow, int &resCol){
    resCol = nCol;
    resRow = 2 * nRow;
    int **cocat2V = new int *[resRow];

    for (int i = 0; i < nRow; i++){
        cocat2V[i] = new int[resCol];
        for (int j = 0; j < resCol; j++){
            cocat2V[i][j] = a[i][j];
        }
    }

    for (int i = nRow; i < resRow; i++){
        cocat2V[i] = new int[resCol];
        for (int j = 0; j < resCol; j++){
            cocat2V[i][j] = b[i - nRow][j];
        }
    }

    return cocat2V;
}
//17.Multriply two matrices
bool multiplyMatrices(int **a, int aRow, int aCol, int **b, int bRow, int bCol, int **&res, int &resRow, int &resCol){
    if(aCol != bRow){
        return false;
    }

    resRow = aRow;
    resCol = bCol;
    res = new int *[resRow];
    for (int i = 0; i < resRow; i++){
        res[i] = new int[resCol];
    }

    for (int i = 0; i < resRow; i++){       
        for (int j = 0; j < resCol; j++){
            int n = 0;
            res[i][j] = 0;

            while (true){
                res[i][j] += a[i][n] * b[n][j];
                n++;
                if(n == aCol){
                    break;
                }
            }
        }
    }

    return true;
}
//18.Given a matrix, find the submatrix of a specified size (entered at run time) with the largey sum of elements
int **findSubmatrix(int **mat, int nRow, int nCol, int &subRow, int &subCol){
    int IDstart[2] = {0, 0};
    int tempIDstar[] = IDstart;
    int sumMax = 0;
    int tempSumMax = 0;

    int *mangSum = new int *[subRow];
    for (int i = 0; i < subRow; i++){
        mangSum[i] = new int[subCol];
    }

    for (int i = 0; i < subRow; i++){
        for (int j = 0; j < subCol; j++){
            sumMax += mat[i][j];
        }
    }

    int idx = 0, idy = 0;

    tempSumMax = sumMax;
    
    while(true){
        for (int i = 1; i <= nRow - subRow; i++){
            idy = i;
            for (int j = idy; j < subCol; j++){
                sumMax = sumMax + mat[i + subRow - 1][j] - mat[];
            }

            if(sumMax > tempSumMax){
                tempSumMax = sumMax;
                IDstart[0] = idy;
                IDstart[1] = idx;        
            }
        }

        idx++;

        for (int i = idy; i < nRow; i++){
            sumMax = sumMax + mat[i][idx + subCol - 1] - mat[i][idx - 1];
        }       

        if(sumMax > tempSumMax){
                tempSumMax = sumMax;
                IDstart[0] = idy;
                IDstart[1] = idx;        
        }

        for (int i = nRow - subRow - 1; i >= 0; i--){
            idy = i;
            for(int j = )
        }
    }
    
}