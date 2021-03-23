#include "spline.h"

spline::spline(){
}

double spline::ermit(int num, double x, double h){
	switch(num){
		case 0:{
			return 1 - 3*x*x + 2*x*x*x;
		}break;

		case 1:{
			return h * (x - 2*x*x + x*x*x);
		}break;

		case 2:{
			return 3*x*x-2*x*x*x;
	    }break;

		case 3:{
			return h*(-x*x + x*x*x);
		}break;
	}
}



double spline::operator ()(double x){
	int element = 0, el1;
	bool find = false;

	if (x < nodes_x[0] || x > nodes_x[m-1]) return 0;

	for(int i = 1; i < m && !find; i++){
		if(x < nodes_x[i]){
			element = i;
			find = true;
		}
	}

	double val = 0;
	el1 = element - 1;
	double h = nodes_x[element] - nodes_x[el1];
	double t = (x - nodes_x[el1])/h;

	for(int i = 0; i < 4; i++){
		val += coef[2*el1 + i] * ermit(i, t, h);
	}

	return val;
}


bool spline::make_with_reg(int n_s, int m_s, double **points, double *nodes_s_x, double* nodes_s_y)
{

	n = n_s;
	m = m_s;
	//������ ������� �
	int m_add = 2*m;

	nodes_x = new double [m];
	nodes_y = new double[m];
	//��������� ���� x
	for (int i = 0; i < m; i++)
	{
		nodes_x[i] = nodes_s_x[i];
	}
	//��������� ���� y
	for (int i = 0; i < m; i++) 
	{
		nodes_y[i] = nodes_s_y[i];
	}

	coef = new double [m_add];
	double **A = new double* [m_add];
	//������� ������� � � ��������� ������
	for (int i = 0; i < m_add; i++)
	{
		A[i] = new double [m_add];
		for(int j = 0; j < m_add; j++)
			A[i][j] = 0;
	}

	double *b = new double [m_add];
	//������ ������ ����� ��������� ������
	for(int i = 0; i < m_add; i++)
		b[i] = 0;
	//���
	double h_x,h_y;
	int point_p = 0;
	double psi;

	for(int k = 0; k < m-1; k++){
		//��� �������� ����,����� � ������
		double st_node_x = nodes_x[k], fin_node_x = nodes_x[k+1];
		double st_node_y = nodes_y[k], fin_node_y = nodes_y[k + 1];
		//����� ���
		h_x = fin_node_x - st_node_x;
		h_y = fin_node_y - st_node_y;
		//���� ����� ������� ������ � ��
		if(point_p < n && points[point_p][0] >= st_node_x){
			//���� �� ����� �� ������� ���� ��
			while(point_p < n && points[point_p][0] < fin_node_x){
				//���(�	)
				double ksi = (points[point_p][0] - st_node_x)/h_x;
				//4 �������� ������� �� ��
				for(int i = 0; i < 4; i++)
				{
					//�����(���)
					psi = ermit(i, ksi, h_x);
					for(int j = 0; j < 4; j++)
						//��������� �
						A[2*k+i][2*k+j] += psi*ermit(j,ksi,h_x);
					//��������� b
					b[2*k+i] += psi*points[point_p][1];
				}
				point_p++;
			}
		}

	}


	bool success = SLAE_solution_Gauss(A, b, coef, m_add);

	return success;
}

		