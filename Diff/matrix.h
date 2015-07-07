#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

template<typename T> class Matrix
{
    public:
    int    m;
    double n;
    std::vector< std::vector<T> > matrix;
    
    Matrix()
    {
        m = 0;
        n = 0;
    }   
    
    Matrix(int m_size, int n_size)
    {
        m = m_size;
        n = n_size;
        matrix = std::vector< std::vector<T> >(m_size);
        
        for(int i = 0; i < m_size; ++i)
            matrix[i] = std::vector<T>(n_size);
    }
    
    Matrix& operator = (const Matrix &for_copy)     // Почему возвращаемый тип с &???
    {        
        m = for_copy.m;
        n = for_copy.n;
        matrix = std::vector< std::vector<T> >(m);
        
        for(int i = 0; i < m; ++i)
            matrix[i] = std::vector<T>(n);
        
        //копирую элементы
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                matrix[i][j] = for_copy.matrix[i][j];
                
        return (*this);
    }
    
    // инициализирую 1ю строчку и 1й столбец матрицы Левенштейна 
    Matrix<int> createLevensteinMatrix(const int lines_size, const int column_size)
    {
        Matrix<int> levenstein_matrix(lines_size, column_size);
        
        // инициализирую 1ю строчку
        for(int j = 0; j < column_size; ++j)
            levenstein_matrix.matrix[0][j] = j;
        
        // инициализирую 1й столбец
        for(int i = 0; i < lines_size; ++i)
            levenstein_matrix.matrix[i][0] = i;
        
        return levenstein_matrix;
    }

    // инициализирую 1ю строчку и 1й столбец матрицы Левенштейна 
    Matrix< std::vector<int> > createLevensteinWayMatrix(const int lines_size, const int column_size)
    {
        Matrix< std::vector<int> > levenstein_way_matrix(lines_size, column_size);
        
        for(int i = 0; i < lines_size; ++i)
        {
            for(int j = 0; j < column_size; ++j)
                levenstein_way_matrix.matrix[i][j] = std::vector<int>(2);
        }
        
        // инициализирую 1ю строчку
        for(int j = 0; j < column_size; ++j)
        {
            levenstein_way_matrix.matrix[0][j][0] = 0;
            levenstein_way_matrix.matrix[0][j][1] = (j - 1);
        }
        
        // инициализирую 1й столбец
        for(int i = 0; i < lines_size; ++i)
        {
            levenstein_way_matrix.matrix[i][0][0] = (i - 1);
            levenstein_way_matrix.matrix[i][0][1] = 0;
        }
        
        return levenstein_way_matrix;
    }

    
    void print() const
    {
        std::cout << "Matrix size: " << m << "*" << n << std:: endl;
        
        for(int i = 0; i < m ; ++i)
        {
            for(int j = 0; j < n; ++j)
                printf("%2d\t", matrix[i][j]); //matrix[i][j] << "   ";
            std::cout << std::endl;   
        }
    }
    
    ~Matrix()
    {            
        m = 0;
        n = 0;
    }
}; 
