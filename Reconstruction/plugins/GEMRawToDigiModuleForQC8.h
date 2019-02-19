#ifndef gemqc8_Reconstruction_GEMRawToDigiModuleForQC8_h
#define gemqc8_Reconstruction_GEMRawToDigiModuleForQC8_h

/** \class GEMRawToDigiModuleForQC8
 *  \based on CSCDigiToRawModule
 *  \author J. Lee - UoS
 */

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/global/EDProducer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"

//#include "gemqc8/Reconstruction/interface/GEMVfatStatusDigi.h"

#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/GEMDigi/interface/GEMDigiCollection.h"
//#include "DataFormats/GEMDigi/interface/GEMVfatStatusDigiCollection.h"
//#include "DataFormats/GEMDigi/interface/GEMGEBdataCollection.h"
//#include "DataFormats/GEMDigi/interface/GEMAMCdataCollection.h"
//#include "DataFormats/GEMDigi/interface/GEMAMC13EventCollection.h"
#include "gemqc8/Reconstruction/interface/GEMVfatStatusDigiQC8Collection.h"
#include "gemqc8/Reconstruction/interface/GEMGEBdataCollection.h"
#include "gemqc8/Reconstruction/interface/GEMAMCdataCollection.h"
#include "gemqc8/Reconstruction/interface/GEMAMC13EventCollection.h"

#include "CondFormats/DataRecord/interface/GEMELMapRcd.h"
#include "CondFormats/GEMObjects/interface/GEMELMap.h"
#include "CondFormats/GEMObjects/interface/GEMROmap.h"
#include "EventFilter/GEMRawToDigi/interface/AMC13Event.h"
#include "EventFilter/GEMRawToDigi/interface/VFATdata.h"

namespace edm {
   class ConfigurationDescriptions;
}

class GEMRawToDigiModuleForQC8 : public edm::global::EDProducer<edm::RunCache<GEMROmap> > {
 public:
  /// Constructor
  GEMRawToDigiModuleForQC8(const edm::ParameterSet & pset);

  // global::EDProducer
  std::shared_ptr<GEMROmap> globalBeginRun(edm::Run const&, edm::EventSetup const&) const override;  
  void produce(edm::StreamID, edm::Event&, edm::EventSetup const&) const override;
  void globalEndRun(edm::Run const&, edm::EventSetup const&) const override {};
  
  // Fill parameters descriptions
  static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);

 private:
  
  edm::EDGetTokenT<FEDRawDataCollection> fed_token;
  bool useDBEMap_;
  bool unPackStatusDigis_;
  bool embedAMC13EventData_;
};
DEFINE_FWK_MODULE(GEMRawToDigiModuleForQC8);
#endif
