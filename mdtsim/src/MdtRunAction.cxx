#include "MdtRunAction.h"
#include "MdtRun.h"

#include "g4root.hh"

MdtRunAction::MdtRunAction(EventWriter* eventWriter)
  : G4UserRunAction()
{

  m_eventWriter = eventWriter;

}

MdtRunAction::~MdtRunAction() {}

void MdtRunAction::BeginOfRunAction(const G4Run*) {

}


G4Run* MdtRunAction::GenerateRun() {
  return new MdtRun;
}

void MdtRunAction::EndOfRunAction(const G4Run* run) {

  std::cout << "Number of simulated events: " << run->GetNumberOfEvent() << std::endl;

  //  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //analysisManager->Write();
  //analysisManager->CloseFile();

  delete m_eventWriter;
  
}

