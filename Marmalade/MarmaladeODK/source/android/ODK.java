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
java implementation of the OuyaODK extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

package com.ODK;


import android.app.Activity;
import android.content.Intent;
import android.app.NativeActivity;
import android.content.Context;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;
import java.io.IOException;
import java.io.InputStream;
import tv.ouya.console.api.OuyaController;
import tv.ouya.console.api.OuyaInputMapper;

public class ODK extends LoaderActivity
{
	private static final String LOG_TAG = "ODK";

	// stop the thread on exit
	private static boolean m_waitToExit = true;

	public static ODK 				m_Activity = null;
	public static OuyaController	m_SelectedController = null;
    public static boolean			m_bInitialized = false;
    
    private long mLastAnalogTick;
    private long mLastDigitalTick;

    @Override
    public void onCreate(Bundle savedInstanceState)
	{
        Log.v(LOG_TAG, "onCreate" );
        super.onCreate(savedInstanceState);
        m_Activity = this;
        OuyaInputMapper.init(this);
		OuyaController.init(this);

		initializeOUYA();
    }

    @Override
		protected void onDestroy() {
			super.onDestroy();
            
            OuyaInputMapper.shutdown(this);

			// notify threads it's time to exit
			m_waitToExit = false;
	}

	private void initializeOUYA() {

		Log.v(LOG_TAG, "Initializing OUYA...");

		Log.v(LOG_TAG, "Get application context...");
		Context context = getApplicationContext();

		Log.v(LOG_TAG, "Load signing key...");
		// load the application key from assets
		try {
			AssetManager assetManager = context.getAssets();
			InputStream inputStream = assetManager.open("key.der", AssetManager.ACCESS_BUFFER);
			byte[] applicationKey = new byte[inputStream.available()];
			inputStream.read(applicationKey);
			inputStream.close();
			IOuyaActivity.SetApplicationKey(applicationKey);

			Log.v(LOG_TAG, "***Loaded signing key*********");
		} catch (IOException e) {
			e.printStackTrace();
		}

		Log.v(LOG_TAG, "Initialize MarmaladeOuyaPlugin...");

		// Initialize the Marmalade OUYA Plugin
		MarmaladeOuyaPlugin marmaladeOuyaPlugin = new MarmaladeOuyaPlugin();
		IOuyaActivity.SetMarmaladeOuyaPlugin(marmaladeOuyaPlugin);

		//make activity accessible to statically
		IOuyaActivity.SetActivity(this);

		Log.v(LOG_TAG, "Spawn wait thread...");

		// spawn thread to wait to initialize ouya facade
		Thread timer = new Thread() {
			public void run() {
				// wait for developer id to be set
				while (m_waitToExit) {

					final MarmaladeOuyaPlugin marmaladeOuyaPlugin = IOuyaActivity.GetMarmaladeOuyaPlugin();
					if (null != marmaladeOuyaPlugin) {
						if (marmaladeOuyaPlugin.getDeveloperId() != "") {
							Log.v(LOG_TAG, "Detected developer id initializing...");

							Runnable runnable = new Runnable()
							{
								public void run()
								{
									Log.v(LOG_TAG, "MarmaladeOuyaPlugin initializing...");
									marmaladeOuyaPlugin.Initialize();
								}
							};

							runOnUiThread(runnable);

							break;
						}
					}

					try {
						Thread.sleep(50);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
        };
        timer.start();
	}
    
    public boolean dispatchKeyEvent(KeyEvent keyEvent)
      {
        if (OuyaInputMapper.shouldHandleInputEvent(keyEvent))
        {
          broadcastInputNotification(false);
          return OuyaInputMapper.dispatchKeyEvent(this, keyEvent);
        }
        return super.dispatchKeyEvent(keyEvent);
      }
      
      public boolean dispatchGenericMotionEvent(MotionEvent motionEvent)
      {
        if (OuyaInputMapper.shouldHandleInputEvent(motionEvent))
        {
          broadcastInputNotification(true);
          return OuyaInputMapper.dispatchGenericMotionEvent(this, motionEvent);
        }
        return super.dispatchGenericMotionEvent(motionEvent);
      }
      
      private void broadcastInputNotification(boolean analog)
      {
        long curTick = System.nanoTime() / 1000000L;
        long lastTick = analog ? this.mLastAnalogTick : this.mLastDigitalTick;
        if (curTick - lastTick < 30000L) {
          return;
        }
        if (analog) {
          this.mLastAnalogTick = curTick;
        } else {
          this.mLastDigitalTick = curTick;
        }
        Intent intent = new Intent("tv.ouya.metrics.action.USER_INPUT");
        intent.putExtra("analog", analog);
        sendBroadcast(intent);
      }


    public void OuyaController_startOfFrame()
    {
		//Log.v(LOG_TAG, "OuyaController_startOfFrame");
        OuyaController.startOfFrame();
    }


    public boolean OuyaController_selectControllerByPlayer(int playerNum)
    {
		//Log.v(LOG_TAG, "OuyaController_selectControllerByPlayer playerNum="+playerNum);
		m_SelectedController = OuyaController.getControllerByPlayer(playerNum);
        return (m_SelectedController!=null);
    }


    public boolean OuyaController_selectControllerByDeviceID(int deviceID)
    {
		//Log.v(LOG_TAG, "OuyaController_selectControllerByDeviceID deviceID="+deviceID);
        m_SelectedController = OuyaController.getControllerByDeviceId(deviceID);
        return (m_SelectedController!=null);
    }


    public int OuyaController_getAxisValue(int axis)
    {
		//Log.v(LOG_TAG, "OuyaController_getAxisValue axis="+axis);
		if (m_SelectedController!=null)
			return (int)(m_SelectedController.getAxisValue(axis)*256.0f);
		else
			return 0;
    }


    public boolean OuyaController_getButton(int button)
    {
		//Log.v(LOG_TAG, "OuyaController_getButton button="+button);
        if (m_SelectedController!=null)
			return m_SelectedController.getButton(button);
		else
			return false;
    }


    public boolean OuyaController_buttonPressedThisFrame(int button)
    {
		//Log.v(LOG_TAG, "OuyaController_buttonPressedThisFrame button="+button);
		if (m_SelectedController!=null)
			return m_SelectedController.buttonPressedThisFrame(button);
		else
			return false;
    }


    public boolean OuyaController_buttonReleasedThisFrame(int button)
    {
		//Log.v(LOG_TAG, "OuyaController_buttonReleasedThisFrame button="+button);
        if (m_SelectedController!=null)
			return m_SelectedController.buttonReleasedThisFrame(button);
		else
			return false;
    }


    public boolean OuyaController_buttonChangedThisFrame(int button)
    {
		//Log.v(LOG_TAG, "OuyaController_buttonChangedThisFrame button="+button);
        if (m_SelectedController!=null)
			return m_SelectedController.buttonChangedThisFrame(button);
		else
			return false;
    }


    public int OuyaController_getPlayerNum()
    {
		//Log.v(LOG_TAG, "OuyaController_getPlayerNum");
		if (m_SelectedController!=null)
			return m_SelectedController.getPlayerNum();
		else
			return -1;
    }

    public void OuyaPlugin_asyncSetDeveloperId(String developerId)
    {
		Log.v(LOG_TAG, "OuyaPlugin_asyncSetDeveloperId developerId="+developerId);
    }
}