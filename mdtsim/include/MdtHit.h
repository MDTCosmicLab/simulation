#ifndef MDTHIT_H
#define MDTHIT_H

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"

class MdtHit : public G4VHit
{

 public:

  MdtHit();
  ~MdtHit();

  G4int         getLayer()     {return m_layer;}
  G4double      getEnergyDep() {return m_energyDep;}
  G4int         getPdgId()     {return m_pdgId;}
  G4ThreeVector getPosition()  {return m_position;}
  G4ThreeVector getMomentum()  {return m_momentum;}

  void setLayer(G4int layer)               {m_layer=layer;}
  void setEnergyDep(double enDep)          {m_energyDep=enDep;}
  void setPdgId(G4int pdgId)               {m_pdgId=pdgId;}
  void setPosition(G4ThreeVector pos)      {m_position=pos;}
  void setMomentum(G4ThreeVector mom)      {m_momentum=mom;}
  
 private:

  G4int m_layer;
  G4double m_energyDep;

  /// hitting particle properties
  G4int m_pdgId;
  G4ThreeVector m_position;
  G4ThreeVector m_momentum;

};


typedef G4THitsCollection<MdtHit> MdtHitCollection;

#endif
