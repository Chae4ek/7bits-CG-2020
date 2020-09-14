#include "Tools/Localization.h"

Localization::Localization(std::string local_file_name) {
  SetLocal(local_file_name);
}

void Localization::SetLocal(std::string local_file_name) {
  std::ifstream file("./Localization/" + local_file_name);
  std::string key, str;

  while (!file.eof()) {
    file >> key;
    if (key[0] == '[') continue;
    file >> str;  // skip '='
    std::getline(file, str);
    str.erase(str.begin());  // delete ' '
    local[key] = str;
  }

  file.close();
}