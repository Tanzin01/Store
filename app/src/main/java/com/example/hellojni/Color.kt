package com.example.hellojni;

class Color(pColor: String) {
     
     private var mColor: Int = 0
     
     fun Color(pColor: String) {
    mColor = android.graphics.Color.parseColor(pColor)
}

override fun toString(): String {
    return String.format("#%06X", mColor)
}

}
