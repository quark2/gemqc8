import ROOT
import sys, os


strFilename = sys.argv[ 1 ]
strPathMain = "DQMData/Run 1/GEM/Run summary/"

fMain = ROOT.TFile.Open(strFilename)

canvMain = ROOT.TCanvas("c1", "", 800, 600)

dicHist = {
    "StatusDigi": 
      ["amc buffState", "amc chTimeOut", "amc davCnt", "amc oosGlib", "amc ttsState", 
       "amc13Event bx ok", "amcData bx ok", 
       "geb inFIFOund", "geb input status", "geb no vfats", "geb stuckData", "geb zeroSupWordsCnt", 
       "vfat flag", "vfat flag per geb", "vfat quality", "vfat quality per geb", "vfatPos vs Channel"], 
    "digi": 
      ["Digi_Strips_Gemini_15_l_1", "Digi_Strips_Gemini_15_l_1_VFAT", 
       "Digi_Strips_Gemini_15_l_2", "Digi_Strips_Gemini_15_l_2_VFAT"], 
    "recHit": 
      ["StripFired_Gemini_15_la_1", "StripFired_Gemini_15_la_2", 
       "VFAT_vs_ClusterSize_Gemini_15_la_1", "VFAT_vs_ClusterSize_Gemini_15_la_2", 
       "recHit_Gemini_15_la_1", "recHit_Gemini_15_la_2", 
       "recHit_x_Gemini_15_la_1", "recHit_x_Gemini_15_la_2"]
  }

for strStage in dicHist.keys(): 
  for strNameHist in dicHist[ strStage ]: 
    h1 = fMain.Get(strPathMain + strStage + "/" + strNameHist)
    h1.Draw("colz")
    canvMain.SaveAs(strStage + "_" + strNameHist.replace(" ", "_") + ".png")

fMain.Close()


