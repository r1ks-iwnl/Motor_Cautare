#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <filesystem>

Logger::Logger(const std::string& logFile) : m_logFile(logFile) {
    m_logStream.open(m_logFile, std::ios_base::app);
    if (!m_logStream.is_open()) {
        std::filesystem::path caleAbsoluta = std::filesystem::absolute(m_logFile);
        std::cerr << "Nu s-a putut deschide fisierul de log: " << caleAbsoluta << std::endl;
    }
}

void Logger::update(const std::string& message) {
    if (m_logStream.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        
        m_logStream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X")
                    << " - " << message << std::endl;
    }
}
