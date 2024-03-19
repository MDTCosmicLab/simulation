#ifndef TRACK_H
#define TRACK_H

#include <vector>
#include <utility>
#include "TVector2.h"


class Track {

 public:

  Track(double a, double b);
  ~Track();
  
  std::pair<double,double> getPars();
  void setPars(double a, double b);

  std::vector<double>& getDriftTimes() {return m_ionTime;}
  std::vector<double>& getDriftDistances() {return m_ionDistance;}
  
 private:
  
  void intersections();
  void clusters();
  // get the time from the distance
  double getTime(double distance);
    
  std::pair<double,double> m_pars;
  std::vector<double> m_ionPosition;
  std::vector<double> m_ionDistance;
  std::vector<double> m_ionTime;

  // entrance and exit in the tube
  TVector2 m_firstPoint;
  TVector2 m_lastPoint;

  double m_driftDistance[16]={0.,  1.,   2.,   3.,   4.,   5.,   6.,   7.,
			      8.,   9.,   10.,  11.,  12.,  13.,  14.,  15.};
  double m_driftTime[16]    ={0., 20.,  40.,  60.,  80.,  110., 140., 180.,
			      230., 280., 350., 420., 510., 600., 690., 780. };
  
  
};

#endif  // TRACK_H
