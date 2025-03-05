#include <iostream>
#include <string>
#include "BMPReader24BIT.h"

int main() 
{
    string inputFile, outputFile;
    
    cout << ">>> Enter input BMP file name: ";
    cin >> inputFile;

    BMPReader24BIT bmp;

    if (!bmp.TryLoadFile(inputFile)) 
        return 1;

    bmp.PrintFile();

    bmp.DrawLine(0, 0, bmp.GetWidth() - 1, bmp.GetHeight() - 1);
    bmp.DrawLine(0, bmp.GetHeight() - 1, bmp.GetWidth() -1, 0);

    bmp.PrintFile();

    cout << ">> Enter output BMP file name: ";
    cin >> outputFile;
    
    if (!bmp.TrySaveFile(outputFile))
        return 1;

    return 0;
}
