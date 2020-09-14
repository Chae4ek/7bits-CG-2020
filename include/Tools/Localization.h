#pragma once

#include <fstream>
#include <map>
#include <string>

class Localization {
 public:
  std::map<std::string, std::string> local;

  explicit Localization(std::string local_file_name);

  void SetLocal(std::string local_file_name);
};