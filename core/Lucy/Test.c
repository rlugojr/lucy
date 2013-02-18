/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

#include "Lucy/Util/ToolSet.h"

#include "Lucy/Test.h"
#include "Clownfish/Test/TestBatch.h"
#include "Clownfish/Test/TestFormatter.h"
#include "Clownfish/Test/TestRunner.h"
#include "Lucy/Test/Analysis/TestAnalyzer.h"
#include "Lucy/Test/Analysis/TestCaseFolder.h"
#include "Lucy/Test/Analysis/TestNormalizer.h"
#include "Lucy/Test/Analysis/TestPolyAnalyzer.h"
#include "Lucy/Test/Analysis/TestRegexTokenizer.h"
#include "Lucy/Test/Analysis/TestSnowballStemmer.h"
#include "Lucy/Test/Analysis/TestSnowballStopFilter.h"
#include "Lucy/Test/Analysis/TestStandardTokenizer.h"
#include "Lucy/Test/Highlight/TestHeatMap.h"
#include "Lucy/Test/Highlight/TestHighlighter.h"
#include "Lucy/Test/Index/TestDocWriter.h"
#include "Lucy/Test/Index/TestHighlightWriter.h"
#include "Lucy/Test/Index/TestIndexManager.h"
#include "Lucy/Test/Index/TestPolyReader.h"
#include "Lucy/Test/Index/TestPostingListWriter.h"
#include "Lucy/Test/Index/TestSegWriter.h"
#include "Lucy/Test/Index/TestSegment.h"
#include "Lucy/Test/Index/TestSnapshot.h"
#include "Lucy/Test/Index/TestTermInfo.h"
#include "Lucy/Test/Object/TestBitVector.h"
#include "Lucy/Test/Object/TestByteBuf.h"
#include "Lucy/Test/Object/TestCharBuf.h"
#include "Lucy/Test/Object/TestErr.h"
#include "Lucy/Test/Object/TestHash.h"
#include "Lucy/Test/Object/TestI32Array.h"
#include "Lucy/Test/Object/TestLockFreeRegistry.h"
#include "Lucy/Test/Object/TestNum.h"
#include "Lucy/Test/Object/TestObj.h"
#include "Lucy/Test/Object/TestVArray.h"
#include "Lucy/Test/Plan/TestBlobType.h"
#include "Lucy/Test/Plan/TestFieldMisc.h"
#include "Lucy/Test/Plan/TestFieldType.h"
#include "Lucy/Test/Plan/TestFullTextType.h"
#include "Lucy/Test/Plan/TestNumericType.h"
#include "Lucy/Test/Search/TestLeafQuery.h"
#include "Lucy/Test/Search/TestMatchAllQuery.h"
#include "Lucy/Test/Search/TestNOTQuery.h"
#include "Lucy/Test/Search/TestNoMatchQuery.h"
#include "Lucy/Test/Search/TestPhraseQuery.h"
#include "Lucy/Test/Search/TestPolyQuery.h"
#include "Lucy/Test/Search/TestQueryParserLogic.h"
#include "Lucy/Test/Search/TestQueryParserSyntax.h"
#include "Lucy/Test/Search/TestRangeQuery.h"
#include "Lucy/Test/Search/TestReqOptQuery.h"
#include "Lucy/Test/Search/TestSeriesMatcher.h"
#include "Lucy/Test/Search/TestSortSpec.h"
#include "Lucy/Test/Search/TestSpan.h"
#include "Lucy/Test/Search/TestTermQuery.h"
#include "Lucy/Test/Store/TestCompoundFileReader.h"
#include "Lucy/Test/Store/TestCompoundFileWriter.h"
#include "Lucy/Test/Store/TestFSDirHandle.h"
#include "Lucy/Test/Store/TestFSFileHandle.h"
#include "Lucy/Test/Store/TestFSFolder.h"
#include "Lucy/Test/Store/TestFileHandle.h"
#include "Lucy/Test/Store/TestFolder.h"
#include "Lucy/Test/Store/TestIOChunks.h"
#include "Lucy/Test/Store/TestIOPrimitives.h"
#include "Lucy/Test/Store/TestInStream.h"
#include "Lucy/Test/Store/TestRAMDirHandle.h"
#include "Lucy/Test/Store/TestRAMFileHandle.h"
#include "Lucy/Test/Store/TestRAMFolder.h"
#include "Lucy/Test/TestSchema.h"
#include "Lucy/Test/Util/TestAtomic.h"
#include "Lucy/Test/Util/TestIndexFileNames.h"
#include "Lucy/Test/Util/TestJson.h"
#include "Lucy/Test/Util/TestMemory.h"
#include "Lucy/Test/Util/TestMemoryPool.h"
#include "Lucy/Test/Util/TestNumberUtils.h"
#include "Lucy/Test/Util/TestPriorityQueue.h"
#include "Lucy/Test/Util/TestStringHelper.h"

static void
S_unbuffer_stdout();

static VArray*
S_all_test_batches() {
    VArray *batches = VA_new(0);

    VA_Push(batches, (Obj*)TestPriQ_new());
    VA_Push(batches, (Obj*)TestBitVector_new());
    VA_Push(batches, (Obj*)TestVArray_new());
    VA_Push(batches, (Obj*)TestHash_new());
    VA_Push(batches, (Obj*)TestObj_new());
    VA_Push(batches, (Obj*)TestErr_new());
    VA_Push(batches, (Obj*)TestBB_new());
    VA_Push(batches, (Obj*)TestMemPool_new());
    VA_Push(batches, (Obj*)TestCB_new());
    VA_Push(batches, (Obj*)TestNumUtil_new());
    VA_Push(batches, (Obj*)TestNum_new());
    VA_Push(batches, (Obj*)TestStrHelp_new());
    VA_Push(batches, (Obj*)TestIxFileNames_new());
    VA_Push(batches, (Obj*)TestJson_new());
    VA_Push(batches, (Obj*)TestI32Arr_new());
    VA_Push(batches, (Obj*)TestAtomic_new());
    VA_Push(batches, (Obj*)TestLFReg_new());
    VA_Push(batches, (Obj*)TestMemory_new());
    VA_Push(batches, (Obj*)TestRAMFH_new());
    VA_Push(batches, (Obj*)TestFSFH_new());
    VA_Push(batches, (Obj*)TestInStream_new());
    VA_Push(batches, (Obj*)TestFH_new());
    VA_Push(batches, (Obj*)TestIOPrimitives_new());
    VA_Push(batches, (Obj*)TestIOChunks_new());
    VA_Push(batches, (Obj*)TestRAMDH_new());
    VA_Push(batches, (Obj*)TestFSDH_new());
    VA_Push(batches, (Obj*)TestFSFolder_new());
    VA_Push(batches, (Obj*)TestRAMFolder_new());
    VA_Push(batches, (Obj*)TestFolder_new());
    VA_Push(batches, (Obj*)TestIxManager_new());
    VA_Push(batches, (Obj*)TestCFWriter_new());
    VA_Push(batches, (Obj*)TestCFReader_new());
    VA_Push(batches, (Obj*)TestAnalyzer_new());
    VA_Push(batches, (Obj*)TestPolyAnalyzer_new());
    VA_Push(batches, (Obj*)TestCaseFolder_new());
    VA_Push(batches, (Obj*)TestRegexTokenizer_new());
    VA_Push(batches, (Obj*)TestSnowStop_new());
    VA_Push(batches, (Obj*)TestSnowStemmer_new());
    VA_Push(batches, (Obj*)TestNormalizer_new());
    VA_Push(batches, (Obj*)TestStandardTokenizer_new());
    VA_Push(batches, (Obj*)TestSnapshot_new());
    VA_Push(batches, (Obj*)TestTermInfo_new());
    VA_Push(batches, (Obj*)TestFieldMisc_new());
    VA_Push(batches, (Obj*)TestBatchSchema_new());
    VA_Push(batches, (Obj*)TestDocWriter_new());
    VA_Push(batches, (Obj*)TestHLWriter_new());
    VA_Push(batches, (Obj*)TestPListWriter_new());
    VA_Push(batches, (Obj*)TestSegWriter_new());
    VA_Push(batches, (Obj*)TestPolyReader_new());
    VA_Push(batches, (Obj*)TestFullTextType_new());
    VA_Push(batches, (Obj*)TestBlobType_new());
    VA_Push(batches, (Obj*)TestNumericType_new());
    VA_Push(batches, (Obj*)TestFType_new());
    VA_Push(batches, (Obj*)TestSeg_new());
    VA_Push(batches, (Obj*)TestHighlighter_new());
    VA_Push(batches, (Obj*)TestSpan_new());
    VA_Push(batches, (Obj*)TestHeatMap_new());
    VA_Push(batches, (Obj*)TestTermQuery_new());
    VA_Push(batches, (Obj*)TestPhraseQuery_new());
    VA_Push(batches, (Obj*)TestSortSpec_new());
    VA_Push(batches, (Obj*)TestRangeQuery_new());
    VA_Push(batches, (Obj*)TestANDQuery_new());
    VA_Push(batches, (Obj*)TestMatchAllQuery_new());
    VA_Push(batches, (Obj*)TestNOTQuery_new());
    VA_Push(batches, (Obj*)TestReqOptQuery_new());
    VA_Push(batches, (Obj*)TestLeafQuery_new());
    VA_Push(batches, (Obj*)TestNoMatchQuery_new());
    VA_Push(batches, (Obj*)TestSeriesMatcher_new());
    VA_Push(batches, (Obj*)TestORQuery_new());
    VA_Push(batches, (Obj*)TestQPLogic_new());
    VA_Push(batches, (Obj*)TestQPSyntax_new());

    return batches;
}

bool
Test_run_batch(CharBuf *class_name, TestFormatter *formatter) {
    S_unbuffer_stdout();

    VArray   *batches = S_all_test_batches();
    uint32_t  size    = VA_Get_Size(batches);

    for (uint32_t i = 0; i < size; ++i) {
        TestBatch *batch = (TestBatch*)VA_Fetch(batches, i);

        if (CB_Equals(TestBatch_Get_Class_Name(batch), (Obj*)class_name)) {
            bool result = TestBatch_Run(batch);
            DECREF(batches);
            return result;
        }
    }

    DECREF(batches);
    THROW(ERR, "Couldn't find test class '%o'", class_name);
    UNREACHABLE_RETURN(bool);
}

bool
Test_run_all_batches(TestFormatter *formatter) {
    S_unbuffer_stdout();

    TestRunner *runner  = TestRunner_new(formatter);
    VArray     *batches = S_all_test_batches();
    uint32_t    size    = VA_Get_Size(batches);

    for (uint32_t i = 0; i < size; ++i) {
        TestBatch *batch = (TestBatch*)VA_Fetch(batches, i);
        TestRunner_Run_Batch(runner, batch);
    }

    bool result = TestRunner_Finish(runner);

    DECREF(runner);
    DECREF(batches);
    return result;
}

static void
S_unbuffer_stdout() {
    int check_val = setvbuf(stdout, NULL, _IONBF, 0);
    if (check_val != 0) {
        fprintf(stderr, "Failed when trying to unbuffer stdout\n");
    }
}


