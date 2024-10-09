#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// ANSI
void FTFS(int J, int N, double dx, double dt, vector<vector<double>> &v)
// FTFS��ʽ����Ӧԭ�����е���ɢ����A
{
	for (int n = 0; n < N; n++)
	{
		// ѭ���߽紦��
		v[J][n+1] = v[0][n+1];
		for (int j = 0; j < J; j++)
		{
			v[j][n+1] = v[j][n] + dt/dx*(v[j+1][n]-v[j][n]);
		}
	}
}

void FTCS(int J, int N, double dx, double dt, vector<vector<double>> &v)
// FTCS��ʽ����Ӧԭ�����е���ɢ����B
{
	for (int n = 0; n < N; n++)
	{
		// ѭ���߽紦��
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
	// �������񾫶�
	double X = 1, T = 1, t = 0.3;
	double dx = 0.02, dt_s[2] = {0.01, 0.03};
	void (*Func[])(int, int, double, double, vector<vector<double>>&) = {FTFS, FTCS};

	for (auto dt : dt_s)
	{
		// ��׼��д�����ݵ��ļ�
		string file_name = "data/����" + to_string(file_index++) + ".txt";
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
			// �����ֽ���������t=0.3�Ľ��
			for (auto func : Func)
			{
				vector<vector<double>> v(J+1, vector<double>(N+1));
				// ���ó�ʼ����
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
			cout << "�ļ�" + file_name + "д��ɹ���" << endl;
		}
		else
		{
			cout << "�޷����ļ���" << endl;
		}
	}
}

