/******************************************************************************/
/* File   : Csm.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.hpp"
#include "CfgCsm.hpp"
#include "infCsm_EcuM.hpp"
#include "infCsm_Dcm.hpp"
#include "infCsm_SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CSM_AR_RELEASE_MAJOR_VERSION                                           4
#define CSM_AR_RELEASE_MINOR_VERSION                                           3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(CSM_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION)
   #error "Incompatible CSM_AR_RELEASE_MAJOR_VERSION!"
#endif

#if(CSM_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)
   #error "Incompatible CSM_AR_RELEASE_MINOR_VERSION!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_Csm:
      public abstract_module
{
   public:
      FUNC(void, CSM_CODE) InitFunction   (void);
      FUNC(void, CSM_CODE) DeInitFunction (void);
      FUNC(void, CSM_CODE) GetVersionInfo (void);
      FUNC(void, CSM_CODE) MainFunction   (void);

   private:
      CONST(Std_TypeVersionInfo, CSM_CONST) VersionInfo = {
            0x0000
         ,  0xFFFF
         ,  0x01
         ,  '0'
         ,  '1'
         ,  '0'
      };
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_Csm, CSM_VAR) Csm;
CONSTP2VAR(infEcuMClient, CSM_VAR, CSM_CONST) gptrinfEcuMClient_Csm = &Csm;
CONSTP2VAR(infDcmClient,  CSM_VAR, CSM_CONST) gptrinfDcmClient_Csm  = &Csm;
CONSTP2VAR(infSchMClient, CSM_VAR, CSM_CONST) gptrinfSchMClient_Csm = &Csm;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, CSM_CODE) module_Csm::InitFunction(void){
   Csm.IsInitDone = E_OK;
}

FUNC(void, CSM_CODE) module_Csm::DeInitFunction(void){
   Csm.IsInitDone = E_NOT_OK;
}

FUNC(void, CSM_CODE) module_Csm::GetVersionInfo(void){
#if(STD_ON == Csm_DevErrorDetect)
//TBD: API parameter check
   Det_ReportError(
   );
#endif
}

FUNC(void, CSM_CODE) module_Csm::MainFunction(void){
}

class class_Csm_Unused{
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

FUNC(void, CSM_CODE) class_Csm_Unused::Hash(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::MacGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::MacVerify(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::Encrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::Decrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::AEADEncrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::AEADDecrypt(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::SignatureGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::SignatureVerify(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::RandomGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyElementSet(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeySetValid(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeySetInvalid(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyGetStatus(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyElementGet(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyElementCopy(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyCopy(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyElementCopyPartial(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::RandomSeed(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyDerive(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyExchangeCalcPubValue(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::KeyExchangeCalcSecret(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobKeySetValid(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobKeySetInvalid(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobRandomSeed(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobKeyGenerate(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobKeyDerive(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobKeyExchangeCalcPubValue(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::JobKeyExchangeCalcSecret(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::SaveContextJob(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::RestoreContextJob(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::CancelJob(void){
}

FUNC(void, CSM_CODE) class_Csm_Unused::CbNotification(void){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

