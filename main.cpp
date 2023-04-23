#include "lib.h"

int main()
{
	
	std::string filePath, modeMask, isFlagPredominance;
	std::cout << "Specify the path to the file to mask: ";
	std::cin >> filePath;
	filePath = "2.bmp";
	std::cout << "Enter \"mask\" to mask the entire file or \"hmask\" to mask the file without a header: ";
	std::cin >> modeMask;
	modeMask = "hmask";
	
	std::cout << "Enter \"1\" if you want to make a predominance, otherwise \"0\": ";
	std::cin >> isFlagPredominance;
	isFlagPredominance = "1";

	if (modeMask == "mask")
	{
		unsigned int sizeFile = std::filesystem::file_size(std::filesystem::path(filePath));
		if (isFlagPredominance == "1")
		{
			Statistics allParameters(4, 4, 32, sizeFile * 8, sizeFile * 8, true);
			MaskingGenerator generator(8, 10, 97, allParameters, filePath, false, 0);
			generator.maskingAllFile();
		}
		else
		{
			Statistics allParameters(4, 4, 32, sizeFile * 8, sizeFile * 8, false);
			MaskingGenerator generator(8, 10, 97, allParameters, filePath, false, 0);
			generator.maskingAllFile();
		}
		
	}

	else if (modeMask == "hmask")
	{
		int countByteHeader;
		std::cout << "Enter the number of bytes in the file header: ";
		std::cin >> countByteHeader;
		unsigned int sizeFile = std::filesystem::file_size(std::filesystem::path(filePath));
		if (isFlagPredominance == "1")
		{
			Statistics allParameters(4, 4, 32, sizeFile * 8 - countByteHeader * 8, sizeFile * 8, true);
			MaskingGenerator generator(8, 10, 97, allParameters, filePath, false, countByteHeader);
			generator.maskingFileWithoutHeader();
		}
		else
		{
			Statistics allParameters(4, 4, 32, sizeFile * 8 - countByteHeader * 8, sizeFile * 8, false);
			MaskingGenerator generator(8, 10, 97, allParameters, filePath, false, countByteHeader);
			generator.maskingFileWithoutHeader();
		}

	}
	return 0;
}