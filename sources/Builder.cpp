// Copyright [year] <Copyright Owner>

#include "Builder.hpp"

const std::string Builder::kDirectoryBuild = "_build";

const std::string Builder::kDirectoryInstall = "_install";

std::list<std::string> Builder::getConfig() {
  return {"-H.", "-B" + kDirectoryBuild,
          "-DCMAKE_INSTALL_PREFIX=" + kDirectoryInstall,
          "-DCMAKE_BUILD_TYPE=" + Parameters::buildConfig};
}

std::list<std::string> Builder::getBuild() {
  return {"--build", kDirectoryBuild};
}

std::list<std::string> Builder::getInstall() {
  return {"--build", kDirectoryBuild, "--target", "install"};
}

std::list<std::string> Builder::getPack() {
  return {"--build", kDirectoryBuild, "--target", "package"};
}
