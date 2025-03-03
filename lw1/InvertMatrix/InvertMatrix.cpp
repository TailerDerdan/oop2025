#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>
#include <iomanip>
#include <sstream>
#include <limits>

namespace 
{
	const int COUNT_LINE = 3;
	const int COUNT_COL = 3;

	using Matrix3x3 = std::array<std::array<double, COUNT_COL>, COUNT_LINE>;
	using Matrix2x2 = std::array<std::array<double, COUNT_COL - 1>, COUNT_COL - 1>;

	const char SPACE = ' ';
	const char TAB = '\t';

	struct Args
	{
		std::string matrixInputFile;
		bool isFile = false;
	};

	std::optional<Matrix3x3> ReadMatrix(std::istream& input)
	{
		Matrix3x3 matrix{ 0 };
		
		int line = 0;
		std::string lineStr;

		while (std::getline(input, lineStr))
		{
			std::istringstream lineStream(lineStr);
			int col = 0;
			double num = 0.0;

			while (lineStream >> num)
			{
				if (col < COUNT_COL && line < COUNT_LINE)
				{
					matrix[line][col] = num;
				}
				col++;
			}

			if (lineStream.fail() && !lineStream.eof())
			{
				std::cout << "Invalid matrix" << std::endl;
				return std::nullopt;
			}

			if (col != COUNT_COL)
			{
				std::cout << "Invalid matrix format" << std::endl;
				return std::nullopt;
			}

			line++;
		}
		if (line != COUNT_LINE)
		{
			std::cout << "Invalid matrix format" << std::endl;
			return std::nullopt;
		}
		return matrix;
	}

	std::optional<Matrix3x3> ReadMatrixFromFile(const std::string& fileName)
	{
		std::ifstream matrixInputFile;
		matrixInputFile.open(fileName);
		if (!matrixInputFile.is_open())
		{
			std::cout << "Failed to open '" << fileName << "' for reading" << std::endl;
			return std::nullopt;
		}

		return ReadMatrix(matrixInputFile);
	}

	double GetDeterminant(const Matrix2x2& matrix)
	{
		return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
	}

	double GetDeterminant(const Matrix3x3& matrix)
	{
		return (matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[1][0] * matrix[0][2] * matrix[2][1] +
			matrix[0][1] * matrix[2][0] * matrix[1][2] -

			matrix[0][2] * matrix[1][1] * matrix[2][0] -
			matrix[0][0] * matrix[1][2] * matrix[2][1] -
			matrix[2][2] * matrix[0][1] * matrix[1][0]);
	}

	// избавиться от структуры coord на col и line
	double GetMinor(int line, int col, const Matrix3x3& matrix3x3)
	{
		Matrix2x2 matrix2x2{ 0 };

		int line2x2 = 0;
		int col2x2 = 0;
		for (int line = 0; line < COUNT_LINE; line++)
		{
			col2x2 = 0;
			for (int col = 0; col < COUNT_COL; col++)
			{
				if (col == col) continue;
				if (line == line) continue;

				matrix2x2[line2x2][col2x2] = matrix3x3[line][col];
				col2x2++;
			}
			if (col2x2 == COUNT_COL - 1)
			{
				line2x2++;
			}
		}

		return GetDeterminant(matrix2x2);
	}

	void TurnToNegativeMinor(int line, int col, double& minor)
	{
		if ((line + col) % 2 != 0 && minor != 0)
		{
			minor *= -1;
		}
	}

	void DivideOnDet(double& minor, double det)
	{
		minor /= det;
	}

	void TransposeMinor(Matrix3x3& result, int line, int col, double minor)
	{
		result[col][line] = minor;
	}

	//использовать exception вместо optional
	//разбить invert на несколько функций
	std::optional<Matrix3x3> Invert(const Matrix3x3& matrix)
	{
		Matrix3x3 result{ 0 };

		double det = GetDeterminant(matrix);

		// сравнивать не с 0, а с эпселент
		if (det == std::numeric_limits<double>::epsilon())
		{
			std::cout << "Non-invertible" << std::endl;
			return std::nullopt;
		}

		for (int line = 0; line < COUNT_LINE; line++)
		{
			for (int col = 0; col < COUNT_COL; col++)
			{
				double minor = GetMinor(line, col, matrix);
				TurnToNegativeMinor(line, col, minor);
				DivideOnDet(minor, det);
				TransposeMinor(result, line, col, minor);
			}
		}

		return result;
	}
	//переименовать на PrintMatrix
	void PrintMatrix(const Matrix3x3& matrix)
	{
		std::cout << std::setprecision(3) << std::fixed;
		for (int line = 0; line < COUNT_LINE; line++)
		{
			for (int col = 0; col < COUNT_COL; col++)
			{
				std::cout << matrix[line][col];
				if (col != COUNT_COL - 1)
				{
					std::cout << TAB;
				}
			}
			if (line != COUNT_LINE - 1)
			{
				std::cout << std::endl;
			}
		}
	}

	std::optional<Args> ParseArgs(int argc, char* argv[])
	{
		Args args;
		if (argc == 1)
		{
			args.isFile = false;
			return args;
		}
		if (argc != 2)
		{
			std::cout << "Invalid argument count" << std::endl;
			std::cout << "Usage: invertmatrix.exe <matrix>" << std::endl;
			return std::nullopt;
		}
		args.matrixInputFile = argv[1];
		args.isFile = true;
		return args;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	std::optional<Matrix3x3> matrixInput;
	if (!args.value().isFile)
	{
		matrixInput = ReadMatrix(std::cin);
	}
	else
	{
		matrixInput = ReadMatrixFromFile(args.value().matrixInputFile);
	}

	if (!matrixInput)
	{
		return EXIT_FAILURE;
	}

	auto invertMatrix = Invert(matrixInput.value());

	if (!invertMatrix)
	{
		return EXIT_FAILURE;
	}

	PrintMatrix(invertMatrix.value());

	return EXIT_SUCCESS;
}