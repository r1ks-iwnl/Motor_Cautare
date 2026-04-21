#include "Document.h"
#include <fstream>
#include <sstream>
#include <iostream>

Document::Document(const std::string& caleFisier) : m_sCaleFisier(caleFisier) {
    incarcaContinut();
}

const std::string& Document::obtineCaleFisier() const {
    return m_sCaleFisier;
}

const std::string& Document::obtineContinut() const {
    return m_sContinut;
}

void Document::incarcaContinut() {
    std::ifstream fisier(m_sCaleFisier);
    if (fisier.is_open()) {
        std::stringstream buffer;
        buffer << fisier.rdbuf();
        m_sContinut = buffer.str();
        fisier.close();
    } else {
        std::cerr << "Nu s-a putut deschide fisierul: " << m_sContinut << std::endl;
    }
}
