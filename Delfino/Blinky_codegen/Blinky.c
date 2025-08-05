/*
 * Implementation file for: Blinky
 * Generated with         : PLECS 4.9.6
 *                          TI2837x 1.10.5
 * Generated on           : 4 Aug 2025 23:03:07
 */
#include "Blinky.h"
#ifndef PLECS_HEADER_Blinky_h_
#error The wrong header file "Blinky.h" was included. Please check your
#error include path to see whether this file name conflicts with the name
#error of another header file.
#endif /* PLECS_HEADER_Blinky_h_ */
#if defined(__GNUC__) && (__GNUC__ > 4)
#   define _ALIGNMENT 16
#   define _RESTRICT __restrict
#   define _ALIGN __attribute__((aligned(_ALIGNMENT)))
#   if defined(__clang__)
#      if __has_builtin(__builtin_assume_aligned)
#         define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#      else
#         define _ASSUME_ALIGNED(a) a
#      endif
#   else
#      define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#   endif
#else
#   ifndef _RESTRICT
#      define _RESTRICT
#   endif
#   ifndef _ALIGN
#      define _ALIGN
#   endif
#   ifndef _ASSUME_ALIGNED
#      define _ASSUME_ALIGNED(a) a
#   endif
#endif
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "plx_hal.h"
#include <stdlib.h>
#define PLECSRunTimeError(msg) Blinky_errorStatus = msg
static const uint32_t Blinky_subTaskPeriod[1]= {
   /* [0.5, 0], [0, 0] */
   5000
};
static uint32_t Blinky_subTaskTick[1];
static char Blinky_subTaskHit[1];
#define Blinky_UNCONNECTED 0
static uint32_t Blinky_tickLo;
static int32_t Blinky_tickHi;
Blinky_BlockOutputs Blinky_B;
Blinky_ModelStates Blinky_X _ALIGN;
#if defined(EXTERNAL_MODE) && EXTERNAL_MODE
const float * const Blinky_ExtModeSignals[] = {

};
#endif /* defined(EXTERNAL_MODE) */
const char * Blinky_errorStatus;
const float Blinky_sampleTime = 0.0001f;
const char * const Blinky_checksum =
   "e2bf0461b89eca6276159caba7bf44296d3fdd02";
/* Target declarations */
// tag step function to allow special linking
#pragma CODE_SECTION(Blinky_step, "step")
extern void Blinky_initHal();

void Blinky_initialize(void)
{
   Blinky_tickHi = 0;
   Blinky_tickLo = 0;
   /* Initialize sub-task tick counters */
   Blinky_subTaskTick[0] = 0;       /* [0, 0], [0.5, 0] */
   memset(&Blinky_X, 0, sizeof(Blinky_X));

   /* Target pre-initialization */
   Blinky_initHal();


   /* Initialization for Delay : 'Blinky/Delay' */
   Blinky_X.Delay = false;
}

void Blinky_step(void)
{
   if (Blinky_errorStatus)
   {
      return;
   }
   {
      size_t i;
      for (i = 0; i < 1; ++i)
      {
         Blinky_subTaskHit[i] = (Blinky_subTaskTick[i] == 0);
      }
   }
   if (Blinky_subTaskHit[0])
   {
      /* Delay : 'Blinky/Delay' */
      Blinky_B.Delay = Blinky_X.Delay;

      /* Logical Operator : 'Blinky/Logical\nOperator' */
      Blinky_B.LogicalOperator = !Blinky_B.Delay;
   }

   /* Digital Out : 'Blinky/Digital Out' */
   PLXHAL_DIO_set(0, Blinky_B.LogicalOperator);
   if (Blinky_errorStatus)
   {
      return;
   }
   if (Blinky_subTaskHit[0])
   {
      /* Update for Delay : 'Blinky/Delay' */
      Blinky_X.Delay = Blinky_B.LogicalOperator;
   }

   /* Increment sub-task tick counters */
   {
      size_t i;
      for (i = 0; i < 1; ++i)
      {
         Blinky_subTaskTick[i]++;
         if (Blinky_subTaskTick[i] >= Blinky_subTaskPeriod[i])
         {
            Blinky_subTaskTick[i] = 0;
         }
      }
   }
}

void Blinky_terminate(void)
{
}
