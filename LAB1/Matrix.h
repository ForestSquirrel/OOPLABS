#pragma once
#include<stdexcept>
#include<thread>
#include<vector>
#include "triang.h"
#include <iostream>

using namespace std;

void triang(Matrix &matrix, int iter_no1, int iter_no2);
class Matrix {
private:
	float** matrix;
	int row;
	int column;
public:
	Matrix(int dim) {
		this->matrix = new float* [dim];
		for (auto i = 0; i < dim; i++) {
			matrix[i] = new float [dim];
		}
		this->row = dim;
		this->column = dim;
	}
	Matrix(int dim1, int dim2) {
		matrix = new float* [dim1];
		for (auto i = 0; i < dim1; i++) {
			matrix[i] = new float[dim2];
		}
		this->row = dim1;
		this->column = dim2;
	}
public:
	int get_row() {
		return this->row;
	}
	int get_column() {
		return this->column;
	}
	float get_element(int i, int j) {
		if (i < this->row && j < this->column) {
			return this->matrix[i][j];
		}
		else {
			throw (invalid_argument("Dimmensions don't match"));
		}
	}
	void set_element(int i, int j, float new_element) {
		if (i < this->row && j < this->column) {
			this->matrix[i][j] = new_element;
		}
		else {
			throw (invalid_argument("Dimmensions don't match"));
		}
	}
	void delete_matrix() {
		for (auto i = 0; i < this->row; i++)
			delete[]this->matrix[i];
		this->row = 0;
		this->column = 0;
	}
	void ones() { //fill matrix with 1
		for (auto i = 0; i < this->row; i++)
			for (auto j = 0; j < this->column; j++)
				this->matrix[i][j] = 1;
	}
	void zeros() {//fill matrix with 0
		for (auto i = 0; i < this->row; i++)
			for (auto j = 0; j < this->column; j++)
				this->matrix[i][j] = 0;
	}
	void fill(float elements[], int ele_dim) {
		if (ele_dim != this->row * this->column) {
			throw (invalid_argument("Dimmensions don't match"));
		}
		else {
			for (auto i = 0; i < this->row; i++)
				for (auto j = 0; j < this->column; j++)
					this->matrix[i][j] = elements[this->get_row()*i + j];
		}
	}
	Matrix operator* (const Matrix &matr) {
		if (this->get_column() == matr.row) {
			Matrix newMatrix(this->get_row(), matr.column);
			newMatrix.zeros();
			for (int i = 0; i < this->get_row(); i++) {
				for (int j = 0; j < matr.column; j++) {
					for (int k = 0; k < this->get_column(); k++)
						newMatrix.set_element(i,j, newMatrix.get_element(i,j)+this->get_element(i, k) * matr.matrix[k][j]);
				}
			}
			return newMatrix;
		}
		else
			throw (invalid_argument("Dimmensions don't match"));
	}
	Matrix operator+ (const Matrix& matr) {
		if (this->get_column() == matr.column && this->get_row() == matr.row) {
			Matrix newMatrix(this->get_row(), this->get_column());
			for (int i = 0; i < this->get_row(); i++) {
				for (int j = 0; j < this->get_column(); j++) {
					newMatrix.set_element(i, j, this->get_element(i, j) + matr.matrix[i][j]);
				}
			}
			newMatrix.printToConsole();
			return newMatrix;
		}
		else
			throw (invalid_argument("Dimmensions don't match"));
	}
	Matrix operator- (const Matrix& matr) {
		if (this->get_column() == matr.column && this->get_row() == matr.row) {
			Matrix newMatrix(this->get_row(), matr.column);
			for (int i = 0; i < this->get_row(); i++) {
				for (int j = 0; j < this->get_column(); j++) {
					newMatrix.set_element(i, j, this->get_element(i, j) - matr.matrix[i][j]);
				}
			}
			return newMatrix;
		}
		else
			throw (invalid_argument("Dimmensions don't match"));
	}
	Matrix operator* (float scalar) {
		Matrix newMatrix(this->get_row(), this->get_column());
		for (int i = 0; i < this->get_row(); i++) {
			for (int j = 0; j < this->get_column(); j++) {
				newMatrix.set_element(i, j, this->get_element(i, j) * scalar);
			}
		}
		return newMatrix;
	}
	bool operator== (const Matrix& matr) {
		if (this->get_column() == matr.column && this->get_row() == matr.row) {
			for (int i = 0; i < this->get_row(); i++) {
				for (int j = 0; j < this->get_column(); j++) {
					if (matr.matrix[i][j] != this->get_element(i, j))
						return false;
				}
			}
			return true;
		}
		else
			throw (invalid_argument("Dimmensions don't match"));
	}
	float determinant() { //multithreading on
		if (this->get_row() == this->get_column()) {
			vector<thread> threadList;
			float det = 1;
			Matrix temp(this->row, this->column); // create temp matrix
			for (auto i = 0; i < this->row; i++)
				for (auto j = 0; j < this->column; j++)
					temp.set_element(i, j, this->get_element(i, j)); // copy original matrix to temp
			/////////////////////////////////////////////////////////////////////////////////////////////////
			for (auto j = 0; j < this->row - 1; j++) {
				for (auto i = 0; i < this->row - 1 - j; i++) {
					threadList.push_back(thread(triang, ref(temp), i, j));
				}
				for (auto i = 0; i < threadList.size(); i++) {
					if (threadList.at(i).joinable()) {
						threadList.at(i).join();
					}
				}
				for (auto i = 0; i < threadList.size(); i++) {
					threadList.pop_back();
				}
				//output for debug goes here
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			for (auto i = 0; i < temp.get_row(); i++)
				det *= temp.get_element(i, i);
			return det;
		}
		else
			throw (invalid_argument("Matrix isn't square"));
	}
	friend ostream& operator << (ostream &outputStream, Matrix &matrix) {
		for (int i = 0; i < matrix.get_row(); i++) {
			for (int j = 0; j < matrix.get_column(); j++) {
				outputStream << matrix.get_element(i, j) << " ";
			}
			outputStream << endl;
		}
	}
};

