

#if !defined (CSM_RTE_H)
#define CSM_RTE_H

#include "SwcServiceCsm.hpp"

#if !defined CSM_RTE_SOURCE
#error "This is a private header and should only be included by Csm_Rte.c"
#endif

#if(CSM_RTE_PORTS == STD_ON)

#define CSM_START_SEC_CODE
#include "MemMap.hpp"

extern FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob43x(uint32 jobId, Crypto_OperationModeType mode);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJobNoOpMode(uint32 jobId);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_HashDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) macLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerateDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) macLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,  uint32 macLength
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerifyDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,  uint32 macLength
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_EncryptDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_DecryptDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,  uint32 plaintextLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,  uint32 associatedDataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) ciphertextLengthPtr
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) tagLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncryptDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,  uint32 plaintextLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,  uint32 associatedDataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) ciphertextLengthPtr
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) tagLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,  uint32 ciphertextLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,  uint32 associatedDataLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,  uint32 tagLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) plaintextLengthPtr
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecryptDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,  uint32 ciphertextLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,  uint32 associatedDataLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,  uint32 tagLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) plaintextLengthPtr
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerateDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify43x(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) signaturePtr
   ,  uint32 signatureLength
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerifyDataRef(uint32 jobId
   ,  Crypto_OperationModeType mode
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,  uint32 dataLength
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) signaturePtr
   ,  uint32 signatureLength
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerateDataRef(uint32 jobId
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet43x(uint32 keyId
   ,  uint32 keyElementId
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) keyPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) keyLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateParse43x(uint32 keyId);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateVerify43x(uint32 keyId
   ,  uint32 verifyKeyId
   ,  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy43x(uint32 keyId, uint32 targetKeyId);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive43x(uint32 keyId, uint32 targetKeyId);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy43x(uint32 keyId
   ,  uint32 keyElementId
   ,  uint32 targetKeyId
   ,  uint32 targetKeyElementId);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal43x(uint32 keyId
   ,  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) publicValuePtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) publicValueLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret43x(uint32 keyId
   ,  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) partnerPublicValuePtr
   ,  uint32 partnerPublicValueLength);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate43x(uint32 keyId);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_SaveContextJobWithVoidPtr(uint32 jobId
   ,  P2VAR(void, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) contextBufferLengthPtr);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_RestoreContextJobWithVoidPtr(uint32 jobId
   ,  P2VAR(void, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,  uint32 contextBufferLength);

#define CSM_STOP_SEC_CODE
#include "MemMap.hpp"

#endif

#endif

