#ifndef MDTEVENTACTION_H
#define MDTEVENTACTION_H

#include "G4UserEventAction.hh"
#include "EventWriter.h"

class MdtEventAction : public G4UserEventAction
{

 public:
  MdtEventAction();
  MdtEventAction(EventWriter* eventWriter, double bgRate);

  virtual ~MdtEventAction();

  virtual void BeginOfEventAction(const G4Event* evt);
  virtual void EndOfEventAction(const G4Event* evt);
  
 private:

  EventWriter* m_eventWriter;
  
};

#endif
