#include "HandoffRequest.h"

// Single definition:
thread_local HandoffRequest* currentRequest = nullptr;
