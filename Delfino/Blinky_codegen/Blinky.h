/*
 * Header file for: Blinky
 * Generated with : PLECS 4.9.6
 *                  TI2837x 1.10.5
 * Generated on   : 5 Aug 2025 19:55:29
 */
#ifndef PLECS_HEADER_Blinky_h_
#define PLECS_HEADER_Blinky_h_

#include <stdbool.h>
#include <stdint.h>

/* Target typedefs */
typedef int_fast8_t int8_t;
typedef uint_fast8_t uint8_t;


/* Model floating point type */
typedef float Blinky_FloatType;

/* Target declarations */
extern void Blinky_background(void);

/* Model checksum */
extern const char * const Blinky_checksum;

/* Model error status */
extern const char * Blinky_errorStatus;


/* Model sample time */
extern const float Blinky_sampleTime;


/*
 * Model states */
typedef struct
{
   bool Delay;                      /* Blinky/Delay */
} Blinky_ModelStates;
extern Blinky_ModelStates Blinky_X;


/* Block outputs */
typedef struct
{
   bool LogicalOperator;            /* Blinky/Logical Operator */
   bool Delay;                      /* Blinky/Delay */
} Blinky_BlockOutputs;
extern Blinky_BlockOutputs Blinky_B;

/* Entry point functions */
void Blinky_initialize(void);
void Blinky_step(void);
void Blinky_terminate(void);

#endif /* PLECS_HEADER_Blinky_h_ */
