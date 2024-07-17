#include <fstream>
#include <string>

using namespace std;

void createFile (string name) {
    ofstream newFile;
    newFile.open(name);
    newFile.close();
}