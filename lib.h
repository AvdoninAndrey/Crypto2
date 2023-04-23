#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <filesystem>

class Statistics
{
private:
	int countCombination = 0;
	int countingUnits = 0;
	int tau = 0;
	int countBitsFileForMasking = 0;
	int countBitInFile = 0;

	bool isFlagPredominance = false;

	void createTwodimensionalArrays();
	std::string convertBinaryNumberSystem(const int& number, const int& flagSizeStr);
public:
	int** arrayCounterCombination = nullptr;
	int** arrayCounterOfUnits = nullptr;
	
	int** arrayCounterCombinationFile = nullptr;
	int** arrayCounterOfUnitsFile = nullptr;

	int predominanceBitZero = 0;
	int predominanceBitOne = 0;

	int tmpBitsMasking = 0;
	int tmpBitsFile = 0;

	/*int codeAsciiSymbolInFile[256] = { 0 };
	int codeAsciiSymbolGamma[256] = { 0 };*/

public:
	Statistics() = default;
	Statistics(const int&, const int&, const int&, const int&, const int&, const bool & );
	Statistics(const Statistics& other);
	~Statistics();
	int getCountCombination();
	int getCountingUnits();
	int getTau();
	int getCountBitsFileForMasking();
	int getCountBitsInFile();
	int getIsFlagPredominance();
	void printProbabilitiesOfCombinations(int** arrayCombination);
	void printProbabilitiesCounterOfUnits(int** arrayOfUnits);
	void printProbabilitiesAppearanceSymbols(int * countAppearanceSymbols);
	void printValueAutocorrelation(int8_t* sequenceBits);

	float autocorrelation(const int& iTau, int8_t* sequenceBits);


};


class MaskingGenerator 
{
private:
	Statistics allParameters;

	int8_t* arrayFirstRegister = nullptr;
	int8_t* arraySecondRegister = nullptr;

	int8_t* gamma = nullptr;
	int8_t* bitsFile = nullptr;

	int currentBitGamma = 0;
	int currentBitFile = 0;

	int sizeFirstRegister = 0;
	int sizeSecondRegister = 0;
	int countBitsResultFormation = 0;
	std::string filePath = "";
	bool isMaskingHeaderFile = true;
	unsigned int sizeHeaderFileBytes = 0;

	void initRegisters();
	void overwriteRegister(int8_t* arrayRegister, const int& sizeRegister, const int8_t& newBit);

	char formationSequnceByte();
	


	void calcAllCombination(const int& resultBitNum, int& tmp, int** arrayCombination, int** arrayOfUnits, int& currentBit);
	void printAllPatameters();
public:
	MaskingGenerator(const int&, const int&, const int&, Statistics&, std::string&, bool, const int&);
	~MaskingGenerator();
	void maskingAllFile();
	void maskingFileWithoutHeader();
};

