#ifndef MDTSTEPPINGACTION_H
#define MDTSTEPPINGACTION_H

#include "G4UserSteppingAction.hh"
#include "G4String.hh"

class EventWriter;
class MdtDetectorDescription;

class MdtSteppingAction : public G4UserSteppingAction
{

public:

  MdtSteppingAction(EventWriter* eventWriter);
  ~MdtSteppingAction();

  virtual void UserSteppingAction(const G4Step*);
  
private:

  EventWriter* m_eventWriter;
  const MdtDetectorDescription* m_detDescr;

  /// name of the current volume
  G4String m_currentVolumeName;
  
  double m_energyAtEntrance;
  
};

#endif
