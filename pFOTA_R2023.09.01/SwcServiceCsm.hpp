#if !defined (CSM_H)
#define CSM_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "CfgSwcServiceCsm.hpp"

#define CSM_VENDOR_ID                                                (1u)
#define CSM_MODULE_ID                                                (110u)
#define CSM_INSTANCE_ID                                              (0u)
#define CSM_AR_RELEASE_MAJOR_VERSION                                 (0x04u)
#define CSM_AR_RELEASE_MINOR_VERSION                                 (0x04u)
#define CSM_AR_RELEASE_REVISION_VERSION                              (0x00u)
#define CSM_SW_MAJOR_VERSION                                         (6u)
#define CSM_SW_MINOR_VERSION                                         (3u)
#define CSM_SW_PATCH_VERSION                                         (0u)
#define CSM_INIT_ID                                                  (0x00u)
#define CSM_MAINFUNCTION_ID                                          (0x01u)
#define CSM_GETVERSIONINFO_ID                                        (0x3Bu)
#define CSM_KEYELEMENTSET_ID                                         (0x78u)
#define CSM_KEYSETVALID_ID                                           (0x67u)
#define CSM_JOBKEYSETVALID_ID                                        (0x7Au)
#define CSM_KEYELEMENTGET_ID                                         (0x68u)
#define CSM_KEYELEMENTCOPY_ID                                        (0x71u)
#define CSM_KEYELEMENTCOPYPARTIAL_ID                                 (0x79u)
#define CSM_KEYCOPY_ID                                               (0x73u)
#define CSM_RANDOMSEED_ID                                            (0x69u)
#define CSM_JOBRANDOMSEED_ID                                         (0x7Bu)
#define CSM_KEYGENERATE_ID                                           (0x6Au)
#define CSM_JOBKEYGENERATE_ID                                        (0x7Cu)
#define CSM_KEYDERIVE_ID                                             (0x6Bu)
#define CSM_JOBKEYDERIVE_ID                                          (0x7Du)
#define CSM_KEYEXCHANGECALCPUBVAL_ID                                 (0x6Cu)
#define CSM_JOBKEYEXCHANGECALCPUBVAL_ID                              (0x7Eu)
#define CSM_KEYEXCHANGECALCSECRET_ID                                 (0x6Du)
#define CSM_JOBKEYEXCHANGECALCSECRET_ID                              (0x7Fu)
#define CSM_CERTIFICATEPARSE_ID                                      (0x6Eu)
#define CSM_CERTIFICATEVERIFY_ID                                     (0x74u)
#define CSM_HASH_ID                                                  (0x5Du)
#define CSM_MACGENERATE_ID                                           (0x60u)
#define CSM_MACVERIFY_ID                                             (0x61u)
#define CSM_ENCRYPT_ID                                               (0x5Eu)
#define CSM_DECRYPT_ID                                               (0x5Fu)
#define CSM_AEADENCRYPT_ID                                           (0x62u)
#define CSM_AEADDECRYPT_ID                                           (0x63u)
#define CSM_SIGNATUREGENERATE_ID                                     (0x76u)
#define CSM_SIGNATUREVERIFY_ID                                       (0x64u)
#define CSM_SECURECOUNTERINCREMENT_ID                                (0x65u)
#define CSM_SECURECOUNTERREAD_ID                                     (0x66u)
#define CSM_RANDOMGENERATE_ID                                        (0x72u)
#define CSM_CANCELJOB_ID                                             (0x6Fu)
#define CSM_CALLBACKNOTIFICATION_ID                                  (0x70u)
#define CSM_SAVECONTEXTJOB_ID                                        (0x86u)
#define CSM_RESTORECONTEXTJOB_ID                                     (0x87u)
#define CSM_E_NO_ERROR                                               (0x00u)
#define CSM_E_PARAM_POINTER                                          (0x01u)
#define CSM_E_UNINIT                                                 (0x05u)
#define CSM_E_INIT_FAILED                                            (0x07u)
#define CSM_E_SERVICE_TYPE                                           (0x09u)
#define CSM_E_PARAM_METHOD_INVALID                                   (0x03u)
#define CSM_E_ALREADY_INITIALIZED                                    (0x11u)
#define CSM_UNINIT                                                   (0x00u)
#define CSM_INITIALIZED                                              (0x01u)
#define CSM_CALLOUT_STATE_IDLE                                       (0x00u)
#define CSM_CALLOUT_STATE_PRE_INITIAL                                (0x01u)
#define CSM_CALLOUT_STATE_PRE_PENDING                                (0x02u)
#define CSM_CALLOUT_STATE_PROCESSING                                 (0x03u)
#define CSM_CALLOUT_STATE_PROCESSING_ABORTED_BY_CALLOUT              (0x04u)
#define CSM_CALLOUT_STATE_POST_INITIAL                               (0x05u)
#define CSM_CALLOUT_STATE_POST_PENDING                               (0x06u)

#define CSM_START_SEC_CODE
#include "MemMap.hpp"

FUNC( void, CSM_CODE)  Csm_Init(void);
FUNC( void, CSM_CODE ) Csm_InitMemory(void);

#if( CSM_VERSION_INFO_API == STD_ON )

FUNC( void, CSM_CODE ) Csm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CSM_APPL_VAR ) versioninfo );
#endif

FUNC( Std_ReturnType, CSM_CODE ) Csm_CancelJob(uint32 jobId, Crypto_OperationModeType mode);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet(uint32 keyId
   ,                                                uint32 keyElementId
   ,                                                P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) keyPtr
   ,                                                uint32 keyLength);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid(uint32 keyId);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet(uint32 keyId
   ,                                                uint32 keyElementId
   ,                                                P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) keyPtr
   ,                                                P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) keyLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy(uint32 keyId
   ,                                                 uint32 keyElementId
   ,                                                 uint32 targetKeyId
   ,                                                 uint32 targetKeyElementId);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial( uint32 keyId
   ,                                                         uint32 keyElementId
   ,                                                         uint32 keyElementSourceOffset
   ,                                                         uint32 keyElementTargetOffset
   ,                                                         uint32 keyElementCopyLength
   ,                                                         uint32 targetKeyId
   ,                                                         uint32 targetKeyElementId);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy(uint32 keyId
   ,                                          uint32 targetKeyId);

FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed(uint32 keyId
   ,                                             P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) seedPtr
   ,                                             uint32 seedLength);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate(uint32 keyId);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive(uint32 keyId
   ,                                            uint32 targetKeyId);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal(uint32 keyId
   ,                                                        P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) publicValuePtr
   ,                                                        P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) publicValueLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret(uint32 keyId
   ,                                                        P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) partnerPublicValuePtr
   ,                                                        uint32 partnerPublicValueLength);

FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateParse(uint32 keyId);

FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateVerify(uint32 keyId
   ,                                                    uint32 verifyKeyId
   ,                                                    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_Hash(uint32 jobId
   ,                                       Crypto_OperationModeType mode
   ,                                       P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                       uint32 dataLength
   ,                                       P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                       P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate(uint32 jobId
   ,                                              Crypto_OperationModeType mode
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                              uint32 dataLength
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) macLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify(uint32 jobId
   ,                                            Crypto_OperationModeType mode
   ,                                            P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                            uint32 dataLength
   ,                                            P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                            uint32 macLength
   ,                                            P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt(uint32 jobId
   ,                                          Crypto_OperationModeType mode
   ,                                          P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                          uint32 dataLength
   ,                                          P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                          P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt(uint32 jobId
   ,                                          Crypto_OperationModeType mode
   ,                                          P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                          uint32 dataLength
   ,                                          P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                          P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt(uint32 jobId
   ,                                              Crypto_OperationModeType mode
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                              uint32 plaintextLength
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                              uint32 associatedDataLength
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) ciphertextLengthPtr
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) tagLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt(uint32 jobId
   ,                                              Crypto_OperationModeType mode
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                              uint32 ciphertextLength
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                              uint32 associatedDataLength
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                              uint32 tagLength
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) plaintextLengthPtr
   ,                                              P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate(uint32 jobId
   ,                                                    Crypto_OperationModeType mode
   ,                                                    P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                    uint32 dataLength
   ,                                                    P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                    P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify(uint32 jobId
   ,                                                  Crypto_OperationModeType mode
   ,                                                  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                  uint32 dataLength
   ,                                                  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) signaturePtr
   ,                                                  uint32 signatureLength
   ,                                                  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr);

FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate(uint32 jobId
   ,                                                 P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                 P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr);

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeySetValid( uint32 jobId, uint32 keyId );
FUNC( Std_ReturnType, CSM_CODE ) Csm_JobRandomSeed( uint32 jobId, uint32 keyId, P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) seedPtr, uint32 seedLength );
FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyGenerate( uint32 jobId, uint32 keyId );
FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyDerive( uint32 jobId, uint32 keyId, uint32 targetKeyId );

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyExchangeCalcPubVal( uint32 jobId
   ,                                                              uint32 keyId
   ,                                                              P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) publicValuePtr
   ,                                                              P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) publicValueLengthPtr );

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyExchangeCalcSecret(  uint32 jobId
   ,                                                               uint32 keyId
   ,                                                               P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr
   ,                                                               uint32 partnerPublicValueLength );

FUNC(Std_ReturnType, CSM_CODE) Csm_SaveContextJob(  uint32 jobId
   ,                                                   P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,                                                   P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) contextBufferLengthPtr );

FUNC(Std_ReturnType, CSM_CODE) Csm_RestoreContextJob(  uint32 jobId
   ,                                                      P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,                                                      uint32 contextBufferLength );

#define CSM_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
#endif

