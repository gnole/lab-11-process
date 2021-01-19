#include "Parameters.hpp"

int Parameters::timeout{};
bool Parameters::isInstallAdded{};
bool Parameters::isPackAdded{};
std::string Parameters::buildConfig{};

int Parameters::prepareCommandLine(int argc, char **argv) {
  po::positional_options_description positionalArgs;
  positionalArgs.add("input", -1);
  po::options_description visibleOptions("Available options");
  visibleOptions.add_options()("help", ": выводим вспомогательное сообщение")(
      "config",
      po::value<std::string>(&Parameters::buildConfig)->default_value("Debug"),
      ": указываем конфигурацию сборки (по умолчанию Debug)")(
      "install", ": добавляем этап установки (в директорию _install)")(
      "pack", ": добавляем этап упаковки (в архив формата tar.gz)")(
      "timeout", po::value<int>(&Parameters::timeout)->default_value(-1),
      ": указываем время ожидания (в секундах)");

  po::variables_map variablesMap;
  po::store(po::parse_command_line(argc, argv, visibleOptions), variablesMap);
  po::notify(variablesMap);

  if (variablesMap.count("help")) {
    std::cout << visibleOptions << "\n";
    return 1;
  }
  if (variablesMap.count("install")) {
    Parameters::isInstallAdded = true;
  }
  if (variablesMap.count("pack")) {
    Parameters::isPackAdded = true;
  }

  return 0;
}
