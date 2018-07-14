//#include <cstdint>
//#include <cstring>
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#include "XPLMDefs.h"
#include "XPLMPlugin.h"
#include "XPLMUtilities.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#define INT2VOIDP(i) (void*)(uintptr_t)(i)

XPLMDataRef heldData;
float dat = 10.1;
float MyGetDatafCallback(void * inRefcon);
void MySetDatafCallback(void * inRefcon, float invalue);

/*float register_dr_callback(float f1, float f2, int i, void * v)
{
    XPLMPluginID plugin_id = XPLMFindPluginBySignature("com.leecbaker.datareftool");
    if(XPLM_NO_PLUGIN_ID != plugin_id) {
        XPLMSendMessageToPlugin(plugin_id, MSG_ADD_DATAREF, (void*)"datareftool/good_int");
        XPLMSendMessageToPlugin(plugin_id, MSG_ADD_DATAREF, (void*)"datareftool/good_int");	//check duplicates
        XPLMSendMessageToPlugin(plugin_id, MSG_ADD_DATAREF, (void*)"datareftool/bad_int");
    }
    
    return 0;
}*/

float MyGetDatafCallback(void * inRefcon)
{
    return(dat);
}

void MySetDatafCallback(void * inRefcon, float inValue)
{
    float *my_var = &dat;
    *my_var = inValue;
}

PLUGIN_API int XPluginStart(char * outName, char * outSig, char * outDesc) {
    strcpy(outName, "PM");
    strcpy(outSig, "com.chai112.plugins");
    strcpy(outDesc, "Test for Plugin Management");
    
    XPLMDebugString("Start init");
    //XPLMRegisterFlightLoopCallback(register_dr_callback, 1, NULL);
    heldData = XPLMRegisterDataAccessor("bagel/go", xplmType_Float, 1, NULL, NULL, MyGetDatafCallback, MySetDatafCallback, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, INT2VOIDP(1), INT2VOIDP(1));
    XPLMDebugString("Finished Registering Dataref");
    //XPLMSetDataf(XPLMFindDataRef("bagel/go"), 8);
    MySetDatafCallback(0, 8);
    
    int xpVersion;
    int xplmVersion;
    XPLMHostApplicationID hostID;
    XPLMGetVersions(&xpVersion, &xplmVersion, &hostID);
    if (xpVersion > 11000)
    {
        MySetDatafCallback(0, 7);
    }
    else
    {
        MySetDatafCallback(0, 2);
    }
    
    XPLMLanguageCode xpLanguage;
    xpLanguage = XPLMGetLanguage();
    if (xpLanguage == xplm_Language_English)
    {
    //    CODE HERE
    }
    else
    {
    //    CODE HERE
    }
    
    
    
    
    
    /*if(NULL == dr) {
        return 0;
    }
    return 1;*/
    return 1;
}

PLUGIN_API void	XPluginStop(void) {XPLMUnregisterDataAccessor(heldData);}
PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID XPI, long i, void * XPRM) { }
