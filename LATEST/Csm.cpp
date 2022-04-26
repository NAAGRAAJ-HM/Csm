/******************************************************************************/
/* File   : Csm.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "infCsm_EcuM.hpp"
#include "infCsm_Dcm.hpp"
#include "infCsm_SchM.hpp"

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
class class_Csm_Functionality{
   public:
      FUNC(void, CSM_CODE) Hash                       (void);
      FUNC(void, CSM_CODE) MacGenerate                (void);
      FUNC(void, CSM_CODE) MacVerify                  (void);
      FUNC(void, CSM_CODE) Encrypt                    (void);
      FUNC(void, CSM_CODE) Decrypt                    (void);
      FUNC(void, CSM_CODE) AEADEncrypt                (void);
      FUNC(void, CSM_CODE) AEADDecrypt                (void);
      FUNC(void, CSM_CODE) SignatureGenerate          (void);
      FUNC(void, CSM_CODE) SignatureVerify            (void);
      FUNC(void, CSM_CODE) RandomGenerate             (void);
      FUNC(void, CSM_CODE) KeyElementSet              (void);
      FUNC(void, CSM_CODE) KeySetValid                (void);
      FUNC(void, CSM_CODE) KeySetInvalid              (void);
      FUNC(void, CSM_CODE) KeyGetStatus               (void);
      FUNC(void, CSM_CODE) KeyElementGet              (void);
      FUNC(void, CSM_CODE) KeyElementCopy             (void);
      FUNC(void, CSM_CODE) KeyCopy                    (void);
      FUNC(void, CSM_CODE) KeyElementCopyPartial      (void);
      FUNC(void, CSM_CODE) RandomSeed                 (void);
      FUNC(void, CSM_CODE) KeyGenerate                (void);
      FUNC(void, CSM_CODE) KeyDerive                  (void);
      FUNC(void, CSM_CODE) KeyExchangeCalcPubValue    (void);
      FUNC(void, CSM_CODE) KeyExchangeCalcSecret      (void);
      FUNC(void, CSM_CODE) JobKeySetValid             (void);
      FUNC(void, CSM_CODE) JobKeySetInvalid           (void);
      FUNC(void, CSM_CODE) JobRandomSeed              (void);
      FUNC(void, CSM_CODE) JobKeyGenerate             (void);
      FUNC(void, CSM_CODE) JobKeyDerive               (void);
      FUNC(void, CSM_CODE) JobKeyExchangeCalcPubValue (void);
      FUNC(void, CSM_CODE) JobKeyExchangeCalcSecret   (void);
      FUNC(void, CSM_CODE) SaveContextJob             (void);
      FUNC(void, CSM_CODE) RestoreContextJob          (void);
      FUNC(void, CSM_CODE) CancelJob                  (void);
      FUNC(void, CSM_CODE) CbNotification             (void);
};

class module_Csm:
      public abstract_module
   ,  public class_Csm_Functionality
{
   public:
      module_Csm(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, CSM_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, CSM_CONFIG_DATA, CSM_APPL_CONST) lptrCfgModule
      );
      FUNC(void, CSM_CODE) DeInitFunction (void);
      FUNC(void, CSM_CODE) MainFunction   (void);
};

extern VAR(module_Csm, CSM_VAR) Csm;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, CSM_VAR, CSM_CONST) gptrinfEcuMClient_Csm = &Csm;
CONSTP2VAR(infDcmClient,  CSM_VAR, CSM_CONST) gptrinfDcmClient_Csm  = &Csm;
CONSTP2VAR(infSchMClient, CSM_VAR, CSM_CONST) gptrinfSchMClient_Csm = &Csm;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
#include "CfgCsm.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Csm, CSM_VAR) Csm(
   {
         CSM_AR_RELEASE_VERSION_MAJOR
      ,  CSM_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, CSM_CODE) module_Csm::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, CSM_CONFIG_DATA, CSM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Csm_InitCheck)
   if(E_OK == IsInitDone){
#if(STD_ON == Csm_DevErrorDetect)
      Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
      );
#endif
   }
   else{
#endif
      if(NULL_PTR == lptrCfgModule){
#if(STD_ON == Csm_DevErrorDetect)
         Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
         );
#endif
      }
      else{
         if(STD_LOW){
// check lptrCfgModule for memory faults
            lptrCfg = lptrCfgModule;
         }
         else{
// use PBcfgCanIf as back-up configuration
            lptrCfg = &PBcfgCsm;
         }
      }
      IsInitDone = E_OK;
#if(STD_ON == Csm_InitCheck)
   }
#endif
}

FUNC(void, CSM_CODE) module_Csm::DeInitFunction(void){
#if(STD_ON == Csm_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == Csm_DevErrorDetect)
      Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
      );
#endif
   }
   else{
#endif
      IsInitDone = E_NOT_OK;
#if(STD_ON == Csm_InitCheck)
   }
#endif
}

FUNC(void, CSM_CODE) module_Csm::MainFunction(void){
#if(STD_ON == Csm_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == Csm_DevErrorDetect)
      Det_ReportError(
      0 //TBD: IdModule
   ,  0 //TBD: IdInstance
   ,  0 //TBD: IdApi
   ,  0 //TBD: IdError
      );
#endif
   }
   else{
#endif
#if(STD_ON == Csm_InitCheck)
   }
#endif
}

FUNC(void, CSM_CODE) class_Csm_Functionality::Hash(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::MacGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::MacVerify(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::Encrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::Decrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::AEADEncrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::AEADDecrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::SignatureGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::SignatureVerify(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::RandomGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyElementSet(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeySetValid(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeySetInvalid(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyGetStatus(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyElementGet(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyElementCopy(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyCopy(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyElementCopyPartial(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::RandomSeed(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyDerive(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyExchangeCalcPubValue(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::KeyExchangeCalcSecret(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobKeySetValid(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobKeySetInvalid(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobRandomSeed(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobKeyGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobKeyDerive(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobKeyExchangeCalcPubValue(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::JobKeyExchangeCalcSecret(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::SaveContextJob(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::RestoreContextJob(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::CancelJob(void){
}

FUNC(void, CSM_CODE) class_Csm_Functionality::CbNotification(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

