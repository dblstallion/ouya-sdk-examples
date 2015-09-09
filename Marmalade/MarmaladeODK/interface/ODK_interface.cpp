/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"
#include "s3eDevice.h"


#include "ODK.h"


// Define S3E_EXT_SKIP_LOADER_CALL_LOCK on the user-side to skip LoaderCallStart/LoaderCallDone()-entry.
// e.g. in s3eNUI this is used for generic user-side IwUI-based implementation.
#ifndef S3E_EXT_SKIP_LOADER_CALL_LOCK
#if defined I3D_ARCH_MIPS || (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)) || defined I3D_ARCH_NACLX86_64
// For platforms missing stack-switching (MIPS, WP8, NaCl, etc.) make loader-entry via LoaderCallStart/LoaderCallDone() on the user-side.
#define LOADER_CALL_LOCK
#endif
#endif


#include "ODK_interface.h"

static ODKFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0xb889863, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE,                 "error loading extension: ODK");

        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0xb889863, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool ODKAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

int OuyaPlugin_getAxis(int deviceId, int axis)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[0] func: OuyaPlugin_getAxis"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_getAxis);
#endif

    int ret = g_Ext.m_OuyaPlugin_getAxis(deviceId, axis);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_getAxis);
#endif

    return ret;
}

bool OuyaPlugin_isPressed(int deviceId, int keyCode)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[1] func: OuyaPlugin_isPressed"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_isPressed);
#endif

    bool ret = g_Ext.m_OuyaPlugin_isPressed(deviceId, keyCode);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_isPressed);
#endif

    return ret;
}

bool OuyaPlugin_isPressedDown(int deviceId, int keyCode)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[2] func: OuyaPlugin_isPressedDown"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_isPressedDown);
#endif

    bool ret = g_Ext.m_OuyaPlugin_isPressedDown(deviceId, keyCode);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_isPressedDown);
#endif

    return ret;
}

bool OuyaPlugin_isPressedUp(int deviceId, int keyCode)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[3] func: OuyaPlugin_isPressedUp"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_isPressedUp);
#endif

    bool ret = g_Ext.m_OuyaPlugin_isPressedUp(deviceId, keyCode);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_isPressedUp);
#endif

    return ret;
}

void OuyaPlugin_clearButtonStates()
{
    IwTrace(ODK_VERBOSE, ("calling ODK[4] func: OuyaPlugin_clearButtonStates"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_clearButtonStates);
#endif

    g_Ext.m_OuyaPlugin_clearButtonStates();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_clearButtonStates);
#endif

    return;
}

const char* OuyaPlugin_getDeviceName(int playerNum)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[5] func: OuyaPlugin_getDeviceName"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_getDeviceName);
#endif

    const char* ret = g_Ext.m_OuyaPlugin_getDeviceName(playerNum);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_getDeviceName);
#endif

    return ret;
}

void OuyaPlugin_initOuyaPlugin(const char* jsonData, s3eCallback onSuccess, s3eCallback onFailure)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[6] func: OuyaPlugin_initOuyaPlugin"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_initOuyaPlugin);
#endif

    g_Ext.m_OuyaPlugin_initOuyaPlugin(jsonData, onSuccess, onFailure);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_initOuyaPlugin);
#endif

    return;
}

void OuyaPlugin_asyncOuyaRequestGamerInfo(s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[7] func: OuyaPlugin_asyncOuyaRequestGamerInfo"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestGamerInfo);
#endif

    g_Ext.m_OuyaPlugin_asyncOuyaRequestGamerInfo(onSuccess, onFailure, onCancel);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestGamerInfo);
#endif

    return;
}

void OuyaPlugin_asyncOuyaRequestProducts(const char* productsJson, s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[8] func: OuyaPlugin_asyncOuyaRequestProducts"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestProducts);
#endif

    g_Ext.m_OuyaPlugin_asyncOuyaRequestProducts(productsJson, onSuccess, onFailure, onCancel);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestProducts);
#endif

    return;
}

void OuyaPlugin_asyncOuyaRequestPurchase(const char* purchasable, s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[9] func: OuyaPlugin_asyncOuyaRequestPurchase"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestPurchase);
#endif

    g_Ext.m_OuyaPlugin_asyncOuyaRequestPurchase(purchasable, onSuccess, onFailure, onCancel);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestPurchase);
#endif

    return;
}

void OuyaPlugin_asyncOuyaRequestReceipts(s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel, void* userData)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[10] func: OuyaPlugin_asyncOuyaRequestReceipts"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestReceipts);
#endif

    g_Ext.m_OuyaPlugin_asyncOuyaRequestReceipts(onSuccess, onFailure, onCancel, userData);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_asyncOuyaRequestReceipts);
#endif

    return;
}

int OuyaPlugin_JSONObject_Construct()
{
    IwTrace(ODK_VERBOSE, ("calling ODK[11] func: OuyaPlugin_JSONObject_Construct"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONObject_Construct);
#endif

    int ret = g_Ext.m_OuyaPlugin_JSONObject_Construct();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONObject_Construct);
#endif

    return ret;
}

void OuyaPlugin_JSONObject_Put(int jsonObject, const char* name, const char* value)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[12] func: OuyaPlugin_JSONObject_Put"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONObject_Put);
#endif

    g_Ext.m_OuyaPlugin_JSONObject_Put(jsonObject, name, value);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONObject_Put);
#endif

    return;
}

const char* OuyaPlugin_JSONObject_ToString(int jsonObject)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[13] func: OuyaPlugin_JSONObject_ToString"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONObject_ToString);
#endif

    const char* ret = g_Ext.m_OuyaPlugin_JSONObject_ToString(jsonObject);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONObject_ToString);
#endif

    return ret;
}

int OuyaPlugin_JSONArray_Construct()
{
    IwTrace(ODK_VERBOSE, ("calling ODK[14] func: OuyaPlugin_JSONArray_Construct"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONArray_Construct);
#endif

    int ret = g_Ext.m_OuyaPlugin_JSONArray_Construct();

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONArray_Construct);
#endif

    return ret;
}

void OuyaPlugin_JSONArray_Put(int jsonArray, int index, int jsonObject)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[15] func: OuyaPlugin_JSONArray_Put"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONArray_Put);
#endif

    g_Ext.m_OuyaPlugin_JSONArray_Put(jsonArray, index, jsonObject);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONArray_Put);
#endif

    return;
}

const char* OuyaPlugin_JSONArray_ToString(int jsonArray)
{
    IwTrace(ODK_VERBOSE, ("calling ODK[16] func: OuyaPlugin_JSONArray_ToString"));

    if (!_extLoad())
        return false;

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallStart(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONArray_ToString);
#endif

    const char* ret = g_Ext.m_OuyaPlugin_JSONArray_ToString(jsonArray);

#ifdef LOADER_CALL_LOCK
    s3eDeviceLoaderCallDone(S3E_TRUE, (void*)g_Ext.m_OuyaPlugin_JSONArray_ToString);
#endif

    return ret;
}
