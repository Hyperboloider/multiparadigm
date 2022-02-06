#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main() {

	int N = 5;
	int numberOfWords = 0;
	int numberOfOddWords = 7;
	int currentNumberOfWords = 0;
	int* wordFrequency;
	std::string* words;

	std::string word;
	std::ifstream fileCount("test.txt");
	
	std::string* oddWords = new std::string[numberOfOddWords];
	oddWords[0] = "the";
	oddWords[1] = "of";
	oddWords[2] = "in";
	oddWords[3] = "to";
	oddWords[4] = "a";
	oddWords[5] = "an";
	oddWords[6] = "and";

	countLoop:
	if (fileCount >> word) {
		numberOfWords++;
		goto countLoop;
	}

	wordFrequency = new int[numberOfWords];
	words = new std::string[numberOfWords];
	fileCount.close();

	std::ifstream file("test.txt");
	readLoop:
	if (file >> word) {

		word += '\0';
		std::string tmp;
		int charIndex = 0;
		bool wordMatched = false;

		forCharInWord:
		if (word[charIndex] != '\0') {
			if (word[charIndex] <= 90 && word[charIndex] >= 65) {
				tmp += char(word[charIndex] + 32);
			} else {
				tmp += word[charIndex];
			}

			charIndex++;
			goto forCharInWord;
		}
			
		word = tmp;

		int oddWordIndex = 0;
		forWordInOddWords:
		if (oddWordIndex < numberOfOddWords) {
			if (oddWords[oddWordIndex] == word) {
				wordMatched = true;
			} else {
				oddWordIndex++;
				goto forWordInOddWords;
			}
		}

		int currentWordNumber = 0;
		
		wordsForEach:
		if (currentWordNumber < currentNumberOfWords && !wordMatched) {
			if (words[currentWordNumber] == word) {
				wordFrequency[currentWordNumber] += 1;
				wordMatched = true;
			}

			currentWordNumber++;
			goto wordsForEach;
		}

		if (!wordMatched) {
			words[currentWordNumber] = word;
			wordFrequency[currentWordNumber] = 1;
			currentNumberOfWords++;
		}


		currentWordNumber = 0;
		wordMatched = false;
		goto readLoop;
	}

	file.close();

	int i = 0;
	int j = 0;

	bubbleSortOuter:
	if (i < currentNumberOfWords) {

		bubbleSortInner:
		if (j < currentNumberOfWords - i - 1) {
			if (wordFrequency[j] < wordFrequency[j + 1]) {
				int tmpFrequency = wordFrequency[j];
				std::string tmpWord = words[j];

				wordFrequency[j] = wordFrequency[j + 1];
				words[j] = words[j + 1];

				wordFrequency[j + 1] = tmpFrequency;
				words[j + 1] = tmpWord;
			}

			j++;
			goto bubbleSortInner;
		}

		j = 0;
		i++;
		goto bubbleSortOuter;
	}

	std::ofstream outFile("result.txt");
	int outputIndex = 0;

	outputLoop:
	if (outputIndex < N && outputIndex < currentNumberOfWords) {
		outFile << words[outputIndex] << "-" << wordFrequency[outputIndex] << std::endl;
		outputIndex++;
		goto outputLoop;
	}

	return 0;
}