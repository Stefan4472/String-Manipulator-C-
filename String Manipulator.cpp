#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


string GetFileName();
bool ReadFile(string file_name, string &file);
int Menu();
void CharacterCount(string file);
void CharacterFrequency(string file);
int Digits(int n);
void WordCount(string file);
void LineCount(string file_name);
void ForceUpperCase(string file, string file_name);
string NewFile(string file_name, string suffix, string file);
void ForceLowerCase(string file, string file_name);
void CorrectCapitalization(string file, string file_name);
bool isLowerCase(char c);
void FixContractions(string file, string file_name);
int main()
{
	string file = "", file_name;
	int function;
	bool file_exists;
	char keep_going = 0;
	cout << "Stefan's String Manipulator\n";
	cout << "\t\tPress enter\n";
	cin.get();
	do {
	file_name = GetFileName();
	file_exists = ReadFile(file_name, file);
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
		case 8: FixContractions(file, file_name);
				break;
		}
	}
	cout << "\nRun again? (y/n) ";
	cin >> keep_going;
	}while (keep_going == 'y');

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
bool ReadFile(string file_name, string &file) {
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
	cout << "\nAvailable Functions\n";
	cout << "----------------------------------------\n";
	cout << "1. Character Count\n";
	cout << "2. Character Frequency\n";
	cout << "3. Word Count\n";
	cout << "4. Line Count\n";
	cout << "5. Force Upper Case\n";
	cout << "6. Force Lower Case\n";
	cout << "7. Correct capitalization\n";
	cout << "8. Fix Contractions\n";
	/// help function
	cout << "----------------------------------------\n";
	cout << "Enter choice: ";
	cin >> choice;
	cout << endl;
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
		if(file[i] != ' ')
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
void ForceUpperCase(string file, string file_name) {
	int char_value;
	string file_edited = "";
	for(int i = 0; i < file.size(); i++) {
		char_value = int(file[i]);
		if(char_value >= 97 && char_value <= 122)
			char_value = char_value - 32;
		file_edited = file_edited + char(char_value);
	}
	cout << "Edited text: \n";
	cout << file_edited;
	string suffix = "uppercase";
	string new_file_name = NewFile(file_name, suffix, file);
	cout << "New file saved as << " << new_file_name << " >>\n";
}
string NewFile(string file_name, string suffix, string file) {
	/* currently assuming file names don't have an ending */
	string new_file_name = file_name + "_" + suffix;
	ofstream myfile (new_file_name.c_str());
  if (myfile.is_open())
  {
    myfile << file;
    myfile.close();
  }
  else cout << "Unable to open file";
	return new_file_name;
}
void ForceLowerCase(string file, string file_name) {
	int char_value;
	string file_edited = ""; /// new string for file_edited is not necessary
	for(int i = 0; i < file.size(); i++) {
		char_value = int(file[i]);
		if(char_value >= 65 && char_value <= 90)
			char_value = char_value + 32;
		file_edited = file_edited + char(char_value);
	}
	cout << "Edited text: \n";
	cout << file_edited;
	string suffix = "lowercase";
	string new_file_name = NewFile(file_name, suffix, file);
	cout << "New file saved as << " << new_file_name << " >>\n";
}
void CorrectCapitalization(string file, string file_name) {
	for(int i = 0; i < file.size(); i++) {
		if(file[i] == 'i' && file[i - 1] == ' ') { /// won't work if file[0] needs to be capitalized
			if(file[i + 1] == ' ')
				file[i] = 'I';
			else if(int(file[i + 1]) == 39) {
				if(file[i + 2] == 'm' || (file[i + 2] == 'l' && file[i + 3] == 'l') || file[i + 2] == 'd' || (file[i + 2] == 'v' && file[i + 3] == 'e'))
					file[i] = 'I';
			}
		}
		else if(isLowerCase(file[i]) == 1 && file[i - 1] == ' ' && file[i - 2] == '.')
			file[i] = file[i] - 32;
	}
	cout << "Edited text: \n\n";
	cout << file;
}
bool isLowerCase(char c) {
	bool lower = 1;
		if(int(c) >= 65 && int(c) <= 90)
			lower = 0;
	return lower;
}
void FixContractions(string file, string file_name) { /// don't won't can't
	string file_edited;
	for(int i = 0; i < file.size(); i++) {
		if(file[i + 1] == 39) { /// I'd I'll I'm
			if(file[i] == 'I') {
				if(file[i + 2] == 'd')
					file_edited = file_edited + "I would";
				else if(file[i + 2] == 'l' && file[i + 3] == "l")
					file_edited = file_edited + "I will";
				else if(file[i + 2] == 'm')
					file_edited = file_edited + "I am";
				else if(file[i + 2] == 'v' && file[i + 3] == 'e')
					file_edited = file_edited + "I have";
			}
		}
		else if(file[i + 2] == 39) { ///

		}
	}
}
