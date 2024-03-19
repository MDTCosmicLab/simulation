#ifndef SIGNALSHAPE_H
#define SIGNALSHAPE_H

#include "TH1F.h"

#include <vector>
#include <utility>

class SignalShape {
  
 public:
  
  SignalShape();
  ~SignalShape();

  TH1F* getSignal() {return m_signal;}

  void addCluster(double time,int nel);

  double getShape(double t);

  void getCrossings(std::vector<int>& edge, std::vector<double>& time);

  void setLeadingThresh(double val) {m_leadingThresh=val;}
  void setTrailingThresh(double val) {m_trailingThresh=val;}
  
 private:

  double m_firstBin;
  double m_lastBin;
  double m_nBins;
  double m_binSize;

  double m_leadingThresh;
  double m_trailingThresh;
  double m_thresholdNorm;
  
  TH1F* m_signal;
  std::vector<std::pair<double,double>> m_shape;

};

#endif
