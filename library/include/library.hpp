#pragma once

#include <iostream>
#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Logbook
{
public:
  // message importance level
  enum class Level
  {
    ORDINARY = 0,
    IMPORTANT = 1,
    EMERGANCY = 2
  };
  std::mutex mtx;
  bool empty_flag; //     true when queue is empty
  bool end_flag;

private:
  std::string bookpath; // path to [logbook-name].txt
  Level default_importance;
  std::vector<std::pair<std::string, Level>> messages_queue;

public:
  Logbook(const std::string logbook_path,
          const std::string default_importance_level);
  ~Logbook();

  void
  AddMessageToQueue(const std::string new_message,
                    std::optional<std::string> importance_level);
  void WriteMessage();
  void ChangeDefaultLevel(Level &new_default_message_importance);
  Level ParseLevelFromString(const std::string &level_string);
};

std::ostream &
operator<<(std::ostream &stream, Logbook::Level importance_level)
{
  const std::string names[] = {"ORDINARY", "IMPORTANT", "EMERGANCY"};
  return stream << names[static_cast<int>(importance_level)];
}
