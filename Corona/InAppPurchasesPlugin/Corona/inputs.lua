-- Copyright (C) 2012, 2013 OUYA, Inc.
--
-- Licensed under the Apache License, Version 2.0 (the "License");
-- you may not use this file except in compliance with the License.
-- You may obtain a copy of the License at
--
--    http://www.apache.org/licenses/LICENSE-2.0
--
-- Unless required by applicable law or agreed to in writing, software
-- distributed under the License is distributed on an "AS IS" BASIS,
-- WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
-- See the License for the specific language governing permissions and
-- limitations under the License.

-----------------------------------------------------------------------------------------
--
-- inputs.lua
--
-----------------------------------------------------------------------------------------

callbacksRequestGamerInfo = require "callbacksRequestGamerInfo"
callbacksRequestProducts = require "callbacksRequestProducts"
callbacksRequestPurchase = require "callbacksRequestPurchase"
callbacksRequestReceipts = require "callbacksRequestReceipts"
OuyaController = require "OuyaController"

plugin_ouya = require "plugin_ouya"
globals = require "globals"
ui = require "ui"

local inputs = {}


inputs.onGenericMotionEvent = function (playerNum, axis, val)
end


inputs.onKeyDown = function (playerNum, button)
end


inputs.onKeyUp = function (playerNum, button)

	if playerNum < 0 or playerNum > OuyaController.MAX_CONTROLLERS then
		playerNum = 0;
	end
	    
    if (button == OuyaController.BUTTON_MENU) then
		globals.txtStatus.text = "Pause Detected";
    	ui.setButtonFocus(globals.btnPause);
    end

	if (button == OuyaController.BUTTON_DPAD_LEFT) then
		ui.setButtonFocus(globals.focusButton.btnLeft);
    end
    
    if (button == OuyaController.BUTTON_DPAD_RIGHT) then
		ui.setButtonFocus(globals.focusButton.btnRight);
    end
    
    if (globals.focusButton == globals.btnProducts or globals.focusButton == globals.btnPurchase) then
	    if (button == OuyaController.BUTTON_DPAD_UP) then
			if #globals.getProducts > 1 then
				globals.selectedProduct = (globals.selectedProduct + #globals.getProducts - 1) % #globals.getProducts;
				ui.displayProductList();
			end
	    end
	    
	    if (button == OuyaController.BUTTON_DPAD_DOWN) then
			if #globals.getProducts > 1 then
				globals.selectedProduct = (globals.selectedProduct + 1) % #globals.getProducts;
				ui.displayProductList();
			end
	    end
    end
    
    if (button == OuyaController.BUTTON_O and nil ~= plugin_ouya) then
    	if globals.focusButton == globals.btnGamerInfo then
    		globals.txtStatus.text = "Request Gamer Info...";
    		globals.txtGamerUUID.text = "Gamer UUID:";
			globals.txtGamerUsername.text = "Gamer Username:";
    		print "Accessing plugin_ouya...";
    		plugin_ouya.asyncLuaOuyaRequestGamerInfo(callbacksRequestGamerInfo.onSuccess, callbacksRequestGamerInfo.onFailure, callbacksRequestGamerInfo.onCancel);
    	elseif globals.focusButton == globals.btnProducts then
    		globals.getProducts = { };
    		ui.displayProductList();
    		globals.txtStatus.text = "Requesting products...";
            local products =  { "long_sword", "sharp_axe", "cool_level", "awesome_sauce", "__DECLINED__THIS_PURCHASE" };
            local jsonData = json.encode(products);
            print "Accessing ouyaSDK...";
            plugin_ouya.asyncLuaOuyaRequestProducts(callbacksRequestProducts.onSuccess, callbacksRequestProducts.onFailure, callbacksRequestProducts.onCancel, jsonData);
    	elseif globals.focusButton == globals.btnPurchase then
    		if #globals.getProducts > 1 and globals.selectedProduct < #globals.getProducts then
	    		globals.txtStatus.text = "Requesting purchase: " .. globals.getProducts[globals.selectedProduct + 1].name;
	    		local purchasable = globals.getProducts[globals.selectedProduct + 1].identifier;
				print "Accessing plugin_ouya...";
	    		plugin_ouya.asyncLuaOuyaRequestPurchase(callbacksRequestPurchase.onSuccess, callbacksRequestPurchase.onFailure, callbacksRequestPurchase.onCancel, purchasable);
    		else
    			globals.txtStatus.text = "Select a product for purchase...";
    		end
    	elseif globals.focusButton == globals.btnReceipts then
    		globals.getReceipts = { };
    		ui.displayReceiptList();
    		globals.txtStatus.text = "Requesting receipts...";
    		print "Accessing plugin_ouya...";
    		plugin_ouya.asyncLuaOuyaRequestReceipts(callbacksRequestReceipts.onSuccess, callbacksRequestReceipts.onFailure, callbacksRequestReceipts.onCancel);	
    	elseif globals.focusButton == globals.btnExit then
    		globals.txtStatus.text = "Exiting...";
    		print "Exiting...";
    		native.requestExit();
    	end
    end
       	
	return false

end


if nil ~= plugin_ouya and nil ~= plugin_ouya.asyncLuaOuyaInitInput then
	plugin_ouya.asyncLuaOuyaInitInput(inputs.onGenericMotionEvent, inputs.onKeyDown, inputs.onKeyUp);
end


return inputs;