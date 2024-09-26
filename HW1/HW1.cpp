#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

double V(double x)
{
	return (M_PI - x) / 2;
}

double V_N(double x, int N)
{
	double sum = 0;
	for (int i = 1; i <= N; i++)
	{
		sum += sin(i * x) / i;
	}
	return sum;
}

double V_N_tilde(double x, int N)
{
	double sum = 0;
	for (int i = 1; i <= N; i++)
	{
		sum += sin(i * x) / i * sin(i * M_PI / N) / (i * M_PI / N);
	}
	return sum;
}

int main()
{
	int m_num[] = {20, 160};
	int N_num[] = {10, 100};
	double (*Numericals[])(double, int) = {V_N, V_N_tilde};
	int file_index = 0;
	for (auto numerical : Numericals)
	{
		for (auto m : m_num)
		{
			double dx = 2 * M_PI / m;
			string file_name = "data/output_" + to_string(file_index++) + ".txt";
			ofstream outputFile(file_name);
			if (outputFile.is_open())
			{
				for (int j = 1; j <= m; j++)
				{
					double x = dx * j;
					outputFile << x << '\t' << V(x);
					for (auto N : N_num)
					{
						outputFile << '\t' << numerical(x, N);
					}
					outputFile << '\n';
				}
				outputFile.close();
				cout << "文件" + file_name + "写入成功。" << endl;
			}
			else
			{
				cout << "无法打开文件。" << endl;
			}
		}
	}
}
