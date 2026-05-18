# Motor de Cautare

Acesta este un proiect simplu de motor de căutare în C++, care indexează fișiere text dintr-un director și permite utilizatorului să caute cuvinte în acele fișiere. Proiectul include o interfață de linie de comandă, cât și o interfață grafică construită cu ImGui.

## Caracteristici

*   Indexarea cuvintelor din fișiere text.
*   Căutarea cuvintelor și afișarea documentelor și a liniilor unde apar.
*   Gestionarea "stopwords".
*   Interfață grafică.
*   Logging-ul acțiunilor într-un fișier `log.txt` folosind modelul de proiectare Observer.

## Dependințe

Pentru a compila și rula acest proiect, veți avea nevoie de următoarele:

*   **Git**
*   **CMake** (versiunea 3.10 sau mai recentă)
*   **Un compilator C++17** (de ex., GCC, Clang)
*   **OpenGL**
*   **GLFW**

Funcționalitatea ImGUI și dependențele relevante pot fi ignorate comentând/eliminând liniile 9-29 din CMakeLists.txt

### Instalarea Dependințelor 

Puteți instala majoritatea dependențelor folosind managerul de pachete `apt`:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake git libglfw3-dev libopengl-dev
```

## Compilare și Rulare

1. **Clonați repository-ul**

   Clonați repository-ul și submodulele sale (`imgui`) folosind comanda `--recurse-submodules`:

   ```bash
   git clone --recurse-submodules <url-repository>
   cd POO_MotorCautare
   ```

   Dacă ați clonat deja proiectul fără submodule, rulați:
   ```bash
   git submodule update --init --recursive
   ```

2. **Configurați și construiți proiectul**

   Proiectul se compilează cu CMake:

   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
   cmake --build build
   ```

3. **Rulați aplicația**

   Executabilele vor fi create în directorul `build`.

   * **Versiunea CLI:**
     ```bash
     ./build/motor_cautare_cli
       ./build/motor_cautare_cli path
     ```
       Dacă nu dați niciun argument ca path, programul folosește implicit directorul proiectului, iar la pornire puteți introduce o cale diferită.

   * **Versiunea GUI:**
     ```bash
     ./build/motor_cautare_gui
     ```

4. **Rulați testele unitare**

   Testele sunt simple și pot fi rulate local cu:
   ```bash
   ./build/test_index
   ```

## Organizarea Documentației

Documentația extinsă este în [docs/Documentatie.md](docs/Documentatie.md). Aceasta include descrierea claselor, conceptele POO utilizate, diagrama UML și optimizările aplicate.

## Integrare GitHub Actions

Repository-ul include workflow-ul [tests.yml](.github/workflows/tests.yml), care compilează proiectul și rulează automat testele prin `ctest` la fiecare `push` sau `pull_request` pe branch-urile `main`, `master` și `develop`.
