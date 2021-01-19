// Copyright [year] <Copyright Owner>

#ifndef INCLUDE_PROCESS_HPP_
#define INCLUDE_PROCESS_HPP_

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/process.hpp>
#include <chrono>
#include <list>
#include <memory>
#include <sstream>
#include <string>

#include "Builder.hpp"
#include "Parameters.hpp"
#include "ThreadData.hpp"

class Process {
 public:
  static void create(std::unique_ptr<ThreadData> &data);
  static void init();
  static void startProcess(const std::list<std::string> &commandArg,
                           std::unique_ptr<ThreadData> &data);
};

#endif  // INCLUDE_PROCESS_HPP_
