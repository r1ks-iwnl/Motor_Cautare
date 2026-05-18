#include "Index.h"
#include "Logger.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <limits.h>
#include <unistd.h>

namespace {

std::filesystem::path obtineDirectorExecutabil() {
    char buffer[PATH_MAX + 1] = {0};
    const ssize_t lungime = ::readlink("/proc/self/exe", buffer, PATH_MAX);
    if (lungime <= 0) {
        return std::filesystem::current_path();
    }

    return std::filesystem::path(std::string(buffer, static_cast<size_t>(lungime))).parent_path();
}

std::string obtineDirectorImplicitCautare() {
    const std::filesystem::path directorExecutabil = obtineDirectorExecutabil();
    const std::filesystem::path directorProiect = directorExecutabil.parent_path().empty()
        ? directorExecutabil
        : directorExecutabil.parent_path();

    return directorProiect.string();
}

} // namespace

int main(int argc, char* argv[]) {
    const std::string directorImplicit = obtineDirectorImplicitCautare();
    const std::filesystem::path caleStopwords = std::filesystem::path(directorImplicit) / "stopwords.txt";

    Logger logger((std::filesystem::path(directorImplicit) / "log.txt").string());
    Index index(caleStopwords.string());
    index.adaugaObserver(&logger);

    std::string directorCautare = directorImplicit;
    if (argc > 1 && argv[1] != nullptr && std::string(argv[1]).size() > 0) {
        directorCautare = argv[1];
    } else {
        std::cout << "Director de cautare [" << directorImplicit << "]: ";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            directorCautare = input;
        }
    }

    std::cout << "Se încarcă documentele din '" << directorCautare << "' și se construiește indexul..." << std::endl;
    index.incarcaDocumenteDinDirector(directorCautare);
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
