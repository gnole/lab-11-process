#pragma once

#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <string>

namespace po = boost::program_options;

struct Parameters {
  static int timeout;
  static bool isInstallAdded;
  static bool isPackAdded;
  static std::string buildConfig;
  static int prepareCommandLine(int argc, char **argv);
};
