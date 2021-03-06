#ifndef __LOGGER_HPP_
#define __LOGGER_HPP_

#include <string>
#include <iostream>
    
#include "datetime.hpp"
#include "logger.hpp"

namespace logger{

  void debug(
    const std::string &name,
    const std::string &message,
    std::ostream &out = std::cout) {
    out << datetime::unixtime_str() << \
      " DEBUG ["<< name << "] "<< message << std::endl;
  }

  void info(
    const std::string &name,
    const std::string &message,
    std::ostream &out = std::cout) {
    out << datetime::unixtime_str() << \
      " INFO ["<< name << "] "<< message << std::endl;
  }

  void warning(
    const std::string &name,
    const std::string &message,
    std::ostream &out = std::cout) {
    out << datetime::unixtime_str() << \
      " WARNING ["<< name << "] "<< message << std::endl;
  }

  void error(
    const std::string &name,
    const std::string &message,
    std::ostream &out = std::cout) {
    out << datetime::unixtime_str() << \
      " ERROR (-A-) ["<< name << "] "<< message << std::endl;
  }

  void fital(
    const std::string &name,
    const std::string &message,
    std::ostream& out = std::cout) {
    out << datetime::unixtime_str() << \
      " FITAL (`o') ["<< name << "] "<< message << std::endl;
  }

};
#endif
