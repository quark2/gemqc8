import csv
import os
import sys
import io
import subprocess
import time
import datetime

if __name__ == '__main__':

    # Define the parser
    import argparse
    parser = argparse.ArgumentParser(description="QC8 data analysis step 3. Fast efficiency calculation. For any doubt: https://twiki.cern.ch/twiki/bin/view/CMS/GEMCosmicRayAnalysis")
    # Positional arguments
    parser.add_argument("run_number", type=int, help="Specify the run number")
    args = parser.parse_args()

    # Different paths definition
    srcPath = os.path.join(os.environ[ "CMSSW_BASE" ], "src")
    pyhtonModulesPath = os.path.join(srcPath, "Analysis/GEMQC8/python/")
    runPath = os.path.join(srcPath, "Analysis/GEMQC8/test/")
    configTablesPath = os.path.join(srcPath, "Analysis/GEMQC8/data/StandConfigurationTables/")
    alignmentTablesPath = os.path.join(srcPath, "Analysis/GEMQC8/data/StandAligmentTables/")
    resDirPath = os.path.join(os.environ[ "CMSSW_BASE" ], "../")

    sys.path.insert(0,pyhtonModulesPath)

    import dumpDBtables
    import config_creator
    import geometry_files_creator

    # Retrieve start date and time of the run
    fpath =  "/eos/cms/store/group/dpg_gem/comm_gem/QC8_Commissioning/run{:06d}/".format(int(args.run_number))
    for x in os.listdir(fpath):
        if x.endswith("ls0001_allindex.raw"):
            file0name = x
            break
        elif x.endswith("chunk_000000.dat"):
            file0name = x
            break
        else:
            print "Check the data files... First file (at least) is missing!"
    startDateTime = file0name.split('_')[3] + "_" + file0name.split('_')[4]
    time.sleep(1)

    # Get stand configuration table from the DB
    if int(args.run_number) > 237:
        dumpDBtables.getConfigurationTable(args.run_number,startDateTime)

    # Generate configuration file
    config_creator.configMaker(args.run_number)
    time.sleep(1)

    # Generate geometry files
    geometry_files_creator.geomMaker(args.run_number,"noAlignment")
    time.sleep(1)

    # Compiling after the generation of the geometry files
    scramCommand = "scram build -j 4"
    scramming = subprocess.Popen(scramCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=srcPath)
    while scramming.poll() is None:
        line = scramming.stdout.readline()
        print(line)
    print scramming.stdout.read()
    scramming.communicate()
    time.sleep(1)

    # Running the CMSSW code
    runCommand = "cmsRun -n 8 runGEMCosmicStand_fast_efficiency.py"
    running = subprocess.Popen(runCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=runPath)
    while running.poll() is None:
        line = running.stdout.readline()
        print(line)
    print running.stdout.read()
    running.communicate()
    time.sleep(1)

    #  # Creating folder outside the CMMSW release to put the output files and plots
    outDirName = "Results_QC8_fast_efficiency_run_"+str(args.run_number)
    #---# Remove old version if want to recreate
    if (os.path.exists(resDirPath+outDirName)):
        rmDirCommand = "rm -rf "+outDirName
        rmDir = subprocess.Popen(rmDirCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=resDirPath)
        rmDir.communicate()
    #---# Create the new empty folder
    resDirCommand = "mkdir "+outDirName
    resDir = subprocess.Popen(resDirCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=resDirPath)
    resDir.communicate()
    time.sleep(1)

    # Create folders for ouput plots per chamber
    import configureRun_cfi as runConfig
    SuperChType = runConfig.StandConfiguration
    #effoutDir = os.path.abspath("launcher_fast_efficiency.py").split('QC8Test')[0] + outDirName
    effoutDir = resDirPath + outDirName
    for i in range (0,30):
        if (SuperChType[int(i/2)] != '0'):
            plotsDirCommand = "mkdir outPlots_Chamber_Pos_" + str(i)
            plotsDirChamber = subprocess.Popen(plotsDirCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=effoutDir)
            plotsDirChamber.communicate()
    time.sleep(1)

    # Selecting the correct output file, changing the name and moving to the output folder
    out_name = 'out_run_'
    for i in range(6-len(str(args.run_number))):
        out_name = out_name + '0'
    out_name = out_name + str(args.run_number) + '.root'

    mvToDirCommand = "mv fast_efficiency_" + out_name + " " + resDirPath+outDirName + "/fast_efficiency_" + out_name
    movingToDir = subprocess.Popen(mvToDirCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=runPath)
    movingToDir.communicate()
    time.sleep(1)

    # Efficiency computation & output
    effCommand = "root -l -q " + runPath + "macro_fast_efficiency.c(" + str(args.run_number) + ",\"" + configTablesPath + "\")"
    efficiency = subprocess.Popen(effCommand.split(),stdout=subprocess.PIPE,universal_newlines=True,cwd=effoutDir)
    while efficiency.poll() is None:
        line = efficiency.stdout.readline()
        print(line)
    print efficiency.stdout.read()
    efficiency.communicate()
    time.sleep(1)
