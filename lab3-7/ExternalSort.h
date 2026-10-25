#pragma once

#include <climits>
#include <fstream>
#include <string>
#include <vector>

#include "Sorts.h"

void externalMergeSort(const std::string& inputFile, const std::string& outputFile,
                       int chunkSize = 1000) {
    std::vector<std::string> tempFiles;
    int chunkIndex = 0;
    std::ifstream in;
    in.open(inputFile, std::ios::in);

    if (in.is_open()) {
        while (true) {
            std::vector<int> chunk;
            int number;
            int chunkCount = 0;

            while (chunkCount < chunkSize and in >> number) {
                chunk.push_back(number);
                chunkCount++;
            }

            if (chunkCount == 0) break;

            quickSort(chunk.data(), 0, chunk.size() - 1);

            if (!chunk.empty()) {
                std::ofstream out;
                out.open("temp_" + std::to_string(chunkIndex) + ".txt");
                if (out.is_open()) {
                    for (size_t i = 0; i < chunk.size(); i++) {
                        out << chunk[i] << std::endl;
                    }
                }
                out.close();
            }

            tempFiles.push_back("temp_" + std::to_string(chunkIndex) + ".txt");
            chunkIndex++;
            chunk.clear();
        }
    }

    std::vector<std::ifstream> files;
    files.reserve(tempFiles.size());
    for (const std::string& name : tempFiles) {
        files.emplace_back(name);
    }

    std::vector<int> current;
    current.resize(tempFiles.size());
    for (size_t i = 0; i < tempFiles.size(); i++) {
        files[i] >> current[i];
        if (files[i].fail()) current[i] = INT_MAX;
    }

    if (tempFiles.empty()) return;
    std::ofstream out;
    out.open(outputFile, std::ios::out);

    while (true) {
        int minIndex = 0;
        for (size_t i = 0; i < current.size(); i++) {
            if (current[i] < current[minIndex]) {
                minIndex = i;
            }
        }
        if (current[minIndex] == INT_MAX) break;
        out << current[minIndex] << "\n";

        files[minIndex] >> current[minIndex];
        if (files[minIndex].fail()) current[minIndex] = INT_MAX;
    }
    out.close();
    for (auto& f : files) f.close();
    for (const std::string& name : tempFiles) std::remove(name.c_str());
}