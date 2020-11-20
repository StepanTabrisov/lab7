#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <queue>
#include <string.h>

int* DIST;
int* DIST1;
int** arr1;
int** arr2;
int** arr3;
int** arr4;

int** dynamic(int count) {

	int** mass;
	mass = (int**)malloc(count * sizeof(int*));
	for (int i = 0; i < count; i++) mass[i] = (int*)malloc(count * sizeof(int));
	return mass;

}

void generate_typeNV_Nroute(int** mass, int count) { //невзвешанный неориентированынй

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (j > i) {
				mass[i][j] = rand() % 2;
				mass[j][i] = mass[i][j];
			}
			else if (i == j) mass[i][j] = 0;
		}
	}
}

void generate_typeV_Nroute(int** mass, int count) { // взвешанный неориентированный

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (j > i) {
				mass[i][j] = rand() % 7 + 0;
				mass[j][i] = mass[i][j];
			}
			else if (i == j) mass[i][j] = 0;
		}
	}
}

void generate_typeNV_route(int** mass, int count) { //невзвешанный ориентированнынй
	int a;
	int b;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			a = rand() % 101;
			if (a < 70) {
				mass[j][i] = 1;
				mass[i][j] = 0;
			}
			else mass[j][i] = 0;
			 if (i == j) mass[j][i] = 0;

		}
	}
	
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			b = rand() % 101;
			if ((b < 50) && (mass[j][i]==1)) {
				mass[i][j] = 1;
				mass[j][i] = 0;
			}

			if (i == j) mass[i][j] = 0;

		}
	}
}

void generate_typeV_route(int** mass, int count) { //взвешанынный ориентированный
	
	int a;
	int b;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			a = rand() % 101;
			if (a < 70) {
				mass[j][i] = rand() % 6 + 1;
				mass[i][j] = 0;
			}
			else mass[j][i] = 0;
			if (i == j) mass[j][i] = 0;

		}
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			b = rand() % 101;
			if ((b < 50) && (mass[j][i] >= 1)) {
				mass[i][j] = mass[j][i];
				mass[j][i] = 0;
			}

			if (i == j) mass[i][j] = 0;

		}
	}
}

void print(int** mass, int count) {
	printf(" ");
	for (int k = 1; k <= count; k++) printf("%d ", k);
	printf("\n -----------\n");
	for (int i = 0; i < count; i++) {
		printf("%d |", i + 1);
		for (int j = 0; j < count; j++) {
			printf("%d ", mass[i][j]);
		}
		printf("\n");
	}
}

int* dynamic_dist(int count) {

	int* dist;
	dist = (int*)malloc(count * sizeof(int));
	return dist;

}

void generate_dist_v(int* DISTV, int count) {
	for (int i = 0; i < count; i++) {
		DISTV[i] = -1;
	}
}

void generate_dist_nv(int* DISTNV, int count) {
	for (int i = 0; i < count; i++) {
		DISTNV[i] = -1;
	}
}

void BFSD_V(int v, int a, int** arr) {
	std::queue <int> qu;
	qu.push(v);
	DIST[v] = 0;
	while (!qu.empty()) {
		v = qu.front();
		printf(" %d  ", v + 1);
		qu.pop();
		for (int i = 0; i < a; i++) {
			if ((arr[v][i] > 0) && (DIST[i] == -1)) {
				qu.push(i);
				DIST[i] = DIST[v] + arr[v][i];
			}
		}
	}
}

void BFSD_NV(int v, int a, int** arr) { 
	std::queue <int> qu1;
	qu1.push(v);
	DIST1[v] = 0;
	while (!qu1.empty()) {
		v = qu1.front();
		printf(" %d  ", v + 1);
		qu1.pop();
		for (int i = 0; i < a; i++) {
			if ((arr[v][i] == 1) && (DIST1[i] == -1)) {
				qu1.push(i);
				DIST1[i] = DIST1[v] + 1;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int begin;
	int n=0;
	int min = 1000;
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));


	if (argc < 2) {
		printf("Введите параметры в командной строке и попробуйте снова.\n");
		printf("Варианты параметров:\n");
		printf("Взвешанный граф - typev.\n");
		printf("Незвешанный граф - typenv.\n");
		printf("Ориентированный граф - route.\n");
		printf("Нериентированный граф - nroute.\n");
		return 1;
	}
	
		if ((argc >= 3) && (strcmp(argv[1], "typev")==0) && (strcmp(argv[2], "route")==0)) {
			if (argc > 4) {
				printf("Слишком много параметров(Больше 4). Попробуйте снова!\n");
				return 1;
			}
			if (argv[3] != NULL) {
				n = atoi(argv[3]);
			}
			else if (n == 0) {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			else {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			arr1 = dynamic(n);
			DIST = dynamic_dist(n);
			generate_dist_v(DIST, n);
			generate_typeV_route(arr1, n);
			printf("Матрица смежности взвешанного ориентированного графа:\n\n");
			print(arr1, n);
			printf("Введите вершину с которой хотите начать обход - ");
			scanf_s("%d", &begin);
			BFSD_V(begin - 1, n, arr1);
			printf("\n--------------------------------------------\n");
			printf("| Вершины    |");
			for (int i = 1; i <= n; i++) {
				printf("| %d |", i);
			}
			printf("\n--------------------------------------------\n");
			printf("| Расстояние |");
			for (int i = 0; i < n; i++) {
				printf("| %d |", DIST[i]);
			}
			printf("\n--------------------------------------------\n");
			free(arr1);
			free(DIST);
			system("pause");
			return 0;
		}
		if ((argc >= 3) && (strcmp(argv[1], "typev") == 0) && (strcmp(argv[2], "nroute") == 0)) {
			if (argc > 4) {
				printf("Слишком много параметров(Больше 4). Попробуйте снова!\n");
				return 1;
			}
			if (argv[3] != NULL) {
				n = atoi(argv[3]);
			}
			else if (n == 0) {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			else { 
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6; }
			arr2 = dynamic(n);
			generate_typeV_Nroute(arr2, n);
			DIST = dynamic_dist(n);
			generate_dist_v(DIST, n);
			printf("Матрица смежности взвешанного неориентированного графа:\n\n");
			print(arr2, n);
			printf("Введите вершину с которой хотите начать обход - ");
			scanf_s("%d", &begin);
			BFSD_V(begin - 1, n, arr2);
			printf("\n--------------------------------------------\n");
			printf("| Вершины    |");
			for (int i = 1; i <= n; i++) {
				printf("| %d |", i);
			}
			printf("\n--------------------------------------------\n");
			printf("| Расстояние |");
			for (int i = 0; i < n; i++) {
				printf("| %d |", DIST[i]);
			}
			printf("\n--------------------------------------------\n");
			free(arr2);
			free(DIST);
			system("pause");
			return 0;
		}
		if ((argc >= 3) && (strcmp(argv[1], "typenv") == 0) && (strcmp(argv[2], "route") == 0)) {
			if (argc > 4) {
				printf("Слишком много параметров(Больше 4).  Попробуйте снова!\n");
				return 1;
			}
			if (argv[3] != NULL) {
				n = atoi(argv[3]);
			}
			else if (n == 0) {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			else {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			arr3 = dynamic(n);
			generate_typeNV_route(arr3, n);
			DIST1 = dynamic_dist(n);
			generate_dist_nv(DIST1, n);
			printf("Матрица смежности невзвешанного ориентированного графа:\n\n");
			print(arr3, n);
			printf("Введите вершину с которой хотите начать обход - ");
			scanf_s("%d", &begin);
			BFSD_NV(begin - 1, n, arr3);
			printf("\n--------------------------------------------\n");
			printf("| Вершины    |");
			for (int i = 1; i <= n; i++) {
				printf("| %d |", i);
			}
			printf("\n--------------------------------------------\n");
			printf("| Расстояние |");
			for (int i = 0; i < n; i++) {
				printf("| %d |", DIST1[i]);
			}
			printf("\n--------------------------------------------\n");
			free(arr3);
			free(DIST1);
			system("pause");
			return 0;
		}
		if ((argc >= 3) && (strcmp(argv[1], "typenv")==0) && (strcmp(argv[2], "nroute")==0)) {
			if (argc > 4) {
				printf("Слишком много параметров(Больше 4).  Попробуйте снова!\n");
				return 1;
			}
			if (argv[3] != NULL) {
				n = atoi(argv[3]);
			}
			else if (n == 0) {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			else {
				printf("Число не обнаружено, количество вершин равно 6!\n");
				n = 6;
			}
			arr4 = dynamic(n);
			generate_typeNV_Nroute(arr4, n);
			DIST1 = dynamic_dist(n);
			generate_dist_nv(DIST1, n);
			printf("Матрица смежности невзвешанного неориентированного графа:\n\n");
			print(arr4, n);
			printf("Введите вершину с которой хотите начать обход - ");
			scanf_s("%d", &begin);
			BFSD_NV(begin - 1, n, arr4);
			printf("\n--------------------------------------------\n");
			printf("| Вершины    |");
			for (int i = 1; i <= n; i++) {
				printf("| %d |", i);
			}
			printf("\n--------------------------------------------\n");
			printf("| Расстояние |");
			for (int i = 0; i < n; i++) {
				printf("| %d |", DIST1[i]);
			}
			printf("\n--------------------------------------------\n");
			free(arr4);
			free(DIST1);
			system("pause");
			return 0;
		}
	system("pause");
	return 0;	
}
