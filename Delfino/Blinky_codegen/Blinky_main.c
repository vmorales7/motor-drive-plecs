/*
   Copyright (c) 2019-2021 by Plexim GmbH
   All rights reserved.

   A free license is granted to anyone to use this software for any legal
   non safety-critical purpose, including commercial applications, provided
   that:
   1) IT IS NOT USED TO DIRECTLY OR INDIRECTLY COMPETE WITH PLEXIM, and
   2) THIS COPYRIGHT NOTICE IS PRESERVED in its entirety.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
 */

#include "includes.h"

#include "plx_dispatcher.h"



extern volatile unsigned int IFR;
extern volatile unsigned int IER;

// function prototypes
extern void MemCopy(Uint16 *SourceAddr, Uint16 *SourceEndAddr, Uint16 *DestAddr);

// linker addresses, needed to copy code from flash to ram
extern Uint16 RamfuncsLoadStart, RamfuncsLoadEnd, RamfuncsRunStart;

void Blinky_initialize();

#define TSP_VER 0x0110
#ifdef TSP_VER
#if (TSP_VER != THIS_TSP_VER)
#error TSP Version mismatch.
#endif
#endif

void main(void)
{
#ifdef _FLASH
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
#endif

    // Initialize CPU-to-CPU MSG RAM used for IPC
    EALLOW;
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCPU != 1){}
    EDIS;

    // disable all interrupts
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    
    Blinky_initialize();

    // enable interrupts
    EINT;   // global
    ERTM;   // real-time

    // go!
    DISPR_start(); // will not return

    PLX_ASSERT(0); // should never get here
}

