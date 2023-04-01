#pragma once
/******************************************************************************/
/* File   : ServiceCsm_core.hpp                                                      */
/*                                                                            */
/* Author : Nagaraja HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Nagaraja HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/NagarajaHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "CompilerCfg_ServiceCsm.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SERVICECSM_CORE_FUNCTIONALITIES                                               \
              FUNC(void, SERVICECSM_CODE) Hash                       (void);          \
              FUNC(void, SERVICECSM_CODE) MacGenerate                (void);          \
              FUNC(void, SERVICECSM_CODE) MacVerify                  (void);          \
              FUNC(void, SERVICECSM_CODE) Encrypt                    (void);          \
              FUNC(void, SERVICECSM_CODE) Decrypt                    (void);          \
              FUNC(void, SERVICECSM_CODE) AECUABEADEncrypt                (void);          \
              FUNC(void, SERVICECSM_CODE) AECUABEADDecrypt                (void);          \
              FUNC(void, SERVICECSM_CODE) SignatureGenerate          (void);          \
              FUNC(void, SERVICECSM_CODE) SignatureVerify            (void);          \
              FUNC(void, SERVICECSM_CODE) RandomGenerate             (void);          \
              FUNC(void, SERVICECSM_CODE) KeyElementSet              (void);          \
              FUNC(void, SERVICECSM_CODE) KeySetValid                (void);          \
              FUNC(void, SERVICECSM_CODE) KeySetInvalid              (void);          \
              FUNC(void, SERVICECSM_CODE) KeyGetStatus               (void);          \
              FUNC(void, SERVICECSM_CODE) KeyElementGet              (void);          \
              FUNC(void, SERVICECSM_CODE) KeyElementCopy             (void);          \
              FUNC(void, SERVICECSM_CODE) KeyCopy                    (void);          \
              FUNC(void, SERVICECSM_CODE) KeyElementCopyPartial      (void);          \
              FUNC(void, SERVICECSM_CODE) RandomSeed                 (void);          \
              FUNC(void, SERVICECSM_CODE) KeyGenerate                (void);          \
              FUNC(void, SERVICECSM_CODE) KeyDerive                  (void);          \
              FUNC(void, SERVICECSM_CODE) KeyExchangeCalcPubValue    (void);          \
              FUNC(void, SERVICECSM_CODE) KeyExchangeCalcSecret      (void);          \
              FUNC(void, SERVICECSM_CODE) JobKeySetValid             (void);          \
              FUNC(void, SERVICECSM_CODE) JobKeySetInvalid           (void);          \
              FUNC(void, SERVICECSM_CODE) JobRandomSeed              (void);          \
              FUNC(void, SERVICECSM_CODE) JobKeyGenerate             (void);          \
              FUNC(void, SERVICECSM_CODE) JobKeyDerive               (void);          \
              FUNC(void, SERVICECSM_CODE) JobKeyExchangeCalcPubValue (void);          \
              FUNC(void, SERVICECSM_CODE) JobKeyExchangeCalcSecret   (void);          \
              FUNC(void, SERVICECSM_CODE) SaveContextJob             (void);          \
              FUNC(void, SERVICECSM_CODE) RestoreContextJob          (void);          \
              FUNC(void, SERVICECSM_CODE) McalCancelJob                  (void);          \
              FUNC(void, SERVICECSM_CODE) CbNotification             (void);          \

#define SERVICECSM_CORE_FUNCTIONALITIES_VIRTUAL                                       \
      virtual FUNC(void, SERVICECSM_CODE) Hash                       (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) MacGenerate                (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) MacVerify                  (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) Encrypt                    (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) Decrypt                    (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) AECUABEADEncrypt                (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) AECUABEADDecrypt                (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) SignatureGenerate          (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) SignatureVerify            (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) RandomGenerate             (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyElementSet              (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeySetValid                (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeySetInvalid              (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyGetStatus               (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyElementGet              (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyElementCopy             (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyCopy                    (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyElementCopyPartial      (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) RandomSeed                 (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyGenerate                (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyDerive                  (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyExchangeCalcPubValue    (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) KeyExchangeCalcSecret      (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobKeySetValid             (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobKeySetInvalid           (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobRandomSeed              (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobKeyGenerate             (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobKeyDerive               (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobKeyExchangeCalcPubValue (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) JobKeyExchangeCalcSecret   (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) SaveContextJob             (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) RestoreContextJob          (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) McalCancelJob                  (void) = 0;      \
      virtual FUNC(void, SERVICECSM_CODE) CbNotification             (void) = 0;      \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class class_ServiceCsm_Functionality{
   public:
      SERVICECSM_CORE_FUNCTIONALITIES_VIRTUAL
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

