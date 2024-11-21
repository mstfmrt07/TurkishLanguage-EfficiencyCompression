//
// Created by Mustafa Mert Aladağ on 19.11.2024.
//

#ifndef __TEXTOPERATIONS_H__
#define __TEXTOPERATIONS_H__

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <codecvt>

#include "Utils.h"

#define BUFFER_SIZE 4096

class TextOperations
{
public:

    static std::string read(std::string filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        std::string str;
        char buffer[BUFFER_SIZE];

        if (file.is_open())
        {
            while (file.read(buffer, BUFFER_SIZE))
            {
                str.append(buffer, file.gcount());
            }

            if (file.bad())
            {
                std::cerr << "Error reading file: " << filePath << std::endl;
                file.close();
                return "";
            }

            str.append(buffer, file.gcount());
            file.close();
            return str;
        }
        else
        {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return "";
        }
    }

    static bool write(const std::string& str, const std::string& filePath)
    {
        std::ofstream file(filePath, std::ios::binary);
        if (file.is_open())
        {
            file.write(str.c_str(), str.size());
            file.close();
            return true;
        }
        else
        {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return false;
        }
    }



    static std::string wstring_to_utf8(const std::wstring& wstr)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }


    static std::wstring utf8_to_wstring(std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }

    static std::string filterTurkishText(std::wstring& text)
    {
        const std::wstring turkishAlphabet = L"abcçdefgğhıijklmnoöprsştuüvyz";

         std::map<wchar_t, wchar_t> lowerCaseMap = {
                {L'A', L'a'}, {L'B', L'b'}, {L'C', L'c'}, {L'Ç', L'ç'}, {L'D', L'd'}, {L'E', L'e'},
                {L'F', L'f'}, {L'G', L'g'}, {L'Ğ', L'ğ'}, {L'H', L'h'}, {L'I', L'ı'}, {L'İ', L'i'},
                {L'J', L'j'}, {L'K', L'k'}, {L'L', L'l'}, {L'M', L'm'}, {L'N', L'n'}, {L'O', L'o'},
                {L'Ö', L'ö'}, {L'P', L'p'}, {L'R', L'r'}, {L'S', L's'}, {L'Ş', L'ş'}, {L'T', L't'},
                {L'U', L'u'}, {L'Ü', L'ü'}, {L'V', L'v'}, {L'Y', L'y'}, {L'Z', L'z'}
        };

        std::wstring filteredText;

        bool spaceEncountered = false;
        for (wchar_t c: text)
        {
            if (turkishAlphabet.find(c) != std::string::npos)
            {
                filteredText.push_back(c);
                spaceEncountered = false;
            }
            else if (lowerCaseMap.find(c) != lowerCaseMap.end())
            {
                filteredText.push_back(lowerCaseMap[c]);
                spaceEncountered = false;
            }
            else if (c == L' ' && !spaceEncountered) // Logic for skipping multiple spaces
            {
                filteredText.push_back(c);
                spaceEncountered = true;
            }
        }

        std::string utf8_filtered_text = wstring_to_utf8(filteredText);
        return utf8_filtered_text;
    }
};


#endif //__TEXTOPERATIONS_H__
