/******************************************************************************/
/* File   : Csm.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "Csm.hpp"
#include "infCsm_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CSM_AR_RELEASE_VERSION_MAJOR                                           4
#define CSM_AR_RELEASE_VERSION_MINOR                                           3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(CSM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible CSM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(CSM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible CSM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, CSM_VAR, CSM_CONST) gptrinfEcuMClient_Csm = &Csm;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Csm, CSM_VAR) Csm;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, CSM_CODE) module_Csm::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, CSM_CONFIG_DATA, CSM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Csm_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         lptrCfg = lptrCfgModule;
      }
      else{
#if(STD_ON == Csm_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == Csm_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == Csm_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  CSM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, CSM_CODE) module_Csm::DeInitFunction(
   void
){
#if(STD_ON == Csm_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == Csm_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == Csm_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  CSM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, CSM_CODE) module_Csm::MainFunction(
   void
){
#if(STD_ON == Csm_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == Csm_InitCheck)
   }
   else{
#if(STD_ON == Csm_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  CSM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, CSM_CODE) module_Csm::Hash(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::MacGenerate(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::MacVerify(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::Encrypt(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::Decrypt(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::AEADEncrypt(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::AEADDecrypt(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::SignatureGenerate(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::SignatureVerify(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::RandomGenerate(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyElementSet(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeySetValid(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeySetInvalid(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyGetStatus(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyElementGet(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyElementCopy(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyCopy(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyElementCopyPartial(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::RandomSeed(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyGenerate(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyDerive(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyExchangeCalcPubValue(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::KeyExchangeCalcSecret(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobKeySetValid(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobKeySetInvalid(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobRandomSeed(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobKeyGenerate(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobKeyDerive(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobKeyExchangeCalcPubValue(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::JobKeyExchangeCalcSecret(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::SaveContextJob(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::RestoreContextJob(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::CancelJob(
   void
){
}

FUNC(void, CSM_CODE) module_Csm::CbNotification(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

