#include <chrono>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "library.hpp"

Logbook::Logbook(const std::string logbook_path,
                 const std::string default_importance_level)
{
  bookpath = logbook_path;
  default_importance = ParseLevelFromString(default_importance_level);
  empty_flag = true;
}
Logbook::~Logbook() {};

void Logbook::AddMessageToQueue(
    const std::string new_message,
    std::optional<std::string> importance_level)
{
  std::pair<std::string, Level> level_and_message;
  if (importance_level == std::nullopt)
  {
    level_and_message.first = new_message;
    level_and_message.second = default_importance;
  }
  else
  {
    level_and_message.first = new_message;
    level_and_message.second = ParseLevelFromString(importance_level.value());
  }
  if (level_and_message.second < default_importance)
    return;
  messages_queue.push_back(level_and_message);
  if (empty_flag)
    empty_flag = false;
  return;
}

void Logbook::WriteMessage()
{
  std::fstream out;
  out.open(bookpath, std::ios::app);

  // set writing message time
  auto now = std::chrono::system_clock::now();
  std::time_t curr_time = std::chrono::system_clock::to_time_t(now);

  // wrtite time & importance & message text
  out << std::ctime(&curr_time);
  out << messages_queue.front().second << ": "
      << messages_queue.front().first << std::endl
      << std::endl;

  messages_queue.erase(messages_queue.begin());
  if (messages_queue.size() == 0)
    empty_flag = true;

  out.close();
  return;
}

void Logbook::ChangeDefaultLevel(Level &new_default_message_importance)
{
  default_importance = new_default_message_importance;
  return;
}
Logbook::Level Logbook::ParseLevelFromString(const std::string &level_string)
{
  Level result;

  if (level_string == "ORDINARY")
    result = static_cast<Level>(0);
  if (level_string == "IMPORTANT")
    result = static_cast<Level>(1);
  if (level_string == "EMERGANCY")
    result = static_cast<Level>(2);

  return result;
}