#ifndef MDTACTIONINIT_H
#define MDTACTIONINIT_H

#include "G4VUserActionInitialization.hh"
#include "EventWriter.h"

class MdtActionInit : public G4VUserActionInitialization
{
  
public:

  MdtActionInit(EventWriter* eventWriter);

  void setBackground(double bgRate)  {m_bgRate=bgRate;}
  
  virtual ~MdtActionInit();
  
  virtual void Build() const;
  
private:
  
  EventWriter* m_eventWriter;
  /// background in kHz/cm^2
  double m_bgRate;
  
};


#endif
