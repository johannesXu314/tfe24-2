#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    int x = 10;
    int& r = x;

    // --- Aufgabe: Übergabe per Parameter vs. Referenz

    // Teil: Funktionen definieren (hier lokal vor der Nutzung)
    auto changeValueByParameter = [](int value) {
        value = 99;
        fmt::print("Inside changeValueByParameter: value = {}\n", value);
    };

    auto changeValueByReference = [](int &ref) {
        ref = 77;
        fmt::print("Inside changeValueByReference: ref = {}\n", ref);
    };

    // Vergleichsbeispiel
    int y = 5;
    fmt::print("y before changeValueByParameter: {}\n", y);
    changeValueByParameter(y);
    fmt::print("y after changeValueByParameter: {}\n", y);

    fmt::print("\n");

    fmt::print("y before changeValueByReference: {}\n", y);
    changeValueByReference(y);
    fmt::print("y after changeValueByReference: {}\n", y);

    return 0; /* exit gracefully*/
}
