//external libraries
#include "../include/json.hpp"

#include <iostream>
#include <array>
#include <string>
#include <map>
#include <vector>

// file handling
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace std;
using json = nlohmann::json;

map <string, bool> settings;

json loadData(const string& path) {
    stringstream buffer;

    // checks if file exists and loads it into buffer if it does
    ifstream file;
    if (filesystem::exists(path))
        file.open(path);
    else {
        throw std::runtime_error("Loading settings: file does not exist: \"" + path + "\"");
    }

    // loading settings as text from file
    buffer << file.rdbuf();
    file.close();

    return json::parse(buffer.str());
}

void loadSettings(const string& path) {
    // retrieves json data from file
    json settingsData = loadData(path);

    // applies settings
    settings.clear();

    for (auto& item : settingsData.items()) {
        settings[item.key()] = item.value();
    }
}

int main() {

    loadSettings("../data/settings.json");
    for (auto& item : settings) {
        cout << item.first << ": " << item.second << endl;
    }

    return 0;
}