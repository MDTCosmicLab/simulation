#include "MdtEventAction.h"
#include "MdtRunAction.h"
#include "MdtHit.h"
#include "MdtDigitizer.h"
#include "MdtClusterDigitizer.h"

#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4RootAnalysisManager.hh"

MdtEventAction::MdtEventAction() :
  m_eventWriter(NULL)
{

}

MdtEventAction::MdtEventAction(EventWriter* eventWriter, double bgRate) :
  m_eventWriter(eventWriter)
{
  /// create the digitizer
  MdtDigitizer* digitizer = new MdtDigitizer("MdtDigitizer", eventWriter);
  G4DigiManager* digiManager = G4DigiManager::GetDMpointer();
  digiManager->AddNewModule(digitizer);
}

MdtEventAction::~MdtEventAction()
{ }

void MdtEventAction::BeginOfEventAction(const G4Event* evt)
{
 
}

void MdtEventAction::EndOfEventAction(const G4Event* evt)
{

  int nevents = evt->GetEventID();
  int nevtot  = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  if ( nevents%100 == 0) {
    G4cout << "=====> Processed " << nevents << " / " << nevtot << " events" << G4endl;
  }

  /// retrieve the hits in the sensitive detectors
  G4HCofThisEvent* hce = evt->GetHCofThisEvent();
  if ( !hce ) {
    G4cout << ">>> ERROR HCE not found !! " << G4endl;
    return;
  }

  MdtHitCollection* mdtHitCollection;
  static G4SDManager* SDman = G4SDManager::GetSDMpointer();
  const G4int mdtCollID = SDman->GetCollectionID("MdtHitCollection");
  //  G4cout << ">>> collID " << mdtCollID << G4endl;
  
  if (hce && mdtCollID>-1) {
    mdtHitCollection = (MdtHitCollection*) hce->GetHC(mdtCollID);
    //    G4cout << "Size of the hit collection: " << mdtHitCollection->GetSize()  << G4endl;
  }
  else {    
    G4cout << ">>> ERROR Hit collection not found !! " << G4endl;
    return;
  }

  /// run the digitization
  G4DigiManager* digiManager = G4DigiManager::GetDMpointer();
  MdtDigitizer* mdtDigitizer = static_cast<MdtDigitizer*> (digiManager->FindDigitizerModule("MdtDigitizer"));
  mdtDigitizer->setHitCollection(mdtHitCollection);
  mdtDigitizer->Digitize();

  /// run the reconstruction
  

  
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->AddNtupleRow(0);

  m_eventWriter->clearTree();

}
