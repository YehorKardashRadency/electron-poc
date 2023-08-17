#include <node.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "ssnsdk.h"
#include "ssnerror.h"
#include "ssnsbfstream.h"
#include "ssnsbfanalyze.h"


namespace calculate {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::Value;

// ppsdk example
int analyze()
{
  ssn_hsdk_t        ssnsdkhandle;       // SSN SDK handle
  ssn_hsbfstream_t  sbfstream;          // SBF stream handle
  ssn_error_t       rerror;             // Assess the outcome of different functions (runtime)
  ssn_error_t       cerror;             // Error occuring during the clean-up process

  ssn_pvterror_percentages_t errorDistrib;  // PVT error percentages
  size_t                     listSize;      // Size of list of tracked satellites
  unsigned char*             buffer;        // List of tracked satellites
  char                       inputFile[] = "input_file.sbf";

  /* Create all handles */

  rerror = SSNSDK_open(&ssnsdkhandle);
  if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
    goto exit_error;

  rerror = SSNSBFStream_open(ssnsdkhandle, &sbfstream);
  if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
    goto clean_sdk;

  /* The input SBF file is loaded */

  rerror = SSNSBFStream_loadFile(sbfstream, inputFile, SSNSBFSTREAM_OPENOPTION_READONLY);
  if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
    goto clean_sbf;

  /* Get error percentages */

  rerror = SSNSBFAnalyze_getPVTErrorPercentages(sbfstream, sbfid_ALL, &errorDistrib);
  if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
    goto clean_sbf;

  /*
   * Get list of tracked satelllites via double-call:
   *   1) Get size
   *   2) Get list
   */

  rerror = SSNSBFAnalyze_listTrackedSatellites(sbfstream, 295766.0, &listSize, NULL);
  if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
    goto clean_sbf;

  if (listSize > 0)
  {
    buffer = (unsigned char*) malloc(listSize);
    if (buffer != NULL)
    {
      rerror = SSNSBFAnalyze_listTrackedSatellites(sbfstream, 295766.0, &listSize, (ssn_tracked_satellites_t*) buffer);
      if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
        goto free_memory;
    }
  }

  /* Clean-up */

free_memory:
  free(buffer);

clean_sbf:

  cerror = SSNSBFStream_close(sbfstream);
  if (SSNERROR_GETCODE(cerror) != SSNERROR_WARNING_OK)
    fprintf(stderr, "Error: %s\n", SSNError_getMessage(cerror));

clean_sdk:

  cerror = SSNSDK_close(ssnsdkhandle);
  if (SSNERROR_GETCODE(cerror) != SSNERROR_WARNING_OK)
    fprintf(stderr, "Error: %s\n", SSNError_getMessage(cerror));

  if (SSNERROR_GETCODE(rerror) != SSNERROR_WARNING_OK)
    goto exit_error;

  return EXIT_SUCCESS;

exit_error:

  fprintf(stderr, "Error: %s\n", SSNError_getMessage(rerror));
  return EXIT_FAILURE;
}

// method to be exported
void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  // return status code
  args.GetReturnValue().Set(analyze());
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "executeSync", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} 


