#define CSM_SOURCE
#ifdef __cplusplus
extern "C"
{
#endif

#include "SwcServiceCsm.hpp"
#include "Csm_Cbk.hpp"
#include "EcuabCryIf.hpp"
#include "SchM_Csm.hpp"

#if(CSM_DEV_ERROR_REPORT == STD_ON)
#include "SwcServiceDet.hpp"
#endif

#if((CSM_SW_MAJOR_VERSION != (6u)) \
    || (CSM_SW_MINOR_VERSION != (3u)) \
    || (CSM_SW_PATCH_VERSION != (0u)))
# error "Vendor specific version numbers of Csm.c and Csm.h are inconsistent"
#endif

#if((CSM_AR_RELEASE_MAJOR_VERSION != (4u)) \
    || (CSM_AR_RELEASE_MINOR_VERSION != (4u)) \
    || (CSM_AR_RELEASE_REVISION_VERSION != (0u)))
# error "AUTOSAR Specification Version numbers of Csm.c and Csm.h are inconsistent!"
#endif

#define CSM_CALLBACK_IDLE                                             (0xFEu)

#define CSM_EMPTY_JOB                                                 (0xFFFFFFFFuL)

#define CSM_JOB_STATE_IDLE                                            CRYPTO_JOBSTATE_IDLE

#define CSM_JOB_STATE_ACTIVE                                          CRYPTO_JOBSTATE_ACTIVE

#define CSM_JOB_STATE_PROGRESSING                                     CRYPTO_JOBSTATE_PROGRESSING

#define CSM_JOB_STATE_WAITING                                         3u

#define CSM_JOB_STATE_QUEUED                                          4u

#define CSM_JOB_STATE_CANCELING                                       5u

#define CSM_JOB_STATE_CANCELED                                        6u

#define CSM_JOB_STATE_CALLBACK_OCCURRED                               64u

#define CSM_JOB_STATE_CALLBACK_OCCURRED_CLEAR_MASK                    191u

#define CSM_ASYNC_JOB_RETRIGGER_STATE_IDLE                            (0x00u)
#define CSM_ASYNC_JOB_RETRIGGER_STATE_PENDING                         (0x01u)

#if !defined (CSM_LOCAL)
#define CSM_LOCAL                                                    static
#endif

#if !defined (CSM_LOCAL_INLINE)
#define CSM_LOCAL_INLINE                                             LOCAL_INLINE
#endif

#define CSM_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.hpp"

#if(CSM_DEV_ERROR_DETECT == STD_ON)

CSM_LOCAL VAR(uint8, CSM_VAR_ZERO_INIT) Csm_IsInitialized = CSM_UNINIT;
#endif

#define CSM_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.hpp"

#define CSM_START_SEC_CODE
#include "MemMap.hpp"

#if(CSM_JOB == STD_ON)

CSM_LOCAL FUNC(Std_ReturnType, CSM_CODE) Csm_ProcessJob(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job);

CSM_LOCAL FUNC(Std_ReturnType, CSM_CODE) Csm_GetJobObj(uint32 jobId, P2VAR(Csm_SizeOfJobType, AUTOMATIC, AUTOMATIC) jobObjId);

#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_PrepareJobObj(uint32 jobId, P2VAR(Crypto_JobType, AUTOMATIC, AUTOMATIC) job);
#endif

#if(CSM_ASYNC_PROCESSING == STD_ON)

CSM_LOCAL_INLINE FUNC(Std_ReturnType, CSM_CODE) Csm_EnqueueJob(Csm_QueueInfoIterType queueIdx, P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job);

CSM_LOCAL FUNC(void, CSM_CODE) Csm_DequeueJob(Csm_QueueInfoIterType queueIdx, uint32 jobId);

CSM_LOCAL FUNC(void, CSM_CODE) Csm_TriggerAsynchJobProcessing(Csm_QueueInfoIterType queueIdx);

CSM_LOCAL_INLINE FUNC(Std_ReturnType, CSM_CODE) Csm_CancelAsynchronousJob(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job);

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_HandleApplicationCallback(
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job
   ,  Std_ReturnType result
   ,  P2VAR(uint8, AUTOMATIC, AUTOMATIC) errorId);

#if(CSM_RTECALLBACK == STD_ON)

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_HandleRteCallbacks(void);
#endif

#endif

CSM_LOCAL FUNC(Std_ReturnType, CSM_CODE) Csm_HandleJobProcessing(Csm_ChannelIdOfQueueInfoType channelId, P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job);

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_AppendRedirectionToJob(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job);
#endif

#if(CSM_CALLOUT == STD_ON)

CSM_LOCAL_INLINE FUNC(Std_ReturnType, CSM_CODE) Csm_CallPreJobCallout(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job);

CSM_LOCAL FUNC(void, CSM_CODE) Csm_CallPostJobCallout(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job, P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) retValFromProcessing);
#endif

#if(CSM_CALLOUT == STD_ON)

CSM_LOCAL FUNC(void, CSM_CODE) Csm_CallPostJobCallout(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job, P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) retValFromProcessing){
  Csm_CalloutInfoIdxOfJobTableType calloutInfoId;

  calloutInfoId = Csm_GetCalloutInfoIdxOfJobTable(job->jobId);

  if(calloutInfoId < Csm_GetSizeOfCalloutInfo()){
    (void)Csm_GetPostJobCalloutFuncOfCallout(Csm_GetCalloutIdxOfCalloutInfo(calloutInfoId))(
      job
   ,     CSM_CALLOUT_STATE_POST_INITIAL
   ,     retValFromProcessing);

    Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_IDLE);
  }
}

CSM_LOCAL_INLINE FUNC(Std_ReturnType, CSM_CODE) Csm_CallPreJobCallout(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job){
  Csm_CalloutInfoIdxOfJobTableType calloutInfoId;
  Std_ReturnType retVal = E_OK;

  calloutInfoId = Csm_GetCalloutInfoIdxOfJobTable(job->jobId);

  if(calloutInfoId < Csm_GetSizeOfCalloutInfo()){
#if(CSM_ASYNC_PROCESSING == STD_ON)
    uint8 calloutState = Csm_GetCalloutStateOfCalloutState(calloutInfoId);

    if( job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC){
      if((calloutState == CSM_CALLOUT_STATE_IDLE) || (calloutState == CSM_CALLOUT_STATE_PRE_PENDING))
      {
        retVal = Csm_GetPreJobCalloutFuncOfCallout(Csm_GetCalloutIdxOfCalloutInfo(calloutInfoId))(
          job
   ,         (calloutState == CSM_CALLOUT_STATE_IDLE) ? (CSM_CALLOUT_STATE_PRE_INITIAL) : (CSM_CALLOUT_STATE_PRE_PENDING));

        switch(retVal)
        {
          case E_OK:
          {
            Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_PROCESSING);
            break;
          }

          case CSM_E_PENDING:
          {
            Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_PRE_PENDING);
            break;
          }

          default:
          {
            Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_PROCESSING_ABORTED_BY_CALLOUT);

            retVal = E_OK;
            break;
          }
        }
      }
    }
    else
#endif
    {
      retVal = Csm_GetPreJobCalloutFuncOfCallout(Csm_GetCalloutIdxOfCalloutInfo(calloutInfoId))(job, CSM_CALLOUT_STATE_PRE_INITIAL);

      if(retVal == E_OK)
      {
        Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_PROCESSING);
      }
      else
      {
        Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_POST_INITIAL);

        Csm_CallPostJobCallout(job, &retVal);
      }
    }
  }
  return retVal;
}
#endif

#if(CSM_JOB == STD_ON)

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_AppendRedirectionToJob(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job){
#if(CSM_INOUTREDIRECTION == STD_ON)
  uint32 jobId = job->jobId;

  if(Csm_IsInOutRedirectionMapUsedOfJobTable(jobId)){
    Csm_SizeOfInOutJobRedirectionTableType indexOfInOutRedirectionTable = Csm_GetInOutJobRedirectionTableIdxOfInOutRedirectionMap(Csm_GetInOutRedirectionMapIdxOfJobTable(jobId));
    Csm_RedirectionConfigValueOfInOutJobRedirectionTableType redirectionConfigValue = Csm_GetRedirectionConfigValueOfInOutJobRedirectionTable(indexOfInOutRedirectionTable);

    job->jobRedirectionInfoRef = Csm_GetAddrInOutRedirection(Csm_GetInOutRedirectionMapIdxOfJobTable(jobId));
    job->jobRedirectionInfoRef->redirectionConfig = redirectionConfigValue;

    if((redirectionConfigValue & ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT)) == (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT){
      job->jobRedirectionInfoRef->inputKeyElementId = Csm_GetInputKeyElementIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable);
      job->jobRedirectionInfoRef->inputKeyId = Csm_GetCryIfKeyIdOfKey(Csm_GetInputKeyIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable));
    }

    if((redirectionConfigValue & ((uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT)) == (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT){
      job->jobRedirectionInfoRef->secondaryInputKeyElementId = Csm_GetSecondaryInputKeyElementIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable);
      job->jobRedirectionInfoRef->secondaryInputKeyId = Csm_GetCryIfKeyIdOfKey(Csm_GetSecondaryInputKeyIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable));
    }

    if((redirectionConfigValue & ((uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT)) == (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT){
      job->jobRedirectionInfoRef->tertiaryInputKeyElementId = Csm_GetTertiaryInputKeyElementIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable);
      job->jobRedirectionInfoRef->tertiaryInputKeyId = Csm_GetCryIfKeyIdOfKey(Csm_GetTertiaryInputKeyIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable));
    }

    if((redirectionConfigValue & ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT)) == (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT){
      job->jobRedirectionInfoRef->outputKeyElementId = Csm_GetOutputKeyElementIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable);
      job->jobRedirectionInfoRef->outputKeyId = Csm_GetCryIfKeyIdOfKey(Csm_GetOutputKeyIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable));
    }

    if((redirectionConfigValue & ((uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT)) == (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT){
      job->jobRedirectionInfoRef->secondaryOutputKeyElementId = Csm_GetSecondaryOutputKeyElementIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable);
      job->jobRedirectionInfoRef->secondaryOutputKeyId = Csm_GetCryIfKeyIdOfKey(Csm_GetSecondaryOutputKeyIdOfInOutJobRedirectionTable(indexOfInOutRedirectionTable));
    }
  }
  else
#endif
  {
#if(CSM_JOB_TYPE_LAYOUT_REDIRECTION_INFO_REF == STD_ON)
    job->jobRedirectionInfoRef = (P2VAR(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_VAR_NOINIT)) (NULL_PTR);
#else
    CSM_DUMMY_STATEMENT(job);
#endif
  }
}

CSM_LOCAL FUNC(Std_ReturnType, CSM_CODE) Csm_HandleJobProcessing(Csm_ChannelIdOfQueueInfoType channelId, P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job){
  Std_ReturnType retVal;

#if(CSM_CALLOUT == STD_ON)
  Csm_CalloutInfoIdxOfJobTableType calloutInfoId;

  calloutInfoId = Csm_GetCalloutInfoIdxOfJobTable(job->jobId);

  retVal = Csm_CallPreJobCallout(job);

  if((calloutInfoId >= Csm_GetSizeOfCalloutInfo()) || (Csm_GetCalloutStateOfCalloutState(calloutInfoId) == CSM_CALLOUT_STATE_PROCESSING))
#endif
  {
    retVal = EcuabCryIf_ProcessJob(channelId, job);
#if(CSM_CALLOUT == STD_ON)
    if(calloutInfoId < Csm_GetSizeOfCalloutInfo()){
#if(CSM_ASYNC_PROCESSING == STD_ON)
      if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_SYNC)
#endif
      {
        Csm_SetCalloutStateOfCalloutState(calloutInfoId, CSM_CALLOUT_STATE_POST_INITIAL);
        Csm_CallPostJobCallout(job, &retVal);
      }
    }
#endif
  }
  return retVal;
}

CSM_LOCAL FUNC(Std_ReturnType, CSM_CODE) Csm_ProcessJob(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job){
  Std_ReturnType retVal;
  uint32 jobId = job->jobId;
  Csm_QueueInfoIterType queueIdx = Csm_GetQueueRefIdxOfJobTable(jobId);
  Csm_ChannelIdOfQueueInfoType channelId = Csm_GetChannelIdOfQueueInfo(queueIdx);
#if(CSM_ASYNC_PROCESSING == STD_ON)
  Crypto_JobStateType combinedJobState = job->jobState;

#if(CSM_JOB_TYPE_LAYOUT_ASR430_COMPATIBILITY == STD_ON)
  combinedJobState |= job->state;
#endif
#endif

  Csm_AppendRedirectionToJob(job);

#if(CSM_ASYNC_PROCESSING == STD_ON)

  if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC){
    boolean gotLockOfQueue = (Csm_GetLockOfQueueState(queueIdx) == 0u) ? TRUE : FALSE;

    if((gotLockOfQueue == TRUE) &&
      ((Csm_GetQueueIdxOfQueueState(queueIdx) == Csm_GetQueueStartIdxOfQueueInfo(queueIdx))
        || ((combinedJobState & CRYPTO_JOBSTATE_ACTIVE) == CRYPTO_JOBSTATE_ACTIVE))){
      Csm_SetJobState(jobId, CSM_JOB_STATE_PROGRESSING);
      Csm_IncLockOfQueueState(queueIdx);
#if(CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON)
      Csm_SetRetriggeringOfQueueState(queueIdx, CSM_ASYNC_JOB_RETRIGGER_STATE_IDLE);
#endif
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

      retVal = Csm_HandleJobProcessing(channelId, job);

      SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
      Csm_DecLockOfQueueState(queueIdx);
    }
    else{
      retVal = CRYPTO_E_BUSY;
    }

    if((retVal == CRYPTO_E_BUSY) || (retVal == CRYPTO_E_QUEUE_FULL)){
      retVal = Csm_EnqueueJob(queueIdx, job);
#if(CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON)
      if(Csm_IsTriggerAsynchJobsInCallbackOfQueueInfo(queueIdx))
      {
        if(!gotLockOfQueue)
        {
          Csm_SetRetriggeringOfQueueState(queueIdx, CSM_ASYNC_JOB_RETRIGGER_STATE_PENDING);
        }
        else if(Csm_GetRetriggeringOfQueueState(queueIdx) == CSM_ASYNC_JOB_RETRIGGER_STATE_PENDING)
        {
          Csm_TriggerAsynchJobProcessing(queueIdx);
        }
        else
        {
        }
      }
#endif
    }

    else if(retVal == E_OK){
      if(Csm_GetJobState(jobId) == CSM_JOB_STATE_PROGRESSING)
      {
        Csm_SetJobState(jobId, CSM_JOB_STATE_WAITING);
      }
      else
      {
        Csm_IncLockOfQueueState(queueIdx);
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
        Csm_CallbackNotification(job, Csm_GetJobState(jobId) & CSM_JOB_STATE_CALLBACK_OCCURRED_CLEAR_MASK);
        SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
        Csm_DecLockOfQueueState(queueIdx);
      }
    }
    else{
      Csm_SetJobState(jobId, CSM_JOB_STATE_IDLE);
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
      job->jobId = CSM_EMPTY_JOB;
#endif
    }
    SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
  }
  else{
    if(
      (Csm_GetQueueIdxOfQueueState(queueIdx) != Csm_GetQueueStartIdxOfQueueInfo(queueIdx))
      && ((combinedJobState & CRYPTO_JOBSTATE_ACTIVE) != CRYPTO_JOBSTATE_ACTIVE)
      ){
      if((job->jobInfo->jobPriority > (Csm_GetQueue((Csm_QueueIdxOfQueueStateType)(Csm_GetQueueIdxOfQueueState(queueIdx) - 1u))->jobInfo->jobPriority)))
      {
        Csm_SetJobState(jobId, CSM_JOB_STATE_PROGRESSING);
        Csm_IncLockOfQueueState(queueIdx);
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
        retVal = Csm_HandleJobProcessing(channelId, job);
        SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
        Csm_DecLockOfQueueState(queueIdx);
      }
      else
      {
        retVal = CRYPTO_E_BUSY;
      }

      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
    else
#else
  {
#endif
    {
      Csm_SetJobState(jobId, CSM_JOB_STATE_PROGRESSING);
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

      retVal = Csm_HandleJobProcessing(channelId, job);
    }

    if((retVal != E_OK) || ((job->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_FINISH) == CRYPTO_OPERATIONMODE_FINISH)){
      Csm_SetJobState(jobId, CSM_JOB_STATE_IDLE);
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
      job->jobId = CSM_EMPTY_JOB;
#endif
    }
    else{
      Csm_SetJobState(jobId, CSM_JOB_STATE_ACTIVE);
    }
  }

  return retVal;
}

#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_PrepareJobObj(uint32 jobId, P2VAR(Crypto_JobType, AUTOMATIC, AUTOMATIC) job){
  job->jobId = jobId;
  job->jobPrimitiveInfo = Csm_GetAddrJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId));
  job->jobInfo = Csm_GetAddrJobInfo(Csm_GetJobInfoIdxOfJobTable(jobId));
  job->jobState = CRYPTO_JOBSTATE_IDLE;

#if(CSM_JOB_TYPE_LAYOUT_ASR430_COMPATIBILITY == STD_ON)
  job->PrimitiveInputOutput = job->jobPrimitiveInputOutput;
  job->state = job->jobState;
#endif
}
#endif

CSM_LOCAL FUNC(Std_ReturnType, CSM_CODE) Csm_GetJobObj(uint32 jobId, P2VAR(Csm_SizeOfJobType, AUTOMATIC, AUTOMATIC) jobObjId){
  Std_ReturnType retVal = CRYPTO_E_BUSY;

  if(Csm_GetJobState(jobId) >= CSM_JOB_STATE_PROGRESSING){
  }
  else if(Csm_GetJobState(jobId) == CSM_JOB_STATE_ACTIVE){
    *jobObjId = Csm_GetJobToObjMap(jobId);
    retVal = E_OK;
  }
#if(CSM_JOBIDXOFJOBTABLE == STD_ON)
  else
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
  if(Csm_IsJobUsedOfJobTable(jobId))
#endif
  {
    *jobObjId = Csm_GetJobIdxOfJobTable(jobId);
    Csm_SetJobToObjMap(jobId, *jobObjId);
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
    Csm_GetAddrJob(*jobObjId)->jobId = jobId;
#endif
    retVal = E_OK;
  }
#endif
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
  else{
    Csm_QueueInfoIterType queueIdx = Csm_GetQueueRefIdxOfJobTable(jobId);
    Csm_SizeOfJobType idx;
#if(CSM_ASYNC_PROCESSING == STD_ON)

    if(Csm_IsAsynchronousOfJobTable(jobId)){
      retVal = CRYPTO_E_QUEUE_FULL;

      for(idx = Csm_GetJobPoolStartIdxOfQueueInfo(queueIdx); idx < Csm_GetJobPoolEndIdxOfQueueInfo(queueIdx); idx++)
      {
        if(Csm_GetJob(idx).jobId == CSM_EMPTY_JOB)
        {
          *jobObjId = idx;
          Csm_SetJobToObjMap(jobId, idx);
          Csm_PrepareJobObj(jobId, Csm_GetAddrJob(idx));
          retVal = E_OK;
          break;
        }
      }
    }
    else
#endif
    {
      idx = Csm_GetJobObjSynchronousIdxOfQueueInfo(queueIdx);
      if(Csm_GetJob(idx).jobId == CSM_EMPTY_JOB)
      {
        *jobObjId = idx;
        Csm_SetJobToObjMap(jobId, idx);
        Csm_PrepareJobObj(jobId, Csm_GetAddrJob(idx));
        retVal = E_OK;
      }
    }
  }
#endif

  return retVal;
}

#if(CSM_ASYNC_PROCESSING == STD_ON)

CSM_LOCAL_INLINE FUNC(Std_ReturnType, CSM_CODE) Csm_EnqueueJob(Csm_QueueInfoIterType queueIdx, P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job){
  Std_ReturnType retVal = E_OK;
  Csm_QueueIterType i, j;

  if((Csm_GetJobState(job->jobId) == CSM_JOB_STATE_ACTIVE) && (Csm_GetQueueIdxOfQueueState(queueIdx) < Csm_GetQueueEndIdxOfQueueInfo(queueIdx))){
    Csm_SetQueue(Csm_GetQueueIdxOfQueueState(queueIdx), job);

    Csm_IncQueueIdxOfQueueState(queueIdx);
  }

  else if(Csm_GetQueueIdxOfQueueState(queueIdx) < (Csm_GetQueueEndIdxOfQueueInfo(queueIdx) - 1u)){
    for(i = Csm_GetQueueStartIdxOfQueueInfo(queueIdx); i <= Csm_GetQueueIdxOfQueueState(queueIdx); i++){
      if(i == Csm_GetQueueIdxOfQueueState(queueIdx))
      {
        Csm_SetQueue(i, job);
      }

      else if((job->jobInfo->jobPriority <= Csm_GetQueue(i)->jobInfo->jobPriority) || (Csm_GetJobState(Csm_GetQueue(i)->jobId) == CSM_JOB_STATE_ACTIVE))
      {
        for(j = Csm_GetQueueIdxOfQueueState(queueIdx); j > i; j--)
        {
          Csm_SetQueue(j, Csm_GetQueue(j - 1u));
        }

        Csm_SetQueue(i, job);
        break;
      }
      else
      {
      }
    }

    Csm_SetJobState(job->jobId, CSM_JOB_STATE_QUEUED);
    Csm_IncQueueIdxOfQueueState(queueIdx);
  }
  else{
    retVal = CRYPTO_E_QUEUE_FULL;
  }

  return retVal;
}

CSM_LOCAL FUNC(void, CSM_CODE) Csm_DequeueJob(Csm_QueueInfoIterType queueIdx, uint32 jobId){
  Csm_QueueIterType i, j;

  for(i = Csm_GetQueueIdxOfQueueState(queueIdx); i > Csm_GetQueueStartIdxOfQueueInfo(queueIdx); i--){
    if(jobId == Csm_GetQueue(i - 1u)->jobId){
      for(j = i; j < Csm_GetQueueIdxOfQueueState(queueIdx); j++)
      {
        Csm_SetQueue(j - 1u, Csm_GetQueue(j));
      }

      Csm_DecQueueIdxOfQueueState(queueIdx);

      break;
    }
  }
}

CSM_LOCAL FUNC(void, CSM_CODE) Csm_TriggerAsynchJobProcessing(Csm_QueueInfoIterType queueIdx){
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
  uint32 jobId;
  Std_ReturnType retVal;

  if((Csm_GetLockOfQueueState(queueIdx) == 0u) && (Csm_GetQueueIdxOfQueueState(queueIdx) != Csm_GetQueueStartIdxOfQueueInfo(queueIdx))){
    job = Csm_GetQueue(Csm_GetQueueIdxOfQueueState(queueIdx) - 1u);
    jobId = job->jobId;

#if(CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON)
    Csm_SetRetriggeringOfQueueState(queueIdx, CSM_ASYNC_JOB_RETRIGGER_STATE_IDLE);
#endif

    if(jobId < Csm_GetSizeOfJobState()){
      Csm_SetJobState(jobId, CSM_JOB_STATE_PROGRESSING);
      Csm_IncLockOfQueueState(queueIdx);
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
      retVal = Csm_HandleJobProcessing(Csm_GetChannelIdOfQueueInfo(queueIdx), job);
      SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
      Csm_DecLockOfQueueState(queueIdx);

      if(retVal == E_OK)
      {
        Csm_DequeueJob(queueIdx, jobId);

        if(Csm_GetJobState(jobId) == CSM_JOB_STATE_PROGRESSING)
        {
          Csm_SetJobState(jobId, CSM_JOB_STATE_WAITING);
        }
        else
        {
          SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
          Csm_CallbackNotification(job, Csm_GetJobState(jobId) & CSM_JOB_STATE_CALLBACK_OCCURRED_CLEAR_MASK);
          SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
        }
      }

      else if((retVal == CRYPTO_E_BUSY) || (retVal == CRYPTO_E_QUEUE_FULL)) {
        Csm_SetJobState(jobId, CSM_JOB_STATE_QUEUED);
      }
      else
      {
        Csm_DequeueJob(queueIdx, jobId);

        Csm_SetJobState(jobId, CSM_JOB_STATE_WAITING);
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
        Csm_CallbackNotification(job, retVal);
        SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
      }
    }
    else{
      Csm_DecQueueIdxOfQueueState(queueIdx);
    }
  }
}

CSM_LOCAL_INLINE FUNC(Std_ReturnType, CSM_CODE) Csm_CancelAsynchronousJob(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job){
  uint32 jobId = job->jobId;
  Std_ReturnType retVal = E_NOT_OK;
  Csm_QueueInfoIterType queueInfoIdx = Csm_GetQueueRefIdxOfJobTable(jobId);

  boolean notifyByCallback = FALSE;

#if(CSM_CANCELATION_DURING_PROCESSING == STD_ON)
  if(Csm_GetJobState(jobId) == CSM_JOB_STATE_WAITING){
    Csm_SetJobState(jobId, CSM_JOB_STATE_CANCELING);
    SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = EcuabCryIf_CancelJob(Csm_GetChannelIdOfQueueInfo(queueInfoIdx), job);

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    if(Csm_GetJobState(jobId) == CSM_JOB_STATE_CANCELING){
      if(retVal == E_OK)
      {
        notifyByCallback = TRUE;
      }
      else if(retVal == CRYPTO_E_JOB_CANCELED)
      {
        Csm_SetJobState(jobId, CSM_JOB_STATE_CANCELED);
      }
      else
      {
        Csm_SetJobState(jobId, CSM_JOB_STATE_WAITING);
      }
    }
    else{
      retVal = E_NOT_OK;
    }
  }
  else
#endif
    if(Csm_GetJobState(jobId) == CSM_JOB_STATE_QUEUED){
      if((job->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_START) == CRYPTO_OPERATIONMODE_START)
      {
        retVal = E_OK;
      }
      else
      {
        Csm_IncLockOfQueueState(queueInfoIdx);
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
        retVal = EcuabCryIf_CancelJob(Csm_GetChannelIdOfQueueInfo(queueInfoIdx), job);
        SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
        Csm_DecLockOfQueueState(queueInfoIdx);
      }

      if(retVal == E_OK)
      {
        Csm_DequeueJob(queueInfoIdx, jobId);
        notifyByCallback = TRUE;
      }
    }
    else if(Csm_GetJobState(jobId) == CSM_JOB_STATE_ACTIVE){
      Csm_SetJobState(jobId, CSM_JOB_STATE_CANCELING);
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

      retVal = EcuabCryIf_CancelJob(Csm_GetChannelIdOfQueueInfo(queueInfoIdx), job);

      SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
      if(retVal == E_OK)
      {
        notifyByCallback = TRUE;
      }
      else
      {
        Csm_SetJobState(jobId, CSM_JOB_STATE_ACTIVE);
        retVal = E_NOT_OK;
      }
    }
    else{
    }

  if(notifyByCallback){
    SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    Csm_CallbackNotification(job, CRYPTO_E_JOB_CANCELED);
    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
  }

  return retVal;
}

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_HandleApplicationCallback(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job, Std_ReturnType result, P2VAR(uint8, AUTOMATIC, AUTOMATIC) errorId){
#if(CSM_CALLBACK_START_NOTIFICATION == STD_OFF)
  if((((job->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_UPDATE) == CRYPTO_OPERATIONMODE_UPDATE)
          && (job->jobPrimitiveInfo->callbackUpdateNotification == TRUE))
      || ((job->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_FINISH) == CRYPTO_OPERATIONMODE_FINISH)
      || (result == CRYPTO_E_JOB_CANCELED))
#endif
  {
#if(CSM_CALLBACKFUNC43OFBSWCALLBACKS == STD_ON)
    if(Csm_IsBswCallbacksUsedOfJobTable(job->jobId) && (Csm_GetCallbackFunc43OfBswCallbacks(Csm_GetBswCallbacksIdxOfJobTable(job->jobId)) != NULL_PTR)){
      Csm_GetCallbackFunc43OfBswCallbacks(Csm_GetBswCallbacksIdxOfJobTable(job->jobId))(job, result);
    }
    else
#endif

#if(CSM_CALLBACKFUNC44OFBSWCALLBACKS == STD_ON)
    if(Csm_IsBswCallbacksUsedOfJobTable(job->jobId) && (Csm_GetCallbackFunc44OfBswCallbacks(Csm_GetBswCallbacksIdxOfJobTable(job->jobId)) != NULL_PTR)){
      Csm_GetCallbackFunc44OfBswCallbacks(Csm_GetBswCallbacksIdxOfJobTable(job->jobId))(job->jobId, result);
    }
    else
#endif

#if(CSM_CALLBACKFUNC45OFBSWCALLBACKS == STD_ON)

    if(Csm_IsBswCallbacksUsedOfJobTable(job->jobId)){
      Csm_GetCallbackFunc45OfBswCallbacks(Csm_GetBswCallbacksIdxOfJobTable(job->jobId))(job, result);
    }
    else
#endif

#if(CSM_RTECALLBACK == STD_ON)
    if(Csm_IsRteCallbackUsedOfJobTable(job->jobId)){
      Csm_SetRteResult(Csm_GetRteCallbackIdxOfJobTable(job->jobId), result);
      Csm_SetRteCallbackOccurred(TRUE);
    }
    else
#endif

    {
      *errorId = CSM_E_PARAM_METHOD_INVALID;

      CSM_DUMMY_STATEMENT(job);
      CSM_DUMMY_STATEMENT(result);
    }
  }
}

#if(CSM_RTECALLBACK == STD_ON)

CSM_LOCAL_INLINE FUNC(void, CSM_CODE) Csm_HandleRteCallbacks(void){
  if(Csm_IsRteCallbackOccurred()){
    Csm_RteCallbackIterType callbackIdx;
    Std_ReturnType retVal;

    Csm_SetRteCallbackOccurred(FALSE);
    for(callbackIdx = 0u; callbackIdx < Csm_GetSizeOfRteCallback(); callbackIdx++){
      retVal = Csm_GetRteResult(callbackIdx);
      if(retVal != CSM_CALLBACK_IDLE)
      {
        Csm_SetRteResult(callbackIdx, CSM_CALLBACK_IDLE);
        (void)Csm_GetRteCallback(callbackIdx)(retVal);
      }
    }
  }
}
#endif

#endif
#endif

FUNC(void, CSM_CODE) Csm_InitMemory(void){
#if(CSM_DEV_ERROR_DETECT == STD_ON)
  Csm_IsInitialized = CSM_UNINIT;
#endif
}

FUNC(void, CSM_CODE) Csm_Init(void){
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized == (uint8)CSM_INITIALIZED){
    errorId = CSM_E_ALREADY_INITIALIZED;
  }
  else
#endif
  {
#if(CSM_JOB == STD_ON)
    uint32_least index;

    for(index = 0u; index < Csm_GetSizeOfJob(); index++){
      Csm_GetJob(index).jobState                                         = CRYPTO_JOBSTATE_IDLE;
      Csm_GetJob(index).jobPrimitiveInputOutput.inputPtr                 = (const uint8*)NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.inputLength              = 0u;
      Csm_GetJob(index).jobPrimitiveInputOutput.secondaryInputPtr        = (const uint8*)NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.secondaryInputLength     = 0u;
      Csm_GetJob(index).jobPrimitiveInputOutput.tertiaryInputPtr         = (const uint8*)NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.tertiaryInputLength      = 0u;
      Csm_GetJob(index).jobPrimitiveInputOutput.outputPtr                = (uint8*) NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.outputLengthPtr          = (uint32*)NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.secondaryOutputPtr       = (uint8*) NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.secondaryOutputLengthPtr = (uint32*)NULL_PTR;
      Csm_GetJob(index).jobPrimitiveInputOutput.verifyPtr                = (Crypto_VerifyResultType*)NULL_PTR;
#if(CSM_JOB_TYPE_LAYOUT_INPUT64 == STD_ON)
      Csm_GetJob(index).jobPrimitiveInputOutput.input64 = 0u;
#endif
#if(CSM_JOB_TYPE_LAYOUT_OUTPUT64_PTR == STD_ON)
      Csm_GetJob(index).jobPrimitiveInputOutput.output64Ptr = NULL_PTR;
#endif
      Csm_GetJob(index).jobPrimitiveInputOutput.mode = 0u;
      Csm_GetJob(index).cryptoKeyId = 0u;
      Csm_GetJob(index).jobId = CSM_EMPTY_JOB;
#if(CSM_JOB_TYPE_LAYOUT_ASR430_COMPATIBILITY == STD_ON)
      Csm_GetJob(index).PrimitiveInputOutput = Csm_GetJob(index).jobPrimitiveInputOutput;
      Csm_GetJob(index).state = CRYPTO_JOBSTATE_IDLE;
#endif
    }

    for(index = 0u; index < Csm_GetSizeOfJobTable(); index++){
#if(CSM_JOBIDXOFJOBTABLE == STD_ON)
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
      if(Csm_IsJobUsedOfJobTable(index))
#endif
      {
        Csm_GetJob(Csm_GetJobIdxOfJobTable(index)).jobPrimitiveInfo = Csm_GetAddrJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(index));
        Csm_GetJob(Csm_GetJobIdxOfJobTable(index)).jobInfo = Csm_GetAddrJobInfo(Csm_GetJobInfoIdxOfJobTable(index));
        Csm_GetJob(Csm_GetJobIdxOfJobTable(index)).jobId = (uint32)index;
      }
#endif
      Csm_SetJobState(index, CSM_JOB_STATE_IDLE);
    }

    for(index = 0u; index < Csm_GetSizeOfQueueInfo(); index++){
      Csm_SetQueueIdxOfQueueState(index, Csm_GetQueueStartIdxOfQueueInfo(index));
      Csm_SetLockOfQueueState(index, 0u);

#if((CSM_ASYNC_PROCESSING == STD_ON) && (CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON))
      if(Csm_IsTriggerAsynchJobsInCallbackOfQueueInfo(index))
      {
        Csm_SetRetriggeringOfQueueState(index, CSM_ASYNC_JOB_RETRIGGER_STATE_IDLE);
      }
#endif
    }

#if(CSM_CALLOUT == STD_ON)

    for(index = 0u; index < Csm_GetSizeOfCalloutState(); index++){
      Csm_SetCalloutStateOfCalloutState(index, CSM_CALLOUT_STATE_IDLE);
    }
#endif

#if(CSM_RTECALLBACK == STD_ON)
    Csm_SetRteCallbackOccurred(FALSE);
    for(index = 0u; index < Csm_GetSizeOfRteCallback(); index++){
      Csm_SetRteResult(index, CSM_CALLBACK_IDLE);
    }
#endif

#endif

#if(CSM_DEV_ERROR_DETECT == STD_ON)

    Csm_IsInitialized = CSM_INITIALIZED;
#endif

  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_INIT_ID, errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif
}

#if(CSM_VERSION_INFO_API == STD_ON)

FUNC(void, CSM_CODE) Csm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_VAR) versioninfo){
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)
  if(versioninfo == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }
  else
#endif
  {
    versioninfo->vendorID = (uint16)CSM_VENDOR_ID;
    versioninfo->moduleID = (uint8)CSM_MODULE_ID;
    versioninfo->sw_major_version = (uint8)CSM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)CSM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)CSM_SW_PATCH_VERSION;
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)CSM_GETVERSIONINFO_ID, errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif
}
#endif

FUNC(void, CSM_CODE) Csm_MainFunction(void){
#if(CSM_JOB == STD_ON)

  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }
  else
#endif
  {
#if(CSM_ASYNC_PROCESSING == STD_ON)

    Csm_QueueInfoIterType queueIdx;
#if(CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON)
    Csm_QueueIterType triggerCounter;
#endif

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
    for(queueIdx = 0u; queueIdx < Csm_GetSizeOfQueueInfo(); queueIdx++){
#if(CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON)
      if(Csm_IsTriggerAsynchJobsInCallbackOfQueueInfo(queueIdx))
      {
        for(triggerCounter = 0u; triggerCounter < ((Csm_QueueIterType)(Csm_GetQueueEndIdxOfQueueInfo(queueIdx)) - (Csm_QueueIterType)(Csm_GetQueueStartIdxOfQueueInfo(queueIdx))); triggerCounter++)
        {
          Csm_TriggerAsynchJobProcessing(queueIdx);

          if(Csm_GetRetriggeringOfQueueState(queueIdx) == CSM_ASYNC_JOB_RETRIGGER_STATE_IDLE)
          {
            break;
          }
        }
      }
      else
#endif
      {
        Csm_TriggerAsynchJobProcessing(queueIdx);
      }
    }
    SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

#if(CSM_CALLOUT == STD_ON){
      Csm_CalloutInfoIterType calloutInfoIdx;
      for(calloutInfoIdx = 0u; calloutInfoIdx < Csm_GetSizeOfCalloutInfo(); calloutInfoIdx++)
      {
        if(Csm_GetCalloutStateOfCalloutState(calloutInfoIdx) == CSM_CALLOUT_STATE_PROCESSING_ABORTED_BY_CALLOUT)
        {
          Csm_CallbackNotification(&Csm_GetJob(Csm_GetJobToObjMap(Csm_GetJobTableIdxOfCalloutInfo(calloutInfoIdx))), E_NOT_OK);
        }
      }
    }
#endif

#if(CSM_RTECALLBACK == STD_ON)
    Csm_HandleRteCallbacks();
#endif

#endif
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MAINFUNCTION_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif
#endif
}

FUNC(void, CSM_CODE) Csm_CallbackNotification(P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job
   ,                                             Std_ReturnType result){
#if(CSM_JOB == STD_ON) && (CSM_ASYNC_PROCESSING == STD_ON)

  uint8 errorId = CSM_E_NO_ERROR;
  Std_ReturnType resultCopy = result;
  boolean notify = TRUE;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(job == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }
  else if((job->jobId >= Csm_GetSizeOfJobTable()) || ((resultCopy & CSM_JOB_STATE_CALLBACK_OCCURRED) != 0u)){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    uint32 jobId = job->jobId;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
#if(CSM_CANCELATION_DURING_PROCESSING == STD_ON)

    if(Csm_GetJobState(jobId) == CSM_JOB_STATE_CANCELED){
      resultCopy = CRYPTO_E_JOB_CANCELED;
      Csm_SetJobState(jobId, CSM_JOB_STATE_IDLE);
    }
    else
#endif

    if(Csm_GetJobState(jobId) == CSM_JOB_STATE_PROGRESSING){
      Csm_SetJobState(jobId, CSM_JOB_STATE_CALLBACK_OCCURRED | resultCopy);
      notify = FALSE;
    }

    else if((resultCopy == E_OK) && ((job->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_FINISH) != CRYPTO_OPERATIONMODE_FINISH)){
      Csm_SetJobState(jobId, CSM_JOB_STATE_ACTIVE);
    }
    else{
      Csm_SetJobState(jobId, CSM_JOB_STATE_IDLE);
    }

    SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

    if(notify){
#if(CSM_CALLOUT == STD_ON)
      Csm_CallPostJobCallout(job, &resultCopy);
#endif

      Csm_HandleApplicationCallback(job, resultCopy, &errorId);

#if(CSM_JOBIDXOFJOBTABLE == STD_ON) && (CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
      if(!(Csm_IsJobUsedOfJobTable(jobId)))
#endif
      {
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
        if((resultCopy != E_OK) || ((job->jobPrimitiveInputOutput.mode & CRYPTO_OPERATIONMODE_FINISH) == CRYPTO_OPERATIONMODE_FINISH))
        {
          job->jobId = CSM_EMPTY_JOB;
        }
#endif
      }

#if(CSM_TRIGGERASYNCHJOBSINCALLBACKOFQUEUEINFO == STD_ON)
      {
        Csm_QueueInfoIterType queueIdx;
        queueIdx = Csm_GetQueueRefIdxOfJobTable(jobId);

        if(Csm_IsTriggerAsynchJobsInCallbackOfQueueInfo(queueIdx))
        {
          SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();
          Csm_SetRetriggeringOfQueueState(queueIdx, CSM_ASYNC_JOB_RETRIGGER_STATE_PENDING);
          Csm_TriggerAsynchJobProcessing(queueIdx);
          SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
        }
      }
#endif
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CALLBACKNOTIFICATION_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(job);
  CSM_DUMMY_STATEMENT(errorId);
#endif
#else
  CSM_DUMMY_STATEMENT(job);
  CSM_DUMMY_STATEMENT(result);
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet(uint32 keyId
   ,                                                uint32 keyElementId
   ,                                                P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) keyPtr
   ,                                                uint32 keyLength){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(keyPtr == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyElementSet(Csm_GetCryIfKeyIdOfKey(keyId), keyElementId, keyPtr, keyLength);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYELEMENTSET_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(keyElementId);
  CSM_DUMMY_STATEMENT_CONST(keyPtr);
  CSM_DUMMY_STATEMENT(keyLength);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid(uint32 keyId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeySetValid(Csm_GetCryIfKeyIdOfKey(keyId));
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYSETVALID_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet(uint32 keyId
   ,                                                uint32 keyElementId
   ,                                                P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) keyPtr
   ,                                                P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) keyLengthPtr){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyPtr == NULL_PTR)
         || (keyLengthPtr == NULL_PTR)){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyElementGet(Csm_GetCryIfKeyIdOfKey(keyId), keyElementId, keyPtr, keyLengthPtr);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYELEMENTGET_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(keyElementId);
  CSM_DUMMY_STATEMENT(keyPtr);
  CSM_DUMMY_STATEMENT(keyLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy(uint32 keyId
   ,                                                 uint32 keyElementId
   ,                                                 uint32 targetKeyId
   ,                                                 uint32 targetKeyElementId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (targetKeyId >= Csm_GetSizeOfKey())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyElementCopy(Csm_GetCryIfKeyIdOfKey(keyId), keyElementId, Csm_GetCryIfKeyIdOfKey(targetKeyId), targetKeyElementId);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYELEMENTCOPY_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(keyElementId);
  CSM_DUMMY_STATEMENT(targetKeyId);
  CSM_DUMMY_STATEMENT(targetKeyElementId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial( uint32 keyId
   ,                                                         uint32 keyElementId
   ,                                                         uint32 keyElementSourceOffset
   ,                                                         uint32 keyElementTargetOffset
   ,                                                         uint32 keyElementCopyLength
   ,                                                         uint32 targetKeyId
   ,                                                         uint32 targetKeyElementId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (targetKeyId >= Csm_GetSizeOfKey())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyElementCopyPartial(Csm_GetCryIfKeyIdOfKey(keyId), keyElementId, keyElementSourceOffset, keyElementTargetOffset, keyElementCopyLength, Csm_GetCryIfKeyIdOfKey(targetKeyId), targetKeyElementId);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYELEMENTCOPYPARTIAL_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(keyElementId);
  CSM_DUMMY_STATEMENT(keyElementSourceOffset);
  CSM_DUMMY_STATEMENT(keyElementTargetOffset);
  CSM_DUMMY_STATEMENT(keyElementCopyLength);
  CSM_DUMMY_STATEMENT(targetKeyId);
  CSM_DUMMY_STATEMENT(targetKeyElementId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy(uint32 keyId
   ,                                          uint32 targetKeyId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (targetKeyId >= Csm_GetSizeOfKey())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyCopy(Csm_GetCryIfKeyIdOfKey(keyId), Csm_GetCryIfKeyIdOfKey(targetKeyId));
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYCOPY_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(targetKeyId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed(uint32 keyId
   ,                                             P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) seedPtr
   ,                                             uint32 seedLength){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(seedPtr == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = EcuabCryIf_RandomSeed(Csm_GetCryIfKeyIdOfKey(keyId), seedPtr, seedLength);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RANDOMSEED_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT_CONST(seedPtr);
  CSM_DUMMY_STATEMENT(seedLength);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate(uint32 keyId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = EcuabCryIf_KeyGenerate(Csm_GetCryIfKeyIdOfKey(keyId));
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYGENERATE_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive(uint32 keyId
   ,                                            uint32 targetKeyId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (targetKeyId >= Csm_GetSizeOfKey())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyDerive(Csm_GetCryIfKeyIdOfKey(keyId), Csm_GetCryIfKeyIdOfKey(targetKeyId));
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYDERIVE_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(targetKeyId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal(uint32 keyId
   ,                                                        P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) publicValuePtr
   ,                                                        P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) publicValueLengthPtr){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((publicValuePtr == NULL_PTR)
         || (publicValueLengthPtr == NULL_PTR)){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyExchangeCalcPubVal(Csm_GetCryIfKeyIdOfKey(keyId), publicValuePtr, publicValueLengthPtr);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCPUBVAL_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(publicValuePtr);
  CSM_DUMMY_STATEMENT(publicValueLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret(uint32 keyId
   ,                                                        P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) partnerPublicValuePtr
   ,                                                        uint32 partnerPublicValueLength){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(partnerPublicValuePtr == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_KeyExchangeCalcSecret(Csm_GetCryIfKeyIdOfKey(keyId), partnerPublicValuePtr, partnerPublicValueLength);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSECRET_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(partnerPublicValuePtr);
  CSM_DUMMY_STATEMENT(partnerPublicValueLength);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateParse(uint32 keyId){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(keyId >= Csm_GetSizeOfKey()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_CertificateParse(Csm_GetCryIfKeyIdOfKey(keyId));
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CERTIFICATEPARSE_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateVerify(uint32 keyId
   ,                                                    uint32 verifyKeyId
   ,                                                    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr){
#if(CSM_KEY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(verifyPtr == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (verifyKeyId >= Csm_GetSizeOfKey())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    retVal = CryIf_CertificateVerify(Csm_GetCryIfKeyIdOfKey(keyId), Csm_GetCryIfKeyIdOfKey(verifyKeyId), verifyPtr);
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CERTIFICATEVERIFY_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(keyId);
  CSM_DUMMY_STATEMENT(verifyKeyId);
  CSM_DUMMY_STATEMENT(verifyPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob(uint32 jobId
   ,                                            Crypto_OperationModeType mode){
#if(CSM_JOB == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    if(Csm_GetJobState(jobId) == CSM_JOB_STATE_IDLE){
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
      retVal =  E_OK;
    }
    else{
      P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job = Csm_GetAddrJob(Csm_GetJobToObjMap(jobId));

#if(CSM_ASYNC_PROCESSING == STD_ON)
      if(Csm_IsAsynchronousOfJobTable(jobId))
      {
        retVal = Csm_CancelAsynchronousJob(job);
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
      }
      else
#endif
      if(Csm_GetJobState(jobId) == CSM_JOB_STATE_ACTIVE)
      {
        Csm_SetJobState(jobId, CSM_JOB_STATE_CANCELING);
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

        retVal = EcuabCryIf_CancelJob(Csm_GetChannelIdOfQueueInfo(Csm_GetQueueRefIdxOfJobTable(jobId)), job);

        if(retVal == E_OK)
        {
#if(CSM_CALLOUT == STD_ON)

          retVal = CRYPTO_E_JOB_CANCELED;
          Csm_CallPostJobCallout(job, &retVal);
          retVal = E_OK;
#endif
#if(CSM_JOBSHARINGOFQUEUEINFO == STD_ON)
          job->jobId = CSM_EMPTY_JOB;
#endif
          Csm_SetJobState(jobId, CSM_JOB_STATE_IDLE);
        }
        else
        {
          Csm_SetJobState(jobId, CSM_JOB_STATE_ACTIVE);
        }
      }
      else
      {
        SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();

      }
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CANCELJOB_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  CSM_DUMMY_STATEMENT(mode);
  return retVal;
#else

  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_Hash(uint32 jobId
   ,                                       Crypto_OperationModeType mode
   ,                                       P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                       uint32 dataLength
   ,                                       P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                       P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr){
#if(CSM_EXIST_HASH == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_HASH){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.outputPtr = resultPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_HASH_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(resultPtr);
  CSM_DUMMY_STATEMENT(resultLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate(uint32 jobId
   ,                                              Crypto_OperationModeType mode
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                              uint32 dataLength
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) macLengthPtr){
#if(CSM_EXIST_MACGENERATE == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_MACGENERATE){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.outputPtr = macPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = macLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACGENERATE_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(macPtr);
  CSM_DUMMY_STATEMENT(macLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify(uint32 jobId
   ,                                            Crypto_OperationModeType mode
   ,                                            P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                            uint32 dataLength
   ,                                            P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) macPtr
   ,                                            uint32 macLength
   ,                                            P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr){
#if(CSM_EXIST_MACVERIFY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_MACVERIFY){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.secondaryInputPtr = macPtr;
      job->jobPrimitiveInputOutput.secondaryInputLength = macLength;
      job->jobPrimitiveInputOutput.verifyPtr = verifyPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACVERIFY_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(macPtr);
  CSM_DUMMY_STATEMENT(macLength);
  CSM_DUMMY_STATEMENT(verifyPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt(uint32 jobId
   ,                                          Crypto_OperationModeType mode
   ,                                          P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                          uint32 dataLength
   ,                                          P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                          P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr){
#if(CSM_EXIST_ENCRYPT == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_ENCRYPT){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.outputPtr = resultPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ENCRYPT_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(resultPtr);
  CSM_DUMMY_STATEMENT(resultLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt(uint32 jobId
   ,                                          Crypto_OperationModeType mode
   ,                                          P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                          uint32 dataLength
   ,                                          P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                          P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr){
#if(CSM_EXIST_DECRYPT == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_DECRYPT){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.outputPtr = resultPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_DECRYPT_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(resultPtr);
  CSM_DUMMY_STATEMENT(resultLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt(uint32 jobId
   ,                                              Crypto_OperationModeType mode
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) plaintextPtr
   ,                                              uint32 plaintextLength
   ,                                              P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) associatedDataPtr
   ,                                              uint32 associatedDataLength
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) ciphertextPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) ciphertextLengthPtr
   ,                                              P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) tagPtr
   ,                                              P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) tagLengthPtr){
#if(CSM_EXIST_AEADENCRYPT == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_AEADENCRYPT){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = plaintextPtr;
      job->jobPrimitiveInputOutput.inputLength = plaintextLength;
      job->jobPrimitiveInputOutput.secondaryInputPtr = associatedDataPtr;
      job->jobPrimitiveInputOutput.secondaryInputLength = associatedDataLength;
      job->jobPrimitiveInputOutput.outputPtr = ciphertextPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = ciphertextLengthPtr;
      job->jobPrimitiveInputOutput.secondaryOutputPtr = tagPtr;
      job->jobPrimitiveInputOutput.secondaryOutputLengthPtr = tagLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_AEADENCRYPT_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(plaintextPtr);
  CSM_DUMMY_STATEMENT(plaintextLength);
  CSM_DUMMY_STATEMENT(associatedDataPtr);
  CSM_DUMMY_STATEMENT(associatedDataLength);
  CSM_DUMMY_STATEMENT(ciphertextPtr);
  CSM_DUMMY_STATEMENT(ciphertextLengthPtr);
  CSM_DUMMY_STATEMENT(tagPtr);
  CSM_DUMMY_STATEMENT(tagLengthPtr);
  return E_NOT_OK;
#endif
}

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
   ,                                              P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr){
#if(CSM_EXIST_AEADDECRYPT == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_AEADDECRYPT){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = ciphertextPtr;
      job->jobPrimitiveInputOutput.inputLength = ciphertextLength;
      job->jobPrimitiveInputOutput.secondaryInputPtr = associatedDataPtr;
      job->jobPrimitiveInputOutput.secondaryInputLength = associatedDataLength;
      job->jobPrimitiveInputOutput.tertiaryInputPtr = tagPtr;
      job->jobPrimitiveInputOutput.tertiaryInputLength = tagLength;
      job->jobPrimitiveInputOutput.outputPtr = plaintextPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = plaintextLengthPtr;
      job->jobPrimitiveInputOutput.verifyPtr = verifyPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_AEADDECRYPT_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(ciphertextPtr);
  CSM_DUMMY_STATEMENT(ciphertextLength);
  CSM_DUMMY_STATEMENT(associatedDataPtr);
  CSM_DUMMY_STATEMENT(associatedDataLength);
  CSM_DUMMY_STATEMENT(tagPtr);
  CSM_DUMMY_STATEMENT(tagLength);
  CSM_DUMMY_STATEMENT(plaintextPtr);
  CSM_DUMMY_STATEMENT(plaintextLengthPtr);
  CSM_DUMMY_STATEMENT(verifyPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate(uint32 jobId
   ,                                                    Crypto_OperationModeType mode
   ,                                                    P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                    uint32 dataLength
   ,                                                    P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                    P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr){
#if(CSM_EXIST_SIGNATUREGENERATE == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_SIGNATUREGENERATE){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.outputPtr = resultPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREGENERATE_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(resultPtr);
  CSM_DUMMY_STATEMENT(resultLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify(uint32 jobId
   ,                                                  Crypto_OperationModeType mode
   ,                                                  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) dataPtr
   ,                                                  uint32 dataLength
   ,                                                  P2CONST(uint8, AUTOMATIC, CSM_APPL_VAR) signaturePtr
   ,                                                  uint32 signatureLength
   ,                                                  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_VAR) verifyPtr){
#if(CSM_EXIST_SIGNATUREVERIFY == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_SIGNATUREVERIFY){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = mode;
      job->jobPrimitiveInputOutput.inputPtr = dataPtr;
      job->jobPrimitiveInputOutput.inputLength = dataLength;
      job->jobPrimitiveInputOutput.secondaryInputPtr = signaturePtr;
      job->jobPrimitiveInputOutput.secondaryInputLength = signatureLength;
      job->jobPrimitiveInputOutput.verifyPtr = verifyPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREVERIFY_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(mode);
  CSM_DUMMY_STATEMENT(dataPtr);
  CSM_DUMMY_STATEMENT(dataLength);
  CSM_DUMMY_STATEMENT(signaturePtr);
  CSM_DUMMY_STATEMENT(signatureLength);
  CSM_DUMMY_STATEMENT(verifyPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate(uint32 jobId
   ,                                                 P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) resultPtr
   ,                                                 P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) resultLengthPtr){
#if(CSM_EXIST_RANDOMGENERATE == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_RANDOMGENERATE){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.outputPtr = resultPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RANDOMGENERATE_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(resultPtr);
  CSM_DUMMY_STATEMENT(resultLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeySetValid( uint32 jobId, uint32 keyId ){
#if(CSM_EXIST_JOBKEYSETVALID == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if( ( keyId >= Csm_GetSizeOfKey() ) || ( jobId >= Csm_GetSizeOfJobTable() ) ){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_KEYSETVALID){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.cryIfKeyId = Csm_GetCryIfKeyIdOfKey( keyId );

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_JOBKEYSETVALID_ID), errorId );
  }
#else
  CSM_DUMMY_STATEMENT( errorId );
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT( jobId );
  CSM_DUMMY_STATEMENT( keyId );
  return E_NOT_OK;
#endif
}

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobRandomSeed( uint32 jobId, uint32 keyId, P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) seedPtr, uint32 seedLength ){
#if(CSM_EXIST_JOBRANDOMSEED == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if( ( keyId >= Csm_GetSizeOfKey() ) || ( jobId >= Csm_GetSizeOfJobTable() ) ){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_RANDOMSEED){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.cryIfKeyId = Csm_GetCryIfKeyIdOfKey( keyId );
      job->jobPrimitiveInputOutput.inputPtr = seedPtr;
      job->jobPrimitiveInputOutput.inputLength = seedLength;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_JOBRANDOMSEED_ID), errorId );
  }
#else
  CSM_DUMMY_STATEMENT( errorId );
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT_CONST( jobId );
  CSM_DUMMY_STATEMENT( keyId );
  CSM_DUMMY_STATEMENT_CONST( seedPtr );
  CSM_DUMMY_STATEMENT( seedLength );
  return E_NOT_OK;
#endif
}

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyGenerate( uint32 jobId, uint32 keyId ){
#if(CSM_EXIST_JOBKEYGENERATE == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (jobId >= Csm_GetSizeOfJobTable())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_KEYGENERATE){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.cryIfKeyId = Csm_GetCryIfKeyIdOfKey( keyId );

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_JOBKEYGENERATE_ID), errorId );
  }
#else
  CSM_DUMMY_STATEMENT( errorId );
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT( jobId );
  CSM_DUMMY_STATEMENT( keyId );
  return E_NOT_OK;
#endif
}

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyDerive( uint32 jobId, uint32 keyId, uint32 targetKeyId ){
#if(CSM_EXIST_JOBKEYDERIVE == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if( (keyId >= Csm_GetSizeOfKey()) || (targetKeyId >= Csm_GetSizeOfKey()) || (jobId >= Csm_GetSizeOfJobTable()) ){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_KEYDERIVE){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.cryIfKeyId = Csm_GetCryIfKeyIdOfKey( keyId );
      job->jobPrimitiveInputOutput.targetCryIfKeyId = Csm_GetCryIfKeyIdOfKey( targetKeyId );

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_JOBKEYDERIVE_ID), errorId );
  }
#else
  CSM_DUMMY_STATEMENT( errorId );
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT( jobId );
  CSM_DUMMY_STATEMENT( keyId );
  CSM_DUMMY_STATEMENT( targetKeyId );
  return E_NOT_OK;
#endif
}

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyExchangeCalcPubVal( uint32 jobId
   ,                                                              uint32 keyId
   ,                                                              P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) publicValuePtr
   ,                                                              P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) publicValueLengthPtr ){
#if(CSM_EXIST_JOBKEYEXCHANGECALCPUBVAL == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (jobId >= Csm_GetSizeOfJobTable())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_KEYEXCHANGECALCPUBVAL){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.cryIfKeyId = Csm_GetCryIfKeyIdOfKey( keyId );
      job->jobPrimitiveInputOutput.outputPtr = publicValuePtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = publicValueLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_JOBKEYEXCHANGECALCPUBVAL_ID), errorId );
  }
#else
  CSM_DUMMY_STATEMENT( errorId );
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT( jobId );
  CSM_DUMMY_STATEMENT( keyId );
  CSM_DUMMY_STATEMENT( publicValuePtr );
  CSM_DUMMY_STATEMENT( publicValueLengthPtr );
  return E_NOT_OK;
#endif
}

FUNC( Std_ReturnType, CSM_CODE ) Csm_JobKeyExchangeCalcSecret(  uint32 jobId
   ,                                                               uint32 keyId
   ,                                                               P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr
   ,                                                               uint32 partnerPublicValueLength ){
#if(CSM_EXIST_JOBKEYEXCHANGECALCSECRET == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if((keyId >= Csm_GetSizeOfKey()) || (jobId >= Csm_GetSizeOfJobTable())){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service != CRYPTO_KEYEXCHANGECALCSECRET){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      job->jobPrimitiveInputOutput.cryIfKeyId = Csm_GetCryIfKeyIdOfKey( keyId );
      job->jobPrimitiveInputOutput.inputPtr = partnerPublicValuePtr;
      job->jobPrimitiveInputOutput.inputLength = partnerPublicValueLength;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_JOBKEYEXCHANGECALCSECRET_ID), errorId );
  }
#else
  CSM_DUMMY_STATEMENT( errorId );
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT( jobId );
  CSM_DUMMY_STATEMENT( keyId );
  CSM_DUMMY_STATEMENT( partnerPublicValuePtr );
  CSM_DUMMY_STATEMENT( partnerPublicValueLength );
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_SaveContextJob(  uint32 jobId
   ,                                                   P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,                                                   P2VAR(uint32, AUTOMATIC, CSM_APPL_VAR) contextBufferLengthPtr ){
#if(CSM_JOB == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if((contextBufferPtr == NULL_PTR) || (contextBufferLengthPtr == NULL_PTR)){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service > CRYPTO_SIGNATUREVERIFY){
    errorId = CSM_E_SERVICE_TYPE;
  }
  else
#endif

  if(Csm_GetJobState(jobId) == CSM_JOB_STATE_IDLE){
  }
  else{
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SAVE_CONTEXT;
      job->jobPrimitiveInputOutput.outputPtr = contextBufferPtr;
      job->jobPrimitiveInputOutput.outputLengthPtr = contextBufferLengthPtr;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SAVECONTEXTJOB_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(contextBufferPtr);
  CSM_DUMMY_STATEMENT(contextBufferLengthPtr);
  return E_NOT_OK;
#endif
}

FUNC(Std_ReturnType, CSM_CODE) Csm_RestoreContextJob(  uint32 jobId
   ,                                                      P2VAR(uint8, AUTOMATIC, CSM_APPL_VAR) contextBufferPtr
   ,                                                      uint32 contextBufferLength ){
#if(CSM_JOB == STD_ON)

  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

#if(CSM_DEV_ERROR_DETECT == STD_ON)

  if(Csm_IsInitialized != CSM_INITIALIZED){
    errorId = CSM_E_UNINIT;
  }

  else if(jobId >= Csm_GetSizeOfJobTable()){
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }

  else if(contextBufferPtr == NULL_PTR){
    errorId = CSM_E_PARAM_POINTER;
  }

  else if(Csm_GetJobPrimitiveInfo(Csm_GetJobPrimitiveInfoIdxOfJobTable(jobId)).primitiveInfo->service > CRYPTO_SIGNATUREVERIFY){
    errorId = CSM_E_SERVICE_TYPE;
  }
  else
#endif
  {
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_VAR) job;
    Csm_SizeOfJobType jobObjId = 0u;

    SchM_Enter_Csm_CSM_EXCLUSIVE_AREA_0();

    retVal = Csm_GetJobObj(jobId, &jobObjId);
    if(retVal == E_OK){
      job = Csm_GetAddrJob(jobObjId);

      job->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_RESTORE_CONTEXT;
      job->jobPrimitiveInputOutput.inputPtr = contextBufferPtr;
      job->jobPrimitiveInputOutput.inputLength = contextBufferLength;

      retVal = Csm_ProcessJob(job);

    }
    else{
      SchM_Exit_Csm_CSM_EXCLUSIVE_AREA_0();
    }
  }

#if(CSM_DEV_ERROR_REPORT == STD_ON)
  if(errorId != CSM_E_NO_ERROR){
    (void)Det_ReportError((uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RESTORECONTEXTJOB_ID), errorId);
  }
#else
  CSM_DUMMY_STATEMENT(errorId);
#endif

  return retVal;
#else
  CSM_DUMMY_STATEMENT(jobId);
  CSM_DUMMY_STATEMENT(contextBufferPtr);
  CSM_DUMMY_STATEMENT(contextBufferLength);
  return E_NOT_OK;
#endif
}

#define CSM_STOP_SEC_CODE
#include "MemMap.hpp"

#ifdef __cplusplus
}
#endif
