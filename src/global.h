// Autoruns2
// Copyright (c) 2025 Henry++

#pragma once

#include "routine.h"

#include "app.h"
#include "rapp.h"
#include "main.h"

#include "resource.h"

DECLSPEC_SELECTANY STATIC_DATA config = {0};

DECLSPEC_SELECTANY R_WORKQUEUE scan_queue = {0};
DECLSPEC_SELECTANY R_WORKQUEUE file_queue = {0};

#include "search.h"
