

#define CSM_RTE_SOURCE

#include "Csm_Rte.hpp"

#if(CSM_RTE_PORTS == STD_ON)

#define CSM_START_SEC_CODE
#include "MemMap.hpp"

FUNC( Std_ReturnType, CSM_CODE ) Csm_KeyElementGet43x( uint32 keyId
   ,                                                      uint32 keyElementId
   ,                                                      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) keyPtr
   ,                                                      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) keyLengthPtr ){
  return Csm_KeyElementGet( keyId, keyElementId, keyPtr, keyLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_HashDataRef( uint32 jobId
   ,                                                 Crypto_OperationModeType mode
   ,                                                 P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                 uint32 dataLength
   ,                                                 P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                 P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_Hash(  jobId
   ,                   mode
   ,                   dataPtr
   ,                   dataLength
   ,                   resultPtr
   ,                   resultLengthPtr  );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_MacGenerate43x(  uint32 jobId
   ,                                                     Crypto_OperationModeType mode
   ,                                                     P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                     uint32 dataLength
   ,                                                     P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                                     P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) macLengthPtr ){
  return Csm_MacGenerate( jobId
   ,                         mode
   ,                         dataPtr
   ,                         dataLength
   ,                         macPtr
   ,                         macLengthPtr  );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_MacGenerateDataRef( uint32 jobId
   ,                                                        Crypto_OperationModeType mode
   ,                                                        P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                        uint32 dataLength
   ,                                                        P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                                        P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) macLengthPtr ){
  return Csm_MacGenerate( jobId
   ,                         mode
   ,                         dataPtr
   ,                         dataLength
   ,                         macPtr
   ,                         macLengthPtr  );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_MacVerify43x(  uint32 jobId
   ,                                                   Crypto_OperationModeType mode
   ,                                                   P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                   uint32 dataLength
   ,                                                   P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                                   uint32 macLength
   ,                                                   P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr ){
  return Csm_MacVerify( jobId
   ,                       mode
   ,                       dataPtr
   ,                       dataLength
   ,                       macPtr
   ,                       macLength
   ,                       verifyPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_MacVerifyDataRef(  uint32 jobId
   ,                                                       Crypto_OperationModeType mode
   ,                                                       P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                       uint32 dataLength
   ,                                                       P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                                       uint32 macLength
   ,                                                       P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr ){
  return Csm_MacVerify( jobId
   ,                       mode
   ,                       dataPtr
   ,                       dataLength
   ,                       macPtr
   ,                       macLength
   ,                       verifyPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_Encrypt43x( uint32 jobId
   ,                                                Crypto_OperationModeType mode
   ,                                                P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                uint32 dataLength
   ,                                                P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_Encrypt( jobId
   ,                     mode
   ,                     dataPtr
   ,                     dataLength
   ,                     resultPtr
   ,                     resultLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_EncryptDataRef( uint32 jobId
   ,                                                    Crypto_OperationModeType mode
   ,                                                    P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                    uint32 dataLength
   ,                                                    P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                    P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_Encrypt( jobId
   ,                     mode
   ,                     dataPtr
   ,                     dataLength
   ,                     resultPtr
   ,                     resultLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_Decrypt43x(  uint32 jobId
   ,                                                 Crypto_OperationModeType mode
   ,                                                 P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                 uint32 dataLength
   ,                                                 P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                 P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_Decrypt( jobId
   ,                     mode
   ,                     dataPtr
   ,                     dataLength
   ,                     resultPtr
   ,                     resultLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_DecryptDataRef(  uint32 jobId
   ,                                                     Crypto_OperationModeType mode
   ,                                                     P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                     uint32 dataLength
   ,                                                     P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                     P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_Decrypt( jobId
   ,                     mode
   ,                     dataPtr
   ,                     dataLength
   ,                     resultPtr
   ,                     resultLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_AEADEncrypt43x(  uint32 jobId
   ,                                                     Crypto_OperationModeType mode
   ,                                                     P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                                     uint32 plaintextLength
   ,                                                     P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                                     uint32 associatedDataLength
   ,                                                     P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                                     P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) ciphertextLengthPtr
   ,                                                     P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                                     P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) tagLengthPtr ){
  return Csm_AEADEncrypt(  jobId
   ,                          mode
   ,                          plaintextPtr
   ,                          plaintextLength
   ,                          associatedDataPtr
   ,                          associatedDataLength
   ,                          ciphertextPtr
   ,                          ciphertextLengthPtr
   ,                          tagPtr
   ,                          tagLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_AEADEncryptDataRef(  uint32 jobId
   ,                                                         Crypto_OperationModeType mode
   ,                                                         P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                                         uint32 plaintextLength
   ,                                                         P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                                         uint32 associatedDataLength
   ,                                                         P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                                         P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) ciphertextLengthPtr
   ,                                                         P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                                         P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) tagLengthPtr ){
  return Csm_AEADEncrypt(  jobId
   ,                          mode
   ,                          plaintextPtr
   ,                          plaintextLength
   ,                          associatedDataPtr
   ,                          associatedDataLength
   ,                          ciphertextPtr
   ,                          ciphertextLengthPtr
   ,                          tagPtr
   ,                          tagLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_AEADDecrypt43x( uint32 jobId
   ,                                                    Crypto_OperationModeType mode
   ,                                                    P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                                    uint32 ciphertextLength
   ,                                                    P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                                    uint32 associatedDataLength
   ,                                                    P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                                    uint32 tagLength
   ,                                                    P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                                    P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) plaintextLengthPtr
   ,                                                    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr ){
  return Csm_AEADDecrypt( jobId
   ,                         mode
   ,                         ciphertextPtr
   ,                         ciphertextLength
   ,                         associatedDataPtr
   ,                         associatedDataLength
   ,                         tagPtr
   ,                         tagLength
   ,                         plaintextPtr
   ,                         plaintextLengthPtr
   ,                         verifyPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_AEADDecryptDataRef( uint32 jobId
   ,                                                        Crypto_OperationModeType mode
   ,                                                        P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                                        uint32 ciphertextLength
   ,                                                        P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                                        uint32 associatedDataLength
   ,                                                        P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                                        uint32 tagLength
   ,                                                        P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                                        P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) plaintextLengthPtr
   ,                                                        P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr ){
  return Csm_AEADDecrypt( jobId
   ,                         mode
   ,                         ciphertextPtr
   ,                         ciphertextLength
   ,                         associatedDataPtr
   ,                         associatedDataLength
   ,                         tagPtr
   ,                         tagLength
   ,                         plaintextPtr
   ,                         plaintextLengthPtr
   ,                         verifyPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_SignatureGenerate43x(  uint32 jobId
   ,                                                           Crypto_OperationModeType mode
   ,                                                           P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                           uint32 dataLength
   ,                                                           P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                           P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_SignatureGenerate( jobId
   ,                               mode
   ,                               dataPtr
   ,                               dataLength
   ,                               resultPtr
   ,                               resultLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_SignatureGenerateDataRef(  uint32 jobId
   ,                                                               Crypto_OperationModeType mode
   ,                                                               P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                               uint32 dataLength
   ,                                                               P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                               P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_SignatureGenerate( jobId
   ,                               mode
   ,                               dataPtr
   ,                               dataLength
   ,                               resultPtr
   ,                               resultLengthPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_SignatureVerify43x(  uint32 jobId
   ,                                                         Crypto_OperationModeType mode
   ,                                                         P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                         uint32 dataLength
   ,                                                         P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) signaturePtr
   ,                                                         uint32 signatureLength
   ,                                                         P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr ){
  return Csm_SignatureVerify( jobId
   ,                             mode
   ,                             dataPtr
   ,                             dataLength
   ,                             signaturePtr
   ,                             signatureLength
   ,                             verifyPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_SignatureVerifyDataRef(  uint32 jobId
   ,                                                             Crypto_OperationModeType mode
   ,                                                             P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                             uint32 dataLength
   ,                                                             P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) signaturePtr
   ,                                                             uint32 signatureLength
   ,                                                             P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr ){
  return Csm_SignatureVerify( jobId
   ,                             mode
   ,                             dataPtr
   ,                             dataLength
   ,                             signaturePtr
   ,                             signatureLength
   ,                             verifyPtr );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_RandomGenerateDataRef( uint32 jobId
   ,                                                           P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                           P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr ){
  return Csm_RandomGenerate( jobId
   ,                            resultPtr
   ,                            resultLengthPtr  );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_CancelJob43x( uint32 jobId, Crypto_OperationModeType mode ){
  return Csm_CancelJob( jobId, mode );

}

FUNC( Std_ReturnType, CSM_CODE ) Csm_CancelJobNoOpMode( uint32 jobId ){
  return Csm_CancelJob( jobId, CRYPTO_OPERATIONMODE_SINGLECALL);

}

FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateParse43x( uint32 keyId ){
  return Csm_CertificateParse( keyId );

}

FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateVerify43x( uint32 keyId
   ,                                                        uint32 verifyKeyId
   ,                                                        P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr){
  return Csm_CertificateVerify( keyId
   ,                               verifyKeyId
   ,                               verifyPtr );

}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy43x( uint32 keyId
   ,                                              uint32 targetKeyId ){
  return Csm_KeyCopy( keyId, targetKeyId );

}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive43x( uint32 keyId, uint32 targetKeyId ){
  return Csm_KeyDerive( keyId, targetKeyId );
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy43x( uint32 keyId
   ,                                                     uint32 keyElementId
   ,                                                     uint32 targetKeyId
   ,                                                     uint32 targetKeyElementId ){
  return Csm_KeyElementCopy( keyId
   ,                            keyElementId
   ,                            targetKeyId
   ,                            targetKeyElementId );
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal43x( uint32 keyId
   ,                                                            P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) publicValuePtr
   ,                                                            P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) publicValueLengthPtr ){
  return Csm_KeyExchangeCalcPubVal( keyId
   ,                                   publicValuePtr
   ,                                   publicValueLengthPtr );

}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret43x( uint32 keyId
   ,                                                            P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) partnerPublicValuePtr
   ,                                                            uint32 partnerPublicValueLength ){
  return Csm_KeyExchangeCalcSecret( keyId
   ,                                   partnerPublicValuePtr
   ,                                   partnerPublicValueLength );

}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate43x( uint32 keyId ){
  return Csm_KeyGenerate( keyId );

}

FUNC(Std_ReturnType, CSM_CODE) Csm_SaveContextJobWithVoidPtr(uint32 jobId
   ,  P2VAR(void, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) contextBufferLengthPtr){
  return Csm_SaveContextJob(jobId
   ,   (P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR))contextBufferPtr
   ,   (P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR))contextBufferLengthPtr);

}

FUNC(Std_ReturnType, CSM_CODE) Csm_RestoreContextJobWithVoidPtr(uint32 jobId
   ,  P2VAR(void, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,  uint32 contextBufferLength){
  return Csm_RestoreContextJob(jobId
   ,   (P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR))contextBufferPtr
   ,   contextBufferLength);

}

#define CSM_STOP_SEC_CODE
#include "MemMap.hpp"

#endif

