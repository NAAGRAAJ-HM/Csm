#pragma once

#include "Std_Types.h"

class class_Csm{
   public:
      void InitFunction               (void);
      void GetVersionInfo             (void);
      void Hash                       (void);
      void MacGenerate                (void);
      void MacVerify                  (void);
      void Encrypt                    (void);
      void Decrypt                    (void);
      void AEADEncrypt                (void);
      void AEADDecrypt                (void);
      void SignatureGenerate          (void);
      void SignatureVerify            (void);
      void RandomGenerate             (void);
      void KeyElementSet              (void);
      void KeySetValid                (void);
      void KeySetInvalid              (void);
      void KeyGetStatus               (void);
      void KeyElementGet              (void);
      void KeyElementCopy             (void);
      void KeyCopy                    (void);
      void KeyElementCopyPartial      (void);
      void RandomSeed                 (void);
      void KeyGenerate                (void);
      void KeyDerive                  (void);
      void KeyExchangeCalcPubValue    (void);
      void KeyExchangeCalcSecret      (void);
      void JobKeySetValid             (void);
      void JobKeySetInvalid           (void);
      void JobRandomSeed              (void);
      void JobKeyGenerate             (void);
      void JobKeyDerive               (void);
      void JobKeyExchangeCalcPubValue (void);
      void JobKeyExchangeCalcSecret   (void);
      void SaveContextJob             (void);
      void RestoreContextJob          (void);
      void CancelJob                  (void);
      void CbNotification             (void);
      void MainFunction               (void);
};

extern class_Csm Csm;

