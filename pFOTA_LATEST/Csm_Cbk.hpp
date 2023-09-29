

#if !defined (CSM_CBK_H)
#define CSM_CBK_H

#include "Types_SwcServiceCsm.hpp"

#define CSM_START_SEC_CODE
#include "MemMap.hpp"

FUNC(void, CSM_CODE) Csm_CallbackNotification(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job
   ,                                             Std_ReturnType result);

#define CSM_STOP_SEC_CODE
#include "MemMap.hpp"

#endif

