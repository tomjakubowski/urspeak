#pragma once

#include "probes.hh"  // generated at build time, thanks cmake!

// TODO: make these toggleable, a la
// https://sourceware.org/systemtap/wiki/AddingUserSpaceProbingToApps#Adding_Probes_in_Source_Code

#define TRACE(probe) probe
#define TRACE_ENABLED(probe) probe##_ENABLED()
