package com.example.hellojni

class Store {

    external fun getInteger(pKey: String): Int
    external fun setInteger(pKey: String, pInt: Int)

    external fun getString(pKey: String): String
    external fun setString(pKey: String, pString: String)
    
   external fun getColor(pKey: String): Color 
   external fun setColor( pKey: String,  pColor:Color)
   
    companion object {
        init {
            System.loadLibrary("store")
        }
    }
}