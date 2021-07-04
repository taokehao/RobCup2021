/**
 * @file HulkFieldCoverage.h
 * @author Enno R�hrig
 */

#pragma once

#include "Tools/Streams/AutoStreamable.h"
#include "Representations/Modeling/FieldCoverage.h"
#include <vector>

STREAMABLE(HulkFieldCoverage,
{,
  (std::vector<FieldCoverage::GridLine>) lines,
});
