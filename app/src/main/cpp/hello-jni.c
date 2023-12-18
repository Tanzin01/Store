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
 *
 */

#include "Store.h"
#include <string.h>

static Store gStore = { {}, 0 };





  JNIEXPORT jint JNICALL
Java_com_example_hellojni_Store_getInteger(JNIEnv* env, jobject thiz, jstring key) {
    // Assuming these functions and structures are declared/defined elsewhere
    StoreEntry* entry = findEntry(env, &gStore, key, NULL);

    if (isEntryValid(env, entry, StoreType_Integer)) {
        return entry->mValue.mInteger;
    } else {
        return 0; // Return 0 for non-existent or invalid entry
    }
}

JNIEXPORT void JNICALL
Java_com_example_hellojni_Store_setInteger(JNIEnv* env, jobject thiz, jstring key, jint pInteger) {
    // Assuming these functions and structures are declared/defined elsewhere
    StoreEntry* entry = allocateEntry(env, &gStore, key);

    if (entry != NULL) {
        entry->mType = StoreType_Integer;
        entry->mValue.mInteger = pInteger;
    }
}

 JNIEXPORT jstring JNICALL
Java_com_example_hellojni_Store_getString(JNIEnv* env, jobject thiz, jstring key) {
    // Assuming these functions and structures are declared/defined elsewhere
    StoreEntry* entry = findEntry(env, &gStore, key, NULL);

    if (isEntryValid(env, entry, StoreType_String)) {
        return (*env)->NewStringUTF(env, entry->mValue.mString);
    } else {
        return NULL;
    }
}


int32_t isEntryValid(JNIEnv * pEnv, StoreEntry * pEntry, StoreType pType ){
    
    if(pEntry != NULL && pEntry->mType == pType ) {
        
        return 1;
        
    }
    return 0;
}
 JNIEXPORT void JNICALL
Java_com_example_hellojni_Store_setString(JNIEnv* env, jobject thiz, jstring key, jstring string) {
    const char* stringTmp =(*env)->GetStringUTFChars(env, string, NULL);

    if (stringTmp == NULL) {
        return;
    }

    // Assuming these functions and structures are declared/defined elsewhere
    StoreEntry* entry = allocateEntry(env, &gStore, key);

    if (entry != NULL) {
        entry->mType = StoreType_String;
        jsize stringLength =(*env)->GetStringUTFLength(env, string);
        entry->mValue.mString = (char*)malloc(sizeof(char) * (stringLength + 1));
        
        if (entry->mValue.mString != NULL) {
            strcpy(entry->mValue.mString, stringTmp);
        }
    }

   (*env)->ReleaseStringUTFChars(env, string, stringTmp);
}


StoreEntry* findEntry(JNIEnv* pEnv, Store* pStore, jstring pKey, int32_t* pError) {
    

    const char* lKeyTmp = (*pEnv)->GetStringUTFChars(pEnv, pKey, NULL);
    if (lKeyTmp == NULL) {
        
        return NULL;
    }

    StoreEntry* lEntry = pStore->mEntries;
    StoreEntry* lEntryEnd = lEntry + pStore->mLength;

    while (lEntry < lEntryEnd && strcmp(lEntry->mKey, lKeyTmp) != 0) {
        ++lEntry;
    }

    (*pEnv)->ReleaseStringUTFChars(pEnv, pKey, lKeyTmp);

    if (lEntry == lEntryEnd) {
        return NULL;
    } else {
        return lEntry;
    }
}

StoreEntry* allocateEntry(JNIEnv* pEnv, Store* pStore, jstring pKey) {
    int32_t lError = 0;
    StoreEntry* lEntry = findEntry(pEnv, pStore, pKey, &lError); 
    if (lEntry != NULL) {
        releaseEntryValue(pEnv, lEntry); 
    } else if (!lError) {
        if (pStore->mLength >= STORE_MAX_CAPACITY) { 
            return NULL;
        } 
        lEntry = pStore->mEntries + pStore->mLength;
        const char* lKeyTmp = (*pEnv)->GetStringUTFChars(pEnv,pKey, NULL);
        if (lKeyTmp == NULL) { 
            return NULL; // Fixed: Added return statement if lKeyTmp is NULL
        }
        lEntry->mKey = (char*) malloc(strlen(lKeyTmp) + 1); // Fixed: Allocated space for null terminator
        if (lEntry->mKey == NULL) {
            return NULL; // Fixed: Added check for malloc failure
        }
        strcpy(lEntry->mKey, lKeyTmp);
        (*pEnv)->ReleaseStringUTFChars(pEnv, pKey, lKeyTmp); 
        ++pStore->mLength;
    }
    return lEntry; 
}

void releaseEntryValue(JNIEnv* pEnv, StoreEntry* pEntry) { 
    int i;
    switch (pEntry->mType) {
         case StoreType_String:
         free(pEntry->mValue.mString);
         break;
        case StoreType_Color:
(*pEnv)->DeleteGlobalRef(pEnv, pEntry->mValue.mColor); 
break;
         
} } 


JNIEXPORT jobject JNICALL Java_com_example_hellojni_Store_getColor(JNIEnv* pEnv, jobject pThis, jstring pKey) {
     StoreEntry* lEntry = findEntry(pEnv, &gStore, pKey, NULL);
      if (isEntryValid(pEnv, lEntry, StoreType_Color)) { 
          return lEntry->mValue.mColor;}
       else { return NULL; } }

JNIEXPORT void JNICALL Java_com_example_hellojni_Store_setColor (JNIEnv* pEnv, jobject pThis, jstring pKey, jobject pColor) { 
    jobject lColor = (*pEnv)->NewGlobalRef(pEnv, pColor); 
    if (lColor == NULL) {
         return;
    }
StoreEntry* lEntry = allocateEntry(pEnv, &gStore, pKey); 
if (lEntry != NULL) {
lEntry->mType = StoreType_Color;
 lEntry->mValue.mColor = lColor;
} else { (*pEnv)->DeleteGlobalRef(pEnv, lColor); } }


