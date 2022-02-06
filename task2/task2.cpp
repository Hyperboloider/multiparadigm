#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main() {

	int N = 5;
	int numberOfWords = 0;
	int numberOfOddWords = 7;
	int currentNumberOfWords = 0;
	int lineNumber = 1;
	int pageNumber = 1;
	int numberOfLinesInPage = 45;
	int** occurenceRecords;
	std::string* words;

	std::string word;
	std::ifstream fileCount("test.txt");

countLoop:
	if (fileCount >> word) {
		numberOfWords++;
		goto countLoop;
	}

	fileCount.close();

	words = new std::string[numberOfWords];
	occurenceRecords = new int* [numberOfWords];

	int recordIndex = 0;

forInNumberOfWords:
	if (recordIndex < numberOfWords) {
		occurenceRecords[recordIndex] = new int[101];
		occurenceRecords[recordIndex][0] = 0;
		recordIndex++;
		goto forInNumberOfWords;
	}

	std::ifstream file("test.txt");
readLoop:
	if (file >> word) {

		word += '\0';
		std::string tmp;
		int charIndex = 0;

	forCharInWord:
		if (word[charIndex] != '\0') {
			if (
				word[charIndex] >= 65 && word[charIndex] <= 90 ||
				word[charIndex] >= 97 && word[charIndex] <= 122 ||
				word[charIndex] == 45
				) 
			{
				if (word[charIndex] <= 90 && word[charIndex] >= 65) {
					tmp += char(word[charIndex] + 32);
				}
				else {
					tmp += word[charIndex];
				}
			}

			charIndex++;
			goto forCharInWord;
		}

		word = tmp;
		int currentWordNumber = 0;
		bool wordMatched = false;

	wordsForEach:
		if (currentWordNumber < currentNumberOfWords) {
			if (words[currentWordNumber] == word) {
				int lastFreeIndex = occurenceRecords[currentWordNumber][0];
				if (lastFreeIndex < 101) {
					if (occurenceRecords[currentWordNumber][0] == 0 || occurenceRecords[currentWordNumber][lastFreeIndex] != pageNumber) {
						occurenceRecords[currentWordNumber][lastFreeIndex + 1] = pageNumber;
						occurenceRecords[currentWordNumber][0] = lastFreeIndex + 1;
					}
				}

				wordMatched = true;
			}

			currentWordNumber++;
			goto wordsForEach;
		}

		if (!wordMatched) {
			words[currentWordNumber] = word;
			occurenceRecords[currentNumberOfWords][0] = 1;
			occurenceRecords[currentNumberOfWords][1] = pageNumber;
			currentNumberOfWords++;
		}

		if (file.peek() == '\n') {
			lineNumber++;
			if (lineNumber % numberOfLinesInPage == 0) {
				lineNumber = 1;
				pageNumber++;
			}
		}

		currentWordNumber = 0;
		goto readLoop;
	}

	file.close();

	for (int i = 0; i < currentNumberOfWords; i++) {
		for (int j = 0; j < currentNumberOfWords - i - 1; j++) {
			if (words[j] > words[j + 1]) {
				std::string tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;

				int* tmpRecord = occurenceRecords[j];
				occurenceRecords[j] = occurenceRecords[j + 1];
				occurenceRecords[j + 1] = tmpRecord;
			}
		}
	}

	std::ofstream outFile("result.txt");
	int outputIndex = 0;
	int i = 0;

outputLoopOuter:
	if (i < currentNumberOfWords) {
		std::string recordsConcat;
		int j = 1;
		bool isFirstRecord = true;

		if (words[i] == "" || words[i] == "-" || occurenceRecords[i][0] > 100) {
			i++;
			goto outputLoopOuter;
		}

		outFile << words[i] << " - ";


	outputLoopInner:
		if (j <= occurenceRecords[i][0]) {
			outFile << (isFirstRecord ? "" : ", ");
			outFile << occurenceRecords[i][j];
			isFirstRecord = false;
			j++;
			goto outputLoopInner;
		}
		
	
		
		outFile << std::endl;
		i++;
		goto outputLoopOuter;
	}

	return 0;
}