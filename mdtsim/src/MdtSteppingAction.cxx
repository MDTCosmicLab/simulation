#include "MdtSteppingAction.h"
#include "MdtDetectorDescription.h"
#include "EventWriter.h"

#include "G4RunManager.hh"

MdtSteppingAction::MdtSteppingAction(EventWriter* eventWriter) :
  m_eventWriter(eventWriter),
  m_currentVolumeName("World"),
  m_energyAtEntrance(-1.)
{

  m_detDescr = static_cast<const MdtDetectorDescription*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  
}


MdtSteppingAction::~MdtSteppingAction()
{

}

void MdtSteppingAction::UserSteppingAction(const G4Step* step)
{

  if ( !step->GetPostStepPoint()->GetTouchableHandle()->GetVolume() ) return;

  /// check if the particle is changing volume
  G4LogicalVolume* currVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4LogicalVolume* nextVol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // get all particles entering each volume
  if (currVol && nextVol ) {
  
    if ( step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary ) {
      //std::cout << "Exiting from a volume: " << currVol->GetName() << std::endl;
      
            
    }
    
  }

  
}
