#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<random>
#include<math.h>
void s_accum()
{

}
void s_fanin()
{

}
void fld_accum()
{

}
void fld_fanin()
{

}
void fulld_accum()
{

}
void fulld_fanin()
{

}
void tdigit_accum()
{

}
void tdigit_fanin()
{

}
void s_accum(std::vector<float> matrix)
{
    
    float xi_i;
    for (float x : matrix) //recursive
    {
        //std::cout << x << "\t";
        xi_i = xi_i + x;
        //std::cout << xi_i<<"\t";
    }
    std::cout << "single precision accumulation: " << xi_i << "\n";
}
void s_fanin(std::vector<float> matrix)
{
    float s_sp, sp_end, s_sp_total = 0, sp_end_total = 0;
    int j = matrix.size() - 1;
    for (float i = 0; i < (matrix.size() / 2) - 1; i += 2)
    {

        s_sp = matrix[i] + matrix[i + 1];
        s_sp_total = s_sp + s_sp_total;
        sp_end = matrix[j] + matrix[j - 1];
        sp_end_total = sp_end + sp_end_total;
        j -= 2;
    }
    float sum = s_sp_total + sp_end_total;
    if (matrix.size() % 2 == 1) //if for some reason, array/vector isn't 2^n or even, then this is needed.
    {
        sum = sum + matrix[(matrix.size() / 2) + 1];
    }
    std::cout << "single precision fan-in: " << sum << "\n";
}
void fld_accum(std::vector<float> matrix)
{
    double xi_i;
    for (float x : matrix) //recursive
    {
        //std::cout << x << "\t";
        xi_i = xi_i + double(x);
        //std::cout << xi_i<<"\t";
    }
    std::cout << "double precision accumulation: " << float(xi_i) << "\n";
}
void fld_fanin(std::vector<float> matrix)
{
    double s_sp, sp_end, s_sp_total = 0, sp_end_total = 0;
    int j = matrix.size() - 1;
    for (double i = 0; i < (matrix.size() / 2) - 1; i += 2)
    {

        s_sp = double(matrix[i]) + double(matrix[i + 1]);
        s_sp_total = s_sp + s_sp_total;
        sp_end = double(matrix[j]) + double(matrix[j - 1]);
        sp_end_total = sp_end + sp_end_total;
        j -= 2;
    }
    double sum = s_sp_total + sp_end_total;
    if (matrix.size() % 2 == 1) //if for some reason, array/vector isn't 2^n or even, then this is needed.
    {
        sum = sum + matrix[(matrix.size() / 2) + 1];
    }
    std::cout << "double precision fan-in: " << float(sum) << "\n";
}
void fulld_accum(std::vector<double> matrix)
{
    double xi_i;
    for (double x : matrix) //recursive
    {
        //std::cout << x << "\t";
        xi_i = xi_i + x;
        //std::cout << xi_i<<"\t";
    }
    std::cout << "full double precision accumulation: " << xi_i << "\n";
}
void fulld_fanin(std::vector<double> matrix)
{
    double s_sp, sp_end, s_sp_total = 0, sp_end_total = 0;
    int j = matrix.size() - 1;
    for (double i = 0; i < (matrix.size() / 2) - 1; i += 2)
    {

        s_sp = matrix[i] + matrix[i + 1];
        s_sp_total = s_sp + s_sp_total;
        sp_end = matrix[j] + matrix[j - 1];
        sp_end_total = sp_end + sp_end_total;
        j -= 2;
    }
    double sum = s_sp_total + sp_end_total;
    if (matrix.size() % 2 == 1) //if for some reason, array/vector isn't 2^n or even, then this is needed.
    {
        sum = sum + matrix[(matrix.size() / 2) + 1];
    }
    std::cout << "full double fan-in: " << sum << "\n";
}
void tdigit_accum(std::vector<double> matrix)
{
    double xi_i;
    for (double x : matrix) //recursive
    {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(-.5, .5);
        double epsilon_i = distribution(generator) * pow(10,-1); //change t here.
       
        //double epsilon_i = (float)rand() / RAND_MAX;

        //std::cout << x << "\t";
        xi_i = (xi_i + x) * (1 + epsilon_i);
        //std::cout << epsilon_i << "\n";
        //std::cout << xi_i<<"\t";
    }
    std::cout << "t digit accumulation: " << xi_i << "\n";
}
void tdigit_fanin(std::vector<double> matrix)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-.5, .5);

    double s_sp, sp_end, s_sp_total = 0, sp_end_total = 0;
    int j = matrix.size() - 1;
    for (double i = 0; i < (matrix.size() / 2) - 1; i += 2)
    {
        double epsilon_i = distribution(generator) * pow(10, -1); //change t here.

        s_sp = (matrix[i] + matrix[i + 1]) * (1 + epsilon_i);
        s_sp_total = s_sp + s_sp_total;
        sp_end = (matrix[j] + matrix[j - 1]) * (1 + epsilon_i);
        sp_end_total = sp_end + sp_end_total;
        j -= 2;
    }
    double sum = s_sp_total + sp_end_total;
    if (matrix.size() % 2 == 1) //if for some reason, array/vector isn't 2^n or even, then this is needed.
    {
        sum = sum + matrix[(matrix.size() / 2) + 1];
    }
    std::cout << "t digit fan-in: " << sum << "\n";
}

int main()
{	
    
    std::ifstream fl("r#.txt");
    std::vector<float> matrix; 
    
    float element;
    while (fl >> element) //storing the file into a vector as single precision
    {
        matrix.push_back(element);
        //std::cout << element <<"\t";
    }
    s_accum(matrix);
    s_fanin(matrix);
    fld_accum(matrix);
    fld_fanin(matrix);

    std::ifstream dou("r#.txt");
    std::vector<double> dmatrix;
    double delement;
    while (dou >> delement) //storing the file into a vector as double precision
    {
        dmatrix.push_back(delement);
        //std::cout << delement << "\t";
    }
    
    fulld_accum(dmatrix);
    fulld_fanin(dmatrix);
    tdigit_accum(dmatrix);
    tdigit_fanin(dmatrix);
}


//https://www.cplusplus.com/forum/beginner/264090/
//https://stackoverflow.com/questions/33389553/random-number-generator-between-1-and-1-in-c