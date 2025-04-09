#ifndef MDTDIGITIZER_H
#define MDTDIGITIZER_H

#include "G4VDigitizerModule.hh"
#include "MdtHit.h"
#include "EventWriter.h"

class MdtDigitizer : public G4VDigitizerModule
{
  
public:
  MdtDigitizer(const G4String name, EventWriter* ew);
  ~MdtDigitizer();
  
  void Digitize();

  void setHitCollection(MdtHitCollection* hitCol) {m_hitCollection = hitCol;}

  MdtHitCollection* getHitCollection() {return m_hitCollection;}
  
private:

  EventWriter* m_eventWriter;
  
  MdtHitCollection* m_hitCollection;

};


#endif   /// MDTDIGITIZER_H
