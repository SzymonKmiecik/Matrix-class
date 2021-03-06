// Matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <iostream>

const double Matrix<double>::pi = std::acos(-1);

template <typename T>
Matrix<T>::Matrix()
{
}
/*
template <typename T>
void Matrix<T>::initMatrix(std::vector<std::vector<double> >& data, unsigned cols, unsigned rows)
{	

	std::vector<std::vector<double> > tempData(cols, std::vector<double>(rows, 0));
	data = tempData;
} */
template <typename T>
Matrix<T>::Matrix(unsigned rowsNumber, unsigned colsNumber,  const T& initParam)
{
	this->rows = rowsNumber;
	this->cols = colsNumber;
	this->data.resize(rows);
	for (unsigned i = 0; i < data.size(); i++)
		data[i].resize(cols, initParam);
	//initMatrix(this->data,this->rows, this->cols);
}
template <typename T>
Matrix<T>::~Matrix()
{
}

template<typename T>
unsigned Matrix<T>::get_rows() const
{
	return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const
{
	return this->cols;
}



template<typename T>
Matrix<T>& Matrix<T>::homogenous_transform()
{
	cols++;
	rows++;
	data.resize(rows);
	for (unsigned i = 0; i < data.size(); i++)
		data[i].resize(cols);

	for (unsigned i = 0; i < rows; i++)
		data[i][cols-1] = 1.0;

	for (unsigned i = 0; i < cols - 1; i++)
		data[rows-1][i] = 0.0; 

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::input_offset(const double offset[])
{	
	for (unsigned i = 0; i < rows-1; i++)
	{
		data[i][cols-1] = offset[i];
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& r)
{	
	if (&r == this)
		return *this;

	unsigned new_rows = r.get_rows();
	unsigned new_cols = r.get_cols();
	data.resize(new_rows);
	for (unsigned i = 0; i < data.size(); i++)
		data[i].resize(new_cols);

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++)
		{
			data[i][j] = r(i, j);
		}
	}
	rows = new_rows;
	cols = new_cols;
	return *this;

}

template<typename T>
T & Matrix<T>::operator()(const unsigned & row, const unsigned & col)
{
	return this->data[row][col];
}

template<typename T>
const T & Matrix<T>::operator()(const unsigned & row, const unsigned & col) const
{
	return this->data[row][col];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& r)
{
	Matrix result(rows, cols, 0.0);

		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
			{
				result(i, j) = this->data[i][j] + r(i, j);
			}
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& r)
{
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
		{
			 this->data[i][j] += r(i, j);
		}
	return *this;

}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& r)
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
		{
			result(i, j) = this->data[i][j] - r(i, j);
		}
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& r)
{
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
		{
			this->data[i][j] -= r(i, j);
		}
	return *this;

}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& r)
{	
	unsigned rows = r.get_rows();
	unsigned cols = r.get_cols();
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			for (unsigned k = 0; k < rows; k++)
				result(i, j) += this->data[i][k] * r(k, j);
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& r)
{
	Matrix result = (*this) * r;
	*this = result;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] + r;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] - r;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] * r;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] / r;
		}
	}

	return result;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& r)
{
	std::vector<T> result;
	result.resize(rows);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result[i] = this->data[i][j] * r[j];
		}
	}

	return result;
}
template<typename T>
double Matrix<T>::deg2rad(double angle)
{	
	double result =  Matrix<T>::pi / 180.0*angle; 
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::rotX(double angle)
{
	double radians = Matrix<double>::deg2rad(angle);
	Matrix<double> rotation_matrix(4, 4, 0.0);
	//rotationa around x axis declaration
	rotation_matrix(0, 0) = 1.0;
	rotation_matrix(0, 1) = 0.0;
	rotation_matrix(0, 2) = 0.0;
	rotation_matrix(0, 3) = 0.0;

	rotation_matrix(1, 0) = 0.0;
	rotation_matrix(1, 1) = std::cos(radians);
	rotation_matrix(1, 2) = -(std::sin(radians));
	rotation_matrix(1, 3) = 0.0;

	rotation_matrix(2, 0) = 0.0;
	rotation_matrix(2, 1) = std::sin(radians);
	rotation_matrix(2, 2) = std::cos(radians);
	rotation_matrix(2, 3) = 0.0;

	rotation_matrix(3, 0) = 0.0;
	rotation_matrix(3, 1) = 0.0;
	rotation_matrix(3, 2) = 0.0;
	rotation_matrix(3, 3) = 1.0;
	//-------------------------------------

	Matrix<double> result = (*this) * rotation_matrix;
	*this = result;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::rotY(double angle)
{
	double radians = Matrix<double>::deg2rad(angle);
	Matrix<double> rotation_matrix(4, 4, 0.0);
	//rotationa around x axis declaration
	rotation_matrix(0, 0) = std::cos(radians);
	rotation_matrix(0, 1) = 0.0;
	rotation_matrix(0, 2) = std::sin(radians);
	rotation_matrix(0, 3) = 0.0;

	rotation_matrix(1, 0) = 0.0;
	rotation_matrix(1, 1) = 1.0;
	rotation_matrix(1, 2) = 0.0;
	rotation_matrix(1, 3) = 0.0;

	rotation_matrix(2, 0) = -(std::sin(radians));
	rotation_matrix(2, 1) = 0.0;
	rotation_matrix(2, 2) = std::cos(radians);
	rotation_matrix(2, 3) = 0.0;

	rotation_matrix(3, 0) = 0.0;
	rotation_matrix(3, 1) = 0.0;
	rotation_matrix(3, 2) = 0.0;
	rotation_matrix(3, 3) = 1.0;
	//-------------------------------------

	std::cout << std::endl;
	Matrix<double> result = (*this) * rotation_matrix;
	*this = result;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::rotZ(double angle)
{
	double radians = Matrix<double>::deg2rad(angle);
	Matrix<double> rotation_matrix(4, 4, 0.0);
	//rotationa around x axis declaration
	rotation_matrix(0, 0) = std::cos(radians);
	rotation_matrix(0, 1) = -(std::sin(radians));
	rotation_matrix(0, 2) = 0.0;
	rotation_matrix(0, 3) = 0.0;

	rotation_matrix(1, 0) = std::sin(radians);
	rotation_matrix(1, 1) = std::cos(radians);
	rotation_matrix(1, 2) = 0.0;
	rotation_matrix(1, 3) = 0.0;

	rotation_matrix(2, 0) = 0.0;
	rotation_matrix(2, 1) = 0.0;
	rotation_matrix(2, 2) = 1.0;
	rotation_matrix(2, 3) = 0.0;

	rotation_matrix(3, 0) = 0.0;
	rotation_matrix(3, 1) = 0.0;
	rotation_matrix(3, 2) = 0.0;
	rotation_matrix(3, 3) = 1.0;
	//-------------------------------------

	std::cout << std::endl;
	Matrix<double> result = (*this) * rotation_matrix;
	*this = result;
	return *this;
}






//Testing code (delete this if you want to include in own program)------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	Matrix<double> mat1(3, 3, 25.0);
	Matrix<double> mat2(3, 3, 13.5);
	Matrix<double> rotationTest(4, 4, 1.0);
	mat2.homogenous_transform();
	rotationTest(0, 0) = -8.0;
	rotationTest.rotX(180.0);
	//mat2(1, 1) = -3.0;
	mat1(0, 0) = 1.5;
	//Matrix<double> mat3 = mat1 * mat2;

	std::cout << "Rotation Test: " << std::endl;
	for (unsigned i = 0; i < rotationTest.get_rows(); i++) {
		for (unsigned j = 0; j < rotationTest.get_cols(); j++) {
			std::cout << rotationTest(i, j) << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << "\nHomogenous test: " << std::endl;
	for (unsigned i = 0; i < mat2.get_rows(); i++) {
		for (unsigned j = 0; j < mat2.get_cols(); j++) {
			std::cout << mat2(i, j) << ", ";
		}
		std::cout << std::endl;
	}
	double test[3] = { 33.0,22.0,11.0 };
	mat2.input_offset(test);

	std::cout << "\nOffset test: " << std::endl;
	for (unsigned i = 0; i < mat2.get_rows(); i++) {
		for (unsigned j = 0; j < mat2.get_cols(); j++) {
			std::cout << mat2(i, j) << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << "\nDegrees to radians test: " << std::endl;
	std::cout << "33,342 degree= " << Matrix<double>::deg2rad(33.342) << " radians" << std::endl;

	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	std::cout << "\nBVH check: " << std::endl;
	// OFFSET -19.163 -10.737 -301.755
	// CHANNELS 6 Xposition Yposition Zposition Zrotation Xrotation Yrotation
	// first frame: -15.4714 -11.5965 -304.041 -0.0824751 -3.55841 16.6619
	// six frame: -14.5814 -11.8259 -305.446 -0.226228 -2.80006 16.0714
	Matrix<double> bvh_transform(3, 3, 0.0);
	//load identity
	bvh_transform(0, 0) = 1.0;
	bvh_transform(1, 1) = 1.0;
	bvh_transform(2, 2) = 1.0;
	bvh_transform.homogenous_transform();
	double offset[] = { -19.163, -10.737, -301.755 };
	bvh_transform.input_offset(offset);
	bvh_transform(0, 3) += -15.4714;
	bvh_transform(1, 3) += -11.5965;
	bvh_transform(2, 3) += -304.041;

	//bvh_transform(0, 3) += -14.5814;
	//bvh_transform(1, 3) += -11.8259;
	//bvh_transform(2, 3) += -305.446;

	bvh_transform.rotZ(-0.0824751);
	bvh_transform.rotX(-3.55841);
	bvh_transform.rotY(16.6619);

	//bvh_transform.rotZ(-0.226228);
	//bvh_transform.rotX(-2.80006);
	//bvh_transform.rotY(16.0714);
	std::vector<double> origin = { -19.163, -10.737, -301.755, 1.0 };

	//OFFSET 7.016 -7.243 2.992
	//CHANNELS 6 Xposition Yposition Zposition Zrotation Xrotation Yrotation
	//first frame 7.46244 -7.63879 2.47149 0.163176 -2.23323 -5.90964
	//six frame 7.42241 -7.62118 2.5475 -0.401849 -2.86034 -6.62257

	Matrix<double> bvh_transform2(3, 3, 0.0);
	//load identity
	bvh_transform2(0, 0) = 1.0;
	bvh_transform2(1, 1) = 1.0;
	bvh_transform2(2, 2) = 1.0;
	bvh_transform2.homogenous_transform();
	double offset2[] = { 7.016, -7.243, 2.992 };
	bvh_transform2.input_offset(offset2);
	bvh_transform2(0, 3) += 7.46244;
	bvh_transform2(1, 3) += -7.63879;
	bvh_transform2(2, 3) += 2.47149;

	bvh_transform2.rotZ(0.163176);
	bvh_transform2.rotX(-2.2332);
	bvh_transform2.rotY(-5.90964);
	std::vector<double> origin2 = { 7.016,-7.243, 2.992, 0.0 };
	std::vector<double> origin_zeros = { 0.0,0.0,0.0,1.0 };
	for (unsigned i = 0; i < origin2.size(); i++)
		origin2[i] += origin[i];

	std::vector<double> result = bvh_transform * bvh_transform2  * origin_zeros; //working >> origin is no matter until is homogenous. First matrices for multiplying are the oldest in hierarchy
																				 //---------------------------------------------------------------------------------------------------------------------------------------------------------
	std::cout << "\nXYZ: " << std::endl;
	for (unsigned i = 0; i < result.size(); i++)
	{
		std::cout << result[i] << std::endl;
	}

	return 0;
}
