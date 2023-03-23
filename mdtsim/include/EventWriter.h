#ifndef EVENTWRITER_H
#define EVENTWRITER_H

#include <vector>
#include <iostream>
#include <string>

class EventWriter
{

 public:

  EventWriter();
  EventWriter(std::string fileName);
  ~EventWriter();

  /// add a variable to the ntuple
  void bookTree();
  void clearTree();

 private:

  std::string m_fileName;
  

};


#endif
