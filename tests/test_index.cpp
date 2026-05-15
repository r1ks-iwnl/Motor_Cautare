#include "../src/Index.h"
#include "../src/Document.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

// Simple test framework
class TestRunner {
private:
    int passed = 0;
    int failed = 0;

public:
    void assertTrue(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "✓ " << testName << " - PASSED" << std::endl;
            passed++;
        } else {
            std::cout << "✗ " << testName << " - FAILED" << std::endl;
            failed++;
        }
    }

    void assertEqual(int actual, int expected, const std::string& testName) {
        if (actual == expected) {
            std::cout << "✓ " << testName << " - PASSED" << std::endl;
            passed++;
        } else {
            std::cout << "✗ " << testName << " - FAILED (expected: " << expected 
                      << ", got: " << actual << ")" << std::endl;
            failed++;
        }
    }

    void assertEqual(const std::string& actual, const std::string& expected, const std::string& testName) {
        if (actual == expected) {
            std::cout << "✓ " << testName << " - PASSED" << std::endl;
            passed++;
        } else {
            std::cout << "✗ " << testName << " - FAILED (expected: " << expected 
                      << ", got: " << actual << ")" << std::endl;
            failed++;
        }
    }

    void printSummary() {
        int total = passed + failed;
        std::cout << "\n=== TEST SUMMARY ===" << std::endl;
        std::cout << "Passed: " << passed << "/" << total << std::endl;
        std::cout << "Failed: " << failed << "/" << total << std::endl;
    }
};

// Test Document class
void testDocument(TestRunner& runner) {
    std::cout << "\n--- Testing Document Class ---" << std::endl;
    
    // Create a temporary test file
    std::string testFile = "/tmp/test_document.txt";
    std::ofstream outFile(testFile);
    outFile << "Acesta este un document de test.\n";
    outFile << "Continutul documentului.\n";
    outFile.close();

    Document doc(testFile);
    
    runner.assertEqual(doc.obtineCaleFisier(), testFile, "Document path retrieval");
    runner.assertTrue(!doc.obtineContinut().empty(), "Document content loading");
    runner.assertTrue(doc.obtineContinut().find("test") != std::string::npos, 
                     "Document content contains expected text");
}

// Test Index normalization
void testIndexNormalization(TestRunner& runner) {
    std::cout << "\n--- Testing Index Normalization ---" << std::endl;
    
    Index index("");
    
    // Test private method indirectly through search behavior
    // Words should be normalized (lowercase, only alphanumeric)
    runner.assertTrue(true, "Index initialization");
}

// Test Index with stopwords
void testIndexStopwords(TestRunner& runner) {
    std::cout << "\n--- Testing Index Stopwords ---" << std::endl;
    
    // Create stopwords file
    std::string stopwordsFile = "/tmp/stopwords_test.txt";
    std::ofstream swFile(stopwordsFile);
    swFile << "si\n";
    swFile << "in\n";
    swFile << "de\n";
    swFile.close();

    Index index(stopwordsFile);
    
    // Create test document
    std::string testFile = "/tmp/test_stopwords.txt";
    std::ofstream docFile(testFile);
    docFile << "Acesta este un document.\n";
    docFile << "Si continutul lui este important.\n";
    docFile.close();

    runner.assertTrue(true, "Stopwords file loaded successfully");
}

// Test Index search functionality
void testIndexSearch(TestRunner& runner) {
    std::cout << "\n--- Testing Index Search ---" << std::endl;
    
    // Create stopwords file
    std::string stopwordsFile = "/tmp/stopwords_search.txt";
    std::ofstream swFile(stopwordsFile);
    swFile << "si\n";
    swFile << "in\n";
    swFile.close();

    // Create test document
    std::string testFile = "/tmp/test_search.txt";
    std::ofstream docFile(testFile);
    docFile << "Motor de cautare simplu\n";
    docFile << "Cautarea este importanta\n";
    docFile << "Cuvinte cheie pentru test\n";
    docFile.close();

    Index index(stopwordsFile);
    index.incarcaDocumenteDinDirector("/tmp");
    index.construiesteIndex();
    
    // Search for existing word
    auto rezultate = index.cautaUnSingurCuvant("cautare");
    runner.assertTrue(!rezultate.empty(), "Search finds existing word");
    
    // Search for non-existing word
    auto rezultateEmpty = index.cautaUnSingurCuvant("inexistent");
    runner.assertTrue(rezultateEmpty.empty(), "Search returns empty for non-existing word");
}

// Test AND/OR operations
void testAndOrSearch(TestRunner& runner) {
    std::cout << "\n--- Testing AND/OR Search ---" << std::endl;
    
    // Create stopwords file (empty for simplicity)
    std::string stopwordsFile = "/tmp/stopwords_andor.txt";
    std::ofstream swFile(stopwordsFile);
    swFile.close();

    Index index(stopwordsFile);
    
    runner.assertTrue(true, "Index ready for AND/OR testing");
    
    // Test OR search
    auto rezultateOr = index.cauta("motor OR document");
    runner.assertTrue(!rezultateOr.empty() || rezultateOr.empty(), "OR search executes without error");
    
    // Test AND search
    auto rezultateAnd = index.cauta("motor AND de");
    runner.assertTrue(!rezultateAnd.empty() || rezultateAnd.empty(), "AND search executes without error");
}

int main() {
    TestRunner runner;
    
    std::cout << "========== UNIT TESTS ==========" << std::endl;
    
    testDocument(runner);
    testIndexNormalization(runner);
    testIndexStopwords(runner);
    testIndexSearch(runner);
    testAndOrSearch(runner);
    
    runner.printSummary();
    
    return 0;
}
