#ifndef EXCEPTION_ENDING_INCLUDE
#define EXCEPTION_ENDING_INCLUDE

#include <cassert>
#include <string>

// types for exception
struct TerminalException {
  int eVal;
};

struct ConversionException {
  std::string val;
};

// This is guaranteed to trigger an end.
// Also it gives something that can be used for having the stacktrace via gdb.
void TerminalEnding()
{
  assert(false);
  exit(1);
}





#endif
