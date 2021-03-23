#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "spline.h"

void gen();

int main(){

	//gen();
	//файл точек и зн функций в них
	FILE* p_f = fopen("points.txt", "r");
	//файл узлов
	FILE* n_f_x = fopen("nodes_x.txt", "r");
	//полученный сплайн
	FILE *res = fopen("vals.txt", "w");

	int n, m;
	double **points, *xnodes, *ynodes;
	//количество точек для исходной функции
	fscanf(p_f, "%d", &n);
	//количество узлов сетки
	fscanf(n_f_x, "%d", &m);
	//точки и функции
	points = new double* [n];
	//узлы
	xnodes = new double [m];
	ynodes = new double[m];

	//считали точки и функции
	for(int i = 0; i < n; i++)
	{
		points[i] = new double [2];
		fscanf(p_f,"%lf %lf",&points[i][0], &points[i][1]);
	}
	//считали узлы
	for(int i = 0; i < m; i++)
	{
		fscanf(n_f_x, "%lf", &xnodes[i]);
		ynodes[i] = xnodes[i];

	}
		

	spline our_S;
	//создаем матрицу и вектор правой части
	bool can_we = our_S.make_with_reg(n, m, points, xnodes, ynodes);
	
	if(can_we){
		for(double x = -2.1; x < 2.1; x += 0.1)
			fprintf(res, "%.15lf\t%.15lf\n", x, our_S(x));
	}
	else
		fprintf(res, "We can't create spline");

	fclose(p_f);
	fclose(n_f_x);
	fclose(res);

}

void gen(){

	FILE* gen_p = fopen("points.txt","w");
	FILE* gen_n = fopen("nodes.txt","w");

	int n = 200;
	int m = 11;

	double s_p = -1;
	double s_n = -1;

	double h_p = 0.01;
	double h_n = 0.2;

	fprintf(gen_p,"%d\n",n);
	fprintf(gen_n,"%d\n",m);

	double x;

	for(int i = 0; i < n; i++){
		x = s_p + i*h_p;
		fprintf(gen_p, "%.15lf\t%.15lf\n", x, sin(20*x));
	}

	for(int i = 0; i < m; i++){
		x = s_n + i*h_n;
		fprintf(gen_n, "%.15lf\n", x);
	}

	fclose(gen_p);
	fclose(gen_n);

}