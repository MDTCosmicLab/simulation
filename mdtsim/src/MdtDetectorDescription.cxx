#include "MdtDetectorDescription.h"
#include "MdtSensitiveDetector.h"

#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4SystemOfUnits.hh"

MdtDetectorDescription::MdtDetectorDescription(G4String fileName, EventWriter* eventWriter) :
  G4VUserDetectorConstruction(),
  m_fileName(fileName),
  m_eventWriter(eventWriter)
{
  m_parser.Read(m_fileName,false);
}

MdtDetectorDescription::~MdtDetectorDescription()
{}

G4VPhysicalVolume* MdtDetectorDescription::Construct()
{
  // define the sensitive detectors
  MdtSensitiveDetector* mdtSD = new MdtSensitiveDetector("/MdtSD");
  mdtSD->setEventWriter(m_eventWriter);
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  sdManager->AddNewDetector(mdtSD);
  
  std::cout << ">>>> Initializing the detector volumes" << std::endl;

  G4VPhysicalVolume* world = NULL;
  world = m_parser.GetWorldVolume();

  std::cout << ">>>> Read the world volume" << std::endl;

  /// initialize the map of the detector volumes
  G4PhysicalVolumeStore* volumeStore = G4PhysicalVolumeStore::GetInstance();
  if ( !volumeStore ) {
    std::cout << "ERROR volumeStore not found !!" << std::endl;
    throw(1);
  }
  std::cout << "The size of the volume store is: " << volumeStore->size() << std::endl;
  G4UserLimits* userLimits = new G4UserLimits();
  userLimits->SetMaxAllowedStep(0.001);
  for (unsigned int i=0 ; i<volumeStore->size() ; i++) {
    G4String name = volumeStore->at(i)->GetName();
    std::cout << "Vol number: " << i << " name: " << name << std::endl;

    /// add the tracking sensitive detector
    if (name == "MDT1_GAP" || name=="MDT2_GAP" || name=="MDT3_GAP" || name=="MDT4_GAP" || name=="MDT5_GAP" || name=="MDT6_GAP" ||
	name == "MDT7_GAP" || name=="MDT8_GAP" || name=="MDT9_GAP" || name=="MDT10_GAP" || name=="MDT11_GAP" || name=="MDT12_GAP" ||
	name == "MDT13_GAP" || name=="MDT14_GAP" || name=="MDT15_GAP" || name=="MDT16_GAP")
      {
	std::cout << "Adding sensitive detector with name: " << name << std::endl;
	
	volumeStore->at(i)->GetLogicalVolume()->SetSensitiveDetector(mdtSD);
      }

    /// set the stepping if needed
    volumeStore->at(i)->GetLogicalVolume()->SetUserLimits(userLimits);
    
    m_physicalVolumes.insert(std::pair<G4String,unsigned int>(name,i));
  }

  return world;
}


/// construct the b-field map
void MdtDetectorDescription::ConstructSDandField()
{
  G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(1.*tesla,0.,0.));
  
  G4FieldManager* globalFieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  globalFieldMgr->SetDetectorField(magField);  

  globalFieldMgr->CreateChordFinder(magField);
  return;
}






