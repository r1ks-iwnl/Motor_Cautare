#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
//cum functioneaza pt. documente extreme
#include "Observable.h"

class Document : public Observable {
public:
    void notificaCautare(const std::string& cuvant) {
        notifica("S-a cautat cuvantul: " + cuvant);
    }
        Document(const std::string& caleFisier);
        //referinta, read-only
        const std::string& obtineCaleFisier() const;
        const std::string& obtineContinut() const;

    private:
        std::string m_caleFisier;
        std::string m_continut;

        void incarcaContinut();
};

#endif // DOCUMENT_H
