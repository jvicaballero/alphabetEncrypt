//*******************************************************************
//*  Programmer: Jasper Caballero                                          *
//* *
//*                    *
//*                                                                 *
//*  Write a program that reads the data file “Lab3B.txt” and then  *
//*  proceeds to decrypt the message.  The message should display   *
//*  on the screen in both forms (encrypted and decrypted).         *
//*                                                                 *
//*                                                                 *
//*  EXAMPLE:  If the data file stored the word HELLO and the       *
//*            encrypted message                                    *
//*  TN ARR FS DUKHM, TN RAHJJY KASS TDFMCS UP RAQUFRAS H LNKPUTAR! *
//*                                                                 *
//*            then the following would display on screen:          *
//*                                                                 *
//*  Encrypted message:                                             *
//*  TN ARR FS DUKHM, TN RAHJJY KASS TDFMCS UP RAQUFRAS H LNKPUTAR! *
//*  After decryption:                                              *
//*  TO ERR IS HUMAN, TO REALLY MESS THINGS UP REQUIRES A COMPUTER! *
//*                                                                
//*This program only uses single words with all capital letters to create the encryption alphabet
//*******************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//class that can both encrypt and decrypt a message by creating an alternate Alphabet as its key
class encryptMessageType
{
public:

	//function that will change repeated characters to a space ' '
	void changeRepeat();

	//function to delete the spaces
	void deleteSpace();

	//function that will prompt/get a word from the user
	void getWord();

	// function that will display the changedWord after modifications
	void displayChangedWord();

	// function that will make the alternate alphabet using the changedWord and the normAlphabet to compare
	void buildAltAlphabet(int, char[27]);

	// function that will display both the normAlphabet and altAlphabet
	void display(char[27]);

	//function that will get a sentence from the user and store to private variable sentence
	void getSentence();

	//function that will encrypt the given sentence using the altAlphabet
	void encryptSentence(char[27]);

	//function that will dispLay the encrypted sentence 
	void displayEncrypt();

	//function that will display both the changedWord and the encrypted sentence onto a file
	void displayOnFile();

	//function that will retrieve the changed word and sentence from file
	void getFromFile();

	// function that will decrypt the message
	void decryptMessage(char[27]);

private:
	// variable to record the length of a string
	int  stringLength;

	// variable to record the length of a sentence/phrase
	int  sentenceLength;

	// variable to record the size of a word after modifications
	int  sizeOfChangedWord;

	// char array that will store a word from the user
	char wordInput[30];

	//char array that will store the word after modifications
	char changedWord[30];

	// char array that will store the alternate alphabet after modifications
	char altAlphabet[27];

	// char array that will store a sentence from the user
	char sentence[150];

	// output file to put text on a file
	ofstream outFile;

	// input file to read in text from a file
	ifstream inFile;

	// char array that will store the word from the file
	char charWord[30];

	// char array that will store the phrase from the file
	char cphrase[150];

}; // Bottom of Class

int main()
{
	// object that will call the class to store values in private variables, call functions, and display words/messages
	encryptMessageType word;

	// variable to help compare the character to others
	char letter;

	// character array containing the traditional normal alphabet
	char normAlphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// variable that will store the number of characters in the normal, as well as alternate alphabet
	int alphLength = strlen(normAlphabet);

	// call function getword under the object word
	word.getWord();

	// call function changeRepeat under object word
	word.changeRepeat();

	// call function deleteSpace under object word
	word.deleteSpace();

	// call function displayChangedWord under object word
	word.displayChangedWord();

	// call function buildAltAlphabet with parameters alphLength and normAlphabet to help make altalphabet under object word
	word.buildAltAlphabet(alphLength, normAlphabet);

	// call function display under object word
	word.display(normAlphabet);

	cout << "We will use your word to create an alternate alphabet to encrypt a sentence. " << endl << endl;

	// call function getSentence under object word
	word.getSentence();

	// call function encryptSentence passing normAlphabet as a parameter under object word
	word.encryptSentence(normAlphabet);

	// call function displayEncrypt() under object word
	word.displayEncrypt();

	// call function displayOnFile() under object word
	word.displayOnFile();

	cout << "Both the word and the encrypted message have been transferred to a file. " << endl;

	word.getFromFile();

	word.decryptMessage(normAlphabet);

	return 0; //SUCCESS!!
} // bottom of function main

  // ALL functions are public member variables of class encryptMessageType

void encryptMessageType::deleteSpace()
{
	// variable to keep track of position in char array
	int count = 0;

	// Loop that will exclude adding the space into the array changedWord
	// Will return the new array changedWord since it arrays are reference parameters
	for (int i = 0; i <= stringLength; i++)
	{
		if (changedWord[i] != ' ')
			changedWord[count++] = changedWord[i];
	}

	// work on this, put null there
	//changeTheWord[length] = '\0';

} // bottom of function deleteSpace()

void encryptMessageType::changeRepeat()
{
	char letter;
	for (int i = 0; i <= stringLength; i++)
	{
		// compare character to the other letters in changedWord
		letter = changedWord[i];

		// run through other letters in changedWord
		for (int j = i + 1; j <= stringLength; j++)
		{
			// if character is the same letter, it will change it to a space
			if (changedWord[j] == letter)
			{
				changedWord[j] = ' ';
			}

		}
	}
} //bottom of changeRepeat()

void encryptMessageType::getWord()
{
	// prompt user for a word
	cout << "Please enter a word: ";

	// input the word and store to variable wordInput
	cin >> wordInput;

	// flush memory for excess/unwanted characters
	cin.ignore(99, '\n');

	// find length of word and store into variable stringLength
	stringLength = strlen(wordInput);

	// set array changedWord = word
	for (int i = 0; i <= stringLength; i++)
	{
		changedWord[i] = wordInput[i];
	}
}// bottome of getWord()

void encryptMessageType::displayChangedWord()
{
	// display changedWord with duplicates removed
	cout << "Your word with its duplicates removed is: " << changedWord << endl << endl;
}// bottom of displayChangedWord()

void encryptMessageType::buildAltAlphabet(int alphLength, char normAlphabet[])
{
	// record the size of the changedWord (need in separate position to keep track of different positions at the same time)
	int size;

	// variable that will save the position of the character inputed to altAlphabet
	int newPosition;

	// find length of the changedWord and store value to sizeOfChangedWord
	sizeOfChangedWord = strlen(changedWord);

	// set size equal to sizeOfChangedWord
	size = sizeOfChangedWord;

	//Set altAlphabet = changedWord
	for (int i = 0; i <= sizeOfChangedWord; i++)
	{
		altAlphabet[i] = changedWord[i];
	}

	// null terminate altAlphabet
	altAlphabet[sizeOfChangedWord] = '\0';

	//Loop that will create the complete altAlphabet by comparing both the changedWord and normAlphabet
	for (int position = 0; position < alphLength; position++)
	{
		//keep track of position whether or not it will be the same or modified later on
		newPosition = position;

		//Loop to compare changedWord to normAlphabet, if any of the characters are equal, modify the position terms
		for (int changedWordPosition = 0; changedWordPosition < size; changedWordPosition++)
		{
			// basically skips over the character if any character in changedWord = normAlphabet
			if (changedWord[changedWordPosition] == normAlphabet[position])
			{
				// changed value to the next character of the normAlphabet
				newPosition += 1;

				// increment position to skip over character
				position += 1;
			}

		}

		// store the character in normAlphabet[newPosition] to altAlphabet[sizeOfChangedWord] 
		// where the following characters will be stored after the previously saved characters of altAlphabet from changedWord 
		altAlphabet[sizeOfChangedWord++] = normAlphabet[newPosition];
	}

	//null terminate altAlphabet in the end
	altAlphabet[alphLength] = '\0';
}// bottom of buildAltAlphabet()

void encryptMessageType::display(char normAlphabet[])
{
	// print out normAlphabet
	cout << "Regular alphabet:   " << normAlphabet << endl << endl;

	// print out altAlphabet
	cout << "Alternate alphabet: " << altAlphabet << endl << endl;

}//bottom of display()

void encryptMessageType::getSentence()
{
	//prompt user to enter a sentence
	cout << "Please enter a sentence: ";

	// Include spaces with cin.get and store the sentence to private member variable sentence
	cin.get(sentence, 99, '\n');

	//Flush memory for extra characters
	cin.ignore(99, '\n');
}// bottom of getSentence()

void encryptMessageType::encryptSentence(char normAlphabet[])
{
	// store the length of the given sentence to sentenceLength
	sentenceLength = strlen(sentence);

	//Loop that will encrypt the sentence by comparing the character positions of the normAlphabet to altAlphabet
	//and storing to sentence the encrypted sentence using the altAlphabet
	for (int i = 0; i <= sentenceLength; i++)
	{
		//z will record the position of the normalAlphabet
		int z = 0;

		//reads characters other than the space, otherwise skips if it is a space
		if (sentence[i] != ' ')
		{
			// if statement that will keep(not alter) the essential punctuations in a sentence, if any
			if (sentence[i] == '!' || sentence[i] == '?' || sentence[i] == '.' || sentence[i] == ',')
				sentence[i] = sentence[i];

			// while the character in sentence[i] doesn't equal the normAlphabet at z
			else {
				// loop that will increment z until sentence[i] = normAlphabet[z] where z will record the position 
				while (sentence[i] != normAlphabet[z])
				{
					z++;
				}

				// set sentence [i] with the character in altAlphabet using the recorded position from the normAlphabet, z
				sentence[i] = altAlphabet[z];
			}

		}

	}

}// bottom of encryptSentence()

void encryptMessageType::displayEncrypt()
{
	//display the changed sentence
	cout << "Your encrypted message: " << sentence << endl << endl;
}// bottom of displayEncrypt()

void encryptMessageType::displayOnFile()
{
	//open an output file named "Lab3b.txt"
	outFile.open("Lab3b.txt");

	//print out changed word onto output file
	outFile << changedWord << endl;

	//print out encrypted sentence onto output file
	outFile << sentence << endl;

	//close output file
	outFile.close();
}// bottom of displayOnFile()

void encryptMessageType::getFromFile()
{
	//declare strings to store text from file
	string word1;
	string phrase;

	// open input file
	inFile.open("Lab3b.txt");

	//read text from file until the end of the file
	do
	{
		//read text from first line of file and store to string word1
		getline(inFile, word1);

		//read text from next line of file and store to string phrase
		getline(inFile, phrase);

	} while (inFile.eof());

	//copy the word1 string into char array charWord
	strcpy_s(charWord, word1.c_str());

	//copy the phrase string to a char array cphrase
	strcpy_s(cphrase, phrase.c_str());

	//close input file
	inFile.close();
}//bottom of getFromFile()
void encryptMessageType::decryptMessage(char normAlphabet[])
{
	//reset string length to the length of the char array cphrase
	stringLength = strlen(cphrase);

	//loop that will decrypt the message back 
	for (int i = 0; i <= stringLength; i++)
	{
		//set position recorder z to 0
		int z = 0;

		// if the character is not a space, change it
		if (cphrase[i] != ' ')
		{
			// if statements that will keep the punctuation the same in the phrase
			if (cphrase[i] == '!' || cphrase[i] == '?' || cphrase[i] == '.' || cphrase[i] == ',')
				cphrase[i] = cphrase[i];

			else
			{
				// if the character does not equal the altAlphabet char at position z
				while (cphrase[i] != altAlphabet[z])
				{
					//increment z until it does
					z++;
				}

				//use position z to set cphrase[i] equal to the normAlphabet at position z to revert back to normal alphabet
				cphrase[i] = normAlphabet[z];
			}

		}

	}

	//display decrypted message
	cout << "Your messsage decrypted:" << endl << cphrase << endl;


}// Bottom of decryptMessage()



