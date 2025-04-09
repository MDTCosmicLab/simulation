#ifndef MDTSENSITIVEDETECTOR_H
#define MDTSENSITIVEDETECTOR_H

#include "G4VSensitiveDetector.hh"
#include "EventWriter.h"
#include "MdtHit.h"

#include <map>

class MdtSensitiveDetector :  public G4VSensitiveDetector
{

 public:
  MdtSensitiveDetector(G4String name);
  ~MdtSensitiveDetector();

  G4bool ProcessHits(G4Step* step , G4TouchableHistory* hist);
  void Initialize(G4HCofThisEvent* HCE);
  void EndOfEvent(G4HCofThisEvent* HCE);

  void setEventWriter(EventWriter* ev)   {m_eventWriter=ev;}
  
 private:

  MdtHitCollection* m_hitCollection;
  EventWriter* m_eventWriter;
  G4int m_HCID;

  /// map of the active detectors identifiers
  std::map<G4String,int> m_detIdMap;
    
};
#endif
