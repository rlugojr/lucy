#define C_LUCY_SIMILARITY
#include "Lucy/Util/ToolSet.h"

#include "Lucy/Index/Similarity/LuceneSimilarity.h"

LuceneSimilarity*
LuceneSim_new()
{
    LuceneSimilarity *self 
        = (LuceneSimilarity*)VTable_Make_Obj(LUCENESIMILARITY);
    return LuceneSim_init(self);
}

LuceneSimilarity*
LuceneSim_init(LuceneSimilarity *self)
{
    Sim_init((Similarity*)self);
    return self;
}

float
LuceneSim_coord(LuceneSimilarity *self, uint32_t overlap, 
                uint32_t max_overlap)
{
    UNUSED_VAR(self);
    if (max_overlap == 0)
        return 1;
    else 
        return (float)overlap / (float)max_overlap;
}

/* Copyright 2010 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

