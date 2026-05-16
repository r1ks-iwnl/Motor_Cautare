#include "Index.h"
#include "Logger.h"

#include <iostream>
#include <string>

int main() {
    Logger logger("log.txt");
    Index index("./stopwords.txt");
    index.adaugaObserver(&logger);

    std::cout << "Se încarcă documentele și se construiește indexul..." << std::endl;
    index.incarcaDocumenteDinDirector(".");
    index.construiesteIndex();
    std::cout << "Indexare finalizată." << std::endl;

    std::string query;
    while (true) {
        std::cout << "\nIntroduceți interogarea de căutare (sau 'exit' pentru a ieși): ";
        std::getline(std::cin, query);

        if (query == "exit") {
            break;
        }

        if (query.empty()) {
            continue;
        }

        const auto rezultate = index.cauta(query);

        std::cout << "Rezultate pentru query-ul '" << query << "':" << std::endl;
        if (rezultate.empty()) {
            std::cout << "Niciun document gasit." << std::endl;
        } else {
            std::map<std::string, std::vector<std::pair<std::string, std::vector<int>>>> documenteAfisate;
            for (const auto& [cuvant, docs] : rezultate) {
                for (const auto& [doc, linii] : docs) {
                    documenteAfisate[doc].push_back({cuvant, linii});
                }
            }

            for (const auto& [doc, detalii] : documenteAfisate) {
                std::cout << "- " << doc << ":" << std::endl;
                for (const auto& pereche : detalii) {
                    std::cout << "  - Cuvantul '" << pereche.first << "' gasit pe liniile: ";
                    for (size_t i = 0; i < pereche.second.size(); ++i) {
                        std::cout << pereche.second[i] << (i < pereche.second.size() - 1 ? ", " : "");
                    }
                    std::cout << std::endl;
                }
            }
        }
    }

    return 0;
}
