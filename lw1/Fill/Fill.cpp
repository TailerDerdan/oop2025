﻿#include <iostream>
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

	//разбить на несколько структур
	struct Field
	{
		std::vector<Coord> coordsStart;
		FieldArray field = { ' ' };
		Coord coordMax;
	};

	struct FilesIO
	{
		std::ifstream inputFile;
		std::ofstream outputFile;
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

	bool ReadField(Field& field, FilesIO& files, const std::string& inputPath)
	{
		if (!ReadField(inputPath, files.inputFile))
		{
			return false;
		}

		char ch;
		Coord coord;

		while (files.inputFile.get(ch))
		{
			if (ch == '\n')
			{
				coord.y++;
				field.coordMax.x = std::max(field.coordMax.x, coord.x - 1);
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
		field.coordMax.y = coord.y;
		return true;
	}

	void FillCell(Field& field, Coord& coord, std::vector<Coord>& result)
	{
		if (coord.x < MIN_WIDTH || coord.y < MIN_WIDTH) return;
		if (coord.x > MAX_WIDTH - 1 || coord.y > MAX_WIDTH - 1) return;

		if (field.field[coord.y][coord.x] == EMPTY_CELL || field.field[coord.y][coord.x] == SPECIAL_CELL)
		{
			result.push_back(coord);
			field.field[coord.y][coord.x] = FILLED_CELL;
			field.coordMax.y = std::max(coord.y, field.coordMax.y);
			field.coordMax.x = std::max(coord.x, field.coordMax.x);
		}
	}

	void FillInSides(Coord currentCell, Field& field, std::vector<Coord>& result)
	{
		Coord topCoord;
		topCoord.x = currentCell.x;
		topCoord.y = currentCell.y - 1;

		FillCell(field, topCoord, result);

		Coord bottomCoord;
		bottomCoord.x = currentCell.x;
		bottomCoord.y = currentCell.y + 1;

		FillCell(field, bottomCoord, result);

		Coord leftCoord;
		leftCoord.x = currentCell.x - 1;
		leftCoord.y = currentCell.y;

		FillCell(field, leftCoord, result);

		Coord rightCoord;
		rightCoord.x = currentCell.x + 1;
		rightCoord.y = currentCell.y;

		FillCell(field, rightCoord, result);
	}

	std::vector<Coord> GetCoordFilledCell(Field& field, std::vector<Coord>& coordStartCell)
	{
		//заменить на очередь
		std::vector<Coord> result;
		while (!coordStartCell.empty())
		{
			Coord currentCell;
			currentCell = coordStartCell.at(coordStartCell.size() - 1);
			coordStartCell.pop_back();

			//выделить в отдельную функцию
			//объединить нижнее и верхнее условие
			if ((currentCell.x <= MAX_WIDTH) && (currentCell.x >= MIN_WIDTH) &&
				(currentCell.y <= MAX_WIDTH) && (currentCell.y >= MIN_WIDTH))
			{
				FillInSides(currentCell, field, result);
			}
		}
		return result;
	}

	void Fill(Field& field)
	{
		std::vector<Coord> nextGenerationCell;

		nextGenerationCell = GetCoordFilledCell(field, field.coordsStart);
		while (!nextGenerationCell.empty())
		{
			nextGenerationCell = GetCoordFilledCell(field, nextGenerationCell);
		}
	}

	bool Render(Field& field, FilesIO& files, const std::string& output)
	{
		files.outputFile.open(output);
		if (!files.outputFile.is_open())
		{
			std::cout << "Failed to open '" << output << "' for writing\n";
			return false;
		}
		for (int iterY = 0; iterY <= field.coordMax.y; iterY++)
		{
			for (int iterX = 0; iterX <= field.coordMax.x; iterX++)
			{
				char cell = field.field[iterY][iterX];
				files.outputFile.put(cell);
			}
			if (iterY != field.coordMax.y)
			{
				files.outputFile.put('\n');
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

	Field field;
	FilesIO files;
	if (!ReadField(field, files, args->inputFile))
	{
		return EXIT_FAILURE;
	}

	Fill(field);

	if (!Render(field, files, args->outputFile))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}