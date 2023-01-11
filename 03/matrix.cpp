#include <iostream>


class Matrix

{

public:
    Matrix()
    {
        rows = 0;
        cols = 0;
        M = nullptr;
    }

    Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        M = new int*[rows];

        for (int i = 0; i < rows; i++)
            M[i] = new int[cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M[i][j] = 0;
    }

    int getRows()
    {
        return rows;
    }

    int getColumns()
    {
        return cols;
    }

    int getElement(int i, int j) 
    {
        if (i <= rows && j <= cols)
        {
            return M[i][j];
        }
        else 
        {
            throw std::out_of_range("Element is out of range!");
        }
    }

    void setElement(int i, int j, int value)
    {
        if (i <= rows && j <= cols)
        {
            M[i][j] = value;
        }
        else 
        {
            throw std::out_of_range("Element is out of range!");
        }
    }

    void operator*=(int num)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M[i][j] *= num;
    }

    Matrix operator+(const Matrix& _M)
    {
        Matrix newMatrix(rows, cols);
        if (rows != _M.rows || cols != _M.cols)
        {
            throw std::out_of_range("Sizes are different!");

        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                newMatrix.M[i][j] = M[i][j] + _M.M[i][j];
        return newMatrix;
    }

    bool operator==(const Matrix& _M)
    {
        if (rows != _M.rows || cols != _M.cols)
        {
            throw std::out_of_range("Sizes are different!");

        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (M[i][j] != _M.M[i][j])
                {
                    return false;
                }
                    
        return true;
    }

    friend std::ostream& operator<< (std::ostream& out, const Matrix& mat);

   /* std::ostream& operator<<(std::ostream& s)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                s << M[i][j];
                s << "\t";
            }
                
            s << "\n";
        }
        return s;
    }*/


    ~Matrix()
    {
        if (cols > 0)
        {
            for (int i = 0; i < rows; i++)
                delete[] M[i];
        }

        if (rows > 0)
            delete[] M;
    }
    

private:
    int** M = nullptr;
    int rows;
    int cols;
};

inline std::ostream& operator<< (std::ostream& out, const Matrix& matrix)
{
    for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                out << matrix.M[i][j];
                out << "\t";
            }
                
            out << "\n";
        };
    return out;
}

/*int main()

{
    Matrix emptyMatrix;
    Matrix matrixA(3, 2);
    Matrix matrixB(3, 2);
    Matrix matrixD(3, 2);
    Matrix matrixE(2, 3);

    std::cout << "A" << std::endl;
    std::cout << matrixA << std::endl;
    
    std::cout << "Rows: " << matrixA.getRows() << std::endl;
    std::cout << "Columns: " << matrixA.getColumns() << std::endl;
    matrixA.setElement(1, 1, 4);
    matrixA.setElement(0, 0, 5);
    matrixA.setElement(0, 1, 9);
    matrixA.setElement(1, 1, 2);
    matrixA.setElement(2, 1, 2);
    std::cout << "A" << std::endl;
    std::cout << matrixA << std::endl;
    std::cout << "Element[1][1] is: " << matrixA.getElement(1, 1) << std::endl;
    //std::cout << "Element[5][6] is: " << matrixA.getElement(5, 6) << std::endl;
    matrixA *= 5;
    std::cout << "A * 5" << std::endl;
    std::cout << matrixA << std::endl;

    
    matrixB.setElement(1, 1, 4);
    matrixB.setElement(0, 0, 5);
    matrixB.setElement(0, 1, 2);
    matrixB.setElement(1, 2, 6);
    matrixB.setElement(2, 1, 2);
    matrixB.setElement(2, 0, 7);
    std::cout << "B" << std::endl;
    std::cout << matrixB << std::endl;
    std::cout << "Rows: " << matrixB.getRows() << std::endl;
    std::cout << "Columns: " << matrixB.getColumns() << std::endl;

    std::cout << "D" << std::endl;
    std::cout << matrixD << std::endl;
    std::cout << "Rows: " << matrixD.getRows() << std::endl;
    std::cout << "Columns: " << matrixD.getColumns() << std::endl;

    std::cout << "E" << std::endl;
    std::cout << matrixE << std::endl;
    std::cout << "Rows: " << matrixE.getRows() << std::endl;
    std::cout << "Columns: " << matrixE.getColumns() << std::endl;



    bool equalsBD = (matrixB != matrixD);
    std::cout << "D not equals B: " << equalsBD << std::endl;
    bool equalsAD = (matrixA != matrixD);
    std::cout << "D not equals A: " << equalsAD << std::endl;

    Matrix sumMatrix = matrixA + matrixB;
    std::cout << "sumMatrix" << std::endl;
    std::cout << sumMatrix << std::endl;
    return 0;
}*/