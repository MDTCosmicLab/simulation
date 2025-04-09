#include "MdtActionInit.h"
#include "MdtRunAction.h"
#include "MdtEventAction.h"
#include "MdtPrimaryGeneratorAction.h"
#include "MdtSteppingAction.h"

MdtActionInit::MdtActionInit(EventWriter* eventWriter)
  :
  G4VUserActionInitialization(),
  m_eventWriter(eventWriter),
  m_bgRate(0.0)
{
  
}


MdtActionInit::~MdtActionInit()
{

}


void MdtActionInit::Build() const
{
  /// initialize the run action
  MdtRunAction* runAction = new MdtRunAction(m_eventWriter);
  SetUserAction(runAction);
  /// initialize the event action
  MdtEventAction* eventAction = new MdtEventAction(m_eventWriter,m_bgRate);  
  SetUserAction(eventAction);
  /// initialize the generator action
  MdtPrimaryGeneratorAction* generatorAction = new MdtPrimaryGeneratorAction(m_eventWriter);
  SetUserAction(generatorAction);
  /// initialize the stepping action
  MdtSteppingAction* steppingAction = new MdtSteppingAction(m_eventWriter);
  SetUserAction(steppingAction);  
}
