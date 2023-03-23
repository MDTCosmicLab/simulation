#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "TkDetectorDescription.h"
#include "TkActionInit.h"

#include "EventWriter.h"

#include <stdio.h>
#include <vector>
#include <string>

int main(int argc, char** argv)
{

  std::cout << "Number of rguments: " << argc << std::endl;

  std::string fileName="tksim.root"; 
  double bgRate=0.0;
  if (argc>=3) {
    fileName=argv[1];
    bgRate=atof(argv[2]);
  }
  else if (argc==2) {
    fileName=argv[1];
  }

  std::cout << "File Name:  " << fileName << std::endl;
  std::cout << "Background: " << bgRate << std::endl;
  
  // initialize the event writer
  EventWriter* eventWriter = new EventWriter(fileName);
  eventWriter->bookTree();
  eventWriter->clearTree();
  
  // run manager
  G4RunManager* runManager = new G4RunManager();
  
  // set the physics list
  G4PhysListFactory *physListFactory = new G4PhysListFactory();
  G4VModularPhysicsList* physList = physListFactory->GetReferencePhysList("FTFP_BERT_EMV");
  //  G4VModularPhysicsList* physList = physListFactory->GetReferencePhysList("QGSP_BERT_HP");
  physList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physList);
  
  TkActionInit* actionInit = new TkActionInit(eventWriter);
  actionInit->setBackground(bgRate);
  runManager->SetUserInitialization(actionInit);

  // build the detector geometry
  TkDetectorDescription* detDescr = new TkDetectorDescription("layout.gdml",eventWriter);
  runManager->SetUserInitialization(detDescr);

  runManager->Initialize();

  const G4Run* run = runManager->GetCurrentRun();
  G4UImanager* manager = G4UImanager::GetUIpointer();

  //  G4VisManager* visManager = new G4VisExecutive;
  //  visManager->Initialize();
  //  manager->ApplyCommand("/control/execute init_vis.mac");

  /// production mode
  manager->ApplyCommand("/run/beamOn 500000");
  /// testing
  //  manager->ApplyCommand("/run/beamOn 10000");
  
  return 0;
}
