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

            if (!m_InputStream.is_open())
            {
                VLK_CORE_ERROR("Unable to open file \"{0}\", file doesn't exist.", filePath);
            }
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