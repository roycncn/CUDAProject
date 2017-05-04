// CUDA1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<iomanip>
#include <stdlib.h>
using namespace std;
#define e     0.00000001
#define maxn 50

int    n = 4;//��ģnXn
double a[4][4] = { 4,6,2,-2,2,0,5,-2 ,-4,-3,-5,4,8,18,-2,3 };
double b[4] = { 8,4,1,40 };
double m[maxn][maxn];//�м��������
double y[maxn];
double x[maxn];//���ս�
int    H = 1;//����H�����㣨�Ż���

void PrintProc(int cases);
/*
��ȡ����
*/
void read() {
	cout << "������ϵ�������ģn:= ";
	cin >> n;
	cout << "|������ϵ������\n";
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) {
			cin >> a[i][j];
			a[i][j] *= H;
		}
	cout << "|-----------------------------\n";
	cout << "|������b�����磺\n";
	cout << "|9.5342 6.3941 18.4231 16.9237\n";
	cout << "|-----------------------------\n";
	for (int i = 0; i<n; i++) {
		cin >> b[i];
		b[i] *= H;
	}

	PrintProc(0);
}


/*
�м�������
��������Ԫ����
*/
void PrintProc(int cases) {
	printf("--------��%d����Ԫ������£�\n", cases);
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			cout << setw(10) << a[i][j] << ' ';
		}
		cout << setw(10) << y[i] << '\n';
	}
	cout << "-------------\n";
}

/*
��ʾ���
*/
void Print() {
	cout << "|-----------------------------\n";
	cout << "|���Ϊ��\n";
	for (int i = 0; i<n; i++) {
		printf("x[%d]=  %lf\n", i, x[i]);
	}
	cout << "|-----------------------------\n\n";
}

/*
˳����Ԫ��
*/
void ShunXuXiaoYuan() {
	//��Ԫ����

	for (int k = 0; k<n; k++) {
		for (int j = k + 1; j<n; j++) {
			a[k][j] = a[k][j] / a[k][k];
		}
		y[k] = b[k] / a[k][k];
		a[k][k] = 1;

		for (int i = k + 1; i<n; i++) {
			for (int jj = k + 1; jj<n; jj++) {
				a[i][jj] = a[i][jj] - a[i][k] * a[k][jj];
			}
			b[i] = b[i] - a[i][k] * y[k];
			a[i][k] = 0;
		}

		PrintProc(k);//����м�������
	}

	for (int k = n - 1; k >= 0; k--) {
		x[k] = y[k];
		for (int i = k - 1; i >= 0; i--) {
			y[i] = y[i] - x[k] * a[i][k];
		}
	}

	Print();


}

/*
������Ԫ
*/
void LieZhuXiaoYuan() {
	for (int k = 1; k<n; k++) {
		//ѡ��Ԫ[��һ�еľ���ֵ���ֵ]
		double ab_max = -1;
		int       max_ik;
		for (int i = k; i <= n; i++) {
			if (abs(a[i][k])>ab_max) {
				ab_max = abs(a[i][k]);
				max_ik = i;
			}
		}
		//�����д���[���ж��Ƿ�Ϊ0����]
		if (ab_max<e) {//0�������
			cout << "det A=0\n";
			break;
		}
		else if (max_ik != k) {//�Ƿ��ǵ�ǰ�У����ǽ���
			double temp;
			for (int j = 1; j <= n; j++) {
				temp = a[max_ik][j];
				a[max_ik][j] = a[k][j];
				a[k][j] = temp;
			}
			temp = b[max_ik];
			b[max_ik] = b[k];
			b[k] = temp;
		}
		//��Ԫ����
		for (int i = k + 1; i <= n; i++) {
			a[i][k] /= a[k][k];
			for (int j = k + 1; j <= n; j++) {
				a[i][j] -= a[i][k] * a[k][j];
			}
			b[i] -= a[i][k] * b[k];
		}
		PrintProc(k);//����м�������
		if (k<n - 1)continue;
		else {
			if (abs(a[n][n])<e) {
				cout << "det A=0\n";
				break;
			}
			else {//�ش����
				x[n] = b[n] / a[n][n];
				for (int i = n - 1; i>0; i--) {
					x[i] = b[i];
					for (int j = i + 1; j <= n; j++)
						x[i] -= a[i][j] * x[j];
					x[i] /= a[i][i];
				}
				//������
				Print();
			}
		}
	}
}

/*
������
*/
int main() {
	PrintProc(0);
	//LieZhuXiaoYuan();
	ShunXuXiaoYuan();
	return 0;
}
/*
���ϸ�˹��Ԫ�����ӣ�
1 1 1
1 3 -2
2 -2 1

6 1 1
*/
/*
����������Ԫ�����ӣ�
-0.002 2 2
1 0.78125 0
3.996 5.5625 4

0.4 1.3816 7.4178
*/