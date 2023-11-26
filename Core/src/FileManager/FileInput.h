#pragma once

#include <fstream>
#include <string>

namespace Velkro
{
    class FileInput
    {
    public:
        FileInput(const std::string& filePath)
            : m_FilePath(filePath)
        {
            m_InputStream.open(filePath);
        }

        ~FileInput()
        {
            if (m_InputStream.is_open())
                m_InputStream.close();
        }

        static FileInput CreateFileInput(const std::string& filePath)
        {
            return FileInput(filePath);
        }

        std::string GetInput()
        {
            std::string input;

            if (m_InputStream.is_open())
            {
                m_InputStream.seekg(0, std::ios::end);
                input.reserve(m_InputStream.tellg());
                m_InputStream.seekg(0, std::ios::beg);

                input.assign((std::istreambuf_iterator<char>(m_InputStream)),
                    std::istreambuf_iterator<char>());
                m_InputStream.close();
            }

            return input;
        }

    private:
        std::string m_FilePath;
        std::ifstream m_InputStream;
    };
}