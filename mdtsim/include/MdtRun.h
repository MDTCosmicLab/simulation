#ifndef MDTRUN_H
#define MDTRUN_H

#include "G4Run.hh"

class MdtRun : public G4Run
{
 public:
  MdtRun();
  virtual ~MdtRun();

  virtual void Merge(const G4Run*);

};

#endif
