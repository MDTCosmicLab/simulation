#include "Track.h"
#include "TRandom.h"

#include<iostream>
#include<math.h>

Track::Track(double a, double b) :
  m_pars(a,b),
  m_ionPosition(),
  m_ionDistance(),
  m_ionTime()
{

  // get the intersections
  intersections();
  double x1=m_firstPoint.X();
  double x2=m_lastPoint.X();
  double y1=m_firstPoint.Y();
  double y2=m_lastPoint.Y();
  
  double length=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  
  //  std::cout << "x1,y1: " << x1 << " , " << y1
  //	    << "    x2,y2: " << x2 << " , " << y2 << "  length: " << length << std::endl;

  // get the ioization clusters
  double lambda=0.1;
  double totalPath=0.0;
  TRandom rand=TRandom();
  
  while (totalPath<length) {
    double path = rand.Exp(lambda);
    totalPath += path;
    if ( totalPath<length ) { 
      double xp=x1+totalPath;
      double yp=y1;
      m_ionPosition.push_back(xp);
      m_ionDistance.push_back( sqrt( xp*xp + yp*yp) );
    }
  }

  //  for ( unsigned int i=0 ; i<m_ionDistance.size() ; ++i ) {
  //    std::cout << "Position and distance: " << m_ionPosition[i] << " " << m_ionDistance[i] << std::endl;
  //  }

  // sort the distances
  std::sort(m_ionDistance.begin(),m_ionDistance.end());
  
  for ( unsigned int i=0 ; i<m_ionDistance.size() ; ++i ) {
    m_ionTime.push_back(getTime(m_ionDistance[i]));
    //    std::cout << "Distance and time: " << m_ionDistance[i] << " " << m_ionTime[i] << std::endl;
  }

}

Track::~Track()
{
  
}

/// get the drift time from the drift distances
double Track::getTime(double distance) {
  /// simple linear
  //  double time=(distance/15)*780.;
  double time=-1000.;
  // use a drift velocity
  for (unsigned int i=0 ; i<15 ; ++i) {
    if (distance>m_driftDistance[i] && distance<m_driftDistance[i+1]) {
      time = m_driftTime[i] +
	(distance-m_driftDistance[i])*(m_driftTime[i+1]-m_driftTime[i])
	/(m_driftDistance[i+1]-m_driftDistance[i]);
    }
  }
  return time;
}

/// get the intersections with the tube walls
void Track::intersections()
{
  double r=15.0;
  double a=m_pars.first;
  double b=m_pars.second;

  // x of first intersection
  double d=sqrt(a*a*r*r-b*b+r*r);
  double x1= (-a*b-d)/(a*a+1);
  double x2= (-a*b+d)/(a*a+1);

  /// for ang coeff=0 this should not be needed
  double y1=a*x1+b;
  double y2=a*x2+b;

  m_firstPoint = TVector2(x1,y1);
  m_lastPoint  = TVector2(x2,y2);

}
