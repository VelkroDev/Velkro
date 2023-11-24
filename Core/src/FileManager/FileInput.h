#pragma once

#ifdef VLK_PLATFORM_WINDOWS
#include <filesystem>
#endif

#include <cstdio>

namespace Velkro
{
    class FileInput
    {
    public:
        FileInput(const char* filePath, std::FILE* inputData)
            : m_FilePath(filePath)
        {
            m_InputData = inputData;
        }

        ~FileInput()
        {
            if (m_InputData)
                std::fclose(m_InputData);
        }

        static FileInput LoadFileInput(const char* filePath)
        {
            std::FILE* inputData = std::fopen(filePath, "rb");

            return FileInput(filePath, inputData);
        }

        const char* GetInput()
        {
            std::fseek(m_InputData, 0, SEEK_END);
            long fileSize = std::ftell(m_InputData);
            std::rewind(m_InputData);

            char* buffer = new char[fileSize];
            std::fread(buffer, 1, fileSize, m_InputData);

            std::fclose(m_InputData);

            return buffer;
        }

    private:
        const char* m_FilePath = "";

        std::FILE* m_InputData;
    };
}
