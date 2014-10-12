#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


string GetFileName();
bool ReadFile(string file_name);
int Menu();
void CharacterCount(string file);
void CharacterFrequency(string file);
int Digits(int n);
void WordCount(string file);
void LineCount(string file_name);
void ForceUpperCase(string file, string file_name);
string NewFileName(string file_name, string function);
void ForceLowerCase(string file, string file_name);
void CorrectCapitalization(string file, string file_name);
int main()
{
	string file = "", file_name;
	int function;
	bool file_exists;
	char keep_going = 0;
	file_name = GetFileName();
	file_exists = ReadFile(file_name);
	if(file_exists) {
		function = Menu();
		switch(function) {
		case 1: CharacterCount(file);
				break;
		case 2: CharacterFrequency(file);
				break;
		case 3: WordCount(file);
				break;
		case 4: LineCount(file_name);
				break;
		case 5: cout << "A new file will be created\n";
				cout << "Continue? (y/n) ";
				cin >> keep_going;
				if(keep_going == 'y')
					ForceUpperCase(file, file_name);
				break;
		case 6: cout << "A new file will be created\n";
				cout << "Continue? (y/n) ";
				cin >> keep_going;
				if(keep_going == 'y')
					ForceLowerCase(file, file_name);
				break;
		case 7: CorrectCapitalization(file, file_name);
				break;

		}
	}

	return 0;
}
string GetFileName() /// possible additions: makes sure file is in the right location
{
	string file_name;
	///cout << "File must be in C:\Users\[Username]\workspace\String Manipulator" << endl;
	cout << "Enter file name: ";
	cin >> file_name;
	return file_name;
}
bool ReadFile(string file_name, string& file) {
	bool file_exists = 1;
	string line;
	  ifstream myfile (file_name.c_str());
	  if (myfile.is_open()) {
	    while ( getline (myfile,line) ) {
	      file = file + line;
	    }
	    myfile.close();
	  }
	  else {
		  cout << "Unable to open file";
		  file_exists = 0;
	  }
	return file_exists;
}
int Menu() {
	int choice;
	cout << "Available Functions\n";
	cout << "----------------------------------------\n";
	cout << "1. Character Count\n";
	cout << "2. Character Frequency\n";
	cout << "3. Word Count\n";
	cout << "4. Line Count\n";
	cout << "5. Force Upper Case\n";
	cout << "6. Force Lower Case\n";
	cout << "7. Correct capitalization\n";
	/// help function
	cout << "----------------------------------------\n";
	cout << "Enter choice: ";
	cin >> choice;
	return choice;
}
void CharacterCount(string file) {
	cout << "File has " << file.size() << " characters\n";
}
void CharacterFrequency(string file) {
	int char_int, unique_chars, size;
	vector<vector<int> > frequencies(255);
	for(int i = 0; i < 255; i++) {
		frequencies[i].resize(2);
	}
	for(int i = 0; i <= 255; i++) {
		frequencies[i][0] = i; /// want 256 x 2 vector
		frequencies[i][1] = 0; /// set char counter to 0
	}
	for(int i = 0; i < file.size(); i++) {
		char_int = int(file[i]);
		for(int j = 0; j <= 255; j++) {
			if(char_int == frequencies[i][0]) {
				frequencies[i][1]++;
				j = 256; /* break loop */
			}
		}
	}
	for(int i = 0; i <= 255; i++) {
		if(frequencies[i][1] > 0)
			unique_chars++;
	}
	cout << unique_chars << " unique characters found.";
		cout << "| Ascii value | Char | Frequency |\n"; /// ADD FORMATTING
		cout << "---------------------------------\n";
		for(int i = 0; i <= 255; i++)
		{
			if(frequencies[i][1] > 0) {
				size = Digits(frequencies[i][0]);
				cout << "|";
				for(int j = 1; j <= 13; j++) {
					if(j == (13 - size) / 2)
						cout << frequencies[i][0]; /* cout ascii value of char */
					else
						cout << " ";
				}
				cout << "|";
				for(int j = 1; j <= 6; j++) {
					if(j == (6 - size) / 2)
						cout << char(frequencies[i][0]); /* cout char */
					else
						cout << " ";
				}
				cout << "|";
				size = Digits(frequencies[i][1]);
				for(int j = 1; j <= 11; j++) {/* currently can only handle values less than 10^11 before table explodes */
										/// add scientific notation for large numbers?
					if(j == (11 - size) / 2)
						cout << frequencies[i][1]; /* cout occurences */
					else
						cout << " ";
				}
				cout << "|\n";
			}
		}
		cout << "---------------------------------\n";
}
int Digits(int n) { /* only for values 0 <= x <= 256 */
	int num_digits;
	if(n >= 0 && n < 10)
		num_digits = 1;
	else if(n >= 10 && n < 100)
		num_digits = 2;
	else
		num_digits = 3;
	return num_digits;
}
void WordCount(string file) {
	int word_counter = 0, first_word;
	bool word = 0;
	first_word = file.find(" ");
	word_counter++;
	for(int i = first_word; i < file.size(); i++) {
		if(file[i] != " ")
			word = 1;
		else {
			word = 0;
			word_counter++;
		}
	}
	cout << "File has " << word_counter << " words\n";
}
void LineCount(string file_name) {
	string line;
	int line_counter = 0;
	  ifstream myfile (file_name.c_str());
	  if (myfile.is_open()) {
	    while ( getline (myfile,line) ) {
	      line_counter++;
	    }
	    myfile.close();
	  }
	  cout << "File has " << line_counter << " lines\n";
}
void ForceUpperCase(string &file, string file_name) {
	int char_value;
	string file_edited = "", new_file_name;
	for(int i = 0; i < file.size(); i++) {
		char_value = int(file[i]);
		if(char_value >= 97 && char_value <= 122)
			char_value = char_value - 32;
		file_edited = file_edited + char(char_value);
	}
	cout << "Edited text: \n";
	cout << file_edited;
	string function = "uppercase";
	new_file_name = NewFileName(file_name, function);
	/// write file with file_edited and new_file_name
}
string NewFileName(string file_name, string function) {
	string new_file_name;
	/* currently assuming file names don't have an ending (like ".txt") */
	new_file_name = file_name + function;
	return new_file_name;
}
void ForceLowerCase(string file, string file_name) {
	int char_value;
	string file_edited = "", new_file_name; /// new string for file_edited is not necessary
	for(int i = 0; i < file.size(); i++) {
		char_value = int(file[i]);
		if(char_value >= 65 && char_value <= 90)
			char_value = char_value + 32;
		file_edited = file_edited + char(char_value);
	}
	cout << "Edited text: \n";
	cout << file_edited;
	string function = "lowercase";
	new_file_name = NewFileName(file_name, function);
	/// write file with file_edited and new_file_name
}
void CorrectCapitalization(string file, string file_name) {
	for(int i = 0; i < file.size(); i++) {
		if(file[i] == "i" && file[i - 1] == " ") { /// won't work if file[0] needs to be capitalized
			if(file[i + 1] == " ")
				file[i] = "I";
			else if(file[i + 1] == "'") {
				if(file[i + 2] == "m" || (file[i + 2] == "l" && file[i + 3] == "l") || file[i + 2] == "d" || (file[i + 2] == "v" && file[i + 3] == "e"))
					file[i] = "I";
			}
	}
}