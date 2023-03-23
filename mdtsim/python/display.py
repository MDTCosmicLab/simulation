import numpy as np
from ROOT import TFile,TTree
import matplotlib.pyplot as plt

rootFile=TFile("tksim.root")
tree=rootFile.Get("tksim")

nevents=0

for event in tree:

    ySig=np.empty(0)
    zSig=np.empty(0)
    yBkg=np.empty(0)
    zBkg=np.empty(0)
    #loop on the digits
    ndigits = event.yDigHitLink.size()
    for idig in range(ndigits):
        if abs(event.yDigPdgId[idig])==13:
            ySig = np.append(ySig,event.yDigY[idig])
            zSig = np.append(zSig,event.yDigZ[idig])
        else:
            yBkg = np.append(yBkg,event.yDigY[idig])
            zBkg = np.append(zBkg,event.yDigZ[idig])
            
    print (zSig,ySig)
    # make the display
    plt.scatter(zSig,ySig,s=0.1,marker='.')
    plt.scatter(zBkg,yBkg,s=0.1,marker='.')
    plt.savefig("event.pdf")
    nevents=nevents+1

    if nevents==3:
        break


        
        
