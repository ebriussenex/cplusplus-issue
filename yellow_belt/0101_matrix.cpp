#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define pass (void)0

#include <limits>
#include <exception>
#include <cstdint>

#include <ios>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cfenv>
#include <iomanip>

#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <utility>
#include <list>
#include <forward_list>
#include <bitset>


#include <algorithm>
#include <string>
#include <regex>
#include <iterator>

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <functional>

using namespace std;

class Matrix {
public:
	Matrix() {
		num_rows_ = 0;
		num_cols_ = 0;
	}
	Matrix(int num_rows, int num_cols) {
		Reset(num_rows, num_cols);
	}
	void Reset(int num_rows, int num_columns) {
		if (num_rows < 0) {
			throw out_of_range("num_rows must be >= 0");
		}
		if (num_columns < 0) {
			throw out_of_range("num_columns must be >= 0");
		}
		if (num_rows == 0 || num_columns == 0) {
			num_rows = num_columns = 0;
		}

		num_rows_ = num_rows;
		num_cols_ = num_columns;
		matrix.assign(num_rows, vector<int>(num_columns));
	}
	int At(int num_r, int num_c) const {
		return matrix.at(num_r).at(num_c);
	}
	int& At(int num_r, int num_c) {
		return matrix.at(num_r).at(num_c);
	}
	int GetNumRows() const {
		return num_rows_;
	}
	int GetNumColumns() const {
		return num_cols_;
	}
private:
	vector <vector<int>> matrix;
	int num_rows_;
	int num_cols_;
};

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumColumns() != rhs.GetNumColumns() ||
		lhs.GetNumRows() != rhs.GetNumRows()) return false;
	else {
		for (size_t i = 0; i < lhs.GetNumRows(); i++) {
			for (size_t j = 0; j < lhs.GetNumColumns(); j++) {
				if (lhs.At(i, j) != rhs.At(i, j)) {
					return false;
				}
			}
		}
		return true;
	}
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumColumns() != rhs.GetNumColumns() ||
		lhs.GetNumRows() != rhs.GetNumRows()) throw invalid_argument("Invalid argument!");
	else {
		Matrix ret_mat;
		ret_mat.Reset(lhs.GetNumRows(), lhs.GetNumColumns());
		for (size_t i = 0; i < lhs.GetNumRows(); i++) {
			for (size_t j = 0; j < lhs.GetNumColumns(); j++) {
				ret_mat.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
			}
		}
		return ret_mat;
	}
}

istream& operator>>(istream& stream, Matrix& matrix) {
	int num_r, num_c, value;
	stream >> num_r >> num_c;
	matrix.Reset(num_r, num_c);
	for (size_t i = 0; i < matrix.GetNumRows(); i++) {
		for (size_t j = 0; j < matrix.GetNumColumns(); j++) {
			stream >> value;
			matrix.At(i, j) = value;
		}
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
	stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
	for (int i = 0; i < matrix.GetNumRows(); i++) {
		for (int j = 0; j < matrix.GetNumColumns(); j++) {
			if (j > 0) stream << " ";
			stream << matrix.At(i, j);
		}
		stream << endl;
	}
	return stream;
}


int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;
	return 0;
}
