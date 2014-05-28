/*
 * Copyright (C) 2012, 2013 OUYA, Inc.
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

/*
 * android-specific implementation of the ODK extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "ODK_internal.h"
#include "CallbacksFetchGamerUUID.h"
#include "CallbackSingleton.h"
#include "CallbacksRequestProducts.h"
#include "CallbacksRequestPurchase.h"
#include "CallbacksRequestReceipts.h"
#include "PluginOuya.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_OuyaController_startOfFrame;
static jmethodID g_OuyaController_selectControllerByPlayer;
static jmethodID g_OuyaController_selectControllerByDeviceID;
static jmethodID g_OuyaController_getAxisValue;
static jmethodID g_OuyaController_getButton;
static jmethodID g_OuyaController_buttonPressedThisFrame;
static jmethodID g_OuyaController_buttonReleasedThisFrame;
static jmethodID g_OuyaController_buttonChangedThisFrame;
static jmethodID g_OuyaController_getPlayerNum;

static OuyaSDK::PluginOuya g_pluginOuya;

s3eResult ODKInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();

    jobject obj = NULL;
	jfieldID field = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("com/ODK/ODK");
    if (!cls)
        goto fail;

	IwTrace(ODK, ("ODK init Found: com/ODK/ODK"));

    field = env->GetStaticFieldID(cls, "m_Activity", "Lcom/ODK/ODK;");
    if (!field)
        goto fail;

	IwTrace(ODK, ("ODK init Found: GetStaticFieldID"));

    obj = env->GetStaticObjectField(cls,field);
	if (!obj)
        goto fail;

	IwTrace(ODK, ("ODK init Found: GetStaticObjectField "));
/*
    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;
*/
    // Get all the extension methods
    g_OuyaController_startOfFrame = env->GetMethodID(cls, "OuyaController_startOfFrame", "()V");
    if (!g_OuyaController_startOfFrame)
        goto fail;

    g_OuyaController_selectControllerByPlayer = env->GetMethodID(cls, "OuyaController_selectControllerByPlayer", "(I)Z");
    if (!g_OuyaController_selectControllerByPlayer)
        goto fail;

    g_OuyaController_selectControllerByDeviceID = env->GetMethodID(cls, "OuyaController_selectControllerByDeviceID", "(I)Z");
    if (!g_OuyaController_selectControllerByDeviceID)
        goto fail;

    g_OuyaController_getAxisValue = env->GetMethodID(cls, "OuyaController_getAxisValue", "(I)I");
    if (!g_OuyaController_getAxisValue)
        goto fail;

    g_OuyaController_getButton = env->GetMethodID(cls, "OuyaController_getButton", "(I)Z");
    if (!g_OuyaController_getButton)
        goto fail;

    g_OuyaController_buttonPressedThisFrame = env->GetMethodID(cls, "OuyaController_buttonPressedThisFrame", "(I)Z");
    if (!g_OuyaController_buttonPressedThisFrame)
        goto fail;

    g_OuyaController_buttonReleasedThisFrame = env->GetMethodID(cls, "OuyaController_buttonReleasedThisFrame", "(I)Z");
    if (!g_OuyaController_buttonReleasedThisFrame)
        goto fail;

    g_OuyaController_buttonChangedThisFrame = env->GetMethodID(cls, "OuyaController_buttonChangedThisFrame", "(I)Z");
    if (!g_OuyaController_buttonChangedThisFrame)
        goto fail;

    g_OuyaController_getPlayerNum = env->GetMethodID(cls, "OuyaController_getPlayerNum", "()I");
    if (!g_OuyaController_getPlayerNum)
        goto fail;



    IwTrace(ODK, ("ODK init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // cache class references
    g_pluginOuya.CacheClasses(env);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(ODK, ("One or more java methods could not be found"));
    }
    return S3E_RESULT_ERROR;

}

void ODKTerminate_platform()
{
    // Add any platform-specific termination code here
}

void OuyaController_startOfFrame_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_OuyaController_startOfFrame);
}

bool OuyaController_selectControllerByPlayer_platform(int playerNum)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_OuyaController_selectControllerByPlayer, playerNum);
}

bool OuyaController_selectControllerByDeviceID_platform(int deviceID)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_OuyaController_selectControllerByDeviceID, deviceID);
}

int OuyaController_getAxisValue_platform(int axis)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_OuyaController_getAxisValue, axis);
}

bool OuyaController_getButton_platform(int button)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_OuyaController_getButton, button);
}

bool OuyaController_buttonPressedThisFrame_platform(int button)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_OuyaController_buttonPressedThisFrame, button);
}

bool OuyaController_buttonReleasedThisFrame_platform(int button)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_OuyaController_buttonReleasedThisFrame, button);
}

bool OuyaController_buttonChangedThisFrame_platform(int button)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (bool)env->CallBooleanMethod(g_Obj, g_OuyaController_buttonChangedThisFrame, button);
}

int OuyaController_getPlayerNum_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    return (int)env->CallIntMethod(g_Obj, g_OuyaController_getPlayerNum);
}

void OuyaPlugin_asyncSetDeveloperId(const char* developerId)
{
	std::string buffer = "OuyaPlugin_asyncSetDeveloperId developerId=";
	buffer.append(developerId);
	IwTrace(ODK, (buffer.c_str()));

    g_pluginOuya.AsyncSetDeveloperId(developerId);
}

void OuyaPlugin_asyncOuyaFetchGamerUUID(s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel)
{
	IwTrace(ODK, ("ODK_platform: OuyaPlugin_asyncOuyaFetchGamerUUID"));

	OuyaSDK::CallbackSingleton::GetInstance()->m_callbacksFetchGamerUUID->RegisterCallbacks(onSuccess, onFailure, onCancel);

    g_pluginOuya.AsyncOuyaFetchGamerUUID();
}

void OuyaPlugin_asyncOuyaRequestProducts(const char* productsJson, s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel)
{
	IwTrace(ODK, ("ODK_platform: OuyaPlugin_asyncOuyaRequestProducts"));

	std::string msg = "OuyaPlugin_asyncOuyaRequestProducts: productsJson=";
	msg.append(productsJson);
	IwTrace(ODK, (msg.c_str()));

	//convert JSON to product id array

	// Parse example data
	JSONValue* value = JSON::Parse(productsJson);

	if (value == NULL)
	{
		IwTrace(ODK, ("Parsing JSON Failed"));
		return;
	}

	if (!value->IsArray())
	{
		IwTrace(ODK, ("Parsing JSON Failed: Not an array"));
		return;
	}

	// Retrieve the main object
	JSONArray data = value->AsArray();

	std::vector<std::string> productIds;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		if (data[i]->IsString())
		{
			const std::wstring wstr = data[i]->AsString();

			std::string productId( wstr.begin(), wstr.end() );

			productIds.push_back(productId);
		}
	}

	OuyaSDK::CallbackSingleton::GetInstance()->m_callbacksRequestProducts->RegisterCallbacks(onSuccess, onFailure, onCancel);

	g_pluginOuya.AsyncOuyaRequestProducts(productIds);
}

void OuyaPlugin_asyncOuyaRequestPurchase(const char* purchasable, s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel)
{
	IwTrace(ODK, ("ODK_platform: OuyaPlugin_asyncOuyaRequestPurchase"));

	std::string msg = "OuyaPlugin_asyncOuyaRequestPurchase: purchasable=";
	msg.append(purchasable);
	IwTrace(ODK, (msg.c_str()));

	OuyaSDK::CallbackSingleton::GetInstance()->m_callbacksRequestPurchase->RegisterCallbacks(onSuccess, onFailure, onCancel);

	g_pluginOuya.AsyncOuyaRequestPurchase(purchasable);
}

void OuyaPlugin_asyncOuyaRequestReceipts(s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel, void* userData)
{
	IwTrace(ODK, ("ODK_platform: OuyaPlugin_asyncOuyaRequestReceipts"));

	OuyaSDK::CallbackSingleton::GetInstance()->m_callbacksRequestReceipts->RegisterCallbacks(onSuccess, onFailure, onCancel, userData);

	g_pluginOuya.AsyncOuyaRequestReceipts();
}