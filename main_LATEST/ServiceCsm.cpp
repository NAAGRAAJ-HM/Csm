/******************************************************************************/
/* File   : ServiceCsm.cpp                                                    */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "ServiceCsm.hpp"
#include "infServiceCsm_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SERVICECSM_AR_RELEASE_VERSION_MAJOR                                    4
#define SERVICECSM_AR_RELEASE_VERSION_MINOR                                    3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(SERVICECSM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible SERVICECSM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(SERVICECSM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible SERVICECSM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_ServiceCsm, SERVICECSM_VAR) ServiceCsm;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SERVICECSM_CODE) module_ServiceCsm::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, SERVICECSM_CONST,       SERVICECSM_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICECSM_CONFIG_DATA, SERVICECSM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServiceCsm_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrConstModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrConst = (const ConstServiceCsm_Type*)lptrConstModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == ServiceCsm_DevErrorDetect)
         ServiceDet_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == ServiceCsm_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == ServiceCsm_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICECSM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::DeInitFunction(
   void
){
#if(STD_ON == ServiceCsm_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServiceCsm_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == ServiceCsm_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICECSM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::MainFunction(
   void
){
#if(STD_ON == ServiceCsm_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServiceCsm_InitCheck)
   }
   else{
#if(STD_ON == ServiceCsm_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICECSM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::Hash(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::MacGenerate(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::MacVerify(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::Encrypt(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::Decrypt(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::AECUABEADEncrypt(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::AECUABEADDecrypt(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::SignatureGenerate(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::SignatureVerify(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::RandomGenerate(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyElementSet(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeySetValid(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeySetInvalid(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyGetStatus(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyElementGet(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyElementCopy(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyCopy(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyElementCopyPartial(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::RandomSeed(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyGenerate(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyDerive(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyExchangeCalcPubValue(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::KeyExchangeCalcSecret(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobKeySetValid(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobKeySetInvalid(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobRandomSeed(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobKeyGenerate(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobKeyDerive(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobKeyExchangeCalcPubValue(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::JobKeyExchangeCalcSecret(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::SaveContextJob(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::RestoreContextJob(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::McalCancelJob(
   void
){
}

FUNC(void, SERVICECSM_CODE) module_ServiceCsm::CbNotification(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

