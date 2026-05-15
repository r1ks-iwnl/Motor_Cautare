#ifndef INDEX_H
#define INDEX_H

#include "Document.h"
#include "Observable.h"

#include <map>
#include <string>
#include <vector>
#include <unordered_set>

class Index : public Observable {
public:
    explicit Index(const std::string& stopwordsPath);
    void incarcaDocumenteDinDirector(const std::string& caleDirector);
    void construiesteIndex();
    std::map<std::string, std::map<std::string, std::vector<int>>> cauta(const std::string& query);
    std::map<std::string, std::vector<int>> cautaUnSingurCuvant(const std::string& cuvant);
    std::vector<Document>& obtineDocumente();

private:
    std::vector<Document> m_documente;
    std::map<std::string, std::map<std::string, std::vector<int>>> m_index;
    std::unordered_set<std::string> m_stopwords;

    void incarcaStopwords(const std::string& caleFisier);
    static std::string normalizeazaCuvant(const std::string& cuvant);
    static bool esteFisierText(const std::string& caleFisier);
};

#endif // INDEX_H
