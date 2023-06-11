#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class InputOutputUtils {
public:
    static void CoutError() {
        cout << "ERROR!";
    }

    static void coutPrecision(float n)
    {
        if (n == (int)n) {
            cout << n;
        }
        else {
            cout << setprecision(2) << fixed << int(n * 100.0) / 100.0;
        }
    }

    static void M1(vector<vector<float>> matrix) {
        cout << "[";
        for (int i = 0; i < matrix.size(); i++) {
            for (int k = 0; k < matrix[i].size(); k++) {
                coutPrecision(matrix[i][k]);
                if (k != matrix[i].size() - 1) {
                    cout << " ";
                }
            }
            if (i != matrix.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
    }

    static string getinstr() {
        string inString;
        getline(cin, inString);
        return inString;
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
    static vector<vector<float>> emptyVector(int size1, int size2) {
        vector<vector<float>> temp = {};
        for (int i = 0; i < size1; i++) {
            vector<float> temp2 = {};
            for (int k = 0; k < size2; k++) {
                temp2.push_back(0);
            }
            temp.push_back(temp2);
        }
        return temp;
    }
    static float determinant(vector<vector<float>> A, int n) {
        float D = 0;
        if (n == 1)
            return A[0][0];

        vector<vector<float>> temp = emptyVector(A.size(), A.size());

        float sign = 1;
        for (int f = 0; f < n; f++) {
            temp = getCofactor(A, 0, f, n);
            D += sign * A[0][f] * determinant(temp, n - 1);
            sign = -sign;
        }

        return D;
    }
    static vector<vector<float>> inverse(vector<vector<float>> A) {
        vector<vector<float>> inverse = emptyVector(A.size(), A.size());
        float det = determinant(A, A.size());
        if (det == 0) {
            return {};
        }

        vector<vector<float>> adj = adjoint(A);
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < A.size(); j++)
                inverse[i][j] = adj[i][j] / det;

        return inverse;
    }
private:
    static vector<vector<float>> getCofactor(vector<vector<float>> A, int p, int q, int n) {
        int i = 0, j = 0;
        vector<vector<float>> temp = emptyVector(A.size(), A.size());
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != p && col != q) {
                    temp[i][j++] = A[row][col];
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }

        return temp;
    }
    static vector<vector<float>> adjoint(vector<vector<float>> A) {
        vector<vector<float>> adj = emptyVector(A.size(), A.size());;
        if (A.size() == 1) {
            adj[0][0] = 1;
            return adj;
        }
        float sign = 1;
        vector<vector<float>> temp = emptyVector(A.size(), A.size());

        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                temp = getCofactor(A, i, j, A.size());

                sign = ((i + j) % 2 == 0) ? 1 : -1;

                adj[j][i] = (sign) * (determinant(temp, A.size() - 1));
            }
        }

        return adj;
    }
};

bool isSuitableNumberOfItems(vector<string> items) {
    int itemsCount = items.size();
    return itemsCount < 100 && itemsCount > 0;
}

bool isFloatValueAcceptable(float val) {
    return val < 9999.999 && val > -9999.999;
}

bool isMatrixSquare(vector<vector<float>> matrix) {
    return matrix[0].size() == matrix.size();
}

vector<vector<float>> getFloatMatrixFromStringRows(vector<string> rows) {
    vector<vector<float>> matrixFloat = {};

    for (string row : rows) {
        vector<string> itemsInRow = StringUtils::split(row, ' ');
        vector<float> rowFloat = {};
        for (string item : itemsInRow) {
            try {
                float itemFloat = stof(item);
                if (!isFloatValueAcceptable(itemFloat)) {
                    return {};
                }
                rowFloat.push_back(itemFloat);

            }
            catch (...) {
                return {};
            }
        }
        matrixFloat.push_back(rowFloat);
    }
    return matrixFloat;
}

vector<vector<float>> checkAndAssignMatrix(string matrixStr) {
    // check if input text is large enough
    int matrixLen = matrixStr.size();
    if (matrixLen == 0) {
        return {};
    }

    // check if input text starts with [ and ends with ]
    char firstChar = matrixStr[0];
    char lastChar = matrixStr[matrixLen - 1];
    if (firstChar != '[' || lastChar != ']') {
        return {};
    }

    string matrixWithoutBrackets = matrixStr.substr(1, matrixLen - 2);
    vector<string> rows = StringUtils::split(matrixWithoutBrackets, ',');

    // check if input text starts with [ and ends with ]

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

    vector<vector<float>> matrixFloat = getFloatMatrixFromStringRows(rows);

    return matrixFloat;
}

bool checkAndAssignOperator(string operatorStr, char* operatorPtr) {
    // check if input text is large enough
    if (StringUtils::isStringEmpty(operatorStr)) {
        return false;
    }
    char firstChar = operatorStr[0];

    if (firstChar != 'I' && firstChar != 'T' && firstChar != 'D') {
        return false;
    }

    *operatorPtr = firstChar;
    return true;
}

void performInverse(vector<vector<float>> matrix) {
    if (!isMatrixSquare(matrix)) {
        InputOutputUtils::CoutError();
        return;
    }

    vector<vector<float>> inversedMatrix = MatrixCalculator::inverse(matrix);
    if (inversedMatrix.size() == 0) {
        InputOutputUtils::CoutError();
        return;
    }
    InputOutputUtils::M1(inversedMatrix);
}

void performDeterminent(vector<vector<float>> matrix) {
    if (!isMatrixSquare(matrix)) {
        InputOutputUtils::CoutError();
        return;
    }
    InputOutputUtils::coutPrecision(MatrixCalculator::determinant(matrix, matrix.size()));
}

void performTranspose(vector<vector<float>> matrix1) {
    vector<vector<float>> transpose = MatrixCalculator::emptyVector(matrix1[0].size(), matrix1.size());
    for (int i = 0; i < matrix1.size(); ++i)
        for (int j = 0; j < matrix1[0].size(); ++j) {
            transpose[j][i] = matrix1[i][j];
        }
    InputOutputUtils::M1(transpose);
}

void performOperation(vector<vector<float>> matrix, char operatorChar) {
    switch (operatorChar) {
    case 'I':
        performInverse(matrix);
        break;
    case 'D':
        performDeterminent(matrix);
        break;
    case 'T':
        performTranspose(matrix);
        break;
    default:
        InputOutputUtils::CoutError();
        break;
    }
}

void start() {

    string firstMatrix = InputOutputUtils::getinstr();
    vector<vector<float>> matrix1 = checkAndAssignMatrix(firstMatrix);

    if (matrix1.size() == 0) {
        InputOutputUtils::CoutError();
        return;
    }

    string operatorStr = InputOutputUtils::getinstr();

    char operatorChar;
    char* operatorPtr = &operatorChar;

    if (!checkAndAssignOperator(operatorStr, operatorPtr)) {
        InputOutputUtils::CoutError();
        return;
    }

    performOperation(matrix1, operatorChar);
}

int main() {
    start();
    return 0;
}
