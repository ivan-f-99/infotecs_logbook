#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "library.hpp"
#include "testapp.hpp"

int main(int argc, char const *argv[])
{
  // argv_str use for parse console args
  std::vector<std::string> argv_str;

  for (size_t i = 0; i < static_cast<size_t>(argc); ++i)
  {
    std::string buf(argv[i]);
    argv_str.push_back(buf);
  }

  // logbook path & default message importance
  std::string logbook_path;
  std::string default_message_importance;

  //	work with input arguments
  switch (argc)
  {
  case 2:
  {
    if (argv_str[1] == "-help")
    {
      PrintHelp();
    }
    else
    {
      std::cerr << "Invalid options. Use -help for more information"
                << std::endl;
      return -1;
    }
    break;
  }
  case 3:
  {
    logbook_path = argv_str[1];
    default_message_importance = argv_str[2];

    // check logbook path to open stram possibility
    std::fstream check(logbook_path, std::ios::app);
    if (!check.is_open())
    {
      std::cout << "Can't open file. Check assigned path" << std::endl;
      check.close();
      return -1;
    }

    std::cout << "Logbook: " << logbook_path << std::endl
              << "Default importance level: " << default_message_importance << std::endl;
    check.close();
    break;
  }
  default:

    std::cout << "Cant recognize imput parametrs. Work in interactive mod."
              << std::endl;
    std::cout << "Enter path to LOGBook:" << std::endl;
    std::cin >> logbook_path;
    std::cout << "Enter defalt priority mod (ORDINARY||IMPORTANT||EMERGENCY):"
              << std::endl;
    std::cin >> default_message_importance;
  }
  argv_str.clear();

  // 	Initialize library

  Logbook LB(logbook_path, default_message_importance);

  std::thread read_thread(ReadFromTerminal, std::ref(LB));
  std::thread write_thread(WriteToFile, std::ref(LB));
  read_thread.join();
  write_thread.join();

  return 0;
}

void PrintHelp()
{
  std::cout << "testapp.exe [Path-to-logbook] [default-priority]" << std::endl;
  std::cout << "Or just testapp.exe" << std::endl;
}

void ReadFromTerminal(Logbook &LB)
{

  while (true)
  {
    std::string buf;
    std::getline(std::cin, buf);

    // this is a comand to end reading
    if (buf == ":q!")
    {
      while (true)
      {
        const std::lock_guard<std::mutex> lock(LB.mtx);
        if (LB.empty_flag)
          break;
      }
      const std::lock_guard<std::mutex> lock(LB.mtx);
      LB.end_flag = true;
      return;
    }
    if (buf.empty())
    {
      continue;
      ;
    }

    // parse importance and text in message
    size_t pos = buf.find(':');
    if (pos == std::string::npos)
    {
      const std::lock_guard<std::mutex> lock(LB.mtx);
      LB.AddMessageToQueue(buf, std::nullopt);
    }
    else
    {
      std::string importance_buf = buf.substr(0, pos);
      buf.erase(0, pos + 1);
      if (!CheckImportanceLevelCorrection(importance_buf))
      {
        std::cout << "Recieved incorrect importance level." << " Message will not write to Logbook" << std::endl;
        continue;
      }
      const std::lock_guard<std::mutex> lock(LB.mtx);
      LB.AddMessageToQueue(buf, importance_buf);
    }
  }
  return;
}
void WriteToFile(Logbook &LB)
{

  // look queue for new messages
  while (true)
  {
    const std::lock_guard<std::mutex> lock(LB.mtx);
    if (LB.end_flag == true)
    {
      return;
    }

    // write message call to library
    if (!LB.empty_flag)
    {
      LB.WriteMessage();
    }
  }
  return;
}

bool CheckImportanceLevelCorrection(std::string level_string)
{
  bool result = false;
  if (level_string == "ORDINARY")
    result = true;
  if (level_string == "IMPORTANT")
    result = true;
  if (level_string == "EMERGANCY")
    result = true;
  return result;
}
