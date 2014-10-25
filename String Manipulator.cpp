#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;


string GetFileName();
void GetText(string &file, string &file_name);
bool ReadFile(string file_name, string &file);
int Menu();
void CharacterCount(string file);
void CharacterFrequency(string file);
int Digits(int n);
void WordCount(string file);
void LineCount(string file_name);
void ForceUpperCase(string file, string file_name, int parameters [1]);
void NewFile(string file_name, string suffix, string file);
void ForceLowerCase(string file, string file_name, int parameters [1]);
void CorrectCapitalization(string file, string file_name, int parameters [1]);
bool isLowerCase(char c);
void FixContractions(string file, string file_name, int parameters [1]);
bool isWord(string word, int start_location, string file);
bool isUpperCase(char c);
void WordFrequency(string file);
void CaesarShift(string file, string file_name, int shift, bool direction, int parameters [1]);
bool isLetter(char c);
void Accents(string file);
void Settings(int parameters [1]);
int StringToInt(string s);
string IntToString(int b);
int main()
{
	string file = "", file_name = "";
	int function, shift;
	bool file_exists, file_loaded;
	char keep_going = 0;
	int parameters [1];
	cout << "Plain+Simple String Manipulator v. 0.3\n";
	string line;
	ifstream myfile ("file_name");
	if (myfile.is_open()) {
		file_loaded = 1;
		while ( getline (myfile,line) ) {
		     file_name = file_name + line;
		}
		myfile.close();
	 }
	if(file_loaded) {
		cout << "Current file loaded is << " << file_name << " >> \n";
		ifstream myfile (file_name.c_str());
			if (myfile.is_open()) {
				while ( getline (myfile,line) ) {
				     file = file + line;
				}
				myfile.close();
			 }
	}

	cout << "\t    Press enter\n";
	cin.get();
	do {
		function = Menu();
		switch(function) {
		case -1: GetText(file, file_name);
				break;
		case 0: file_name = GetFileName();
				file_exists = ReadFile(file_name, file);
				if(!(file_exists))
					cout << "Error: Invalid file entered.\n\n";
				break;
		case 1: CharacterCount(file);
				break;
		case 2: CharacterFrequency(file);
				break;
		case 3: WordCount(file);
				break;
		case 4: LineCount(file_name);
				break;
		case 5: ForceUpperCase(file, file_name, parameters);
				break;
		case 6:	ForceLowerCase(file, file_name, parameters);
				break;
		case 7: CorrectCapitalization(file, file_name, parameters);
				break;
		case 8: FixContractions(file, file_name, parameters);
				break;
		case 9: WordFrequency(file);
				break;
		case 10: cout << "Enter number of letters to shift by: ";
				cin >> shift;
				CaesarShift(file, file_name, shift, 1, parameters);
				break;
		case 11: cout << "Enter original shift: ";
				cin >> shift;
				shift = shift * -1;
				CaesarShift(file, file_name, shift, -1, parameters);
				break;
		case 12: Accents(file);
				break;
		case 13: Settings(parameters);
				break;
	}
	cout << "\nRun again? (y/n) ";
	cin >> keep_going;
	if(keep_going != 'y') {
		ofstream newFile("file_name");
		    if(newFile.is_open()) {
		        newFile << file_name;
		    }
		    else {
		       cout << "Error saving file name\n";
		    }
		    newFile.close();
	}
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
void GetText(string &file, string &file_name) {
	char answer;
	cout << "Enter text: ";
	getline(cin, file);
	getline(cin, file); // we need a second one because the first one is automatically ignored
	cout << "Write text to file? (y/n) ";
	cin >> answer;
	if(answer == 'y') {
		cout << "Enter name of file to be created: ";
		cin >> file_name;
		ofstream new_file(file_name.c_str());
			if(new_file.is_open())
				new_file << file;
			else
				cout << "Unable to open file";
	}
	else {
		ofstream temp_text ("stringmanipulator_text");
	  if (temp_text.is_open())
	  {
	    temp_text << file;
	    file_name = "stringmanipulator_text";
	  }
	  else cout << "Unable to open file";
	}
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
	cout << "\nAvailable Functions\n"; /// these will most likely be arranged
										/// and changed later on
	cout << "----------------------------------------\n";
	cout << "-1. Manually enter text\n";
	cout << "0. Choose File\n";
	cout << "1. Character Count\n";
	cout << "2. Character Frequency\n";
	cout << "3. Word Count\n";
	cout << "4. Line Count\n";
	cout << "5. Force Upper Case\n";
	cout << "6. Force Lower Case\n";
	cout << "7. Correct capitalization\n";
	cout << "8. Fix Contractions\n";
	cout << "9. Word Frequency\n";
	cout << "10. Encode Caesar Shift\n";
	cout << "11. Decode Caesar Shift\n";
	cout << "12. Use Accents\n";
	cout << "13. Options\n";
	cout << "14. Help\n"; /// hasn't been written yet
	/// help function
	/// options function : create new file? overwrite existing file?
	cout << "----------------------------------------\n";
	cout << "Enter choice: ";
	cin >> choice;
	cout << endl;
	return choice;
}
void CharacterCount(string file) {
	int char_count = 0;
	cout << "File has " << file.size() << " characters, ";
	for(int i = 0; i < file.size(); i++) {
		if(file[i] != 32)
			char_count++;
	}
	cout << char_count << " not including spaces\n";
}
void CharacterFrequency(string file) {
	int char_int, unique_chars = 0, size = 0;
	int char_list [255];
	int frequencies[255];
	for(int i = 0; i < 255; i++) {
		char_list[i] = i;
		frequencies[i] = 0;
	}
	for(int i = 32; i < file.size(); i++) {
		char_int = int(file[i]);
		frequencies[char_int]++;
	}
	for(int i = 32; i <= 255; i++) {
		if(frequencies[i] > 0)
			unique_chars++;
	}
	cout << unique_chars << " unique characters found.\n\n";
		cout << "| Ascii value | Char | Frequency |\n";
		cout << "---------------------------------\n";
		for(int i = 32; i <= 255; i++)
		{
			if(frequencies[i] > 0) {
				size = Digits(char_list[i]);
				cout << "|";
				for(int j = 1; j <= (13 - size)/ 2 + 1; j++) {
					if(j == (13 - size) / 2 + 1)
						cout << char_list[i]; /* cout ascii value of char */
					else
						cout << " ";
				}
				if(size == 1)
					cout << "       ";
				else if(size == 2)
					cout << "      ";
				else
					cout << "     ";
				cout << "|";
				for(int j = 1; j <= 6; j++) {
					if(j == 4)
						cout << char(char_list[i]); /* cout char */
					else
						cout << " ";
				}
				cout << "|";
				size = Digits(frequencies[i]);
				for(int j = 1; j <= 11; j++) {/* currently can only handle values less than 10^11 before table explodes */
										/// add scientific notation for large numbers?
					if(j == (11 - size) / 2 + 1)
						cout << frequencies[i]; /* cout occurences */
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
void WordCount(string file) { // improve definition of "word"
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
void ForceUpperCase(string file, string file_name, int parameters [1]) {
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
	if(parameters[0] == 1)
		NewFile(file_name, "uppercase", file_edited);

}
void NewFile(string file_name, string suffix, string file) {
	/* currently assuming file names don't have an ending */
	string new_file_name = file_name + "_" + suffix;
	ofstream myfile (new_file_name.c_str());
  if (myfile.is_open())
  {
    myfile << file;
    cout << "New file saved as << " << new_file_name << " >>\n";
  }
  else cout << "Error creating new file";
  myfile.close();
}
void ForceLowerCase(string file, string file_name, int parameters [1]) {
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
	if(parameters[0] == 1)
		NewFile(file_name, "lowercase", file_edited);
}
void CorrectCapitalization(string file, string file_name, int parameters [1]) { // implement arrays, like with FixContractions
	if(isLowerCase(file[0]))
		file[0] = file[0] - 32;
	for(int i = 0; i < file.size(); i++) {
		if(file[i] == 'i' && file[i - 1] == ' ') { /// won't work if file[0] needs to be capitalized
			if(file[i + 1] == ' ')
				file[i] = 'I';
			else if(int(file[i + 1]) == 39) {
				if(file[i + 2] == 'm' || (file[i + 2] == 'l' && file[i + 3] == 'l') || file[i + 2] == 'd' || (file[i + 2] == 'v' && file[i + 3] == 'e'))
					file[i] = 'I';
			}
		}
		else if(isLowerCase(file[i]) == 1 && file[i - 1] == ' ')
			if(file[i - 2] == '.' || file[i - 2] == '!' || file[i - 2] == '?')
				file[i] = file[i] - 32;
	}
	cout << "Edited text: \n\n";
	cout << file;
	if(parameters[0] == 1)
		NewFile(file_name, "capitalized", file);
}
bool isLowerCase(char c) {
	bool lower = 1;
		if(int(c) >= 65 && int(c) <= 90)
			lower = 0;
	return lower;
}
void FixContractions(string file, string file_name, int parameters [1]) { // buggy
	string file_edited, c, file_new = "";
	string contractions [12] = {"aren't","can't","couldn't","didn't","doesn't","don't","handn't","hasn't","haven't","he'd","he'll","he's"};
	string contracted [12] = {"are not","cannot","could not","did not","does not","do not","had not","has not", "have not", "he would", "he will", "he is"};
	for(int i = 0; i < file.size(); i++) {
		for(int j = 0; j < 12; j++) {
			c = contractions[j];
			///cout << "contractions [" << j << "] = " << c << endl;;
			///b = isWord(c, i, file);
			///if(b)
				///cout << "isWord (" << c << "," << i << ") = " <<  b << endl;
			if(isWord(c, i, file)) {
				///cout << "isWord is true\n";
				file_edited = file_edited + contracted[j];
				j = 12;
				i = i + c.size() - 1;
			}
			else if(j == 11)
					file_edited = file_edited + file[i];
			}
		}
	cout << "Edited text: \n\n";
	cout << file_edited;
	if(parameters[0] == 1)
		NewFile(file_name, "uncontracted", file_edited);

}
bool isWord(string word, int start_location, string file) { /// possible problems
	for(int i = start_location; i < start_location + word.size(); i++) {
		if(file[i] != word[i])
			return 0;
	}
	return 1;
}
bool isUpperCase(char c) {
	bool upper = 1;
		if(int(c) >= 97 && int(c) <= 122)
			upper = 0;
	return upper;
}
void WordFrequency(string file) {
	vector<string> words; /* empty vector */
	vector<int> frequencies; /* empty vector */
	int end_location;
	string word = "", compare;
	int first_word = file.find(" ");
	for(int i = 0; i < first_word; i++)
		word = word + file[i];
///	cout << word << endl;
	words.push_back(word);
///	cout << words[0] << endl;;
	frequencies.push_back(1);
///	cout << frequencies[0] << endl;
	for(int i = first_word; i < file.size(); i++) {
		cout << "hello " << i << endl;
			word = ""; /* reinitialize 'word' each time */
			for(int j = i; j < file.size(); j++) { /* scan for the next space */
				if(file[j] == 32) {
					end_location = j;
					cout << "end_location = " << end_location << endl;
					i = end_location;
					j = file.size();
				}
				else
					word = word + file[j];
			for(int k = 0; k < words.size(); k++) { /* scan vector of words, look for a match */
				compare = words[k];
				if(word == compare) {
					cout << "<< " << word << " >> added.\n";
					cout << "words[" << k << "] = " << words[k] << endl;
					frequencies[k]++;
					cout << "frequencies[" << k << "] = " << frequencies[k] << endl;
					k = words.size();
				}
				else {
					words.push_back(word); /* if no match, add this word to the list */
					frequencies.push_back(1);
				}
			}
		}
	}
	for(int i = 0; i < words.size(); i++) {
		cout << words[i] << "    |    " << frequencies[i] << endl;
	}
}
void CaesarShift(string file, string file_name, int shift, bool direction, int parameters [1]) {
	char letters [52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int location = 0;
	if(direction == 1) {
			cout << "Encoded Text: \n\n";
	}
	else {
		cout << "Decoded Text: \n\n";
	}
	for(int i = 0; i < file.size(); i++) {
		if(isLetter(file[i])) {
			for(int j = 0; j < 52; j++) {
				if(file[i] == letters[j]) {
					location = (j + shift) % 52;
					if(shift < 0)
						location = location * -1;
					j = 52;
				}
			}
			file[i] = letters[location];
		}
	}
	cout << file;
	if(parameters[0] == 1 && direction > 0)
		NewFile(file_name, "encoded", file);
	else if(parameters[0] == 1 && direction < 0)
		NewFile(file_name, "decoded", file);
}
bool isLetter(char c) {
	if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return 1;
	return 0;
}
void Accents(string file) { /// in Java/Android we would *REALLY* want either buttons or event listeners to write accented chars
	cout << "^a -> " << char(131) << endl; /// perhaps two separate functions: one in which you can read a file and convert
	cout << ":a -> " << char(132) << endl; /// to accents, one where you can type accents live
	cout << "'a -> " << char(133) << endl; // wrong ascii values - need to find correct table
}
void Settings(int parameters [1]) {
	string line, string_parameters = "";
	int parameter_num;
	ifstream file_parameters ("stringmanipulator_parameters");
		if (file_parameters.is_open()) {
			while ( getline (file_parameters,line) ) {
			     for(int i = 0; i < line.size(); i++) {
			    	 parameters[i] = int(line[i]) - 48;
			    	 cout << "parameters[" << i << "] = " << parameters[i] << endl;
			     }
			}
			file_parameters.close();
		 }
		else {
			parameters[0] = 1;
		}
	cout << "Settings:\n";
	cout << "------------------------------------------------\n";
	cout << "1. Write edited text to new file.........";
		if(parameters[0] == 1)
			cout << "TRUE\n";
		else
			cout << "FALSE\n";
	cout << "------------------------------------------------\n";
	cout << "Enter the number of the option you would like to change: ";
	cin >> parameter_num;
	cout << "0. " << parameters[parameter_num] << endl;
	if(parameters[parameter_num] = 1)
		parameters[parameter_num] = 0;
	else
		parameters[parameter_num] = 1;
	cout << "1." << parameters[parameter_num] << endl;
	cout << "Option " << parameter_num << " set to << ";
	if(parameters[parameter_num] == 1) {
		cout << "TRUE";
	}
	else
		cout << "FALSE";
	cout << "2. " << parameters[parameter_num] << endl;
	cout <<  " >>\n";
	char c;
	for(int i = 0; i < 1; i++) {
		if(parameters[i] == 1)
			c = '1';
		else
			c = '0';
		string_parameters = string_parameters + c; /// for some reason I just CANT get this to work. It's stuck on TRUE
		cout << "3. " << string_parameters << endl;
	}
	cout << "4." << string_parameters << endl;
	ofstream parameters_file("stringmanipulator_parameters");
			    if(parameters_file.is_open()) {
			        parameters_file << string_parameters;
			    }
			    parameters_file.close();
}
int StringToInt(string s) {
	int num;
	for(int i = 0; i < s.size(); i++)
		num = num * 10 + (s[i] - '0');
	return num;
}
string IntToString(int b) {
	if(b == 0)
		return "0";
	else
		return "1";
}
