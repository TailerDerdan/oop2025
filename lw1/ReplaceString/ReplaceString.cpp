#include <iostream>
#include <string>
#include <fstream>
#include <optional>

struct Args
{
	std::string input;
	std::string output;
	std::string search;
	std::string replace;
	bool isInputFile = false;
};

namespace
{
	std::string ReplaceString(const std::string& subject,
		const std::string& searchString, const std::string& replacementString)
	{
		if (searchString.empty())
		{
			return subject;
		}

		size_t pos = 0;
		std::string result;
		size_t foundPos = 0;

		//подумать над упрощением условия
		while (foundPos <= std::abs(long(subject.size()) - long(searchString.size())))
		{
			foundPos = subject.find(searchString, pos);
			result.append(subject, pos, foundPos - pos);
			if (foundPos <= subject.size())
			{
				result += replacementString;
			}
			pos = foundPos + searchString.size();
		}

		return result;
	}

	void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
		const std::string& searchString, const std::string& replacementString)
	{
		std::string line;

		while (std::getline(input, line))
		{
			output << ReplaceString(line, searchString, replacementString) << std::endl;
		}
	}

	void CopyStreamWithReplacement(std::string& input, std::ostream& output,
		const std::string& searchString, const std::string& replacementString)
	{
		output << ReplaceString(input, searchString, replacementString) << std::endl;
	}

	std::optional<Args> ParseArgs(int argc, char* argv[])
	{
		std::string search;
		std::string replace;
		std::string text;

		Args args;

		if (argc == 1)
		{
			std::getline(std::cin, search);
			std::getline(std::cin, replace);
			std::getline(std::cin, text);

			args.input = text;
			args.search = search;
			args.replace = replace;
			args.isInputFile = false;
			return args;
		}

		if (argc != 5)
		{
			std::cout << "Invalid argument count\n"
				<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
			return std::nullopt;
		}

		args.input = argv[1];
		args.output = argv[2];
		args.search = argv[3];
		args.replace = argv[4];
		args.isInputFile = true;
		return args;
	}

	bool CopyFileWithReplacement(Args& args)
	{
		if (args.isInputFile)
		{
			std::ifstream inputFile;
			std::ofstream outputFile;

			inputFile.open(args.input);
			outputFile.open(args.output);

			if (!inputFile.is_open())
			{
				std::cout << "Failed to open '" << args.input << "' for reading\n";
				return false;
			}

			if (!outputFile.is_open())
			{
				std::cout << "Failed to open '" << args.output << "' for writing\n";
				return false;
			}

			CopyStreamWithReplacement(inputFile, outputFile, args.search, args.replace);
		}
		else
		{
			CopyStreamWithReplacement(args.input, std::cout, args.search, args.replace);
		}

		return true;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	if (!CopyFileWithReplacement(args.value()))
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}