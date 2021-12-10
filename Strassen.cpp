

#include <iostream>
#include <sstream>
#include <vector>


#include <random>
#include <chrono>

#include<string>



/* Square Matrix */
class Matrix
{
public:
	int n;
	std::vector<std::vector<int>> matrix;
public:
	Matrix(int n) {
		this->n = n;

		std::vector<int> inner(this->n);
		std::vector<std::vector<int>> a(this->n, inner);
		this->matrix = a;

	}

	Matrix(int n, bool random) {
		this->n = n;
		this->matrix = {};
		
		if (random) {
			std::random_device rd;     // only used once to initialise (seed) engine
			std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
			std::uniform_int_distribution<int> uni(0, 10); // guaranteed unbiased

			for (int i = 0; i < this->n; i++) {
				std::vector<int> row = {};
				for (int j = 0; j < this->n; j++) {
					int random_integer = uni(rng);
					row.push_back(random_integer);
				}
				this->matrix.push_back(row);
			}
		}
		
	}

	Matrix(int n, std::vector<std::vector<int>> &matrix) {
		this->n = matrix.size();
		this->matrix = matrix;
	}
	
	void printMatrix() {
		std::cout << "n: " << this->n << std::endl;
		for (unsigned int i = 0; i < this->matrix.size(); i++){
			for (unsigned int j = 0; j < this->matrix[i].size(); j++) {
				//std::cout << "i, j: " << i << "," << j << std::endl;
				std::cout << this->matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	Matrix operator+(const Matrix& m) {

		Matrix newMatrix = Matrix(this->n);

		for (int i = 0; i < this->n; i++) {
			//std::vector<int> row = {};
			for (int j = 0; j < this->n; j++) {
				//row.push_back(this->matrix[i][j] + m.matrix[i][j]);
				newMatrix.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
			}
			//newMatrix.matrix.push_back(row);
		}

		return newMatrix;
	}

	Matrix operator-(const Matrix& m) {

		Matrix newMatrix = Matrix(this->n);

		for (int i = 0; i < this->n; i++) {
			//std::vector<int> row = {};
			for (int j = 0; j < this->n; j++) {
				//row.push_back(this->matrix[i][j] - m.matrix[i][j]);
				newMatrix.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];

			}
			//newMatrix.matrix.push_back(row);
		}

		return newMatrix;
	}

	Matrix operator*(const Matrix& m) {
		Matrix newMatrix = Matrix(this->n);

		for (int i = 0; i < this->n; i++) {
			//std::vector<int> row = {};
			for (int j = 0; j < this->n; j++) {
				int sum = 0;
				for (int k = 0; k < this->n; k++) {
					sum += this->matrix[i][k] * m.matrix[k][j];
				}
				//row.push_back(sum);
				newMatrix.matrix[i][j] = sum;
			}
			//newMatrix.matrix.push_back(row);
		}

		return newMatrix;
	}

};


void strassen(Matrix& first, Matrix& second, Matrix& result, int tam) {
	/*
	if (first.matrix.size() == 1) {
		result = first * second;
		return;
	}
	*/
	if (first.matrix.size() <= 128) {
		result = first * second;
		return;
	}

	// Split
	int n_half = tam / 2;

	Matrix A = Matrix(n_half);
	Matrix B = Matrix(n_half);
	Matrix C = Matrix(n_half);
	Matrix D = Matrix(n_half);

	Matrix E = Matrix(n_half);
	Matrix F = Matrix(n_half);
	Matrix G = Matrix(n_half);
	Matrix H = Matrix(n_half);

	for (int i = 0; i < n_half; i++) {
		for (int j = 0; j < n_half; j++) {
			A.matrix[i][j] = first.matrix[i][j];
			B.matrix[i][j] = first.matrix[i][j + n_half];
			C.matrix[i][j] = first.matrix[i + n_half][j];
			D.matrix[i][j] = first.matrix[i + n_half][j + n_half];

			E.matrix[i][j] = second.matrix[i][j];
			F.matrix[i][j] = second.matrix[i][j + n_half];
			G.matrix[i][j] = second.matrix[i + n_half][j];
			H.matrix[i][j] = second.matrix[i + n_half][j + n_half];
		}
	}

	// Submatrices
	Matrix aResult = Matrix(n_half);
	Matrix bResult = Matrix(n_half);
	Matrix p1 = Matrix(n_half);
	Matrix p2 = Matrix(n_half);
	Matrix p3 = Matrix(n_half);
	Matrix p4 = Matrix(n_half);
	Matrix p5 = Matrix(n_half);
	Matrix p6 = Matrix(n_half);
	Matrix p7 = Matrix(n_half);

	bResult = F - H;
	strassen(A, bResult, p1, n_half);

	aResult = A + B;
	strassen(aResult, H, p2, n_half);

	aResult = C + D;
	strassen(aResult, E, p3, n_half);

	bResult = G - E;
	strassen(D, bResult, p4, n_half);

	aResult = A + D;
	bResult = E + H;
	strassen(aResult, bResult, p5, n_half);

	aResult = B - D;
	bResult = G + H;
	strassen(aResult, bResult, p6, n_half);

	aResult = A - C;
	bResult = E + F;
	strassen(aResult, bResult, p7, n_half);

	Matrix c11 = p5 + p4 - p2 + p6;
	Matrix c21 = p3 + p4;
	Matrix c12 = p1 + p2;
	Matrix c22 = p1 + p5 - p3 - p7;

	//Matrix result = Matrix(2 * n_half);
	for (int i = 0; i < n_half; i++) {
		for (int j = 0; j < n_half; j++) {
			result.matrix[i][j] = c11.matrix[i][j];
			result.matrix[i][j + n_half] = c12.matrix[i][j];
			result.matrix[i + n_half][j] = c21.matrix[i][j];
			result.matrix[i + n_half][j + n_half] = c22.matrix[i][j];
		}
	}
}


void split(std::string str, char sep, std::vector<std::string> &sVec) {
	std::string word = "";

	for (char x : str) {
		if (x == sep) {
			sVec.push_back(word);
			word = "";
		}
		else {
			word = word + x;
		}
	}
	sVec.push_back(word);

	return;
}

int main()
{
	clock_t begin_time;
	auto t_start = std::chrono::high_resolution_clock::now();
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms;

	int n;
	
	std::cout << "N: ";
	std::cin >> n;
	std::cin.ignore();

	Matrix a = Matrix(n);
	Matrix b = Matrix(n);

	for (int i = 0; i < n; i++) {

		std::string line;		
		std::getline(std::cin, line);
		std::vector<std::string> outputArray;
		
		split(line, ' ', outputArray);

		int j = 0;
		for (auto& val : outputArray) {
			a.matrix[i][j] = std::stoi(val);
			j++;
		}
	}

	for (int i = 0; i < n; i++) {

		std::string line;
		std::getline(std::cin, line);
		std::vector<std::string> outputArray;

		split(line, ' ', outputArray);

		int j = 0;
		for (auto& val : outputArray) {
			b.matrix[i][j] = std::stoi(val);
			j++;
		}
	}

	
	std::cout << "Matriz a:" << std::endl;
	a.printMatrix();

	std::cout << "Matriz b:" << std::endl;
	b.printMatrix();
	
	
	// Naive Multiplication
	begin_time = clock();
	t_start = std::chrono::high_resolution_clock::now();

	Matrix d = a * b;

	std::cout << "Multiplicacion normal: " << std::endl;
	d.printMatrix();

	std::cout << "CPU time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
	t_end = std::chrono::high_resolution_clock::now();
	elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "actual time: " << elapsed_time_ms << "ms\n\n\n\n";


	// Strassen
	begin_time = clock();
	t_start = std::chrono::high_resolution_clock::now();

	Matrix e = Matrix(n);

	strassen(a, b, e, n);

	std::cout << "Strassen: " << std::endl;
	e.printMatrix();

	std::cout << "CPU time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
	t_end = std::chrono::high_resolution_clock::now();
	elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cout << "actual time: " << elapsed_time_ms << "ms\n\n\n\n";
	
}
