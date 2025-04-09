#ifndef MDTDETECTORDESCRIPTION_H
#define MDTDETECTORDESCRIPTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4String.hh"
#include "G4GDMLParser.hh"
#include "EventWriter.h"

#include <map>

class MdtDetectorDescription : public G4VUserDetectorConstruction
{

 public:

  MdtDetectorDescription(G4String fileName, EventWriter* eventWriter);
  virtual ~MdtDetectorDescription();

  virtual G4VPhysicalVolume* Construct();

  virtual void ConstructSDandField();
  
  int getDetectorId(G4String name);
  
 private:

  // file reader
  G4GDMLParser m_parser;
  // file name
  G4String m_fileName;
  // map between the physical volume names and the detector Id
  std::map<G4String,unsigned int> m_physicalVolumes;

  // the ntuple writer
  EventWriter* m_eventWriter;
  
};


#endif
