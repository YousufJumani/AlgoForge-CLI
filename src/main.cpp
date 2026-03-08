#include <algorithm>
#include <cctype>
#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using AlgoFn = std::function<void(std::vector<int>&)>;

static std::vector<int> generateRandomInput(size_t n, int minValue, int maxValue, unsigned int seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    std::vector<int> values(n);
    for (size_t i = 0; i < n; ++i) values[i] = dist(rng);
    return values;
}

static void runSort(std::vector<int> &data) {
    std::sort(data.begin(), data.end());
}

static void runStableSort(std::vector<int> &data) {
    std::stable_sort(data.begin(), data.end());
}

static void runPrefixSum(std::vector<int> &data) {
    std::partial_sum(data.begin(), data.end(), data.begin());
}

static bool isSortedNonDecreasing(const std::vector<int> &data) {
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i - 1] > data[i]) return false;
    }
    return true;
}

static void printComplexityReport() {
    std::cout << "\nComplexity Report\n";
    std::cout << "- sort        : O(n log n) average/worst\n";
    std::cout << "- stable_sort : O(n log n) average/worst\n";
    std::cout << "- prefix_sum  : O(n)\n";
}

static void printUsage() {
    std::cout << "AlgoForge CLI\n";
    std::cout << "Usage:\n";
    std::cout << "  algoforge <algorithm> <size> [seed] [--profile] [--memory]\n";
    std::cout << "Algorithms: sort, stable_sort, prefix_sum\n";
}

static void waitForExit() {
    std::cout << "\nPress Enter to exit...";
    std::string ignore;
    std::getline(std::cin, ignore);
}

static bool isYes(const std::string &value) {
    return value == "y" || value == "Y" || value == "yes" || value == "YES";
}

static std::string normalizeAlgorithm(std::string value) {
    size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }

    size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    value = value.substr(start, end - start);
    for (char &c : value) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return value;
}

int main(int argc, char **argv) {
    size_t size = 0;
    unsigned int seed = 42;
    std::string algorithm;
    bool profile = false;
    bool memory = false;
    bool interactiveMode = (argc < 3);

    if (interactiveMode) {
        std::cout << "AlgoForge Interactive Mode\n";
        std::cout << "(Tip: press Enter to use defaults)\n";
        printUsage();

        std::cout << "\nAlgorithm (sort / stable_sort / prefix_sum): ";
        std::getline(std::cin, algorithm);
        if (algorithm.empty()) algorithm = "sort";
        algorithm = normalizeAlgorithm(algorithm);

        std::cout << "Input size (default 10000): ";
        std::string sizeRaw;
        std::getline(std::cin, sizeRaw);
        if (sizeRaw.empty()) sizeRaw = "10000";

        std::cout << "Seed (default 42): ";
        std::string seedRaw;
        std::getline(std::cin, seedRaw);
        if (seedRaw.empty()) seedRaw = "42";

        std::cout << "Enable profiling? (y/n, default y): ";
        std::string profileRaw;
        std::getline(std::cin, profileRaw);
        profile = profileRaw.empty() || isYes(profileRaw);

        std::cout << "Enable memory estimate? (y/n, default n): ";
        std::string memoryRaw;
        std::getline(std::cin, memoryRaw);
        memory = isYes(memoryRaw);

        try {
            size = static_cast<size_t>(std::stoull(sizeRaw));
            seed = static_cast<unsigned int>(std::stoul(seedRaw));
        } catch (...) {
            std::cout << "Invalid numeric input in interactive mode.\n";
            waitForExit();
            return 1;
        }
    } else {
        algorithm = normalizeAlgorithm(argv[1]);
        for (int i = 3; i < argc; ++i) {
            std::string flag = argv[i];
            if (flag == "--profile") profile = true;
            if (flag == "--memory") memory = true;
        }

        try {
            size = static_cast<size_t>(std::stoull(argv[2]));
            if (argc >= 4 && std::string(argv[3]).rfind("--", 0) != 0) {
                seed = static_cast<unsigned int>(std::stoul(argv[3]));
            }
        } catch (...) {
            std::cout << "Invalid numeric argument. `size` and optional `seed` must be numbers.\n";
            printUsage();
            waitForExit();
            return 1;
        }
    }

    if (size == 0) {
        std::cout << "Size must be greater than 0.\n";
        waitForExit();
        return 1;
    }

    std::unordered_map<std::string, AlgoFn> registry = {
        {"sort", runSort},
        {"stable_sort", runStableSort},
        {"prefix_sum", runPrefixSum}
    };

    auto it = registry.find(algorithm);
    if (it == registry.end()) {
        std::cout << "Unknown algorithm: " << algorithm << "\n";
        printUsage();
        waitForExit();
        return 1;
    }

    std::vector<int> data = generateRandomInput(size, 1, 100000, seed);

    auto start = std::chrono::high_resolution_clock::now();
    it->second(data);
    auto end = std::chrono::high_resolution_clock::now();

    if (algorithm == "sort" || algorithm == "stable_sort") {
        std::cout << "Sorted check: " << (isSortedNonDecreasing(data) ? "PASS" : "FAIL") << "\n";
    } else {
        std::cout << "Prefix sum check: output size = " << data.size() << "\n";
    }

    if (profile) {
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Runtime: " << elapsed << " microseconds\n";
    }

    if (memory) {
        size_t bytes = data.capacity() * sizeof(int);
        std::cout << "Approx memory used by input vector: " << bytes << " bytes\n";
    }

    printComplexityReport();
    std::cout << "Plugin architecture note: add a new algorithm by registering a function in `registry`.\n";
    if (interactiveMode) {
        waitForExit();
    }
    return 0;
}
