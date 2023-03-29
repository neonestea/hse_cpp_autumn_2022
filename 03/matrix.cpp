#include <iostream>
#include "matrix.h"




int& Matrix::ProxyRow::operator[](int j)
        {
            if (j > n-1)
            {
                throw std::out_of_range("Sizes are different!");

            }
            return data_[j];
        }

 Matrix::Matrix()
    {
        rows = 0;
        cols = 0;
        rows_ = nullptr;
    }

 Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        rows_ = new ProxyRow[rows];

        for (int i = 0; i < rows; i++)
        {
            rows_[i].data_ = new int[cols];
            rows_[i].n = _cols;
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                rows_[i].data_[j] = 0;
    }

    Matrix::ProxyRow&  Matrix::operator[](int i)
    {
        if (i > rows-1)
        {

            throw std::out_of_range("Sizes are different!");

        }
        return rows_[i];
    }

    int  Matrix::getRows() const
    {
        return rows;
    }

    int  Matrix::getColumns() const
    {
        return cols;
    }

    

    
    void  Matrix::operator*=(int num)
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                rows_[i].data_[j] *= num;
    }

    Matrix  Matrix::operator+(const Matrix& _M)
    {
        Matrix newMatrix(rows, cols);
        if (rows != _M.rows || cols != _M.cols)
        {
            throw std::out_of_range("Sizes are different!");

        }
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                newMatrix.rows_[i].data_[j] = rows_[i].data_[j] + _M.rows_[i].data_[j];
        return newMatrix;
    }

    bool  Matrix::operator==(const Matrix& _M) const
    {
        if (rows != _M.rows || cols != _M.cols)
        {
            throw std::out_of_range("Sizes are different!");

        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "[" << i << "]" << "[" << j << "]" << " - first " << rows_[i].data_[j] << ", second " << _M.rows_[i].data_[j] << std::endl;
                if (rows_[i].data_[j] != _M.rows_[i].data_[j])
                {
                    return false;
                }   
            }
        }          
        return true;
    }


   

    Matrix::~Matrix()
    {
        

        if (rows > 0) {
            
            for (int i = 0; i < rows; ++ i)
            {
                delete[] rows_[i].data_;
            }
            delete[] rows_;
        }
            
    }
    
