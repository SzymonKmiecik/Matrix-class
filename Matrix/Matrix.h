#pragma once

#include <iostream>
#include <vector>
#include <cmath>




template <typename T> class Matrix
{
private:
	unsigned rows;
	unsigned cols;
	//matrix data
	std::vector<std::vector<T> > data;

	void initMatrix(std::vector<std::vector<T> >&, unsigned, unsigned);

	
	

public:
	//usefull static tools
	static const double pi ;
	static double deg2rad(double);

	//constructors
	Matrix();
	Matrix(unsigned rowNum, unsigned colNum, const T& initParam);
	~Matrix();

	//methods
	unsigned get_rows() const;
	unsigned get_cols() const;
	Matrix<T>& rotX(double);
	Matrix<T>& rotY(double);
	Matrix<T>& rotZ(double);
	
	//Method for bvh files motion calculation
	Matrix<T>& homogenous_transform();
	Matrix<T>& input_offset(const double offset[]);

	//operators overloading
	Matrix<T>& operator=(const Matrix<T>& r);
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	//matrix
	Matrix<T> operator+(const Matrix<T>& r);
	Matrix<T>& operator+=(const Matrix<T>& r);
	Matrix<T> operator-(const Matrix<T>& r);
	Matrix<T>& operator-=(const Matrix<T>& r);
	Matrix<T> operator*(const Matrix<T>& r);
	Matrix<T>& operator*=(const Matrix<T>& r);

	//scalar
	Matrix<T> operator+(const T& r);
	Matrix<T> operator-(const T& r);
	Matrix<T> operator*(const T& r);
	Matrix<T> operator/(const T& r);

	//vector
	std::vector<T> operator*(const std::vector<T>& r);





};

