/*
 * Copyright (C) 2012-2015 OUYA, Inc.
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

package tv.ouya.sdk;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import tv.ouya.console.api.*;


public class RequestPurchaseListener implements OuyaResponseListener<PurchaseResult>
{
	private static final String TAG = RequestPurchaseListener.class.getSimpleName();
	
	@Override
	public void onSuccess(PurchaseResult purchaseResult) {			
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "Java: onSuccess");
	}

	@Override	
	public void onFailure(int errorCode, String errorMessage, Bundle info) {
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "Java: onFailure");
	}
	
	@Override
	public void onCancel() {
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "*************");
		Log.i(TAG, "Java: onCancel");
	}
}
