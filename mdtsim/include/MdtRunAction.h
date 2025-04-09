#ifndef MDTRUNACTION_H
#define MDTRUNACTION_H

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "EventWriter.h"

class MdtRunAction : public G4UserRunAction
{

 public:
  MdtRunAction(EventWriter* eventWriter);
  virtual ~MdtRunAction();

  virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

  EventWriter* eventWriter() {return m_eventWriter;}
  
 private:

  /// event writer
  EventWriter* m_eventWriter;
  
};

#endif
