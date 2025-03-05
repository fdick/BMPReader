#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;


#pragma once

class BMPReader24BIT
{
private:
    BITMAPFILEHEADER _fileHeader;
    BITMAPINFOHEADER _infoHeader;
    vector<vector<char>> _pixels;
    int width, height;


public:
    ~BMPReader24BIT();

    bool TryLoadFile(const string& fileName);
    void PrintFile();
    void DrawLine(int x1, int y1, int x2, int y2);
    bool TrySaveFile(const string& fileName);
    int GetWidth();
    int GetHeight();



};

