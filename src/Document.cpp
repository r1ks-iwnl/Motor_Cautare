#include "Document.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

Document::Document(const std::string& caleFisier) : m_caleFisier(caleFisier) {
    incarcaContinut();
}

const std::string& Document::obtineCaleFisier() const {
    return m_caleFisier;
}

const std::string& Document::obtineContinut() const {
    return m_continut;
}

void Document::incarcaContinut() {
    std::ifstream fisier(m_caleFisier);
    if (fisier.is_open()) {
        std::stringstream buffer;
        buffer << fisier.rdbuf();
        m_continut = buffer.str();
        fisier.close();
    } else {
        std::filesystem::path caleAbsoluta = std::filesystem::absolute(m_caleFisier);
        std::cerr << "Nu s-a putut deschide fisierul: " << caleAbsoluta << std::endl;
    }
}
