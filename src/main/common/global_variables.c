/*
 * This file is part of INAV Project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU General Public License Version 3, as described below:
 *
 * This file is free software: you may copy, redistribute and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

#include "platform.h"

#ifdef USE_LOGIC_CONDITIONS

#include <stdint.h>
#include "config/config_reset.h"
#include "config/parameter_group.h"
#include "config/parameter_group_ids.h"
#include "common/global_variables.h"
#include "common/maths.h"
#include "build/build_config.h"
 
static EXTENDED_FASTRAM int globalVariableState[MAX_GLOBAL_VARIABLES];

PG_REGISTER_ARRAY_WITH_RESET_FN(globalVariableConfig_t, MAX_GLOBAL_VARIABLES, globalVariableConfigs, PG_GLOBAL_VARIABLE_CONFIG, 0);

void pgResetFn_globalVariableConfigs(globalVariableConfig_t *globalVariableConfigs)
{
    // set default calibration to full range and 1:1 mapping
    for (int i = 0; i < MAX_GLOBAL_VARIABLES; i++) {
        globalVariableConfigs[i].min = INT32_MIN;
        globalVariableConfigs[i].max = INT32_MAX;
    }
}

int gvGet(uint8_t index) {
    if (index < MAX_GLOBAL_VARIABLES) {
        return globalVariableState[index];
    } else {
        return 0;
    }
}

void gvSet(uint8_t index, int value) {
    if (index < MAX_GLOBAL_VARIABLES) {
        globalVariableState[index] = constrain(value, globalVariableConfigs(index)->min, globalVariableConfigs(index)->max);
    }
}

#endif