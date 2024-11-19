//
// Created by Mustafa Mert Aladağ on 19.11.2024.
//

#ifndef __TEXTREADER_H__
#define __TEXTREADER_H__

#include <string>
#include <fstream>
#include <iostream>
#include "Utils.h"

#define BUFFER_SIZE 4096

class TextReader
{
public:
    TextReader(const std::string& path)
    {
        this->m_path = path;
    }

    std::string read()
    {
        std::ifstream file(m_path, std::ios::binary);
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
                std::cerr << "Error reading file: " << m_path << std::endl;
                return "";
            }

            str.append(buffer, file.gcount());
        }
        else
        {
            std::cerr << "Unable to open file: " << m_path << std::endl;
            return "";
        }
        return str;
    }

private:
    std::string m_path;
};


#endif //__TEXTREADER_H__
