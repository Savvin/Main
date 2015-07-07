#include <iostream>
#include <string>
#include <cstring>
#include "matrix.h"
#include <vector>
#include <fstream>
#include <algorithm>


Matrix<int> levenstein_matrix;
Matrix< std::vector<int> > levenstein_way_matrix;

std::vector<std::string> parseFile(const std::string &file_name)
{    
    std::vector<std::string> strings;
    
    std::ifstream file;
                  file.open(file_name.c_str());
    
    int iteration = 1;              
    std::string tmp;    
    for(int i = 0; !file.eof(); ++i)
    {
        //if(strings.size() < iteration) // если в векторе не хватает места, то расширяю его
          //  strings.resize(strings.size() + 100);
        
        getline(file, tmp);
        strings.push_back(tmp);
        
        ++iteration;
    }
    
    // если размер вектора оказался больше кол-ва строчек, уменьшаю вектор
    if((iteration - 1) < strings.size())
        strings.resize(iteration - 1);
    
    file.close();
    
    return strings;
}

std::vector<std::string> parseFile_i(const std::string &file_name)
{    
    std::vector<std::string> strings;
    
    std::ifstream file;
                  file.open(file_name.c_str());
    
    int iteration = 1;              
    std::string tmp;    
    for(int i = 0; !file.eof(); ++i)
    {
        getline(file, tmp);
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        strings.push_back(tmp);
        
        ++iteration;
    }
    
    // если размер вектора оказался больше кол-ва строчек, уменьшаю вектор
    if((iteration - 1) < strings.size())
        strings.resize(iteration - 1);
    
    file.close();
    
    return strings;
}

void findLevensteinDistanceMatrix(const std::vector<std::string> &file_1, const std::vector<std::string> &file_2)
{
    int column_size = file_2.size() + 1;
    int lines_size  = file_1.size() + 1;
    
    levenstein_matrix     = levenstein_matrix.createLevensteinMatrix(lines_size, column_size);
    // матрица элементы которой - 2 индекса, откуда получилось текущее число(например, если минимальным будет d_i, то будут записаны i-1 и j) 
    levenstein_way_matrix = levenstein_way_matrix.createLevensteinWayMatrix(lines_size, column_size);
    
    for(int i = 1; i < lines_size; ++i)
    {
        for(int j = 1; j < column_size; ++j)
        {
            // инициализирую 3 варианта значений функции d
            int d_j = levenstein_matrix.matrix[i][j - 1] + 1;
            int d_i = levenstein_matrix.matrix[i - 1][j] + 1;
            int d_i_j = (file_1[i - 1] == file_2[j - 1]) ? levenstein_matrix.matrix[i - 1][j - 1] : levenstein_matrix.matrix[i - 1][j - 1] + 1;
            
            // заполняю текущий элемент матрицы levenstein_matrix минимальным из значений d
            if((d_j <= d_i) && (d_j <= d_i_j))
            {
                levenstein_matrix.matrix[i][j]        = d_j;
                levenstein_way_matrix.matrix[i][j][0] = i;
                levenstein_way_matrix.matrix[i][j][1] = (j - 1);
            }
            else
            {
                if(d_i <= d_i_j)
                {
                    levenstein_matrix.matrix[i][j]        = d_i;
                    levenstein_way_matrix.matrix[i][j][0] = (i - 1);
                    levenstein_way_matrix.matrix[i][j][1] = j;
                }
                else
                {
                    levenstein_matrix.matrix[i][j]        = d_i_j;
                    levenstein_way_matrix.matrix[i][j][0] = (i - 1);
                    levenstein_way_matrix.matrix[i][j][1] = (j - 1);
                }
            }
        }
    }
}

// по матрице пути Левенштейна нахожу кратчайший путь для получений из 1го файла 2ого
// возвращаемый результат - вектор индексов, из какой ячейки в какую надо перейти
std::vector< std::vector<int> > findMinWay()
{
    const int column_size  = levenstein_way_matrix.n;
    const int lines_size   = levenstein_way_matrix.m;
    const int min_way_size = column_size + 1;
    
    // каждый элемент вектора - пара индексов i j в который следует перейти в следующий момент

    
    std::vector< std::vector<int> > min_way(1, std::vector<int>(2));

    //! инициализирую min_way

    // инициализирую последнюю ячейку
    min_way[0][0] = lines_size - 1;
    min_way[0][1] = column_size - 1;

    bool b = 1;
    for(int i = 1; b; ++i)
    {   
        min_way.push_back(std::vector < int > (2));
        min_way[i][0] = levenstein_way_matrix.matrix[min_way[i - 1][0]][min_way[i - 1][1]][0];
        min_way[i][1] = levenstein_way_matrix.matrix[min_way[i - 1][0]][min_way[i - 1][1]][1];

        if((min_way[i][0] == 0) && (min_way[i][1] == 0))
            b = 0;
    }   
    reverse(min_way.begin(), min_way.end());   
    //while(i-- >= 0) min_way.erase(min_way.begin()); 
    
    return min_way;
}

void printDiffResult(const std::vector< std::vector<int> > &min_way, 
                     const std::vector<std::string> &file_1, const std::vector<std::string> &file_2)
{
    int min_way_size = min_way.size();    
    
    for(int k = 0; k < (min_way_size - 1); ++k)
    {
        if((min_way[k][0] != min_way[k + 1][0]) && (min_way[k][1] == min_way[k + 1][1])) //удаление
        {
            std::cout << min_way[k + 1][0] << "d" << min_way[k][1] << "\n";
            std::cout << "< " << file_1[min_way[k + 1][0] - 1] << "\n";
        }
        else
        {
            if((min_way[k][1] != min_way[k + 1][1]) && (min_way[k][0] == min_way[k + 1][0])) // вставка
            {
                std::cout << min_way[k][0] << "i" << min_way[k + 1][1] << "\n";
                std::cout << "> " << file_2[min_way[k + 1][1] - 1] << "\n";
            }
            else 
            {
                int curr_i = min_way[k][0];
                int curr_j = min_way[k][1];
                
                if(levenstein_matrix.matrix[curr_i][curr_j] != levenstein_matrix.matrix[curr_i + 1][curr_j + 1]) // замена
                {
                    std::cout << min_way[k + 1][0] << "c" << min_way[k + 1][1] << "\n";
                    std::cout << "< " << file_1[min_way[k + 1][0] - 1] << "\n";
                    std::cout << "> " << file_2[min_way[k + 1][1] - 1] << "\n";
                }
            }
        }
    }
}


std::vector<std::string> parseString(const int a, char* b[])
{
    const int input_data_size = (a - 1);
    std::vector<std::string> input_data(input_data_size);
    
    for(int i = 0; i < input_data_size; ++i)
        input_data[i] = b[i + 1];
    
    return input_data;
}


int main(int argc, char* argv[])
{
    
    if(argc > 1) // 0е - имя файла(./diff)
    {
        std::vector<std::string> input_data      = parseString(argc, argv);
        const int                input_data_size = input_data.size();
        
        if(argc >= 2)
        {
            const std::string name_file_one = input_data[input_data_size - 2];
            const std::string name_file_two = input_data[input_data_size - 1];
            
            std::vector<std::string> file_one;
            std::vector<std::string> file_two;

            if(argc > 2 && strcmp(argv[1], "-i") == 0)
            {
                file_one = parseFile_i(name_file_one);
                file_two = parseFile_i(name_file_two);
            }
            else
            {

                file_one = parseFile(name_file_one);
                file_two = parseFile(name_file_two);
            }
            
            for(int i = 0; i < file_one.size(); ++i)
                std::cout << file_one[i] << " ";
            std::cout << "\n";
            
            for(int i = 0; i < file_two.size(); ++i)
                std::cout << file_two[i] << " ";
            std::cout << "\n";

            std::cout << "File 1 name: " << name_file_one << std::endl;
            std::cout << "File 2 name: " << name_file_two << std::endl;
            std::cout <<"----------------------------------------------------\\" << std::endl;

        
            
            findLevensteinDistanceMatrix(file_one, file_two);
            
                //levenstein_matrix.print();
            
            std::vector< std::vector<int> > min_way = findMinWay();
        
            /*for(int i = 0; i < min_way.size(); ++i)
            {
                std::cout << min_way[i][0] << " " << min_way[i][1] << "\n";
            }*/
            
            printDiffResult(min_way, file_one, file_two);
        }
        
    }
    
    return 0;
}
