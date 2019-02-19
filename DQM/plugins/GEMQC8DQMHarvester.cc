#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"

//DQM services
#include "DQMServices/Core/interface/DQMStore.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DQMServices/Core/interface/MonitorElement.h"
#include "DQMServices/Core/interface/DQMEDHarvester.h"

using namespace edm;

class GEMQC8DQMHarvester: public DQMEDHarvester
{  
public:
  GEMQC8DQMHarvester(const edm::ParameterSet&) {};
  ~GEMQC8DQMHarvester() override {};
  static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);
protected:
  void dqmEndJob(DQMStore::IBooker &, DQMStore::IGetter &) override {};
};

void GEMQC8DQMHarvester::fillDescriptions(edm::ConfigurationDescriptions & descriptions)
{
  edm::ParameterSetDescription desc;
  descriptions.add("GEMQC8DQMHarvester", desc);  
}

DEFINE_FWK_MODULE(GEMQC8DQMHarvester);
