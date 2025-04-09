#include "EventWriter.h"
#include "G4RootAnalysisManager.hh"


EventWriter::EventWriter() :
  m_fileName("tksim.root")
{

}

EventWriter::EventWriter(std::string fileName) :
  m_fileName(fileName)
{

}

EventWriter::~EventWriter()
{
  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

void EventWriter::bookTree()
{

  G4RootAnalysisManager* analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->OpenFile(m_fileName.c_str());
  
  analysisManager->CreateNtuple("tksim","tksimTree");
  /// add variables to the ntuple
  analysisManager->CreateNtupleIColumn(0,"nMuon",     m_nMuon);
  analysisManager->CreateNtupleDColumn(0,"muonPt",    m_muonPt);
  analysisManager->CreateNtupleDColumn(0,"muonTheta", m_muonTheta);
  analysisManager->CreateNtupleDColumn(0,"muonPhi",   m_muonPhi);
  analysisManager->CreateNtupleDColumn(0,"muonVx",    m_muonVx);
  analysisManager->CreateNtupleDColumn(0,"muonVy",    m_muonVy);
  analysisManager->CreateNtupleDColumn(0,"muonVz",    m_muonVz);

//  analysisManager->CreateNtupleIColumn(0,"enDepDetId",  m_enDepDetId);
//  analysisManager->CreateNtupleIColumn(0,"enDepPdgId",  m_enDepPdgId);
//  analysisManager->CreateNtupleIColumn(0,"enDepIsExit", m_enDepIsExit);
//  analysisManager->CreateNtupleDColumn(0,"enDepX",      m_enDepX);
//  analysisManager->CreateNtupleDColumn(0,"enDepY",      m_enDepY);
//  analysisManager->CreateNtupleDColumn(0,"enDepZ",      m_enDepZ);
//  analysisManager->CreateNtupleDColumn(0,"enDepPX",     m_enDepPX);
//  analysisManager->CreateNtupleDColumn(0,"enDepPY",     m_enDepPY);
//  analysisManager->CreateNtupleDColumn(0,"enDepPZ",     m_enDepPZ);
//  analysisManager->CreateNtupleDColumn(0,"enDep",       m_enDep);
  
  analysisManager->CreateNtupleIColumn(0,"hitDetId",m_hitDetId);
  analysisManager->CreateNtupleIColumn(0,"hitPdgId",m_hitPdgId);
  analysisManager->CreateNtupleIColumn(0,"hitIsExit",m_hitIsExit);
  analysisManager->CreateNtupleDColumn(0,"hitX",m_hitX);
  analysisManager->CreateNtupleDColumn(0,"hitY",m_hitY);
  analysisManager->CreateNtupleDColumn(0,"hitZ",m_hitZ);
  analysisManager->CreateNtupleDColumn(0,"hitPX",m_hitPX);
  analysisManager->CreateNtupleDColumn(0,"hitPY",m_hitPY);
  analysisManager->CreateNtupleDColumn(0,"hitPZ",m_hitPZ);
  analysisManager->CreateNtupleDColumn(0,"hitEnergyDep",m_hitEnergyDep);

  analysisManager->CreateNtupleIColumn(0,"smearDigHitLink", m_smearDigHitLink);
  analysisManager->CreateNtupleIColumn(0,"smearDigLayer",   m_smearDigLayer);
  analysisManager->CreateNtupleIColumn(0,"smearDigPdgId",   m_smearDigPdgId);
  analysisManager->CreateNtupleDColumn(0,"smearDigX",       m_smearDigX);
  analysisManager->CreateNtupleDColumn(0,"smearDigY",       m_smearDigY);
  analysisManager->CreateNtupleDColumn(0,"smearDigZ",       m_smearDigZ);
  analysisManager->CreateNtupleDColumn(0,"smearDigErr",     m_smearDigErr);

  analysisManager->CreateNtupleIColumn(0,"yDigHitLink", m_yDigHitLink);
  analysisManager->CreateNtupleIColumn(0,"yDigLayer",   m_yDigLayer);
  analysisManager->CreateNtupleIColumn(0,"yDigPdgId",   m_yDigPdgId);
  analysisManager->CreateNtupleIColumn(0,"yDigChan",    m_yDigChan);
  analysisManager->CreateNtupleDColumn(0,"yDigCharge",  m_yDigCharge);
  analysisManager->CreateNtupleDColumn(0,"yDigX",       m_yDigX);
  analysisManager->CreateNtupleDColumn(0,"yDigY",       m_yDigY);
  analysisManager->CreateNtupleDColumn(0,"yDigZ",       m_yDigZ);
  
  analysisManager->CreateNtupleIColumn(0,"partVol",m_partVol);
  analysisManager->CreateNtupleIColumn(0,"partId",m_partId);
  analysisManager->CreateNtupleDColumn(0,"partPX",m_partPX);
  analysisManager->CreateNtupleDColumn(0,"partPY",m_partPY);
  analysisManager->CreateNtupleDColumn(0,"partPZ",m_partPZ);
  analysisManager->CreateNtupleDColumn(0,"partPosX",m_partPosX);
  analysisManager->CreateNtupleDColumn(0,"partPosY",m_partPosY);
  analysisManager->CreateNtupleDColumn(0,"partPosZ",m_partPosZ);
  analysisManager->CreateNtupleDColumn(0,"partE",m_partE);
  analysisManager->CreateNtupleDColumn(0,"partVX",m_partVX);
  analysisManager->CreateNtupleDColumn(0,"partVY",m_partVY);
  analysisManager->CreateNtupleDColumn(0,"partVZ",m_partVZ);

  analysisManager->CreateNtupleDColumn(0,"recoY",m_recoY);
  analysisManager->CreateNtupleDColumn(0,"recoZ",m_recoZ);
  analysisManager->CreateNtupleIColumn(0,"recoHitIndex",m_recoHitIndex);
  analysisManager->CreateNtupleIColumn(0,"recoPdgId",m_recoPdgId);
  
  analysisManager->FinishNtuple(0);
  
}

void EventWriter::clearTree()
{

  m_nMuon.clear();
  m_muonPt.clear();
  m_muonTheta.clear();
  m_muonPhi.clear();
  m_muonVx.clear();
  m_muonVy.clear();
  m_muonVz.clear();
  
  m_enDepDetId.clear();
  m_enDepPdgId.clear();
  m_enDepIsExit.clear();
  m_enDepX.clear();
  m_enDepY.clear();
  m_enDepZ.clear();
  m_enDepPX.clear();
  m_enDepPY.clear();
  m_enDepPZ.clear();
  m_enDep.clear();

  m_hitDetId.clear();
  m_hitPdgId.clear();
  m_hitIsExit.clear();
  m_hitX.clear();
  m_hitY.clear();
  m_hitZ.clear();
  m_hitPX.clear();
  m_hitPY.clear();
  m_hitPZ.clear();
  m_hitEnergyDep.clear();

  m_smearDigHitLink.clear();
  m_smearDigLayer.clear();
  m_smearDigPdgId.clear();
  m_smearDigX.clear();
  m_smearDigY.clear();
  m_smearDigZ.clear();
  m_smearDigErr.clear();

  m_yDigHitLink.clear();
  m_yDigLayer.clear();
  m_yDigPdgId.clear();
  m_yDigChan.clear();
  m_yDigCharge.clear();
  m_yDigX.clear();
  m_yDigY.clear();
  m_yDigZ.clear();

  m_partVol.clear();
  m_partId.clear();
  m_partPX.clear();
  m_partPY.clear();
  m_partPZ.clear();
  m_partPosX.clear();
  m_partPosY.clear();
  m_partPosZ.clear();
  m_partPY.clear();
  m_partPZ.clear();
  m_partE.clear();
  m_partVX.clear();
  m_partVY.clear();
  m_partVZ.clear();

  m_recoY.clear();
  m_recoZ.clear();
  m_recoHitIndex.clear();
  m_recoPdgId.clear();
  
}
