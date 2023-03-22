#include <iostream>


class Matrix

{
    class ProxyRow
    {
    private:
        int *data_;
        int n = 0;
        friend class Matrix;
        friend std::ostream& operator<< (std::ostream& out, const Matrix& mat) ;
    public:

        int& operator[](int j);
    };

public:
    Matrix();
    

    Matrix(int _rows, int _cols);

    ProxyRow& operator[](int i);

    int getRows() const;

    int getColumns() const;

    

    
    void operator*=(int num);

    Matrix operator+(const Matrix& _M);

    bool operator==(const Matrix& _M) const;

    friend std::ostream& operator<< (std::ostream& out, const Matrix& mat) ;

   

    ~Matrix();
    

private:
    //int** M = nullptr;
    ProxyRow *rows_;
    int rows;
    int cols;
    friend class ProxyRow;
};

inline std::ostream& operator<< (std::ostream& out, const Matrix& matrix)
{
    

    for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                out << matrix.rows_[i].data_[j];
                if (j != matrix.cols - 1)
                    out << "\t";
            }
                
            out << "\n";
        };
    return out;
}
