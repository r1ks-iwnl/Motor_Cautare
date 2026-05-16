#include "Index.h"
#include "Logger.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    // Seteaza fereastra
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Motor de Cautare", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Vsync activat

    // Seteaza context ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Stil ImGUI
    ImGui::StyleColorsDark();

    // Seteaza backend Platform/Renderer
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Starea aplicatiei
    Index index("./stopwords.txt");
    Logger logger("./log.txt");
    index.adaugaObserver(&logger);
    
    char folderPath[128] = ".";
    char searchQuery[128] = "";
    std::map<std::string, std::map<std::string, std::vector<int>>> searchResults;
    bool searchPerformed = false;

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // GUI
        ImGui::Begin("Panou de Control");

        ImGui::InputText("Cale Director", folderPath, IM_ARRAYSIZE(folderPath));
        if (ImGui::Button("Incarca si Indexeaza")) {
            index.incarcaDocumenteDinDirector(folderPath);
            index.construiesteIndex();
        }

        ImGui::Separator();

        ImGui::InputText("Interogare Cautare", searchQuery, IM_ARRAYSIZE(searchQuery));
        if (ImGui::Button("Cauta")) {
            searchResults = index.cauta(searchQuery);
            searchPerformed = true;
        }

        ImGui::End();

        // Fereastra rezultate
        ImGui::Begin("Rezultate Cautare");
        if (searchPerformed) {
            if (searchResults.empty()) {
                ImGui::Text("Niciun rezultat gasit.");
            } else {
                for (const auto& [cuvant, docs] : searchResults) {
                    ImGui::Text("Cuvant: %s", cuvant.c_str());
                    for (const auto& [docPath, linii] : docs) {
                        ImGui::Text("  Document: %s", docPath.c_str());
                        ImGui::Text("    Linii: ");
                        ImGui::SameLine();
                        for (size_t i = 0; i < linii.size(); ++i) {
                            ImGui::Text("%d ", linii[i]);
                            if (i < linii.size() - 1) ImGui::SameLine();
                        }
                    }
                }
            }
        }
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Curatare
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
