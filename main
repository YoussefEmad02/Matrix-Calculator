#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;


void startProgram();


class InputOutputUtils {
public:
    static void coutError() {
        cout << "ERROR!";
    }

    static void coutMatrix(vector<vector<double>> matrix) {
        cout << "[";
        for (int q = 0; q < matrix.size(); q++) {
            for (int w = 0; w < matrix[q].size(); w++) {
                cout << matrix[q][w];
                if (w != matrix[q].size() - 1) {
                    cout << " ";
                }
            }
            if (q != matrix.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
    }

    static string getInputString() {
        string inputString;
        getline(cin, inputString);
        return inputString;
    }
};

class StringUtils {
public:
    static bool isStringEmpty(string str) {
        return str == "";
    }

    static vector<string> split(const string& s, char separator) {
        stringstream stream(s);
        string str;

        vector<string> result;

        while (getline(stream, str, separator)) {
            if (!isStringEmpty(str)) {
                result.push_back(str);
            }
        }

        return result;
    }
};


class MatrixCalculator {
public:
    static double performDotProduct(vector<double> matrix1, vector<double> matrix2) {
        double result = 0;
        for (int q = 0; q < matrix1.size(); q++) {
            result += (matrix1[q] * matrix2[q]);
        }
        return result;
    }
    static vector<double> getColumn(vector<vector<double>> matrix, int columnIndex) {
        vector<double> Col = {};
        for (int q = 0; q < matrix.size(); q++) {
            Col.push_back(matrix[q][columnIndex]);
        }
        return Col;
    }
};


bool isSuitableNumberOfItems(vector<string> items) {
    int Counter = items.size();
    return Counter < 100 && Counter > 0;
}

bool isdoubleValueAcceptable(double val) {
    return val < 9999.999 && val > -9999.999;
}

bool isMatricesSameDimensions(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    return matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size();
}


vector<vector<double>> getdoubleMatrixFromStringRows(vector<string> rows);

vector<vector<double>> checkAndAssignMatrix(string matrixStr) {

    int matrixLen = matrixStr.size();
    if (matrixLen == 0) {
        return {};
    }


    try {
        double itemdouble = stod(matrixStr);
        if (!isdoubleValueAcceptable(itemdouble)) {
            return {};
        }
        return { {itemdouble} };
    }
    catch (...) {}

    char First_Ch = matrixStr[0];
    char last_Ch = matrixStr[matrixLen - 1];
    if (First_Ch != '[' || last_Ch != ']') {
        return {};
    }

    string matrixWithoutBrackets = matrixStr.substr(1, matrixLen - 2);
    vector<string> rows = StringUtils::split(matrixWithoutBrackets, ',');


    if (!isSuitableNumberOfItems(rows)) {
        return {};
    }

    int numberOfItemsInRow = NULL;
    for (string row : rows) {
        vector<string> itemsInRow = StringUtils::split(row, ' ');
        if (!isSuitableNumberOfItems(itemsInRow)) {
            return {};
        }
        if (numberOfItemsInRow != NULL && numberOfItemsInRow != itemsInRow.size()) {
            return {};
        }
        numberOfItemsInRow = itemsInRow.size();
    }

    vector<vector<double>> matrixdouble = getdoubleMatrixFromStringRows(rows);

    return matrixdouble;
}

vector<vector<double>> getdoubleMatrixFromStringRows(vector<string> rows) {
    vector<vector<double>> matrixdouble = {};

    for (string row : rows) {
        vector<string> itemsInRow = StringUtils::split(row, ' ');
        vector<double> rowdouble = {};
        for (string item : itemsInRow) {
            try {
                double itemdouble = stod(item);
                if (!isdoubleValueAcceptable(itemdouble)) {
                    return {};
                }
                rowdouble.push_back(itemdouble);

            }
            catch (...) {
                return {};
            }
        }
        matrixdouble.push_back(rowdouble);
    }
    return matrixdouble;
}


bool checkAndAssignOperator(string operatorStr, char* operatorPtr) {

    if (StringUtils::isStringEmpty(operatorStr)) {
        return false;
    }
    char First_Ch = operatorStr[0];

    if (First_Ch != '+' && First_Ch != '-' && First_Ch != '*') {
        return false;
    }

    *operatorPtr = First_Ch;
    return true;
}



void performAddition(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    if (!isMatricesSameDimensions(matrix1, matrix2)) {
        InputOutputUtils::coutError();
        return;
    }

    vector<vector<double>> tempMatrix = matrix1;


    for (int q = 0; q < matrix2.size(); q++) {
        for (int w = 0; w < matrix2[q].size(); w++) {
            tempMatrix[q][w] += matrix2[q][w];
        }
    }

    InputOutputUtils::coutMatrix(tempMatrix);
}

void performSubtraction(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    if (!isMatricesSameDimensions(matrix1, matrix2)) {
        InputOutputUtils::coutError();
        return;
    }

    vector<vector<double>> tempMatrix = matrix1;


    for (int q = 0; q < matrix2.size(); q++) {
        for (int w = 0; w < matrix2[q].size(); w++) {
            tempMatrix[q][w] -= matrix2[q][w];
        }
    }

    InputOutputUtils::coutMatrix(tempMatrix);
}

void performMultiplication(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    double scalar = NULL;
    vector<vector<double>> multiplyMatrixScalar = {};


    if (matrix1.size() == 1 && matrix1[0].size() == 1) {
        scalar = matrix1[0][0];
        multiplyMatrixScalar = matrix2;
    }
    if (matrix2.size() == 1 && matrix2[0].size() == 1) {
        scalar = matrix2[0][0];
        multiplyMatrixScalar = matrix1;
    }

    if (scalar != NULL) {
        vector<vector<double>> tempMatrix = multiplyMatrixScalar;

        for (int q = 0; q < multiplyMatrixScalar.size(); q++) {
            for (int w = 0; w < multiplyMatrixScalar[q].size(); w++) {
                tempMatrix[q][w] *= scalar;
            }
        }
        InputOutputUtils::coutMatrix(tempMatrix);
        return;
    }
    else if (matrix1[0].size() == matrix2.size()) {
        vector<vector<double>> result = {};
        for (int q = 0; q < matrix1.size(); q++) {
            vector<double> row1 = matrix1[q];
            vector<double> resultRow = {};

            for (int w = 0; w < matrix2[0].size(); w++) {
                vector<double> column = MatrixCalculator::getColumn(matrix2, w);
                resultRow.push_back(MatrixCalculator::performDotProduct(row1, column));
            }
            result.push_back(resultRow);
        }
        InputOutputUtils::coutMatrix(result);
        return;
    }
    InputOutputUtils::coutError();
}

void performOperation(vector<vector<double>> matrix1, vector<vector<double>> matrix2, char operatorChar) {
    switch (operatorChar) {
    case '+':
        performAddition(matrix1, matrix2);
        break;
    case '-':
        performSubtraction(matrix1, matrix2);
        break;
    case '*':
        performMultiplication(matrix1, matrix2);
        break;
    default:
        InputOutputUtils::coutError();
        break;
    }
}

void startProgram() {
    string firstMatrix = InputOutputUtils::getInputString();
    vector<vector<double>> matrix1 = checkAndAssignMatrix(firstMatrix);

    if (matrix1.size() == 0) {
        InputOutputUtils::coutError();
        return;
    }

    string operatorStr = InputOutputUtils::getInputString();

    char operatorChar;
    char* operatorPtr = &operatorChar;

    if (!checkAndAssignOperator(operatorStr, operatorPtr)) {
        InputOutputUtils::coutError();
        return;
    }

    string secondMatrix = InputOutputUtils::getInputString();
    vector<vector<double>> matrix2 = checkAndAssignMatrix(secondMatrix);

    if (matrix2.size() == 0) {
        InputOutputUtils::coutError();
        return;
    }

    performOperation(matrix1, matrix2, operatorChar);
}

int main() {
    startProgram();
    return 0;
}
