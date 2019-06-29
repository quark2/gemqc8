import ROOT
import os
import sys
import shutil

def plot(run, step):
    infile = ROOT.TFile("alignment_out_run_000127.root")
    tree = infile.Get("AlignmentQC8/tree")
    histos = []
    outdir = "../step"+str(step)
    if not(os.path.exists(outdir)):
       #shutil.rmtree(outdir)
        os.makedirs(outdir)
    for i in range(10,20):
        h = ROOT.TH1F("h"+str(i)+"]", "h"+str(i)+"]", 100, -30, 30)
        tree.Project("h"+str(i)+"]","chRecHitX["+str(i)+"]")
        canvas = ROOT.TCanvas("chRecHitX"+str(i)+"_step"+str(step),"c1",50,50,700,600)
        h.Draw()
        canvas.Print(outdir+"/chRecHitX_"+str(i)+"_step"+str(step)+".png")
    for i in range(10,20):
        h = ROOT.TH1F("h"+str(i)+"]", "h"+str(i)+"]", 100, -20, 20)
        tree.Project("h"+str(i)+"]","chTrajHitX["+str(i)+"]")
        canvas = ROOT.TCanvas("chTrajHitX"+str(i)+"_step"+str(step),"c1",50,50,700,600)
        h.Draw()
        canvas.Print(outdir+"/chTrajHitX_"+str(i)+"_step"+str(step)+".png")
    for i in range(6,11):
        canvas = ROOT.TCanvas("hchEtaResidualX_"+str(i)+"_step"+str(step),"c1",50,50,1500,600)
        canvas.Divide(4,2)
        for j in range(1,9):
            print "getting AlignmentQC8/hchEtaResidualX_"+str(i)+"_"+str(j)
            h = infile.Get("AlignmentQC8/hchEtaResidualX_"+str(i)+"_"+str(j))
            canvas.cd(j)
            h.Draw()
        canvas.Print(outdir+"/hchEtaResidualX_"+str(i)+"_step"+str(step)+".png")

if __name__ == '__main__':
    ROOT.gStyle.SetPalette(1)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gROOT.SetBatch()        # don't pop up canvases
    run_number = sys.argv[1]
    step_number = sys.argv[2]
    plot(run_number, step_number)
