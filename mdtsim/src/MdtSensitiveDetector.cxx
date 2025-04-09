#include "MdtSensitiveDetector.h"

MdtSensitiveDetector::MdtSensitiveDetector(G4String name) :
  G4VSensitiveDetector(name)
{

  /// name of the hits collection
  collectionName.insert("MdtHitCollection");

  /// initialize the map with the detector Id's
  std::string detName[16] = {"MDT1_GAP","MDT2_GAP","MDT3_GAP","MDT4_GAP","MDT5_GAP","MDT6_GAP","MDT7_GAP","MDT8_GAP",
  "MDT9_GAP","MDT10_GAP","MDT11_GAP","MDT12_GAP","MDT13_GAP","MDT14_GAP","MDT15_GAP","MDT16_GAP"};
  int detId[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

  for ( unsigned int i=0 ; i<sizeof(detId)/sizeof(*detId) ; ++i) {  
    m_detIdMap.insert(std::pair<std::string,int>(detName[i],detId[i]) );
  }
  
}


MdtSensitiveDetector::~MdtSensitiveDetector()
{

}

void MdtSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{

  m_hitCollection = new MdtHitCollection(GetName(), collectionName[0]);
  
  m_HCID=GetCollectionID(0);
  
  HCE->AddHitsCollection(m_HCID, m_hitCollection);
  
}

G4bool MdtSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* hist)
{
  /// produce the hits inside the sensitive tracking detector
  // G4VPhysicalVolume* currPhysVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume* currPhysVol = step->GetPreStepPoint()->GetPhysicalVolume();

  if ( step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary ) {

    //  std::cout << "New hit in volume: " << currPhysVol->GetName() << std::endl;
    G4String volName = currPhysVol->GetName();
    int detId = -1;
    std::map<G4String,int>::const_iterator it = m_detIdMap.find(volName);
    if (it != m_detIdMap.end() ) {
      detId = (* m_detIdMap.find(volName)).second;
    }
    else {
      std::cout << "ERROR detector: " << volName << " not found !" << std::endl;
    }
    
    /// create the hit and add it to the collection
    G4ThreeVector position = step->GetPostStepPoint()->GetPosition();
    G4ThreeVector momentum = step->GetPostStepPoint()->GetMomentum();
    /// get the corresponding particleId
    G4int pdgId = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
    MdtHit* mdtHit = new MdtHit();
    
    mdtHit->setLayer(detId);
    mdtHit->setPdgId(pdgId);
    mdtHit->setMomentum(momentum);
    mdtHit->setPosition(position);
    
    m_hitCollection->insert(mdtHit);
    
    /// fill the ntuple with the hits information
    m_eventWriter->hitPdgId(pdgId);
    m_eventWriter->hitDetId(detId);
    m_eventWriter->hitX(step->GetPostStepPoint()->GetPosition().x());
    m_eventWriter->hitY(step->GetPostStepPoint()->GetPosition().y());
    m_eventWriter->hitZ(step->GetPostStepPoint()->GetPosition().z());  
    m_eventWriter->hitPX(step->GetPostStepPoint()->GetMomentum().x());
    m_eventWriter->hitPY(step->GetPostStepPoint()->GetMomentum().y());
    m_eventWriter->hitPZ(step->GetPostStepPoint()->GetMomentum().z());  

  }
    
  return true;
}

void MdtSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE)
{


}
