#include "MdtRun.h"

MdtRun::MdtRun() :
  G4Run()
{ }

MdtRun::~MdtRun()
{ }

void MdtRun::Merge(const G4Run* run){
  G4Run::Merge(run); 
} 

