/*
 * Hardware configuration file for: TI2837x
 * Generated with                 : PLECS 4.9.6
 * Generated on                   : Mon Aug  4 23:03:07 2025
 */

/* HAL Includes */
#include "Blinky.h"
#include "plx_hal.h"
#include "plx_dispatcher.h"
#include "pil.h"
#include "plx_sci.h"
#include "string.h"
#include "pin_map.h"
#include "gpio.h"
#include "xbar.h"
#include "asysctl.h"
#include "sysctl.h"
#include "plx_dio.h"

/* HAL Declarations */
void DevInit(uint32_t aDeviceClkConf);
void InitFlashHz(Uint32 clkHz);
void DSP28x_usDelay(long LoopCount);

// Clock configuration
#define PLX_DEVICE_SETCLOCK_CFG  (SYSCTL_OSCSRC_OSC2 | SYSCTL_IMULT(19) |  \
                                  SYSCTL_FMULT_0 | SYSCTL_SYSDIV(1) |   \
                                  SYSCTL_PLL_ENABLE)

#define SYSCLK_HZ 190000000L
#define SYSCLK_WC_HI_HZ 196000000L
#define LSPCLK_HZ (SYSCLK_HZ / 4l)
#define PLX_DELAY_US(A)  DSP28x_usDelay( \
                                        ((((long double) A * \
                                           1000.0L) / \
                                          5.263158L) - 9.0L) / 5.0L)

PIL_Obj_t PilObj;
PIL_Handle_t PilHandle = 0;
// external mode helper symbols
PIL_CONFIG_DEF(uint32_t, ExtMode_targetFloat_Size, sizeof(Blinky_FloatType));
PIL_CONFIG_DEF(uint32_t, ExtMode_targetPointer_Size,
               sizeof(Blinky_FloatType*));
PIL_CONFIG_DEF(uint32_t, ExtMode_sampleTime_Ptr,
               (uint32_t)&Blinky_sampleTime);
PIL_CONFIG_DEF(uint32_t, ExtMode_checksum_Ptr, (uint32_t)&Blinky_checksum);
#if defined(Blinky_NumTunableParameters) && (Blinky_NumTunableParameters > 0)
PIL_CONFIG_DEF(uint32_t, ExtMode_P_Ptr, (uint32_t)&Blinky_P);
PIL_CONFIG_DEF(uint32_t, ExtMode_P_Size,
               (uint32_t)Blinky_NumTunableParameters);
#endif
#if defined(Blinky_NumExtModeSignals) && (Blinky_NumExtModeSignals > 0)
PIL_CONFIG_DEF(uint32_t, ExtMode_ExtModeSignals_Ptr,
               (uint32_t)&Blinky_ExtModeSignals[0]);
PIL_CONFIG_DEF(uint32_t, ExtMode_ExtModeSignals_Size,
               (uint32_t)Blinky_NumExtModeSignals);
#endif

#define CODE_GUID {0x09, 0x3c, 0x97, 0x5e, 0xdb, 0x2d, 0xb8, 0x40};
PIL_CONST_DEF(unsigned char, Guid[], CODE_GUID);
PIL_CONST_DEF(unsigned char, CompiledDate[], "08/04/2025 11:03 PM");
PIL_CONST_DEF(unsigned char, CompiledBy[], "PLECS Coder");
PIL_CONST_DEF(uint16_t, FrameworkVersion, PIL_FRAMEWORK_VERSION);
PIL_CONST_DEF(char, FirmwareDescription[], "TIC2000 Project (CPU0)");
PIL_CONST_DEF(uint16_t, StationAddress, 0);
PIL_CONST_DEF(uint32_t, BaudRate, 115200);
static void SciPoll(PIL_Handle_t aHandle)
{
   PLXHAL_SCI_handleBreak(0);

   while(PLXHAL_SCI_rxIsReady(0))
   {
      // assuming that there will be a "break" when FIFO is empty
      PIL_SERIAL_IN(aHandle, (int16) PLXHAL_SCI_getChar(0));
   }
   int16_t ch;
   if(!PLXHAL_SCI_txIsBusy(0))
   {
      if(PIL_SERIAL_OUT(aHandle, &ch))
      {
         PLXHAL_SCI_putChar(0, ch);
      }
   }
}

#pragma DATA_SECTION(ScopeBuffer, "scope")
uint16_t ScopeBuffer[1000] /*__attribute__((aligned(16)))*/;
extern void PIL_setAndConfigScopeBuffer(PIL_Handle_t aPilHandle,
                                        uint16_t* aBufPtr, uint16_t aBufSize,
                                        uint16_t aMaxTraceWidthInWords);
extern const char * const Blinky_checksum;

uint16_t ScopeFlagCpuRemote;
#pragma DATA_SECTION(ScopeFlagCpuRemote, "scopeflag_remote")
#pragma RETAIN(ScopeFlagCpuRemote)
uint16_t ScopeFlagCpuThis;
#pragma DATA_SECTION(ScopeFlagCpuThis, "scopeflag_local")
#pragma RETAIN(ScopeFlagCpuThis)
PIL_SYMBOL_DEF(ScopeFlagCpuRemote, 0, 1.0, "");
PIL_SYMBOL_DEF(ScopeFlagCpuThis, 0, 1.0, "");
extern void PIL_setAndConfigureScopeIndicator(PIL_Handle_t aPilHandle,
                                              uint16_t* aIndicatorPtr);

PLX_SCI_Obj_t SciObjs[1];
PLX_SCI_Handle_t SciHandles[1];

uint16_t PLXHAL_SCI_getChar(int16_t aChannel)
{
   return PLX_SCI_getChar(SciHandles[aChannel]);
}

void PLXHAL_SCI_putChar(int16_t aChannel, uint16_t data)
{
   PLX_SCI_putChar(SciHandles[aChannel], data);
}

void PLXHAL_SCI_putStr(int16_t aChannel, uint16_t *str)
{
   for (int i = 0; i < strlen((char *)str); i++)
   {
      PLXHAL_SCI_putChar(aChannel, str[i]);
   }
}

bool PLXHAL_SCI_rxIsReady(int16_t aChannel)
{
   return PLX_SCI_rxReady(SciHandles[aChannel]);
}

bool PLXHAL_SCI_txIsBusy(int16_t aChannel)
{
   return PLX_SCI_txIsBusy(SciHandles[aChannel]);
}

void PLXHAL_SCI_handleBreak(int16_t aChannel)
{
   if(PLX_SCI_breakOccurred(SciHandles[aChannel]))
   {
      PLX_SCI_reset(SciHandles[aChannel]);
   }
}

PLX_DIO_Handle_t DoutHandles[1];
PLX_DIO_Obj_t DoutObj[1];

void PLXHAL_DIO_set(uint16_t aHandle, bool aVal)
{
   PLX_DIO_set(DoutHandles[aHandle], aVal);
}

interrupt void Blinky_baseTaskInterrupt(void)
{
   CpuTimer0Regs.TCR.bit.TIF = 1;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
   IER |= M_INT1;
   DISPR_dispatch();
}


void PIL_setErrorMessage(PIL_Handle_t aPilHandle, const char* aMessage);
extern const char * Blinky_errorStatus;

extern PIL_Handle_t PilHandle;
DISPR_TaskObj_t TaskObj[1];
extern void Blinky_step();
extern void Blinky_enableTasksInterrupt();
extern void Blinky_syncTimers();
static void Tasks(bool aInit, void * const aParam)
{
   if(Blinky_errorStatus)
   {
      PIL_setErrorMessage(PilHandle, Blinky_errorStatus);
      return;
   }
   if(aInit)
   {
      Blinky_enableTasksInterrupt();
   }
   else
   {
      Blinky_step();
   }
}



/* Interrupt Enable Code */
void Blinky_enableTasksInterrupt(void)
{
   IER |= M_INT1;
}

/* Timer Synchronization Code */
void Blinky_syncTimers(void)
{
   CpuTimer0Regs.TCR.bit.TSS = 0;
}

/* Background tasks */
void Blinky_background(void)
{

}
/* HAL Initialization Code */
static bool HalInitialized = false;
void Blinky_initHal()
{
   if(HalInitialized == true)
   {
      return;
   }
   HalInitialized = true;
   // Pre init code
   {
      uint32_t sysPllConfig = PLX_DEVICE_SETCLOCK_CFG;
      DevInit(sysPllConfig);
      SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_4);

      PLX_ASSERT(SysCtl_getClock(10000000) == SYSCLK_HZ);
      PLX_ASSERT(SysCtl_getLowSpeedClock(10000000) == LSPCLK_HZ);
   }
   InitFlashHz(SYSCLK_WC_HI_HZ);
   // set cpu timers to same clock as ePWM
   CpuTimer0Regs.TPR.all = 1;
   CpuTimer1Regs.TPR.all = 1;
   CpuTimer2Regs.TPR.all = 1;
   EALLOW;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1;
   CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;  // stop all the TB clocks on the local cpu
   CpuSysRegs.PCLKCR0.bit.GTBCLKSYNC = 0;  // stop all the TB clocks
   ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1;
   EDIS;

   PilHandle = PIL_init(&PilObj, sizeof(PilObj));
   PIL_setGuid(PilHandle, PIL_GUID_PTR);
   PIL_setChecksum(PilHandle, Blinky_checksum);
   PIL_setAndConfigScopeBuffer(PilHandle, (uint16_t *)&ScopeBuffer, 1000, 0);
   PIL_setAndConfigureScopeIndicator(PilHandle, &ScopeFlagCpuThis);
   PIL_setNodeAddress(PilHandle, PIL_D_StationAddress);

   PIL_setSerialComCallback(PilHandle, (PIL_CommCallbackPtr_t)SciPoll);
   {
      for(int i=0; i < 1; i++)
      {
         SciHandles[i] =
            PLX_SCI_init(&SciObjs[i],
                         sizeof(SciObjs[i]));
      }
   }

   PLX_SCI_configure(SciHandles[0],
                     PLX_SCI_SCI_A, 47500000);

   (void)PLX_SCI_setupPort(SciHandles[0], 115200);
   {
      // early system configuration
      PLX_DIO_sinit();
   }
   PLX_DIO_sinit();
   for (int i = 0; i < 1; i++)
   {
      DoutHandles[i] = PLX_DIO_init(&DoutObj[i], sizeof(DoutObj[i]));
   }

   {
      PLX_DIO_OutputProperties_t props = {
         0
      };

      props.enableInvert = false;
      PLX_DIO_configureOut(DoutHandles[0], 34,  &props);
   }

   {
      CpuTimer0Regs.TCR.bit.TSS = 1; // stop timer
      CpuTimer0Regs.TPRH.all = 0;
      CpuTimer0Regs.PRD.all = 9500 - 1;
      CpuTimer0Regs.TCR.bit.TRB = 1; // reload period
      CpuTimer0Regs.TCR.bit.TIE = 1; // enable trigger to SOC/interrupt
      PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
      EALLOW;
      PieVectTable.TIMER0_INT = &Blinky_baseTaskInterrupt;
      EDIS;
      PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
      PieCtrlRegs.PIEACK.all = PIEACK_GROUP1; // acknowledge interrupt to PIE

   }
   DISPR_sinit();
   DISPR_configure((uint32_t)(9500), PilHandle, &TaskObj[0],
                   sizeof(TaskObj)/sizeof(DISPR_TaskObj_t));
   DISPR_registerIdleTask(&Blinky_background);
   DISPR_registerSyncCallback(&Blinky_syncTimers);
   DISPR_setPowerupDelay(10);
   {
      static int taskId = 0;
      // Task 0 at 1.000000e+04 Hz
      DISPR_registerTask(0, &Tasks, 9500L, (void *)&taskId);
   }

   // Post init code (for modules that depend on other modules)

   {
      // late system configuration
      GPIO_setPadConfig(34, GPIO_PIN_TYPE_STD);
      GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);
      GPIO_setPinConfig(GPIO_43_SCIRXDA);
      GPIO_setPinConfig(GPIO_42_SCITXDA);
   }
}
