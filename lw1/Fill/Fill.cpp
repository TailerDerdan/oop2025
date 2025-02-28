#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>

struct Args
{
	std::string inputFile;
	std::string outputFile;
};

namespace
{
	const char START_POINT = 'O';
	const char EMPTY_CELL = ' ';
	const char FILLED_CELL = '.';
	const char SPECIAL_CELL = '\0';

	const int MAX_WIDTH = 100;
	const int MIN_WIDTH = 0;

	using FieldArray = std::array<std::array<char, MAX_WIDTH>, MAX_WIDTH>;

	struct Coord
	{
		int x = 0;
		int y = 0;
	};

	struct StructField
	{
		std::ifstream inputFile;
		std::ofstream outputFile;
		std::vector<Coord> coordsStart;
		FieldArray field = { ' ' };
		int xMax = 0;
		int yMax = 0;
	};

	bool ReadField(const std::string& inputPath, std::ifstream& inputFile)
	{
		inputFile.open(inputPath);
		if (!inputFile.is_open())
		{
			std::cout << "Failed to open '" << inputPath << "' for reading\n";
			return false;
		}
		return true;
	}

	bool ReadField(StructField& field, const std::string& inputPath)
	{
		if (!ReadField(inputPath, field.inputFile))
		{
			return false;
		}

		char ch;
		Coord coord;

		while (field.inputFile.get(ch))
		{
			if (ch == '\n')
			{
				coord.y++;
				field.xMax = std::max(field.xMax, coord.x - 1);
				coord.x = 0;
			}
			else if (coord.x < MAX_WIDTH)
			{
				if (ch == START_POINT)
				{
					field.coordsStart.push_back(coord);
				}
				field.field[coord.y][coord.x] = ch;
				coord.x++;
			}
		}
		field.yMax = coord.y;
		return true;
	}

	void FillCell(StructField& field, Coord& coord, std::vector<Coord>& result)
	{
		if (coord.x < MIN_WIDTH || coord.y < MIN_WIDTH) return;
		if (coord.x > MAX_WIDTH - 1 || coord.y > MAX_WIDTH - 1) return;

		if (field.field[coord.y][coord.x] == EMPTY_CELL || field.field[coord.y][coord.x] == SPECIAL_CELL)
		{
			result.push_back(coord);
			field.field[coord.y][coord.x] = FILLED_CELL;
			field.yMax = std::max(coord.y, field.yMax);
			field.xMax = std::max(coord.x, field.xMax);
		}
	}

	std::vector<Coord> GetCoordFilledCell(StructField& field, std::vector<Coord>& coordStartCell)
	{
		std::vector<Coord> result;
		while (!coordStartCell.empty())
		{
			Coord currentCell;
			currentCell = coordStartCell.at(coordStartCell.size() - 1);
			coordStartCell.pop_back();

			if (currentCell.x == 18 && currentCell.y == 2)
			{
				std::cout << " " << std::endl;
			}

			if ((currentCell.x <= MAX_WIDTH) && (currentCell.x >= MIN_WIDTH) &&
				(currentCell.y <= MAX_WIDTH) && (currentCell.y >= MIN_WIDTH))
			{
				Coord topCoord;
				topCoord.x = currentCell.x;
				topCoord.y = currentCell.y - 1;

				FillCell(field, topCoord, result);

				Coord bottomCoord;
				bottomCoord.x = currentCell.x;
				bottomCoord.y = currentCell.y + 1;

				FillCell(field, bottomCoord, result);
			}
			if ((currentCell.x <= MAX_WIDTH) && (currentCell.x >= MIN_WIDTH) &&
				(currentCell.y <= MAX_WIDTH) && (currentCell.y >= MIN_WIDTH))
			{
				Coord leftCoord;
				leftCoord.x = currentCell.x - 1;
				leftCoord.y = currentCell.y;

				FillCell(field, leftCoord, result);

				Coord rightCoord;
				rightCoord.x = currentCell.x + 1;
				rightCoord.y = currentCell.y;

				FillCell(field, rightCoord, result);
			}
		}
		return result;
	}

	void Fill(StructField& field)
	{
		std::vector<Coord> nextGenerationCell;

		nextGenerationCell = GetCoordFilledCell(field, field.coordsStart);
		while (!nextGenerationCell.empty())
		{
			nextGenerationCell = GetCoordFilledCell(field, nextGenerationCell);
		}
	}

	bool Rendering(StructField& field, const std::string& output)
	{
		field.outputFile.open(output);
		if (!field.outputFile.is_open())
		{
			std::cout << "Failed to open '" << output << "' for writing\n";
			return false;
		}
		for (int iterY = 0; iterY <= field.yMax; iterY++)
		{
			for (int iterX = 0; iterX <= field.xMax; iterX++)
			{
				char cell = field.field[iterY][iterX];
				field.outputFile.put(cell);
			}
			if (iterY != field.yMax)
			{
				field.outputFile.put('\n');
			}
		}
		return true;
	}

	std::optional<Args> ParseArgs(int argc, char* argv[])
	{
		if (argc != 3)
		{
			std::cout << "Invalid argument count\n"
				<< "Usage: fill.exe <inputFile> <outputFile>\n";
			return std::nullopt;
		}
		Args args;
		args.inputFile = argv[1];
		args.outputFile = argv[2];
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

	StructField field;
	if (!ReadField(field, args->inputFile))
	{
		return EXIT_FAILURE;
	}

	Fill(field);

	if (!Rendering(field, args->outputFile))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}