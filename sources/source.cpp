// Copyright [year] <Copyright Owner>

#include <async++.h>

#include "Process.hpp"

int main(int argc, char *argv[]) {
  if (auto returnCode = Parameters::prepareCommandLine(argc, argv);
      returnCode != 0) {
    return returnCode;
  }

  Process::init();

  std::unique_ptr<ThreadData> data{nullptr};

  auto timer = async::spawn(std::bind(&Process::create, std::ref(data)));

  auto config = async::spawn(
      std::bind(Process::startProcess, Builder::getConfig(), std::ref(data)));

  auto build = config.then(
      std::bind(Process::startProcess, Builder::getBuild(), std::ref(data)));

  if (Parameters::isInstallAdded) {
    build = build.then(std::bind(Process::startProcess, Builder::getInstall(),
                                 std::ref(data)));
  }
  if (Parameters::isPackAdded) {
    build = build.then(
        std::bind(Process::startProcess, Builder::getPack(), std::ref(data)));
  }
  build = build.then([&data]() { data->isTerminated = true; });

  build.wait();
  timer.wait();
}
