#include "MdtDigitizer.h"
#include "MdtDigit.h"
#include "Randomize.hh"

MdtDigitizer::MdtDigitizer(const G4String name, EventWriter* ew) :
  G4VDigitizerModule(name),
  m_eventWriter(ew),
  m_hitCollection(NULL)
{

}


MdtDigitizer::~MdtDigitizer()
{

}

void MdtDigitizer::Digitize()
{

  if (!m_hitCollection) {
    G4cout << "ERROR: Hit collection not initialized, can't run digitization " << G4endl;
    return;
  }

  double eff = 0.95;
  // loop on the hits
  for ( unsigned int i = 0 ; i<m_hitCollection->GetSize() ; ++i ) {

    MdtHit * hit = dynamic_cast<MdtHit*>(m_hitCollection->GetHit(i));

  }
  
  return;
}



