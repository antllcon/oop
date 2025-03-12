#include <array>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

enum class AppMode
{
	CommandLine,
	Stdin,
	Help,
	Invalid
};

namespace constants
{
inline constexpr int MATRIX_SIZE = 3;
inline constexpr int OUTPUT_PRECISION = 3;
} // namespace constants

using Matrix = std::array<std::array<double, constants::MATRIX_SIZE>, constants::MATRIX_SIZE>;

AppMode DefineMode(size_t argc, char* argv[])
{
	if (argc == 2)
	{
		std::string arg = argv[1];
		if (arg == "-h" || arg == "--help")
		{
			return AppMode::Help;
		}
		return AppMode::CommandLine;
	}
	else if (argc == 1)
	{
		return AppMode::Stdin;
	}
	else
	{
		return AppMode::Invalid;
	}
}

void PrintHelp()
{
	std::cout << "Usage: invert [input_file]\n";
	std::cout << "       invert 	// read matrix from STDIN\n";
	std::cout << "       invert -h 	// display this help message\n";
}

void ValidateMatrixSize(const Matrix& matrix)
{
	if (matrix.size() != constants::MATRIX_SIZE || matrix[0].size() != constants::MATRIX_SIZE)
	{
		throw std::runtime_error("Matrix must be of size 3x3");
	}
}

void PrintMatrix3x3(const Matrix& matrix3x3)
{
	std::cout << std::fixed << std::setprecision(3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << matrix3x3[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

double GetMatrix3x3Determinant(const Matrix& matrix3x3)
{
	return matrix3x3[0][0] * (matrix3x3[1][1] * matrix3x3[2][2] - matrix3x3[1][2] * matrix3x3[2][1])
		- matrix3x3[0][1] * (matrix3x3[1][0] * matrix3x3[2][2] - matrix3x3[1][2] * matrix3x3[2][0])
		+ matrix3x3[0][2] * (matrix3x3[1][0] * matrix3x3[2][1] - matrix3x3[1][1] * matrix3x3[2][0]);
}

Matrix GetMinorsMatrix3x3(const Matrix& matrix3x3)
{
	Matrix minorMatrix3x3;

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			const int row1 = (i + 1) % 3;
			const int row2 = (i + 2) % 3;
			const int col1 = (j + 1) % 3;
			const int col2 = (j + 2) % 3;

			minorMatrix3x3[i][j] = matrix3x3[row1][col1] * matrix3x3[row2][col2]
				- matrix3x3[row1][col2] * matrix3x3[row2][col1];
		}
	}

	return minorMatrix3x3;
}

Matrix GetTransposedMatrix3x3(const Matrix& matrix3x3)
{
	Matrix transposedMatrix3x3;

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			transposedMatrix3x3[j][i] = matrix3x3[i][j];
		}
	}

	return transposedMatrix3x3;
}

Matrix MultiplyMatrix3x3ByNumber(const Matrix& matrix3x3, const double number)
{
	Matrix inverseMatrix3x3;

	const double inverseDeterminant = 1 / number;

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			inverseMatrix3x3[i][j] = inverseDeterminant * matrix3x3[i][j];
		}
	}
	return inverseMatrix3x3;
}

// Вынести рисование матрицы
void FindInverseMatrix3x3(const Matrix& matrix3x3)
{
	ValidateMatrixSize(matrix3x3);

	const double matrix3x3Determinant = GetMatrix3x3Determinant(matrix3x3);
	if (matrix3x3Determinant == 0)
	{
		throw std::runtime_error("Non-invertible");
	}
	const Matrix minorsMatrix3x3 = GetMinorsMatrix3x3(matrix3x3);
	const Matrix transposedMatrix3x3 = GetTransposedMatrix3x3(minorsMatrix3x3);
	const Matrix inverseMatrix3x3
		= MultiplyMatrix3x3ByNumber(transposedMatrix3x3, matrix3x3Determinant);
	PrintMatrix3x3(inverseMatrix3x3);
}

template <typename Stream> Matrix GetMatrix(Stream& stream)
{
	std::string line;
	Matrix matrix;

	for (size_t i = 0; i < constants::MATRIX_SIZE; ++i)
	{
		if (!std::getline(stream, line))
		{
			throw std::runtime_error("Invalid matrix format");
		}
		std::istringstream rowStream(line);
		for (size_t j = 0; j < constants::MATRIX_SIZE; ++j)
		{
			rowStream >> matrix[i][j];
			if (rowStream.fail())
			{
				throw std::runtime_error("Invalid matrix");
			}
		}
		char ch;
		if (rowStream >> ch)
		{
			throw std::runtime_error("Invalid matrix format");
		}
	}
	return matrix;
}

Matrix ReadMatrixFromStdin() { return GetMatrix(std::cin); }

Matrix ReadMatrixFromFile(const std::string& name)
{
	std::ifstream file(name);
	if (!file)
		throw std::runtime_error("Cannot open file [ " + name + " ]");

	return GetMatrix(file);
}

int main(const int argc, char* argv[])
{
	AppMode mode = DefineMode(argc, argv);
	Matrix matrix;

	try
	{
		switch (mode)
		{
		case AppMode::CommandLine:
			matrix = ReadMatrixFromFile(argv[1]);
			break;

		case AppMode::Stdin:
			matrix = ReadMatrixFromStdin();
			break;

		case AppMode::Help:
			PrintHelp();
			return EXIT_SUCCESS;

		default:
			throw std::runtime_error("invalid usage");
		}
		FindInverseMatrix3x3(matrix);
	}
	catch (const std::exception& errorMessage)
	{
		std::cout << "Error: " << errorMessage.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}