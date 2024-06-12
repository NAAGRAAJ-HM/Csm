#pragma once
/******************************************************************************/
/* File   : ServiceCsm_Version.hpp                                            */
/* Author : Nagaraja HULIYAPURADA-MATA                                        */
/* Date   : 01.02.1982                                                        */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SERVICECSM_AR_RELEASE_VERSION_MAJOR                                    4
#define SERVICECSM_AR_RELEASE_VERSION_MINOR                                    3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(SERVICECSM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible SERVICECSM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(SERVICECSM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible SERVICECSM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

