#include <iostream>
#include <optional>
#include <string>
#include <fstream>
#include <array>
#include <iomanip>
#include <sstream>

namespace 
{
	const int COUNT_LINE = 3;
	const int COUNT_COL = 3;

	using Mat3x3 = std::array<std::array<double, COUNT_COL>, COUNT_LINE>;
	using Mat2x2 = std::array<std::array<double, COUNT_COL - 1>, COUNT_COL - 1>;

	const char SPACE = ' ';

	struct Args
	{
		std::string matrixInputFile;
		bool isFile = false;
	};

	struct Coord
	{
		int line = 0;
		int col = 0;
	};

	std::optional<Mat3x3> ReadMatrix(std::istream& input)
	{
		Mat3x3 matrix{ 0 };
		
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

	std::optional<Mat3x3> ReadMatrixFromFile(const std::string& fileName)
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

	double GetDeterminant(const Mat2x2& matrix)
	{
		return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
	}

	double GetDeterminant(const Mat3x3& matrix)
	{
		return (matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[1][0] * matrix[0][2] * matrix[2][1] +
			matrix[0][1] * matrix[2][0] * matrix[1][2] -

			matrix[0][2] * matrix[1][1] * matrix[2][0] -
			matrix[0][0] * matrix[1][2] * matrix[2][1] -
			matrix[2][2] * matrix[0][1] * matrix[1][0]);
	}

	double GetMinor(const Coord& coord, const Mat3x3& matrix3x3)
	{
		Mat2x2 matrix2x2{ 0 };

		int line2x2 = 0;
		int col2x2 = 0;
		for (int line = 0; line < COUNT_LINE; line++)
		{
			col2x2 = 0;
			for (int col = 0; col < COUNT_COL; col++)
			{
				if (col == coord.col) continue;
				if (line == coord.line) continue;

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

	std::optional<Mat3x3> Invert(const Mat3x3& matrix)
	{
		Mat3x3 result{ 0 };

		double det = GetDeterminant(matrix);

		if (det == 0.0)
		{
			std::cout << "Non-invertible" << std::endl;
			return std::nullopt;
		}

		for (int line = 0; line < COUNT_LINE; line++)
		{
			for (int col = 0; col < COUNT_COL; col++)
			{
				Coord coord = { line, col };
				double minor = GetMinor(coord, matrix);
				if ((line + col) % 2 != 0 && minor != 0)
				{
					minor *= -1;
				}
				minor /= det;
				result[col][line] = minor;
			}
		}

		return result;
	}

	void MatrixOutput(const Mat3x3& m1)
	{
		std::cout << std::setprecision(3) << std::fixed;
		for (int i = 0; i < COUNT_LINE; ++i)
		{
			for (int j = 0; j < COUNT_COL; ++j)
			{
				std::cout << m1[i][j];
				if (j != COUNT_COL - 1)
				{
					std::cout << '\t';
				}
			}
			if (i != COUNT_LINE - 1)
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

	std::optional<Mat3x3> matrixInput;
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

	MatrixOutput(invertMatrix.value());

	return EXIT_SUCCESS;
}