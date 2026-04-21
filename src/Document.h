#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {
    public:
        Document(const std::string& caleFisier);

        const std::string& obtineCaleFisier() const;
        const std::string& obtineContinut() const;

    private:
        std::string m_sCaleFisier;
        std::string m_sContinut;

        void incarcaContinut();
};

#endif // DOCUMENT_H
