#ifndef gemqc8_Reconstruction_GEMVfatStatusDigiQC8Collection_h
#define gemqc8_Reconstruction_GEMVfatStatusDigiQC8Collection_h

//#include "DataFormats/GEMDigi/interface/GEMVfatStatusDigi.h"
#include "gemqc8/Reconstruction/interface/GEMVfatStatusDigiQC8.h"
#include "DataFormats/MuonDetId/interface/GEMDetId.h"
#include "DataFormats/MuonData/interface/MuonDigiCollection.h"

typedef MuonDigiCollection<GEMDetId, GEMVfatStatusDigiQC8> GEMVfatStatusDigiQC8Collection;

#endif
