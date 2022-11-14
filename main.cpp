#include "EnRuDictionary.h"
int main()
{
  std::string f1, f2;
  std::cout << "Enter the commands filename:";
  std::cin >> f1;
  std::cout << "Enter the results filename:";
  std::cin >> f2;
  std::ifstream commandsFile(f1);
  std::ofstream resultsFile(f2);
  if (!commandsFile.is_open() || !resultsFile.is_open())
  {
    std::cerr << "Opening file error\n";
    return 1;
  }
  EnRuDictionary dict;
  SinglyOrderedList list;
  std::string command;
  while (!commandsFile.eof())
  {
    commandsFile >> command;
    if (command == "help")
    {
      resultsFile << "Available commands:\n"
                  << "insert [word] - insert a new word\n"
                  << "add [word] [translation] - add a new translation to the word\n"
                  << "search [word] - search the word, print it with translations if found\n"
                  << "print - print the dictionary\n"
                  << "delete [word] - delete the word\n"
                  << "end - end session\n";
    }
    else if (command == "insert")
    {
      std::string word;
      commandsFile >> word;
      dict.insert(word, list) ? resultsFile << "Inserted '" << word << "'\n" :
      resultsFile << "Word '" << word << "' is already inserted\n";
    }
    else if (command == "add")
    {
      std::string word, translation;
      commandsFile >> word >> translation;
      dict.setValue(word, translation) ?
      resultsFile << "Added translation '" << translation << "' to word '" << word << "'\n" :
      resultsFile << "No word '" << word << "'\n";
    }
    else if (command == "search")
    {
      std::string word;
      commandsFile >> word;
      if (!dict.printWord(resultsFile, word))
      {
        resultsFile << "Word '" << word << "' not found\n";
      }
    }
    else if (command == "print")
    {
      if (!dict.empty())
      {
        dict.print(resultsFile);
      }
      else
      {
        resultsFile << "No words\n";
      }
    }
    else if (command == "delete")
    {
      std::string word;
      commandsFile >> word;
      if (!dict.deleteKey(word))
      {
        resultsFile << "No such word '" << word << "'\n";
      } else resultsFile << "Word '" << word << "' deleted\n";
    }
    else if (command == "end")
    {
      resultsFile << "End of session\n";
      break;
    }
  }
  commandsFile.close();
  resultsFile.close();

  return 0;
}
