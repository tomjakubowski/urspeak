#pragma once

#ifdef __linux  // TODO: ifdef SYSTEMTAP or something.
// hack to not use semaphores.  the recommended way to do it is to include this
// file before including the probes
#include <sys/sdt.h>
#endif

#include "probes.hh"  // generated at build time, thanks cmake!

// TODO: make these toggleable, a la
// https://sourceware.org/systemtap/wiki/AddingUserSpaceProbingToApps#Adding_Probes_in_Source_Code

#define TRACE(probe) probe
#define TRACE_ENABLED(probe) probe##_ENABLED()
