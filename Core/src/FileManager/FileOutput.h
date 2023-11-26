#pragma once

#include <fstream>
#include <string>

namespace Velkro
{
    class FileOutput
    {
    public:
        FileOutput(const std::string& filePath)
            : m_FilePath(filePath)
        {
            m_OutputStream.open(filePath);
        }

        ~FileOutput()
        {
            if (m_OutputStream.is_open())
                m_OutputStream.close();
        }

        static FileOutput CreateFileOutput(const std::string& filePath)
        {
            return FileOutput(filePath);
        }

        void WriteOutput(const std::string& output)
        {
            if (m_OutputStream.is_open())
            {
                m_OutputStream << output;
                m_OutputStream.close();
            }
        }

    private:
        std::string m_FilePath;
        std::ofstream m_OutputStream;
    };
}
