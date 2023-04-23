#include "lib.h"

Statistics::Statistics(const int& countCombination, const int& countingUnits, const int& tau, const int& countBitsFileForMasking, const int& countBitInFile, const bool& isFlagPredominance) :
	countCombination(countCombination),
	countingUnits(countingUnits),
	tau(tau),
	countBitsFileForMasking(countBitsFileForMasking),
	countBitInFile(countBitInFile),
	isFlagPredominance(isFlagPredominance)
{
	createTwodimensionalArrays();
}
Statistics::~Statistics()
{
	if (!(arrayCounterCombination == nullptr))
	{
		for (int i = 0; i < this->countCombination; i++)
		{
			delete[] arrayCounterCombination[i];
		}
		delete[] arrayCounterCombination;
		arrayCounterCombination = nullptr;
	}

	if (!(arrayCounterOfUnits == nullptr))
	{
		for (int i = 0; i < countingUnits - 1; i++)
		{
			delete[] arrayCounterOfUnits[i];
		}
		delete[] arrayCounterOfUnits;
		arrayCounterOfUnits = nullptr;
	}

	if (!(arrayCounterCombinationFile == nullptr))
	{
		for (int i = 0; i < this->countCombination; i++)
		{
			delete[] arrayCounterCombinationFile[i];
		}
		delete[] arrayCounterCombinationFile;
		arrayCounterCombinationFile = nullptr;
	}

	if (!(arrayCounterOfUnits == nullptr))
	{
		for (int i = 0; i < countingUnits - 1; i++)
		{
			delete[] arrayCounterOfUnitsFile[i];
		}
		delete[] arrayCounterOfUnitsFile;
		arrayCounterOfUnitsFile = nullptr;
	}

}

int Statistics::getCountCombination()
{
	return countCombination;
}
int Statistics::getCountingUnits()
{
	return countingUnits;
}
int Statistics::getTau()
{
	return tau;
}
int Statistics::getCountBitsFileForMasking()
{
	return countBitsFileForMasking;
}
int Statistics::getCountBitsInFile()
{
	return countBitInFile;
}
int Statistics::getIsFlagPredominance()
{
	return isFlagPredominance;
}

void Statistics::createTwodimensionalArrays()
{
	this->arrayCounterCombination = new int* [countCombination];
	this->arrayCounterCombinationFile = new int* [countCombination];
	for (int i = 1; i <= countCombination; i++)
	{
		int sizeArray = static_cast<int>(pow(2, i));
		this->arrayCounterCombination[i - 1] = new int[sizeArray] { 0 };
		this->arrayCounterCombinationFile[i - 1] = new int[sizeArray] { 0 };
	}
	this->arrayCounterOfUnits = new int* [countingUnits - 1];
	this->arrayCounterOfUnitsFile = new int* [countingUnits - 1];
	for (int i = 0; i < countingUnits - 1; i++)
	{
		this->arrayCounterOfUnits[i] = new int[i + 3]{ 0 };
		this->arrayCounterOfUnitsFile[i] = new int[i + 3]{ 0 };
	}
}

Statistics::Statistics(const Statistics& other)
{
	this->countCombination = other.countCombination;
	this->countingUnits = other.countingUnits;
	this->tau = other.tau;
	this->countBitsFileForMasking = other.countBitsFileForMasking;
	this->countBitInFile = other.countBitInFile;
	this->isFlagPredominance = other.isFlagPredominance;

	/*for (int i = 0; i < 256; i++)
	{
		codeAsciiSymbolInFile[i] = 0;
		codeAsciiSymbolGamma[i] = 0;
	}*/

	//int codeAsciiSymbolInFile[256] = { 0 };
	//int codeAsciiSymbolGamma[256] = { 0 };

	this->arrayCounterCombination = new int* [other.countCombination];
	this->arrayCounterCombinationFile = new int* [other.countCombination];
	for (int i = 1; i <= other.countCombination; i++)
	{
		int sizeArray = static_cast<int>(pow(2, i));
		this->arrayCounterCombination[i - 1] = new int[sizeArray] { 0 };
		this->arrayCounterCombinationFile[i - 1] = new int[sizeArray] { 0 };
	}

	this->arrayCounterOfUnits = new int* [other.countingUnits - 1];
	this->arrayCounterOfUnitsFile = new int* [other.countingUnits - 1];
	for (int i = 0; i < countingUnits - 1; i++)
	{
		this->arrayCounterOfUnits[i] = new int[i + 3]{ 0 };
		this->arrayCounterOfUnitsFile[i] = new int[i + 3]{ 0 };
	}
}


std::string Statistics::convertBinaryNumberSystem(const int& number, const int& flagSizeStr)
{
	std::string result, resultReverse = "";
	int tmp = number;
	while (tmp)
	{
		int mod = tmp % 2;
		result += std::to_string(mod);
		tmp /= 2;

	}

	for (int i = result.length() - 1; i >= 0; i--)
	{
		resultReverse += result[i];
	}
	while (resultReverse.size() != flagSizeStr)
	{
		resultReverse += "0";
	}

	return resultReverse;
}

float Statistics::autocorrelation(const int& iTau, int8_t* sequenceBits)
{
	if (iTau == 0)
	{
		return 1.0;
	}
	else
	{
		int A_t = 0, B_t = 0;
		for (int i = iTau; i < this->getCountBitsInFile(); i++)
		{
			if (sequenceBits[i] == sequenceBits[i - iTau])
			{
				A_t++;
			}
			else
			{
				B_t++;
			}
		}
		return static_cast<float>(A_t - B_t) / static_cast<float>(A_t + B_t);
	}
}



void Statistics::printProbabilitiesOfCombinations(int** arrayCombination)
{
	for (int i = 1; i <= this->countCombination; i++)
	{
		for (int j = 0; j < static_cast<int>(pow(2, i)); j++)
		{
			if (j < 2)
			{
				std::string countNull = "";
				for (int k = 0; k < i - 1; k++)
				{
					countNull += "0";
				}
				std::cout << "p(" << countNull << j << ") = " << static_cast<float>(arrayCombination[i - 1][j]) / static_cast<float>(countBitInFile - (i - 1)) << std::endl;
			}
			else
			{
				std::cout << "p(" << convertBinaryNumberSystem(j, i) << ") = " << static_cast<float>(arrayCombination[i - 1][j]) / static_cast<float>(countBitInFile - (i - 1)) << std::endl;
			}
		}
		std::cout << std::endl;
	}
}
void Statistics::printProbabilitiesCounterOfUnits(int** arrayOfUnits)
{
	for (int i = 0; i < this->countCombination - 1; i++)
	{
		std::cout << "Probability for " << i + 2 << " bits:\n";
		for (int j = 0; j < i + 3; j++)
		{
			std::cout << "p(number of units = " << j << ") = " << static_cast<float>(arrayOfUnits[i][j]) / static_cast<float>(this->countBitsFileForMasking - (i + 1)) << std::endl;
		}
	}
}

void Statistics::printValueAutocorrelation(int8_t* sequenceBits)
{
	std::cout << "Autocorrelation values: \n" << std::endl;
	for (int i = 0; i <= this->tau; i++)
	{
		std::cout << "K(t = " << i << ") = " << autocorrelation(i, sequenceBits) << std::endl;
	}
}
void Statistics::printProbabilitiesAppearanceSymbols(int* countAppearanceSymbols)
{
	std::cout << "Probabilities of occurrence of symbols of the Aski table" << std::endl;
	for (int i = 0; i < 256; i++)
	{

		std::cout << "p( character Code = " << i << " ) = " << static_cast<float>(countAppearanceSymbols[i]) / static_cast<float>(countBitInFile / 8) << std::endl;

	}
}




MaskingGenerator::MaskingGenerator(const int& countBitsResultFormation, const int& sizeFirstRegister, const int& sizeSecondRegister, Statistics& allParameters,
	std::string& filePath, bool isMaskingHeaderFile, const int& sizeHeaderFileBytes) :
	countBitsResultFormation(countBitsResultFormation),
	sizeFirstRegister(sizeFirstRegister),
	sizeSecondRegister(sizeSecondRegister),
	allParameters(allParameters),
	filePath(filePath),
	isMaskingHeaderFile(isMaskingHeaderFile),
	sizeHeaderFileBytes(sizeHeaderFileBytes)
{
	initRegisters();
}

void MaskingGenerator::overwriteRegister(int8_t* arrayRegister, const int& sizeRegister, const int8_t& newBit)
{
	for (int j = sizeRegister - 1; j > 0; j--)
	{
		arrayRegister[j] = arrayRegister[j - 1];
	}
	arrayRegister[0] = newBit;
}

void MaskingGenerator::initRegisters()
{
	this->arrayFirstRegister = new int8_t[sizeFirstRegister];

	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < this->sizeFirstRegister; i++)
	{
		this->arrayFirstRegister[i] = static_cast<int8_t>(rand() % 2);
	}
	this->arraySecondRegister = new int8_t[sizeSecondRegister];
	for (int i = 0; i < this->sizeSecondRegister; i++)
	{
		this->arraySecondRegister[i] = static_cast<int8_t>(rand() % 2);
	}
	// инициалзировать гамму размером файла - размер заголовка.
}

MaskingGenerator::~MaskingGenerator()
{
	delete[] arrayFirstRegister, arraySecondRegister, gamma, bitsFile;
}

char MaskingGenerator::formationSequnceByte()
{
	for (int i = 0; i < this->countBitsResultFormation; i++)
	{
		int8_t newBitFirstRegister = this->arrayFirstRegister[6] ^ this->arrayFirstRegister[9];
		int8_t newBitSecondRegister = this->arraySecondRegister[90] ^ this->arraySecondRegister[96];
		int8_t resultBit = newBitFirstRegister ^ newBitSecondRegister;

		this->gamma[currentBitGamma] = resultBit;

		int resultBitNum = static_cast<int>(resultBit);

		if (this->allParameters.getIsFlagPredominance())
		{
			if (resultBitNum == 0)
			{
				this->allParameters.predominanceBitZero++;
				if (this->allParameters.predominanceBitZero == 3)
				{
					resultBitNum = 1;
					this->allParameters.predominanceBitZero = 0;
				}
			}
			else
			{
				this->allParameters.predominanceBitOne++;
				if (this->allParameters.predominanceBitOne == 7)
				{
					resultBitNum = 0;
					this->allParameters.predominanceBitOne = 0;
				}
			}
		}
		
		calcAllCombination(resultBitNum, this->allParameters.tmpBitsMasking, this->allParameters.arrayCounterCombination, this->allParameters.arrayCounterOfUnits, this->currentBitGamma);
		overwriteRegister(this->arrayFirstRegister, this->sizeFirstRegister, newBitFirstRegister);
		overwriteRegister(this->arraySecondRegister, this->sizeSecondRegister, newBitSecondRegister);
		currentBitGamma++;
	}
	//std::cout << "\n";
	char sequenceFormatBytesResult;
	int byte = 0, currentIndexBit = currentBitGamma - 8;

	for (int j = 0; j < 8; j++)
	{
		byte = (byte << 1) | static_cast<int>(this->gamma[currentIndexBit]);
		currentIndexBit++;
	}
	sequenceFormatBytesResult = static_cast<char>(byte);

	return sequenceFormatBytesResult;
}

void MaskingGenerator::maskingAllFile()
{
	std::ifstream fileForMasking;
	fileForMasking.open(this->filePath, std::fstream::ios_base::in | std::fstream::ios_base::binary);

	this->gamma = new int8_t[allParameters.getCountBitsInFile()];
	this->bitsFile = new int8_t[allParameters.getCountBitsInFile()];

	std::ofstream fileResultMasking;
	fileResultMasking.open("result.txt", std::fstream::ios_base::app | std::fstream::ios_base::binary);

	char everyByte;
	while (fileForMasking.get(everyByte))
	{
		for (int j = 0, k = 8; j < 8; j++, k--)
		{
			int8_t bit = static_cast<int8_t>((everyByte >> (k - 1)) & 0x1);
			bitsFile[currentBitFile] = bit;
			int resultBitNum = static_cast<int>(bit);
			calcAllCombination(resultBitNum, this->allParameters.tmpBitsFile, this->allParameters.arrayCounterCombinationFile, this->allParameters.arrayCounterOfUnitsFile, this->currentBitFile);
			currentBitFile++;
		}
		//std::cout << static_cast<int>(everyByte) << std::endl;
		//this->allParameters.codeAsciiSymbolInFile[static_cast<int>(everyByte)]++;

		char byteMask[1];
		char byteGamma = formationSequnceByte();
		//this->allParameters.codeAsciiSymbolGamma[static_cast<int>(byteGamma)]++;

		byteMask[0] = static_cast<char>(everyByte ^ byteGamma);
		//this->allParameters.codeAsciiSymbolGamma[static_cast<int>(byteMask[0])]++;
		fileResultMasking.write(byteMask, 1);
	}
	fileForMasking.close();
	fileResultMasking.close();
	printAllPatameters();
}

void MaskingGenerator::maskingFileWithoutHeader()
{
	std::ifstream fileForMasking;
	fileForMasking.open(this->filePath, std::fstream::ios_base::in | std::fstream::ios_base::binary);

	this->gamma = new int8_t [allParameters.getCountBitsInFile()];
	this->bitsFile = new int8_t [allParameters.getCountBitsInFile()];

	std::ofstream fileResultMasking;
	fileResultMasking.open("result" + std::filesystem::path(filePath).extension().string(), std::fstream::ios_base::app | std::fstream::ios_base::binary);

	char* bufferBytesHeaderFile = new char[sizeHeaderFileBytes];
	fileForMasking.read(bufferBytesHeaderFile, sizeHeaderFileBytes); // прочитали байты заголовка файла

	for (int i = 0; i < sizeHeaderFileBytes; i++)
	{
		for (int j = 0, k = 8; j < 8; j++, k--)
		{
			/*this->allParameters.codeAsciiSymbolInFile[static_cast<int>(bufferBytesHeaderFile[i])]++;
			this->allParameters.codeAsciiSymbolGamma[static_cast<int>(bufferBytesHeaderFile[i])]++;*/

			int8_t bit = static_cast<int8_t>((bufferBytesHeaderFile[i] >> (k - 1)) & 0x1);
			gamma[currentBitGamma] = bit;
			bitsFile[currentBitFile] = bit;
			int resultBitNum = static_cast<int>(bit);
	
			calcAllCombination(resultBitNum, this->allParameters.tmpBitsMasking, this->allParameters.arrayCounterCombination, this->allParameters.arrayCounterOfUnits, this->currentBitGamma);
			calcAllCombination(resultBitNum, this->allParameters.tmpBitsFile, this->allParameters.arrayCounterCombinationFile, this->allParameters.arrayCounterOfUnitsFile, this->currentBitFile);

			currentBitGamma++;
			currentBitFile++;
		}
	}


	fileResultMasking.write(bufferBytesHeaderFile, sizeHeaderFileBytes); // записыли байта заголовка файла в результирующий файл
	delete[] bufferBytesHeaderFile;

	std::ios::pos_type pos = sizeHeaderFileBytes;
	fileForMasking.seekg(pos);

	char everyByte;
	while (fileForMasking.get(everyByte))
	{
		//this->allParameters.codeAsciiSymbolInFile[static_cast<int>(everyByte)]++;
		for (int j = 0, k = 8; j < 8; j++, k--)
		{
			int8_t bit = static_cast<int8_t>((everyByte >> (k - 1)) & 0x1);
			bitsFile[currentBitFile] = bit;
			//int resultBitNum = static_cast<int>(bit);
			
			/*if (this->allParameters.getIsFlagPredominance())
			{
				if (resultBitNum == 0)
				{
					this->allParameters.predominanceBitZero++;
					if (this->allParameters.predominanceBitZero == 3)
					{
						resultBitNum = 1;
						this->allParameters.predominanceBitZero = 0;
					}
				}
				else
				{
					this->allParameters.predominanceBitOne++;
					if (this->allParameters.predominanceBitOne == 7)
					{
						resultBitNum = 0;
						this->allParameters.predominanceBitOne = 0;
					}
				}
			}*/

			calcAllCombination(static_cast<int>(bit), this->allParameters.tmpBitsFile, this->allParameters.arrayCounterCombinationFile, this->allParameters.arrayCounterOfUnitsFile, this->currentBitFile);
			currentBitFile++;
		}
		char byteMask[1];
		char byteGamma = formationSequnceByte();
		//this->allParameters.codeAsciiSymbolGamma[static_cast<int>(byteGamma)]++;
		byteMask[0] = static_cast<char>(everyByte ^ byteGamma);
		fileResultMasking.write(byteMask, 1);
	}

	fileForMasking.close();
	fileResultMasking.close();
	printAllPatameters();
	//std::cout << "=====BEFORE=====" << std::endl;
	//this->allParameters.printProbabilitiesOfCombinations(this->allParameters.arrayCounterCombinationFile);
	//this->allParameters.printProbabilitiesCounterOfUnits(this->allParameters.arrayCounterOfUnitsFile);
	//this->allParameters.printValueAutocorrelation(bitsFile);
	////this->allParameters.printProbabilitiesAppearanceSymbols(this->allParameters.codeAsciiSymbolInFile);
	//std::cout << "\n";
	//std::cout << "=====AFTER=====" << std::endl;
	//this->allParameters.printProbabilitiesOfCombinations(this->allParameters.arrayCounterCombination);
	//this->allParameters.printProbabilitiesCounterOfUnits(this->allParameters.arrayCounterOfUnits);
	//this->allParameters.printValueAutocorrelation(gamma);
	//this->allParameters.printProbabilitiesAppearanceSymbols(this->allParameters.codeAsciiSymbolGamma);
}



void MaskingGenerator::calcAllCombination(const int& resultBitNum, int& tmp, int** arrayCombination, int** arrayOfUnits, int& currentBit)
{
	tmp = (tmp << 1) | resultBitNum;
	arrayCombination[0][resultBitNum]++;
	for (int j = 0, k = currentBit, maska = 0x03; j < this->allParameters.getCountCombination() - 1; maska |= static_cast<int>(pow(2, j + 2)), j++)
	{
		if (k > j)
		{
			int indexExternal = j + 1, findIndexCombination = tmp & maska, findIndexCountUnits = 0;
			arrayCombination[indexExternal][findIndexCombination]++;

			for (; findIndexCombination; findIndexCombination >>= 1)
			{
				findIndexCountUnits += findIndexCombination & 1;
			}
			arrayOfUnits[j][findIndexCountUnits]++;
		}
	}
}



void MaskingGenerator::printAllPatameters()
{
	std::cout << "=====BEFORE MASKING=====" << std::endl;
	this->allParameters.printProbabilitiesOfCombinations(this->allParameters.arrayCounterCombinationFile);
	this->allParameters.printProbabilitiesCounterOfUnits(this->allParameters.arrayCounterOfUnitsFile);
	this->allParameters.printValueAutocorrelation(bitsFile);
	//this->allParameters.printProbabilitiesAppearanceSymbols(this->allParameters.codeAsciiSymbolInFile);
	std::cout << "\n";
	std::cout << "=====AFTER MASKING=====" << std::endl;
	this->allParameters.printProbabilitiesOfCombinations(this->allParameters.arrayCounterCombination);
	this->allParameters.printProbabilitiesCounterOfUnits(this->allParameters.arrayCounterOfUnits);
	this->allParameters.printValueAutocorrelation(gamma);
	//this->allParameters.printProbabilitiesAppearanceSymbols(this->allParameters.codeAsciiSymbolGamma);
}
//void MaskingGenerator::calcAllCombination(const int& resultBitNum, int& tmp, int** arrayCombination, int** arrayOfUnits)
//{
//	this->allParameters.tmpBitsMasking = (this->allParameters.tmpBitsMasking << 1) | resultBitNum;
//	this->allParameters.arrayCounterCombination[0][resultBitNum]++;
//	//this->allParameters.arrayCounterCombinationFile[0][resultBitNum]++;
//	for (int j = 0, k = currentBitGamma, maska = 0x03; j < this->allParameters.getCountCombination() - 1; maska |= static_cast<int>(pow(2, j + 2)), j++)
//	{
//		if (k > j)
//		{
//			int indexExternal = j + 1, findIndexCombination = this->allParameters.tmpBitsMasking & maska, findIndexCountUnits = 0;
//			this->allParameters.arrayCounterCombination[indexExternal][findIndexCombination]++;
//
//			for (; findIndexCombination; findIndexCombination >>= 1)
//			{
//				findIndexCountUnits += findIndexCombination & 1;
//			}
//			this->allParameters.arrayCounterOfUnits[j][findIndexCountUnits]++;
//			//this->allParameters.arrayCounterCombinationFile[j][findIndexCountUnits]++;
//		}
//	}
//}