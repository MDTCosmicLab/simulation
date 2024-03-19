#include "Track.h"
#include "SignalShape.h"

#include "TRandom.h"
#include "TFile.h"
#include "TH2F.h"
#include "TProfile.h"

#include <iostream>

int main(int argc, char **argv)
{

  std::cout << "Number of arguments: " << argc << std::endl;

  double seed;
  if (argc>=2) {
    seed=atof(argv[1]);
  }

  TRandom rand(seed);

  TFile* outFile = new TFile("out.root","RECREATE");

  TH2F* leading  = new TH2F("leading","leading",150.,0.,15,1000.,0.,1000.); 
  TH2F* trailing = new TH2F("trailing","trailing",150.,0.,15,1000.,0.,1000.); 
  TH1F* nLeading = new TH1F("nLeading","nLeading",10.,-0.5,9.5);
  TH1F* nTrailing = new TH1F("nTrailing","nTrailing",10.,-0.5,9.5);
  
  std::vector<int> edge;
  std::vector<double> times;
  double R=0;
  for (int jev=0 ; jev<100 ; ++jev) {

    if ( jev%100==0 ) { 
      std::cout << ">>> Signals processed: " << jev << std::endl;
    }

    SignalShape* s = new SignalShape();
    R=rand.Uniform(15.0);
    Track track=Track(0,0);
    std::vector<double> driftTimes = track.getDriftTimes();
    std::vector<double> driftDist  = track.getDriftDistances();
    
    for (unsigned int i=0 ; i<driftTimes.size() ; ++i) {
      /// generate number of electrons according to a poisson distr
      double nel = rand.Poisson(3);

      //      std::cout << "Drift dist, time: " << driftDist[i] << " " << driftTimes[i] << std::endl;
      
      s->addCluster(driftTimes[i],nel);
    }
    
    TH1F* signal=s->getSignal();
    signal->Write();

    s->getCrossings(edge,times);
    int nlead=0;
    int ntrail=0;
    for (unsigned int jcross=0; jcross<times.size() ; ++jcross) {
      if (edge[jcross]==1) {
	//	std::cout << "Leading " << jcross << " " << times[jcross] << std::endl;
	leading->Fill(R,times[jcross]);
	nlead++;
      }
      else if (edge[jcross]==-1) {
	//std::cout << "Trailing " << jcross << " " << times[jcross] << std::endl;
	trailing->Fill(R,times[jcross]);
	ntrail++;
      }
    }
    nLeading->Fill(nlead,1.0);
    nTrailing->Fill(ntrail,1.0);
    edge.clear();
    times.clear();

    delete s;
  }

  leading->Write();
  trailing->Write();
  nLeading->Write();
  nTrailing->Write();
  
  outFile->Close();
  
}
