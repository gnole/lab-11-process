#pragma once

#include <list>
#include <string>

#include "Parameters.hpp"

class Builder {
 public:
  static const std::string kDirectoryBuild;
  static const std::string kDirectoryInstall;
  static std::list<std::string> getConfig();
  static std::list<std::string> getBuild();
  static std::list<std::string> getInstall();
  static std::list<std::string> getPack();
};
