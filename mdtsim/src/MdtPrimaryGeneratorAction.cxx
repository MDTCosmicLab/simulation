#include "MdtPrimaryGeneratorAction.h"
#include "EventWriter.h"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

MdtPrimaryGeneratorAction::MdtPrimaryGeneratorAction(EventWriter* eventWriter) :
  m_eventWriter(eventWriter)
{

  G4ParticleDefinition* particleDef;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;

  int npart = 1;
  G4ParticleGun* muonGun = new G4ParticleGun(npart);
  m_particleGun.push_back(muonGun);

  /// background photons
  G4ParticleDefinition* particleDef2 = particleTable->FindParticle(particleName="gamma");
  npart = 10;
  G4ParticleGun* gammaGun = new G4ParticleGun(npart);
  m_particleGun.push_back(gammaGun);
  m_particleGun[1]->SetParticleDefinition(particleDef2);
  
}



MdtPrimaryGeneratorAction::~MdtPrimaryGeneratorAction()
{

  for (auto g : m_particleGun) {
    delete g;
  }

}

void MdtPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{

  double muonX = G4RandGauss::shoot(0.,100.);
  double muonY = G4RandGauss::shoot(0.,100.);
  double muonZ = G4RandGauss::shoot(0.,100.);
  /// set the position of the primary particle
  m_particleGun[0]->SetParticlePosition(G4ThreeVector(muonX,muonY,muonZ));
  /// set the direction of the momentum
  double pxdir = G4RandGauss::shoot(0.,0.01);
  double pydir = G4RandGauss::shoot(0.,0.01);
  //double pxdir = 0.0;
  //double pydir = 0.0;
  double pzdir = sqrt(1.0-pxdir*pxdir-pydir*pydir);
  m_particleGun[0]->SetParticleMomentumDirection(G4ThreeVector(pxdir,pydir,pzdir));

  /// set the muon sign
  G4ParticleDefinition* particleDef;
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  double sign = G4RandFlat::shoot(0.,1.);
  if (sign<0.5) {
    particleDef = particleTable->FindParticle(particleName="mu-");
  }
  else {
    particleDef = particleTable->FindParticle(particleName="mu+");
  }
  m_particleGun[0]->SetParticleDefinition(particleDef);

  /// set the particle energy
  //G4double energy = 0.050;

  // flat energy between 5 and 100 GeV
  //  G4double energy = 100000;
  G4double energy = G4RandFlat::shoot(20000.,50000.);
  m_particleGun[0]->SetParticleEnergy(energy);
  //  /// generate the particle
  m_particleGun[0]->GeneratePrimaryVertex(event);
  /// copy particle data to the ntuple
  m_eventWriter->nMuon(1);
  m_eventWriter->muonPt(energy*sqrt(pzdir*pzdir));
  m_eventWriter->muonTheta(atan(pxdir/pzdir));
  m_eventWriter->muonPhi(atan(pydir/pzdir));
  m_eventWriter->muonVx(muonX);
  m_eventWriter->muonVy(muonY);
  m_eventWriter->muonVz(muonZ);

  ///  G4double gammaE = 0.01;
  ///  double gammaX = G4RandFlat::shoot(0.,1500.)-750.;
  ///  double gammaY = G4RandFlat::shoot(0.,1500.)-750.;
  ///  //  double gammaZ = G4RandFlat::shoot(0.,3600.)+900.;
  ///  double gammaZ = G4RandFlat::shoot(0.,4100)+300;
  ///  //  std::cout << "gamma x,y,z " << gammaX << " " << gammaY << " " << gammaZ << std::endl;
  ///  double gammaXDir = 0.05;
  ///  double gammaYDir = 0.05;
  ///  double gammaZDir = 1.0;
  ///  m_particleGun[1]->SetParticlePosition(G4ThreeVector(gammaX,gammaY,gammaZ));
  ///  m_particleGun[1]->SetParticleMomentumDirection(G4ThreeVector(gammaXDir,gammaYDir,gammaZDir));
  ///  m_particleGun[1]->SetParticleEnergy(gammaE);
  ///  m_particleGun[1]->GeneratePrimaryVertex(event);
  
}
