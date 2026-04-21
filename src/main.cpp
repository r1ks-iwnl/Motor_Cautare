#include <iostream>
#include "Document.h"

int main() {
    Document doc("../test.txt");
    std::cout << "Cale fisier: " << doc.obtineCaleFisier() << std::endl;
    std::cout << "Continut:" << std::endl;
    std::cout << doc.obtineContinut() << std::endl;
    return 0;
}
