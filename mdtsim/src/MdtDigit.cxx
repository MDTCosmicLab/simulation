#include "MdtDigit.h"
#include "TRandom.h"

MdtDigit::MdtDigit(double norm, double posX, double posY,
		 double sigmaX, double sigmaY, double posZ) :
  G4VDigi()
{

  PdfPars pdfX,pdfY;
  pdfX.gausPar1[0]=norm;
  pdfX.gausPar1[1]=posX;
  pdfX.gausPar1[2]=sigmaX;
  pdfY.gausPar1[0]=norm;
  pdfY.gausPar1[1]=posY;
  pdfY.gausPar1[2]=sigmaY;
  
  m_positionX = PositionPdf(pdfX);
  m_positionY = PositionPdf(pdfY);

  m_positionZ = posZ;

  
}

MdtDigit::~MdtDigit()
{

}
