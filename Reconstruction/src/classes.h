//#include "DataFormats/GEMDigi/interface/GEMVfatStatusDigi.h"
//#include "DataFormats/GEMDigi/interface/GEMVfatStatusDigiCollection.h"
#include "gemqc8/Reconstruction/interface/GEMVfatStatusDigiQC8.h"
#include "gemqc8/Reconstruction/interface/GEMVfatStatusDigiQC8Collection.h"

#include "DataFormats/Common/interface/Wrapper.h"
#include <vector>

namespace gemqc8_Reconstruction {
  struct dictionary {
    GEMVfatStatusDigiQC8 gvs;
    std::vector<GEMVfatStatusDigiQC8> vgvs;
    GEMVfatStatusDigiQC8Collection gvscol;
    edm::Wrapper<GEMVfatStatusDigiQC8Collection> wgvs;
  };
}
