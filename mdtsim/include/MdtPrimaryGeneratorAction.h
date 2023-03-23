#ifndef MDTPRIMARYGENERATORACTION_H
#define MDTPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include <vector>

class EventWriter;

class MdtPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

 public:

  MdtPrimaryGeneratorAction(EventWriter* evW);
  ~MdtPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);
  
 private:

  std::vector<G4ParticleGun*> m_particleGun;

  EventWriter* m_eventWriter;
  
};    /// MDTPRIMARYGENERATORACTION_H


#endif
