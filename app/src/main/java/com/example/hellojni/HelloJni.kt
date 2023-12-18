/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.hellojni

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.hellojni.databinding.ActivityHelloJniBinding

import android.widget.EditText
import android.widget.Spinner
import android.widget.Button
import android.widget.Toast

import android.widget.ArrayAdapter


class HelloJni : AppCompatActivity() {
 


private lateinit var mUIKeyEdit: EditText
private lateinit var mUIValueEdit: EditText
private lateinit var mUITypeSpinner: Spinner
private lateinit var mUIGetButton: Button
private lateinit var mUISetButton: Button
private lateinit var mStore: Store


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        /*
         * Retrieve our TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
        val binding = ActivityHelloJniBinding.inflate(layoutInflater)
        setContentView(binding.root)
      // binding.helloTextview.text = "hi"
       
       // Initialize EditText, Spinner, and Store instance from the binding
    mUIKeyEdit = binding.uiKeyEdit
    mUIValueEdit = binding.uiValueEdit
    mUITypeSpinner = binding.uiTypeSpinner
    mStore = Store()
    
   val values = StoreType.values().map { it.name }

val adapter = ArrayAdapter<String>(mUITypeSpinner.context, android.R.layout.simple_spinner_item, values)
adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)

mUITypeSpinner.adapter = adapter
    

    // Initialize Buttons from the binding
    mUIGetButton = binding.uiRetrieveButton
    mUISetButton = binding.uiSaveButton

    // Set onClickListeners for the buttons
    mUIGetButton.setOnClickListener {
        onGetValue() // call the appropriate method when this button is clicked
    }

    mUISetButton.setOnClickListener {
        onSetValue()  // handle what should happen when the 'Save' button is clicked
        
    }
    
    }
    
    
    private fun onSetValue() {
    val lKey = mUIKeyEdit.text.toString()
    val lValue = mUIValueEdit.text.toString()
    val selectedString = mUITypeSpinner.selectedItem as String
    val lType = StoreType.valueOf(selectedString)

    try {
        when (lType) {
            StoreType.Integer -> mStore.setInteger(lKey, lValue.toInt())
            StoreType.String -> mStore.setString(lKey, lValue)
           StoreType.Color -> mStore.setColor(lKey, Color(lValue))
           
        }
    } catch (e: NumberFormatException) {
        displayError("Incorrect value.")
    }catch (e: NumberFormatException) {
        displayError("Incorrect value.")
    } 
}

private fun displayError(pError: String) {
    Toast.makeText(applicationContext, pError, Toast.LENGTH_LONG).show()
}


    
    
    
    private fun onGetValue() {
    val lKey = mUIKeyEdit.text.toString()
    val selectedString = mUITypeSpinner.selectedItem as String
val lType = StoreType.valueOf(selectedString)
    
    when (lType) {
        StoreType.Integer -> mUIValueEdit.setText(mStore.getInteger(lKey).toString())
        StoreType.String -> mUIValueEdit.setText(mStore.getString(lKey))
        StoreType.Color -> mUIValueEdit.setText(mStore.getColor(lKey).toString())
    }
}

}

