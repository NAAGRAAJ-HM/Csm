

#if !defined (CSM_TYPES_H)
#define CSM_TYPES_H

#include "Std_Types.hpp"
#include "Types_CfgSwcServiceCsm.hpp"

#ifndef CRYPTO_E_BUSY
#define CRYPTO_E_BUSY                                               2u
#endif

#ifndef CRYPTO_E_SMALL_BUFFER
#define CRYPTO_E_SMALL_BUFFER                                       3u
#endif

#ifndef CRYPTO_E_ENTROPY_EXHAUSTED
#define CRYPTO_E_ENTROPY_EXHAUSTED                                  4u
#endif

#ifndef CRYPTO_E_ENTROPY_EXHAUSTION
#define CRYPTO_E_ENTROPY_EXHAUSTION                                 CRYPTO_E_ENTROPY_EXHAUSTED
#endif

#ifndef CRYPTO_E_QUEUE_FULL
#define CRYPTO_E_QUEUE_FULL                                         5u
#endif

#ifndef CRYPTO_E_KEY_READ_FAIL
#define CRYPTO_E_KEY_READ_FAIL                                      6u
#endif

#ifndef CRYPTO_E_KEY_WRITE_FAIL
#define CRYPTO_E_KEY_WRITE_FAIL                                     7u
#endif

#ifndef CRYPTO_E_KEY_NOT_AVAILABLE
#define CRYPTO_E_KEY_NOT_AVAILABLE                                  8u
#endif

#ifndef CRYPTO_E_KEY_NOT_VALID
#define CRYPTO_E_KEY_NOT_VALID                                      9u
#endif

#ifndef CRYPTO_E_KEY_SIZE_MISMATCH
#define CRYPTO_E_KEY_SIZE_MISMATCH                                  10u
#endif

#ifndef CRYPTO_E_COUNTER_OVERFLOW
#define CRYPTO_E_COUNTER_OVERFLOW                                   11u
#endif

#ifndef CRYPTO_E_JOB_CANCELED
#define CRYPTO_E_JOB_CANCELED                                       12u
#endif

#ifndef CRYPTO_E_KEY_EMPTY
#define CRYPTO_E_KEY_EMPTY                                          13u
#endif

#if(CSM_JOB_TYPE_LAYOUT_VAR_MEMBERS == STD_ON)
#define CSM_DEPENDENT_CONST(type)                                   VAR(type, AUTOMATIC)
#else
#define CSM_DEPENDENT_CONST(type)                                   CONST(type, AUTOMATIC)
#endif

#ifndef CSM_E_PENDING
#ifdef E_PENDING
#define CSM_E_PENDING                                              E_PENDING
#else
#define CSM_E_PENDING                                              2u
#endif
#endif

#ifndef CRYPTO_KE_MAC_KEY
#define CRYPTO_KE_MAC_KEY                                           1u
#endif

#ifndef CRYPTO_KE_MAC_PROOF
#define CRYPTO_KE_MAC_PROOF                                         2u
#endif

#ifndef CRYPTO_KE_SIGNATURE_KEY
#define CRYPTO_KE_SIGNATURE_KEY                                     1u
#endif

#ifndef CRYPTO_KE_SIGNATURE_CURVETYPE
#define CRYPTO_KE_SIGNATURE_CURVETYPE                               29u
#endif

#ifndef CRYPTO_KE_RANDOM_SEED_STATE
#define CRYPTO_KE_RANDOM_SEED_STATE                                 3u
#endif

#ifndef CRYPTO_KE_RANDOM_ALGORITHM
#define CRYPTO_KE_RANDOM_ALGORITHM                                  4u
#endif

#ifndef CRYPTO_KE_CIPHER_KEY
#define CRYPTO_KE_CIPHER_KEY                                        1u
#endif

#ifndef CRYPTO_KE_CIPHER_IV
#define CRYPTO_KE_CIPHER_IV                                         5u
#endif

#ifndef CRYPTO_KE_CIPHER_PROOF
#define CRYPTO_KE_CIPHER_PROOF                                      6u
#endif

#ifndef CRYPTO_KE_CIPHER_2NDKEY
#define CRYPTO_KE_CIPHER_2NDKEY                                     7u
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_BASE
#define CRYPTO_KE_KEYEXCHANGE_BASE                                  8u
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_PRIVKEY
#define CRYPTO_KE_KEYEXCHANGE_PRIVKEY                               9u
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY
#define CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY                             10u
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE
#define CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE                           1u
#endif

#ifndef CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE

#define CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE                           1u
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_ALGORITHM

#define CRYPTO_KE_KEYEXCHANGE_ALGORITHM                             12u
#endif

#ifndef CRYPTO_KE_KEYEXCHANGE_CURVETYPE
#define CRYPTO_KE_KEYEXCHANGE_CURVETYPE                             29u
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_PASSWORD
#define CRYPTO_KE_KEYDERIVATION_PASSWORD                            1u
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_SALT
#define CRYPTO_KE_KEYDERIVATION_SALT                                13u
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_ITERATIONS
#define CRYPTO_KE_KEYDERIVATION_ITERATIONS                          14u
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_ALGORITHM

#define CRYPTO_KE_KEYDERIVATION_ALGORITHM                           15u
#endif

#ifndef CRYPTO_KE_KEYDERIVATION_CURVETYPE
#define CRYPTO_KE_KEYDERIVATION_CURVETYPE                           29u
#endif

#ifndef CRYPTO_KE_KEYGENERATE_KEY
#define CRYPTO_KE_KEYGENERATE_KEY                                   1u
#endif

#ifndef CRYPTO_KE_KEYGENERATE_SEED
#define CRYPTO_KE_KEYGENERATE_SEED                                  16u
#endif

#ifndef CRYPTO_KE_KEYGENERATE_ALGORITHM
#define CRYPTO_KE_KEYGENERATE_ALGORITHM                             17u
#endif

#ifndef CRYPTO_KE_KEYGENERATE_CURVETYPE
#define CRYPTO_KE_KEYGENERATE_CURVETYPE                             29u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_DATA
#define CRYPTO_KE_CERTIFICATE_DATA                                  0u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_PARSING_FORMAT

#define CRYPTO_KE_CERTIFICATE_PARSING_FORMAT                        18u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_CURRENT_TIME
#define CRYPTO_KE_CERTIFICATE_CURRENT_TIME                          19u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_VERSION
#define CRYPTO_KE_CERTIFICATE_VERSION                               20u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SERIALNUMBER
#define CRYPTO_KE_CERTIFICATE_SERIALNUMBER                          21u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SIGNATURE_ALGORITHM
#define CRYPTO_KE_CERTIFICATE_SIGNATURE_ALGORITHM                   22u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_ISSUER
#define CRYPTO_KE_CERTIFICATE_ISSUER                                23u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_BEFORE
#define CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_BEFORE                   24u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_AFTER
#define CRYPTO_KE_CERTIFICATE_VALIDITY_NOT_AFTER                    25u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SUBJECT
#define CRYPTO_KE_CERTIFICATE_SUBJECT                               26u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SUBJECT_PUBLIC_KEY
#define CRYPTO_KE_CERTIFICATE_SUBJECT_PUBLIC_KEY                    1u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_EXTENSIONS
#define CRYPTO_KE_CERTIFICATE_EXTENSIONS                            27u
#endif

#ifndef CRYPTO_KE_CERTIFICATE_SIGNATURE
#define CRYPTO_KE_CERTIFICATE_SIGNATURE                             28u
#endif

typedef uint8 Crypto_JobStateType;
#define CRYPTO_JOBSTATE_IDLE                                         0u
#define CRYPTO_JOBSTATE_ACTIVE                                       1u
#define CRYPTO_JOBSTATE_PROGRESSING                                  2u

typedef uint8 Crypto_ServiceInfoType;
#ifndef CRYPTO_HASH
#define CRYPTO_HASH                                                 0x00u
#endif
#ifndef CRYPTO_MACGENERATE
#define CRYPTO_MACGENERATE                                          0x01u
#endif
#ifndef CRYPTO_MACVERIFY
#define CRYPTO_MACVERIFY                                            0x02u
#endif
#ifndef CRYPTO_ENCRYPT
#define CRYPTO_ENCRYPT                                              0x03u
#endif
#ifndef CRYPTO_DECRYPT
#define CRYPTO_DECRYPT                                              0x04u
#endif
#ifndef CRYPTO_AEADENCRYPT
#define CRYPTO_AEADENCRYPT                                          0x05u
#endif
#ifndef CRYPTO_AEADDECRYPT
#define CRYPTO_AEADDECRYPT                                          0x06u
#endif
#ifndef CRYPTO_SIGNATUREGENERATE
#define CRYPTO_SIGNATUREGENERATE                                    0x07u
#endif
#ifndef CRYPTO_SIGNATUREVERIFY
#define CRYPTO_SIGNATUREVERIFY                                      0x08u
#endif
#ifndef CRYPTO_SECCOUNTERINCREMENT
#define CRYPTO_SECCOUNTERINCREMENT                                  0x09u
#endif
#ifndef CRYPTO_SECCOUNTERREAD
#define CRYPTO_SECCOUNTERREAD                                       0x0Au
#endif
#ifndef CRYPTO_RANDOMGENERATE
#define CRYPTO_RANDOMGENERATE                                       0x0Bu
#endif
#ifndef CRYPTO_RANDOMSEED
#define CRYPTO_RANDOMSEED                                           0x0Cu
#endif
#ifndef CRYPTO_KEYGENERATE
#define CRYPTO_KEYGENERATE                                          0x0Du
#endif
#ifndef CRYPTO_KEYDERIVE
#define CRYPTO_KEYDERIVE                                            0x0Eu
#endif
#ifndef CRYPTO_KEYEXCHANGECALCPUBVAL
#define CRYPTO_KEYEXCHANGECALCPUBVAL                                0x0Fu
#endif
#ifndef CRYPTO_KEYEXCHANGECALCSECRET
#define CRYPTO_KEYEXCHANGECALCSECRET                                0x10u
#endif
#ifndef CRYPTO_CERTIFICATEPARSE
#define CRYPTO_CERTIFICATEPARSE                                     0x11u
#endif
#ifndef CRYPTO_CERTIFICATEVERIFY
#define CRYPTO_CERTIFICATEVERIFY                                    0x12u
#endif
#ifndef CRYPTO_KEYSETVALID
#define CRYPTO_KEYSETVALID                                          0x13u
#endif
#ifndef CRYPTO_KEYSETINVALID
#define CRYPTO_KEYSETINVALID                                        0x14u
#endif

#ifndef CRYPTO_RANDOM
#define CRYPTO_RANDOM                                               CRYPTO_RANDOMGENERATE
#endif
#ifndef CRYPTO_SECURECOUNTERREAD
#define CRYPTO_SECURECOUNTERREAD                                    CRYPTO_SECCOUNTERREAD
#endif
#ifndef CRYPTO_SECURECOUNTERINCREMENT
#define CRYPTO_SECURECOUNTERINCREMENT                               CRYPTO_SECCOUNTERINCREMENT
#endif

typedef uint8 Crypto_AlgorithmFamilyType;
typedef uint8 Crypto_AlgorithmSecondaryFamilyType;
#ifndef CRYPTO_ALGOFAM_NOT_SET
#define CRYPTO_ALGOFAM_NOT_SET                                      0x00u
#endif
#ifndef CRYPTO_ALGOFAM_SHA1
#define CRYPTO_ALGOFAM_SHA1                                         0x01u
#endif
#ifndef CRYPTO_ALGOFAM_SHA2_224
#define CRYPTO_ALGOFAM_SHA2_224                                     0x02u
#endif
#ifndef CRYPTO_ALGOFAM_SHA2_256
#define CRYPTO_ALGOFAM_SHA2_256                                     0x03u
#endif
#ifndef CRYPTO_ALGOFAM_SHA2_384
#define CRYPTO_ALGOFAM_SHA2_384                                     0x04u
#endif
#ifndef CRYPTO_ALGOFAM_SHA2_512
#define CRYPTO_ALGOFAM_SHA2_512                                     0x05u
#endif
#ifndef CRYPTO_ALGOFAM_SHA2_512_224
#define CRYPTO_ALGOFAM_SHA2_512_224                                 0x06u
#endif
#ifndef CRYPTO_ALGOFAM_SHA2_512_256
#define CRYPTO_ALGOFAM_SHA2_512_256                                 0x07u
#endif
#ifndef CRYPTO_ALGOFAM_SHA3_224
#define CRYPTO_ALGOFAM_SHA3_224                                     0x08u
#endif
#ifndef CRYPTO_ALGOFAM_SHA3_256
#define CRYPTO_ALGOFAM_SHA3_256                                     0x09u
#endif
#ifndef CRYPTO_ALGOFAM_SHA3_384
#define CRYPTO_ALGOFAM_SHA3_384                                     0x0Au
#endif
#ifndef CRYPTO_ALGOFAM_SHA3_512
#define CRYPTO_ALGOFAM_SHA3_512                                     0x0Bu
#endif
#ifndef CRYPTO_ALGOFAM_SHAKE128
#define CRYPTO_ALGOFAM_SHAKE128                                     0x0Cu
#endif
#ifndef CRYPTO_ALGOFAM_SHAKE256
#define CRYPTO_ALGOFAM_SHAKE256                                     0x0Du
#endif
#ifndef CRYPTO_ALGOFAM_RIPEMD160
#define CRYPTO_ALGOFAM_RIPEMD160                                    0x0Eu
#endif
#ifndef CRYPTO_ALGOFAM_BLAKE_1_256
#define CRYPTO_ALGOFAM_BLAKE_1_256                                  0x0Fu
#endif
#ifndef CRYPTO_ALGOFAM_BLAKE_1_512
#define CRYPTO_ALGOFAM_BLAKE_1_512                                  0x10u
#endif
#ifndef CRYPTO_ALGOFAM_BLAKE_2s_256
#define CRYPTO_ALGOFAM_BLAKE_2s_256                                 0x11u
#endif
#ifndef CRYPTO_ALGOFAM_BLAKE_2s_512
#define CRYPTO_ALGOFAM_BLAKE_2s_512                                 0x12u
#endif
#ifndef CRYPTO_ALGOFAM_3DES
#define CRYPTO_ALGOFAM_3DES                                         0x13u
#endif
#ifndef CRYPTO_ALGOFAM_AES
#define CRYPTO_ALGOFAM_AES                                          0x14u
#endif
#ifndef CRYPTO_ALGOFAM_CHACHA
#define CRYPTO_ALGOFAM_CHACHA                                       0x15u
#endif
#ifndef CRYPTO_ALGOFAM_RSA
#define CRYPTO_ALGOFAM_RSA                                          0x16u
#endif
#ifndef CRYPTO_ALGOFAM_ED25519
#define CRYPTO_ALGOFAM_ED25519                                      0x17u
#endif
#ifndef CRYPTO_ALGOFAM_BRAINPOOL
#define CRYPTO_ALGOFAM_BRAINPOOL                                    0x18u
#endif
#ifndef CRYPTO_ALGOFAM_ECCNIST
#define CRYPTO_ALGOFAM_ECCNIST                                      0x19u
#endif
#ifndef CRYPTO_ALGOFAM_SECURECOUNTER
#define CRYPTO_ALGOFAM_SECURECOUNTER                                0x1Au
#endif
#ifndef CRYPTO_ALGOFAM_RNG
#define CRYPTO_ALGOFAM_RNG                                          0x1Bu
#endif
#ifndef CRYPTO_ALGOFAM_SIPHASH
#define CRYPTO_ALGOFAM_SIPHASH                                      0x1Cu
#endif
#ifndef CRYPTO_ALGOFAM_ECIES
#define CRYPTO_ALGOFAM_ECIES                                        0x1Du
#endif
#ifndef CRYPTO_ALGOFAM_ECCANSI
#define CRYPTO_ALGOFAM_ECCANSI                                      0x1Eu
#endif
#ifndef CRYPTO_ALGOFAM_ECCSEC
#define CRYPTO_ALGOFAM_ECCSEC                                       0x1Fu
#endif
#ifndef CRYPTO_ALGOFAM_DRBG
#define CRYPTO_ALGOFAM_DRBG                                         0x20u
#endif
#ifndef CRYPTO_ALGOFAM_FIPS186
#define CRYPTO_ALGOFAM_FIPS186                                      0x21u
#endif
#ifndef CRYPTO_ALGOFAM_PADDING_PKCS7
#define CRYPTO_ALGOFAM_PADDING_PKCS7                                0x22u
#endif
#ifndef CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS
#define CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS                         0x23u
#endif
#ifndef CRYPTO_ALGOFAM_PBKDF2
#define CRYPTO_ALGOFAM_PBKDF2                                       0x24u
#endif
#ifndef CRYPTO_ALGOFAM_KDFX963
#define CRYPTO_ALGOFAM_KDFX963                                      0x25u
#endif
#ifndef CRYPTO_ALGOFAM_DH
#define CRYPTO_ALGOFAM_DH                                           0x26u
#endif
#ifndef CRYPTO_ALGOFAM_SM2
#define CRYPTO_ALGOFAM_SM2                                          0x27u
#endif
#ifndef CRYPTO_ALGOFAM_EEA3
#define CRYPTO_ALGOFAM_EEA3                                         0x28u
#endif
#ifndef CRYPTO_ALGOFAM_SM3
#define CRYPTO_ALGOFAM_SM3                                          0x29u
#endif
#ifndef CRYPTO_ALGOFAM_EIA3
#define CRYPTO_ALGOFAM_EIA3                                         0x2Au
#endif
#ifndef CRYPTO_ALGOFAM_HKDF
#define CRYPTO_ALGOFAM_HKDF                                         0x2Bu
#endif
#ifndef CRYPTO_ALGOFAM_ECDSA
#define CRYPTO_ALGOFAM_ECDSA                                        0x2Cu
#endif
#ifndef CRYPTO_ALGOFAM_POLY13
#define CRYPTO_ALGOFAM_POLY13                                       0x2Du
#endif
#ifndef CRYPTO_ALGOFAM_X25519
#define CRYPTO_ALGOFAM_X25519                                       0x2Eu
#endif
#ifndef CRYPTO_ALGOFAM_ECDH
#define CRYPTO_ALGOFAM_ECDH                                         0x2Fu
#endif
#ifndef CRYPTO_ALGOFAM_CUSTOM
#define CRYPTO_ALGOFAM_CUSTOM                                       0xFFu
#endif

#ifndef CRYPTO_ALGOFAM_FIPS
#define CRYPTO_ALGOFAM_FIPS                                         CRYPTO_ALGOFAM_FIPS186
#endif

#ifndef CRYPTO_ALGOFAM_SHA3_SHAKE128
#define CRYPTO_ALGOFAM_SHA3_SHAKE128                                CRYPTO_ALGOFAM_SHAKE128
#endif
#ifndef CRYPTO_ALGOFAM_SHA3_SHAKE256
#define CRYPTO_ALGOFAM_SHA3_SHAKE256                                CRYPTO_ALGOFAM_SHAKE256
#endif

typedef uint8 Crypto_AlgorithmModeType;
#ifndef CRYPTO_ALGOMODE_NOT_SET
#define CRYPTO_ALGOMODE_NOT_SET                                     0x00u
#endif
#ifndef CRYPTO_ALGOMODE_ECB
#define CRYPTO_ALGOMODE_ECB                                         0x01u
#endif
#ifndef CRYPTO_ALGOMODE_CBC
#define CRYPTO_ALGOMODE_CBC                                         0x02u
#endif
#ifndef CRYPTO_ALGOMODE_CFB
#define CRYPTO_ALGOMODE_CFB                                         0x03u
#endif
#ifndef CRYPTO_ALGOMODE_OFB
#define CRYPTO_ALGOMODE_OFB                                         0x04u
#endif
#ifndef CRYPTO_ALGOMODE_CTR
#define CRYPTO_ALGOMODE_CTR                                         0x05u
#endif
#ifndef CRYPTO_ALGOMODE_XTS
#define CRYPTO_ALGOMODE_XTS                                         0x06u
#endif
#ifndef CRYPTO_ALGOMODE_GCM
#define CRYPTO_ALGOMODE_GCM                                         0x07u
#endif
#ifndef CRYPTO_ALGOMODE_RSAES_OAEP
#define CRYPTO_ALGOMODE_RSAES_OAEP                                  0x08u
#endif
#ifndef CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5
#define CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5                            0x09u
#endif
#ifndef CRYPTO_ALGOMODE_RSASSA_PSS
#define CRYPTO_ALGOMODE_RSASSA_PSS                                  0x0Au
#endif
#ifndef CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5
#define CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5                           0x0Bu
#endif
#ifndef CRYPTO_ALGOMODE_8ROUNDS
#define CRYPTO_ALGOMODE_8ROUNDS                                     0x0Cu
#endif
#ifndef CRYPTO_ALGOMODE_12ROUNDS
#define CRYPTO_ALGOMODE_12ROUNDS                                    0x0Du
#endif
#ifndef CRYPTO_ALGOMODE_20ROUNDS
#define CRYPTO_ALGOMODE_20ROUNDS                                    0x0Eu
#endif
#ifndef CRYPTO_ALGOMODE_HMAC
#define CRYPTO_ALGOMODE_HMAC                                        0x0Fu
#endif
#ifndef CRYPTO_ALGOMODE_CMAC
#define CRYPTO_ALGOMODE_CMAC                                        0x10u
#endif
#ifndef CRYPTO_ALGOMODE_GMAC
#define CRYPTO_ALGOMODE_GMAC                                        0x11u
#endif
#ifndef CRYPTO_ALGOMODE_CTRDRBG
#define CRYPTO_ALGOMODE_CTRDRBG                                     0x12u
#endif
#ifndef CRYPTO_ALGOMODE_SIPHASH_2_4
#define CRYPTO_ALGOMODE_SIPHASH_2_4                                 0x13u
#endif
#ifndef CRYPTO_ALGOMODE_SIPHASH_4_8
#define CRYPTO_ALGOMODE_SIPHASH_4_8                                 0x14u
#endif
#ifndef CRYPTO_ALGOMODE_PXXXR1
#define CRYPTO_ALGOMODE_PXXXR1                                      0x15u
#endif
#ifndef CRYPTO_ALGOMODE_CUSTOM
#define CRYPTO_ALGOMODE_CUSTOM                                      0xFFu
#endif

typedef uint8 Crypto_InputOutputRedirectionConfigType;
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT                         0x01u
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT                       0x02u
#define CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT                        0x04u
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT                        0x10u
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT                      0x20u

typedef struct{
  Crypto_AlgorithmFamilyType family;
  uint32 keyLength;
  Crypto_AlgorithmModeType mode;
  Crypto_AlgorithmSecondaryFamilyType secondaryFamily;
}Crypto_AlgorithmInfoType;

#ifndef Rte_TypeDef_Crypto_OperationModeType
typedef uint8 Crypto_OperationModeType;
#endif

#ifndef CRYPTO_OPERATIONMODE_START
#define CRYPTO_OPERATIONMODE_START                                  1u
#endif
#ifndef CRYPTO_OPERATIONMODE_UPDATE
#define CRYPTO_OPERATIONMODE_UPDATE                                 2u
#endif
#ifndef CRYPTO_OPERATIONMODE_FINISH
#define CRYPTO_OPERATIONMODE_FINISH                                 4u
#endif

#ifndef CRYPTO_OPERATIONMODE_STREAMSTART
#define CRYPTO_OPERATIONMODE_STREAMSTART                            ( CRYPTO_OPERATIONMODE_START | CRYPTO_OPERATIONMODE_UPDATE )
#endif
#ifndef CRYPTO_OPERATIONMODE_SINGLECALL
#define CRYPTO_OPERATIONMODE_SINGLECALL                             ( CRYPTO_OPERATIONMODE_START | CRYPTO_OPERATIONMODE_UPDATE | CRYPTO_OPERATIONMODE_FINISH )
#endif

#ifndef CRYPTO_OPERATIONMODE_SAVE_CONTEXT
#define CRYPTO_OPERATIONMODE_SAVE_CONTEXT                           8u
#endif

#ifndef CRYPTO_OPERATIONMODE_RESTORE_CONTEXT
#define CRYPTO_OPERATIONMODE_RESTORE_CONTEXT                        16u
#endif

typedef uint8 Crypto_ProcessingType;
#define CRYPTO_PROCESSING_ASYNC                                      0u
#define CRYPTO_PROCESSING_SYNC                                       1u

#define CSM_ASYNCHRONOUS                                             CRYPTO_PROCESSING_ASYNC
#define CSM_SYNCHRONOUS                                              CRYPTO_PROCESSING_SYNC

#ifndef Rte_TypeDef_Crypto_VerifyResultType
typedef uint8 Crypto_VerifyResultType;
#endif

#ifndef Rte_TypeDef_Crypto_ResultType
typedef uint8 Crypto_ResultType;
#endif

#ifndef Rte_TypeDef_Csm_ResultType
typedef uint8 Csm_ResultType;
#endif

#ifndef CRYPTO_E_VER_OK
#define CRYPTO_E_VER_OK                                             0u
#endif
#ifndef CRYPTO_E_VER_NOT_OK
#define CRYPTO_E_VER_NOT_OK                                         1u
#endif

#ifndef CSM_E_VER_OK
#define CSM_E_VER_OK                                                CRYPTO_E_VER_OK
#endif
#ifndef CSM_E_VER_NOT_OK
#define CSM_E_VER_NOT_OK                                            CRYPTO_E_VER_NOT_OK
#endif

typedef struct{
  CSM_DEPENDENT_CONST(uint32) resultLength;
  CSM_DEPENDENT_CONST(Crypto_ServiceInfoType) service;
  CSM_DEPENDENT_CONST(Crypto_AlgorithmInfoType) algorithm;
}Crypto_PrimitiveInfoType;

typedef struct{
  CSM_DEPENDENT_CONST(uint32) callbackId;
  P2CONST(Crypto_PrimitiveInfoType, AUTOMATIC, CSM_CONST) primitiveInfo;
  CSM_DEPENDENT_CONST(uint32) secureCounterId;
  CSM_DEPENDENT_CONST(uint32) cryIfKeyId;
  CSM_DEPENDENT_CONST(Crypto_ProcessingType) processingType;
  CSM_DEPENDENT_CONST(boolean) callbackUpdateNotification;
}Crypto_JobPrimitiveInfoType;

typedef struct{
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) inputPtr;
  uint32 inputLength;
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) secondaryInputPtr;
  uint32 secondaryInputLength;
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) tertiaryInputPtr;
  uint32 tertiaryInputLength;

  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) outputPtr;
  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) outputLengthPtr;
  P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) secondaryOutputPtr;
  P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) secondaryOutputLengthPtr;

#if(CSM_JOB_TYPE_LAYOUT_INPUT64 == STD_ON)
  uint64 input64;
#endif
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr;
#if(CSM_JOB_TYPE_LAYOUT_OUTPUT64_PTR == STD_ON)
  P2VAR(uint64, AUTOMATIC, CSM_APPL_VAR) output64Ptr;
#endif
  Crypto_OperationModeType mode;

  uint32 cryIfKeyId;
  uint32 targetCryIfKeyId;
}Crypto_JobPrimitiveInputOutputType;

typedef struct{
  CSM_DEPENDENT_CONST(uint32) jobId;
  CSM_DEPENDENT_CONST(uint32) jobPriority;
}Crypto_JobInfoType;

typedef struct{
  Crypto_InputOutputRedirectionConfigType redirectionConfig;
  uint32 inputKeyId;
  uint32 inputKeyElementId;
  uint32 secondaryInputKeyId;
  uint32 secondaryInputKeyElementId;
  uint32 tertiaryInputKeyId;
  uint32 tertiaryInputKeyElementId;
  uint32 outputKeyId;
  uint32 outputKeyElementId;
  uint32 secondaryOutputKeyId;
  uint32 secondaryOutputKeyElementId;
}Crypto_JobRedirectionInfoType;

typedef struct{
  uint32 jobId;
  Crypto_JobStateType jobState;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput;
  P2CONST(Crypto_JobPrimitiveInfoType, AUTOMATIC, CSM_CONST) jobPrimitiveInfo;
  P2CONST(Crypto_JobInfoType, AUTOMATIC, CSM_CONST) jobInfo;
  uint32 cryptoKeyId;

#if(CSM_JOB_TYPE_LAYOUT_REDIRECTION_INFO_REF == STD_ON)
  P2VAR(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_VAR_NOINIT) jobRedirectionInfoRef;
#endif
  uint32 targetCryptoKeyId;
#if(CSM_JOB_TYPE_LAYOUT_ASR430_COMPATIBILITY == STD_ON)

  Crypto_JobStateType state;
  Crypto_JobPrimitiveInputOutputType PrimitiveInputOutput;
#endif
}Crypto_JobType;

#endif

