#include "SignalShape.h"
#include <iostream>
#include <fstream>

SignalShape::SignalShape()
{
  
  m_nBins=6000;
  m_firstBin=-100.;
  m_lastBin=1400.;
  m_binSize=(m_lastBin-m_firstBin)/m_nBins;

  m_leadingThresh=25.;
  m_trailingThresh=25.;
  m_thresholdNorm=25./7.;
  
  m_signal=new TH1F("signal","signal",m_nBins,m_firstBin,m_lastBin);

  /// read the signal shape from a file
  //  std::ifstream infile("ASD_Posch.txt");
  std::ifstream infile("ASD6_Abovyan.txt");
  double a,b;
  while(infile>> a >> b) {
    //    std::cout << a << " " << b << std::endl;
    std::pair<double,double> ts(a,b);
    m_shape.push_back(ts);
  }

}

SignalShape::~SignalShape()
{
  delete m_signal;
}

void SignalShape::addCluster(double time, int nel) {

  //  std::cout << " adding a cluster at time " << time << std::endl;
  for (double t=time ; t<time+300 ; t+=m_binSize) {
    int ibin=(t-m_firstBin)/m_binSize;
    /// increment the bin with the additional signal
    double binContent=m_signal->GetBinContent(ibin);
    double sig=this->getShape(t-time)*((double) nel);
    m_signal->SetBinContent(ibin,binContent+sig);
  }
  
}


double SignalShape::getShape(double t)
{

  double sig=0;
  for (unsigned int i=0 ; i<m_shape.size()-1 ; ++i ) {
    /// interpolate the signal
    double t1=m_shape[i].first;
    double t2=m_shape[i+1].first;
    double s1=m_shape[i].second;
    double s2=m_shape[i+1].second;
    if (t>t1 && t<=t2 ) {
      sig=s1+(t-t1)*(s2-s1)/(t2-t1);
    }
  }

  return sig;
  
}

void SignalShape::getCrossings(std::vector<int>& edge, std::vector<double>& time)
{

  bool leadingPassed=false;
  for (unsigned int i=0 ; i<m_nBins-1 ; ++i) {
    double bin1=m_signal->GetBinContent(i);
    double bin2=m_signal->GetBinContent(i+1);

    //    std::cout << i << " " << bin1 << std::endl;
    
    if (!leadingPassed) {
      if ( bin1*m_thresholdNorm<m_leadingThresh && bin2*m_thresholdNorm>=m_leadingThresh ) {
	//	std::cout << "LEADING In bin, bin1, bin2: " << i << ", " << bin1*m_thresholdNorm << ", "
	//	  << bin2*m_thresholdNorm << std::endl;
	double val= (m_leadingThresh-bin1*m_thresholdNorm)*m_binSize/
	  (bin2*m_thresholdNorm-bin1*m_thresholdNorm)+(i*m_binSize+m_firstBin);
	edge.push_back(1);
	time.push_back(val);
	leadingPassed=true;
      }
    }
    else {
      if ( bin1*m_thresholdNorm>m_trailingThresh && bin2*m_thresholdNorm<=m_trailingThresh ) {
	//std::cout << "TRAILING In bin, bin1, bin2: " << i << ", " << bin1*m_thresholdNorm << ", "
	//	  << bin2*m_thresholdNorm << std::endl;
	double val= (-m_leadingThresh+bin1*m_thresholdNorm)*m_binSize/
	  (-bin2*m_thresholdNorm+bin1*m_thresholdNorm)+(i*m_binSize+m_firstBin);
	edge.push_back(-1);
	time.push_back(val);
	leadingPassed=false;
      }
    }
    
  }

}



