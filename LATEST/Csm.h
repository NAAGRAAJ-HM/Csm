#pragma once
/*****************************************************/
/* File   : Csm.h                                    */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "Std_Types.h"
#include "Compiler_Cfg_Csm.h"

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
class class_Csm{
   public:
/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
      FUNC(void, CSM_CODE) GetVersionInfo             (void);
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
      FUNC(void, CSM_CODE) MainFunction               (void);
};

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
extern class_Csm Csm;

/*****************************************************/
/* EOF                                               */
/*****************************************************/

