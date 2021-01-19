// Copyright [year] <Copyright Owner>

#include "Process.hpp"
void Process::create(std::unique_ptr<ThreadData> &data) {
  if (Parameters::timeout <= 0) {
    return;
  }
  static const int kTimeDelta = 1;
  while (Parameters::timeout > 0 && (!data || !data->isTerminated)) {
    std::this_thread::sleep_for(std::chrono::seconds{kTimeDelta});
    Parameters::timeout -= kTimeDelta;
  }

  data->isTerminated = true;

  try {
    data->currentProcess.terminate();
  } catch (std::exception &exception) {
    BOOST_LOG_TRIVIAL(error) << exception.what();
  }

  BOOST_LOG_TRIVIAL(info) << "Timeout";
}

void Process::init() {
  boost::log::register_simple_formatter_factory<
      boost::log::trivial::severity_level, char>("Severity");
  static const std::string format = "%Message%";

  auto loggerFile = boost::log::add_file_log(
      boost::log::keywords::file_name = "_build/logs/log_.log",
      boost::log::keywords::auto_flush = true,
      boost::log::keywords::format = format);
  loggerFile->set_filter(boost::log::trivial::severity >=
                         boost::log::trivial::trace);  // Log file setup

  auto loggerConsole = boost::log::add_console_log(
      std::cout, boost::log::keywords::format = format);
  loggerConsole->set_filter(boost::log::trivial::severity >=
                            boost::log::trivial::info);  // Log console setup

  boost::log::add_common_attributes();
}

void Process::startProcess(const std::list<std::string> &commandArg,
                           std::unique_ptr<ThreadData> &data) {
  namespace pr = boost::process;

  if (data && data->isTerminated) {
    return;
  }
  std::string out;
  for (const auto &com : commandArg) {
    out += com + " ";
  }
  // Start
  BOOST_LOG_TRIVIAL(info) << "$ cmake " << out << "\n";

  pr::ipstream stream;

  pr::child child{"/usr/local/bin/cmake", pr::args(commandArg),
                  pr::std_out > stream};

  // Update data
  if (!data) {
    data = std::make_unique<ThreadData>(ThreadData{false, std::move(child)});
  } else {
    data->currentProcess = std::move(child);
  }
  // Get output
  for (std::string line;
       data->currentProcess.running() && std::getline(stream, line);) {
    BOOST_LOG_TRIVIAL(info) << line;
  }

  // Wait until exit
  data->currentProcess.wait();

  auto exitCode = data->currentProcess.exit_code();
  BOOST_LOG_TRIVIAL(info) << "Exit code: " << exitCode;

  if (exitCode != 0) {
    BOOST_LOG_TRIVIAL(error) << "Non zero exit code. Exiting...";
    data->isTerminated = true;
  }
}
