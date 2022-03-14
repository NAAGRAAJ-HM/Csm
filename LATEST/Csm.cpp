/******************************************************************************/
/* File   : Csm.cpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.h"
#include "infCsm_EcuM.h"
#include "infCsm_Dcm.h"
#include "infCsm_SchM.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/


/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
VAR(module_Csm, CSM_VAR) Csm;
CONSTP2VAR(infEcuMClient, CSM_VAR, CSM_CONST) gptrinfEcuMClient_Csm = &Csm;
CONSTP2VAR(infDcmClient,  CSM_VAR, CSM_CONST) gptrinfDcmClient_Csm  = &Csm;
CONSTP2VAR(infSchMClient, CSM_VAR, CSM_CONST) gptrinfSchMClient_Csm = &Csm;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, CSM_CODE) module_Csm::InitFunction(void){
}

FUNC(void, CSM_CODE) module_Csm::DeInitFunction(void){
}

FUNC(void, CSM_CODE) module_Csm::GetVersionInfo(void){
}

FUNC(void, CSM_CODE) module_Csm::MainFunction(void){
}

#include "Csm_Unused.h"

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

/*****************************************************/
/* EOF                                               */
/*****************************************************/

