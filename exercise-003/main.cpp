#include <fmt/chrono.h>
#include <fmt/format.h>

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

#include "CLI/CLI.hpp"
#include "config.h"

// Global variable placed in the data segment
int globalVar = 1;

// Function placed in the code segment
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
    fmt::print("Hello, {}!\n", app.get_name());

    fmt::print("\n-- Random vector + sorting demo --\n");

    // add CLI option: -c, --count
    int count = 20; // default
    app.add_option("-c,--count", count, "Number of random elements (default: 20)")->default_val("20");

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    // Use a const after parsing
    const int finalCount = count;

    // generate random vector of size finalCount with values 1..100
    std::vector<int> values(static_cast<size_t>(finalCount));
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100);
        std::generate(values.begin(), values.end(), [&]() { return dist(gen); });
    }

    // helper to print vector
    auto print_vector = [](const std::vector<int> &v, const std::string &label) {
        fmt::print("{} (size={}): {}\n", label, v.size(), fmt::join(v, ", "));
    };

    print_vector(values, "Unsorted values");

    // measure sort time
    auto start = std::chrono::steady_clock::now();
    std::sort(values.begin(), values.end());
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    print_vector(values, "Sorted values");
    fmt::print("Sorting took {} ms\n", elapsed.count());

    // show address of function in code segment and call it
    fmt::print("Adresse von foo: {}\n", fmt::ptr(&foo));
    foo();

    // Short conclusion (German)
    fmt::print("\nFazit:\n");
    fmt::print("- Globale Variablen (z.B. globalVar) liegen im Data-Segment.\n");
    fmt::print("- Lokale Variablen (z.B. lokal) werden auf dem Stack angelegt.\n");
    fmt::print("- Dynamisch allozierte Variablen (z.B. mit new) liegen im Heap.\n");
    fmt::print("- Funktionen/Code liegen im Code-Segment (Adresse von foo oben).\n");
    fmt::print("\nWarum unterscheidet man Stack und Heap?\n");
    fmt::print("- Stack ist schnell und verwaltet lokale Variablen automatisch beim Funktionsaufruf.\n");
    fmt::print("- Heap erlaubt flexible Lebensdauer und grössere/variable Speicherblöcke, muss aber manuell (oder via RAII) verwaltet werden.\n");
    fmt::print("\nRolle von Referenzen und Zeigern:\n");
    fmt::print("- Zeiger erlauben direkte Adressmanipulation und sind nötig für dynamische Allokation.\n");
    fmt::print("- Referenzen verhalten sich wie Aliase und vereinfachen die Verwendung ohne direkte Zeigerarithmetik.\n");

    return 0; /* exit gracefully*/
}
