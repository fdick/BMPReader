#include "BMPReader24BIT.h"


    BMPReader24BIT::~BMPReader24BIT()
    {
        _pixels.clear();
    };

    bool BMPReader24BIT::TryLoadFile(const string& fileName)
    {
        ifstream file(fileName, ios::binary);

        if (!file)
        {
            cerr << "File is not load!\n";
            return false;
        }

        //read headers
        file.read(reinterpret_cast<char*>(&_fileHeader), sizeof(_fileHeader));
        file.read(reinterpret_cast<char*>(&_infoHeader), sizeof(_infoHeader));

        if (_infoHeader.biBitCount != 24)
        {
            cerr << "Use 24-bit BMP file!\n";
            return false;
        }

        width = _infoHeader.biWidth;
        //height = abs(_infoHeader.biHeight);
        height = _infoHeader.biHeight;

        //rgb - 3 bytes / channels
        _pixels.resize(height, vector<char>(width * 3));

        //round operation before 4 bcz (rgba)
        int rowSize = ((_infoHeader.biBitCount / 8) * width) / 4 * 4;

        //read all pixels from file
        for (int i = 0; i < height; ++i)
        {
            file.read(_pixels[i].data(), rowSize);
        }

        file.close();
        return true;
    }

    void BMPReader24BIT::PrintFile()
    {
        for (int i = height - 1; i >= 0; --i)
        {
            for (int j = 0; j < width * 3; j += 3)
            {
                if (_pixels[i][j] == 0 && _pixels[i][j + 1] == 0 && _pixels[i][j + 2] == 0)
                    cout << "#";
                else
                    cout << " ";
            }
            cout << "\n";
        }
    }

    void BMPReader24BIT::DrawLine(int x1, int y1, int x2, int y2)
    {
        int dx = abs(x2 - x1);
        int ddx = x1 < x2 ? 1 : -1;

        int dy = -abs(y2 - y1);
        int ddy = y1 < y2 ? 1 : -1;

        int err = dx + dy;

        while (x1 != x2 && y1 != y2)
        {
            _pixels[y1][x1 * 3] = 0;
            _pixels[y1][x1 * 3 + 1] = 0;
            _pixels[y1][x1 * 3 + 2] = 0;

            int e2 = 2 * err;

            if (e2 >= dy)
            {
                err += dy;
                x1 += ddx;
            }

            if (e2 <= dx)
            {
                err += dx;
                y1 += ddy;
            }
        }
    }


    bool BMPReader24BIT::TrySaveFile(const string& fileName)
    {
        ofstream file(fileName, ios::binary);

        if (!file)
        {
            cerr << "File is not saved!\n";
            return false;
        }

        file.write(reinterpret_cast<char*>(&_fileHeader), sizeof(_fileHeader));
        file.write(reinterpret_cast<char*>(&_infoHeader), sizeof(_infoHeader));

        int rowSize = ((_infoHeader.biBitCount / 8) * width) / 4 * 4;

        for (int i = 0; i < height; ++i)
        {
            file.write(_pixels[i].data(), rowSize);
        }

        file.close();
        return true;
    }

    int BMPReader24BIT::GetWidth() { return width; }
    int BMPReader24BIT::GetHeight() { return height; }
