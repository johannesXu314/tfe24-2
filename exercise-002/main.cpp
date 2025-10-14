#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/color.h>

#include "CLI/CLI.hpp"
#include "config.h"

// === Teil 1: Globale Variable (Data-Segment) ===
int globalVar = 1;

// === Teil 4: Funktion (Code-Segment) ===
void foo()
{
    fmt::print("Hello from foo!\n");
}

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n\n", app.get_name());

    /* === INSERTED CODE START === */

    fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::cyan), "=== Speichersegmente in C++ ===\n\n");

    // Teil 2: Lokale Variable (Stack)
    int localVar = 2;

    // Teil 3: Dynamisch allozierte Variable (Heap)
    int *heapVar = new int(3);

    // Data-Segment
    fmt::print("Globale Variable (Data-Segment):\n");
    fmt::print("  Wert: {}\n", globalVar);
    fmt::print("  Adresse: {}\n\n", fmt::ptr(&globalVar));

    // Stack
    fmt::print("Lokale Variable (Stack):\n");
    fmt::print("  Wert: {}\n", localVar);
    fmt::print("  Adresse: {}\n\n", fmt::ptr(&localVar));

    // Heap
    fmt::print("Dynamisch allozierte Variable (Heap):\n");
    fmt::print("  Wert: {}\n", *heapVar);
    fmt::print("  Adresse des Zeigers (auf Stack): {}\n", fmt::ptr(&heapVar));
    fmt::print("  Adresse des Werts (im Heap): {}\n\n", fmt::ptr(heapVar));

    // Code-Segment
    fmt::print("Funktion (Code-Segment):\n");
    fmt::print("  Adresse von foo: {}\n\n", fmt::ptr(&foo));

    foo();

    delete heapVar; // Heap-Speicher freigeben

    fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green),
               "\n=== Fazit ===\n"
               "- Globale Variablen → Data-Segment\n"
               "- Lokale Variablen → Stack\n"
               "- Dynamisch allozierte Variablen → Heap\n"
               "- Funktionen → Code-Segment\n");

    /* === INSERTED CODE END === */

    return 0; /* exit gracefully */
}
