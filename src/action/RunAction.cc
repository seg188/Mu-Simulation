#include "action/RunAction.hh"

#include <fstream>

#include "Geant4/G4Run.hh"

#include "action/GeneratorAction.hh"
#include "analysis/AnalysisManager.hh"
#include "util/FileIO.hh"
#include "util/Time.hh"

namespace MATHUSLA { namespace MU {

static G4String _dir = "";
static G4String _file = "";

RunAction::RunAction() : G4UserRunAction() {
  G4AnalysisManager::Instance()->SetNtupleMerging(true);
}

G4Run* RunAction::GenerateRun() {
  return G4UserRunAction::GenerateRun();
}

void RunAction::BeginOfRunAction(const G4Run* run) {
  G4String dir = "data";
  IO::create_directory(dir);
  dir += "/" + Time::GetDate();
  IO::create_directory(dir);
  dir += "/" + Time::GetTime();
  IO::create_directory(dir);
  _dir = dir;
  _file = "run" + std::to_string(run->GetRunID());
  AnalysisManager::OpenFile(dir, _file + ".root");
}

void RunAction::EndOfRunAction(const G4Run* run) {
  if (!run->GetNumberOfEvent()) return;

  AnalysisManager::Write();
  AnalysisManager::CloseFile();

  const std::string run_file = _dir + '/' + _file;

  std::ofstream _info(run_file + ".info");

  _info << "MATHUSLA -- Muon Simulation\n"
        << Time::GetString("%c %Z") << "\n\n"
        << "Run " << run->GetRunID() << "\n"
        << "Data: " << run_file << ".root\n\n"
        << GeneratorAction::GetGenerator()->InfoString();

  _info.close();

  G4cout << "\nEnd of Run\n"
         << "Data File: " << run_file << ".root\n"
         << "Info File: " << run_file << ".info\n\n";
}

} } /* namespace MATHUSLA::MU */
