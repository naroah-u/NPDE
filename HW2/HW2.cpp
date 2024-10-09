#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// ANSI
void FTFS(int J, int N, double dx, double dt, vector<vector<double>> &v)
// FTFS格式，对应原问题中的离散方程A
{
	for (int n = 0; n < N; n++)
	{
		// 循环边界处理
		v[J][n+1] = v[0][n+1];
		for (int j = 0; j < J; j++)
		{
			v[j][n+1] = v[j][n] + dt/dx*(v[j+1][n]-v[j][n]);
		}
	}
}

void FTCS(int J, int N, double dx, double dt, vector<vector<double>> &v)
// FTCS格式，对应原问题中的离散方程B
{
	for (int n = 0; n < N; n++)
	{
		// 循环边界处理
		v[0][n+1] = v[0][n] + dt/2/dx*(v[1][n]-v[J-1][n]);
		v[J][n+1] = v[0][n+1];
		for (int j = 1; j < J; j++)
		{
			v[j][n+1] = v[j][n] + dt/2/dx*(v[j+1][n]-v[j-1][n]);
		}
	}
}

int main()
{
	int file_index = 1;
	// 设置网格精度
	double X = 1, T = 1, t = 0.3;
	double dx = 0.02, dt_s[2] = {0.01, 0.03};
	void (*Func[])(int, int, double, double, vector<vector<double>>&) = {FTFS, FTCS};

	for (auto dt : dt_s)
	{
		// 打开准备写入数据的文件
		string file_name = "data/问题" + to_string(file_index++) + ".txt";
		ofstream outputFile(file_name);
		if (outputFile.is_open())
		{
			int J = X/dx, N = T/dt;
			for (int j = 0; j <= J; j++)
			{
				double x = j*dx;
				outputFile << x << '\t';
			}
			outputFile << '\n';
			// 计算差分结果并输出在t=0.3的结果
			for (auto func : Func)
			{
				vector<vector<double>> v(J+1, vector<double>(N+1));
				// 设置初始条件
				for (int j = 0; j <= J; j++)
				{
					double x = j*dx;
					v[j][0] = sin(2*M_PI*x);
				}
				func(J, N, dx, dt, v);
				for (int j = 0; j <= J; j++)
				{
					double x = j*dx;
					outputFile << v[j][t/dt + 1] << '\t';
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

