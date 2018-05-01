#ifndef MU__ANALYSIS_ANALYSISMANAGER_HH
#define MU__ANALYSIS_ANALYSISMANAGER_HH
#pragma once

#include "Geant4/g4root.hh"

namespace MATHUSLA { namespace MU {

namespace AnalysisManager {

void Setup();
bool Open(const std::string& file);
bool Save();

bool CreateNTuple(const std::string& name,
                  const std::string& title,
                  const std::initializer_list<const std::string> columns);

bool CreateNTuple(const std::string& name,
                  const std::initializer_list<const std::string> columns);

bool FillNTuple(const std::string& name,
                const std::initializer_list<double> values);

} /* namespace AnalysisManager */

} } /* namespace MATHUSLA::MU */

#endif /* MU__ANALYSIS_ANALYSISMANAGER_HH */