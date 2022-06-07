#include "IFileReader.h"

double IFileReader::readDoubleCell(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
	// read cell
	std::string cell = this->readCell();

	// remove whitespaces & tabs
	this->eraseWhitespacesFromString(cell);

	// validate cell
	if (!std::regex_match(cell, cPositiveDecReg))
	{
		throw std::runtime_error(cell + " is not a decimal number.");
	}

	// additional validation
	if (validate)
	{
		std::string error;
		if (!validate(cell, error))
		{
			throw std::runtime_error(cell + " is not valid. " + error);
		}
	}

	// convert to double
	return std::stod(cell);
}

float IFileReader::readFloatCell(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
	// read cell
	std::string cell = this->readCell();

	// remove whitespaces & tabs
	this->eraseWhitespacesFromString(cell);

	// validate third cell
	if (!std::regex_match(cell, cPositiveDecReg))
	{
		throw std::runtime_error(cell + " is not a decimal number.");
	}

	// additional validation
	if (validate)
	{
		std::string error;
		if (!validate(cell, error))
		{
			throw std::runtime_error(cell + " is not valid. " + error);
		}
	}

	// convert to float
	return std::stof(cell);
}

uint64_t IFileReader::readULongLongCell(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
	// read cell
	std::string cell = this->readCell();

	// remove whitespaces & tabs
	this->eraseWhitespacesFromString(cell);

	// validate cell
	if (!std::regex_match(cell, cPositiveNumReg))
	{
		throw std::runtime_error(cell + " is not a natural number.");
	}

	// additional validation
	if (validate)
	{
		std::string error;
		if (!validate(cell, error))
		{
			throw std::runtime_error(cell + " is not valid. " + error);
		}
	}

	// convert string to int
	return std::stoull(cell);
}

std::string IFileReader::readStringCell(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
	// read cell
	std::string cell = this->readCell();

	// remove whitespaces & tabs
	this->eraseWhitespacesFromString(cell);

	// additional validation
	if (validate)
	{
		std::string error;
		if (!validate(cell, error))
		{
			throw std::runtime_error(cell + " is not valid. " + error);
		}
	}

	return cell;
}

int IFileReader::getNumOfCols() const
{
	return mNumOfCols;
}

void IFileReader::setNumOfCols(int num)
{
	mNumOfCols = num;
}

void IFileReader::eraseWhitespacesFromString(std::string& str)
{
	int start = -1;
	int end = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '\t' || str[i] == ' ')
		{
			if (start == -1)
			{
				start = i;
			}
			end = i;
		}
		else
		{
			break;
		}
	}
	if (start != -1)
	{
		str.erase(start, end + 1);
	}
}