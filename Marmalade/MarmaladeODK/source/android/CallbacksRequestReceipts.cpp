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

#include "CallbacksRequestReceipts.h"
#include "CallbackSingleton.h"

#include "ODK_internal.h"
#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include "IwDebug.h"

#include <stdio.h>

OuyaSDK::ExtensionReceipt* CallbacksRequestReceipts::m_receipts = NULL;

void CallbacksRequestReceipts::RegisterCallback(s3eCallback callback, s3eCallback* savedCallback, int callbackType, void* userData)
{
	if (*savedCallback)
	{
		//IwTrace(ODK, ("Unregistering Callback"));

		s3eEdkCallbacksUnRegister(
				S3E_EXT_ODK_HASH,
				S3E_ODK_CALLBACKS_MAX,
				callbackType,
				*savedCallback,
				userData);
		*savedCallback = NULL;
	}

	*savedCallback = callback;

	//IwTrace(ODK, ("Registering Callback"));

	s3eEdkCallbacksRegister(
			S3E_EXT_ODK_HASH,
			S3E_ODK_CALLBACKS_MAX,
			callbackType,
			*savedCallback,
			userData,
			S3E_FALSE);
}

void CallbacksRequestReceipts::RegisterCallbacks(s3eCallback onSuccess, s3eCallback onFailure, s3eCallback onCancel, void* userData)
{
	RegisterCallback(onSuccess, &m_onSuccess, S3E_ODK_CALLBACKS_REQUEST_RECEIPTS_ON_SUCCESS, userData);
	RegisterCallback(onFailure, &m_onFailure, S3E_ODK_CALLBACKS_REQUEST_RECEIPTS_ON_FAILURE, userData);
	RegisterCallback(onCancel, &m_onCancel, S3E_ODK_CALLBACKS_REQUEST_RECEIPTS_ON_CANCEL, userData);
}

void CallbacksRequestReceipts::OnSuccess(const std::vector<OuyaSDK::Receipt>& receipts)
{
	IwTrace(ODK, ("OnSuccess"));

	if (receipts.size() > 0)
	{
		IwTrace(ODK, ("Allocating receipts"));
		m_receipts = new OuyaSDK::ExtensionReceipt[receipts.size()];
		IwTrace(ODK, ("Copying receipts"));
		for (unsigned int index = 0; index < receipts.size(); ++index)
		{
			OuyaSDK::Receipt receipt = receipts[index];
			OuyaSDK::ExtensionReceipt eReceipt;
			eReceipt.Init();
			eReceipt.Copy(receipt);
			m_receipts[index] = eReceipt;
		}
	}
	else
	{
		IwTrace(ODK, ("No products to copy"));
	}

	s3eRequestReceiptsSuccessEvent event;
	event.m_receipts = m_receipts;
	event.m_receiptsLength = receipts.size();

	IwTrace(ODK, ("Invoking callback"));

	m_dataRequestReceiptsSuccessEvent = event; //don't send a temp pointer
	s3eEdkCallbacksEnqueue(S3E_EXT_ODK_HASH, S3E_ODK_CALLBACKS_REQUEST_RECEIPTS_ON_SUCCESS, &m_dataRequestReceiptsSuccessEvent);
}

void CallbacksRequestReceipts::OnFailure(int errorCode, const std::string& errorMessage)
{
	char buffer[256];
	sprintf(buffer, "OnFailure errorCode=%d errorMessage=%s", errorCode, errorMessage.c_str());
	IwTrace(ODK, (buffer));

	s3eRequestReceiptsFailureEvent event;
	event.m_errorCode = errorCode;
	sprintf(event.m_errorMessage, "%s", errorMessage.c_str());

	m_dataRequestReceiptsFailureEvent = event; //don't send a temp pointer
	s3eEdkCallbacksEnqueue(S3E_EXT_ODK_HASH, S3E_ODK_CALLBACKS_REQUEST_RECEIPTS_ON_FAILURE, &m_dataRequestReceiptsFailureEvent);
}

void CallbacksRequestReceipts::OnCancel()
{
	IwTrace(ODK, ("OnCancel"));

	s3eRequestReceiptsCancelEvent event;

	m_dataRequestReceiptsCancelEvent = event; //don't send a temp pointer
	s3eEdkCallbacksEnqueue(S3E_EXT_ODK_HASH, S3E_ODK_CALLBACKS_REQUEST_RECEIPTS_ON_CANCEL, &m_dataRequestReceiptsCancelEvent);
}