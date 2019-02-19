import FWCore.ParameterSet.Config as cms

#from DQM.GEM.GEMDQMSource_cfi import *
#from DQM.GEM.GEMDQMSourceDigi_cfi import *
#from DQM.GEM.GEMDQMStatusDigi_cfi import *
#from DQM.GEM.GEMDQMHarvester_cfi import *
from gemqc8.DQM.GEMQC8DQMSource_cfi import *
from gemqc8.DQM.GEMQC8DQMSourceDigi_cfi import *
from gemqc8.DQM.GEMQC8DQMStatusDigi_cfi import *
from gemqc8.DQM.GEMQC8DQMHarvester_cfi import *

GEMDQM = cms.Sequence(
  GEMQC8DQMSource
  *GEMQC8DQMSourceDigi
  *GEMQC8DQMStatusDigi
  +GEMQC8DQMHarvester
)
