// -*- C++ -*-
// VisualBoyAdvance - Nintendo Gameboy/GameboyAdvance (TM) emulator.
// Copyright (C) 1999-2003 Forgotten
// Copyright (C) 2004 Forgotten and the VBA development team

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or(at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#ifdef ARM_CORE
#include "thumb-pre.h"
#else
#ifdef C_CORE
#define NEG(i) ((i) >> 31)
#define POS(i) ((~(i)) >> 31)
#define ADDCARRY(a, b, c) \
  C_FLAG = ((NEG(a) & NEG(b)) |\
            (NEG(a) & POS(c)) |\
            (NEG(b) & POS(c))) ? true : false;
#define ADDOVERFLOW(a, b, c) \
  V_FLAG = ((NEG(a) & NEG(b) & POS(c)) |\
            (POS(a) & POS(b) & NEG(c))) ? true : false;
#define SUBCARRY(a, b, c) \
  C_FLAG = ((NEG(a) & POS(b)) |\
            (NEG(a) & POS(c)) |\
            (POS(b) & POS(c))) ? true : false;
#define SUBOVERFLOW(a, b, c)\
  V_FLAG = ((NEG(a) & POS(b) & POS(c)) |\
            (POS(a) & NEG(b) & NEG(c))) ? true : false;
#define ADD_RD_RS_RN \
   {\
     u32 lhs = reg[source].I;\
     u32 rhs = value;\
     u32 res = lhs + rhs;\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     ADDCARRY(lhs, rhs, res);\
     ADDOVERFLOW(lhs, rhs, res);\
   }
#define ADD_RD_RS_O3 \
   {\
     u32 lhs = reg[source].I;\
     u32 rhs = value;\
     u32 res = lhs + rhs;\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     ADDCARRY(lhs, rhs, res);\
     ADDOVERFLOW(lhs, rhs, res);\
   }
#define ADD_RN_O8(d) \
   {\
     u32 lhs = reg[(d)].I;\
     u32 rhs = (opcode & 255);\
     u32 res = lhs + rhs;\
     reg[(d)].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     ADDCARRY(lhs, rhs, res);\
     ADDOVERFLOW(lhs, rhs, res);\
   }
#define CMN_RD_RS \
   {\
     u32 lhs = reg[dest].I;\
     u32 rhs = value;\
     u32 res = lhs + rhs;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     ADDCARRY(lhs, rhs, res);\
     ADDOVERFLOW(lhs, rhs, res);\
   }
#define ADC_RD_RS \
   {\
     u32 lhs = reg[dest].I;\
     u32 rhs = value;\
     u32 res = lhs + rhs + (u32)C_FLAG;\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     ADDCARRY(lhs, rhs, res);\
     ADDOVERFLOW(lhs, rhs, res);\
   }
#define SUB_RD_RS_RN \
   {\
     u32 lhs = reg[source].I;\
     u32 rhs = value;\
     u32 res = lhs - rhs;\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(lhs, rhs, res);\
     SUBOVERFLOW(lhs, rhs, res);\
   }
#define SUB_RD_RS_O3 \
   {\
     u32 lhs = reg[source].I;\
     u32 rhs = value;\
     u32 res = lhs - rhs;\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(lhs, rhs, res);\
     SUBOVERFLOW(lhs, rhs, res);\
   }
#define SUB_RN_O8(d) \
   {\
     u32 lhs = reg[(d)].I;\
     u32 rhs = (opcode & 255);\
     u32 res = lhs - rhs;\
     reg[(d)].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(lhs, rhs, res);\
     SUBOVERFLOW(lhs, rhs, res);\
   }
#define CMP_RN_O8(d) \
   {\
     u32 lhs = reg[(d)].I;\
     u32 rhs = (opcode & 255);\
     u32 res = lhs - rhs;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(lhs, rhs, res);\
     SUBOVERFLOW(lhs, rhs, res);\
   }
#define SBC_RD_RS \
   {\
     u32 lhs = reg[dest].I;\
     u32 rhs = value;\
     u32 res = lhs - rhs - !((u32)C_FLAG);\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(lhs, rhs, res);\
     SUBOVERFLOW(lhs, rhs, res);\
   }
#define LSL_RD_RM_I5 \
   {\
     C_FLAG = (reg[source].I >> (32 - shift)) & 1 ? true : false;\
     value = reg[source].I << shift;\
   }
#define LSL_RD_RS \
   {\
     C_FLAG = (reg[dest].I >> (32 - value)) & 1 ? true : false;\
     value = reg[dest].I << value;\
   }
#define LSR_RD_RM_I5 \
   {\
     C_FLAG = (reg[source].I >> (shift - 1)) & 1 ? true : false;\
     value = reg[source].I >> shift;\
   }
#define LSR_RD_RS \
   {\
     C_FLAG = (reg[dest].I >> (value - 1)) & 1 ? true : false;\
     value = reg[dest].I >> value;\
   }
#define ASR_RD_RM_I5 \
   {\
     C_FLAG = ((s32)reg[source].I >> (int)(shift - 1)) & 1 ? true : false;\
     value = (s32)reg[source].I >> (int)shift;\
   }
#define ASR_RD_RS \
   {\
     C_FLAG = ((s32)reg[dest].I >> (int)(value - 1)) & 1 ? true : false;\
     value = (s32)reg[dest].I >> (int)value;\
   }
#define ROR_RD_RS \
   {\
     C_FLAG = (reg[dest].I >> (value - 1)) & 1 ? true : false;\
     value = ((reg[dest].I << (32 - value)) |\
              (reg[dest].I >> value));\
   }
#define NEG_RD_RS \
   {\
     u32 lhs = reg[source].I;\
     u32 rhs = 0;\
     u32 res = rhs - lhs;\
     reg[dest].I = res;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(rhs, lhs, res);\
     SUBOVERFLOW(rhs, lhs, res);\
   }
#define CMP_RD_RS \
   {\
     u32 lhs = reg[dest].I;\
     u32 rhs = value;\
     u32 res = lhs - rhs;\
     Z_FLAG = (res == 0) ? true : false;\
     N_FLAG = NEG(res) ? true : false;\
     SUBCARRY(lhs, rhs, res);\
     SUBOVERFLOW(lhs, rhs, res);\
   }
#else
#ifdef __GNUC__
#ifdef __POWERPC__
            #define ADD_RD_RS_RN \
            {										\
                register int Flags;					\
                register int Result;				\
                asm volatile("addco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[source].I), 	\
                              "r" (value)			\
                            );						\
                reg[dest].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define ADD_RD_RS_O3 ADD_RD_RS_RN
            #define ADD_RN_O8(d) \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("addco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[(d)].I), 	\
                              "r" (opcode & 255)	\
                            );						\
                reg[(d)].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define CMN_RD_RS \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("addco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[dest].I), 	\
                              "r" (value)			\
                            );						\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define ADC_RD_RS \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("mtspr xer, %4\n"		\
                             "addeo. %0, %2, %3\n"	\
                             "mcrxr cr1\n"			\
                             "mfcr	%1\n"			\
                             : "=r" (Result),		\
                               "=r" (Flags)			\
                             : "r" (reg[dest].I),	\
                               "r" (value),			\
                               "r" (C_FLAG << 29)	\
                             );						\
                reg[dest].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define SUB_RD_RS_RN \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("subco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[source].I), 	\
                              "r" (value)			\
                            );						\
                reg[dest].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define SUB_RD_RS_O3 SUB_RD_RS_RN
            #define SUB_RN_O8(d) \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("subco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[(d)].I), 	\
                              "r" (opcode & 255)	\
                            );						\
                reg[(d)].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define CMP_RN_O8(d) \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("subco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[(d)].I), 	\
                              "r" (opcode & 255)	\
                            );						\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define SBC_RD_RS \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("mtspr xer, %4\n"		\
                             "subfeo. %0, %3, %2\n"	\
                             "mcrxr cr1\n"			\
                             "mfcr	%1\n"			\
                             : "=r" (Result),		\
                               "=r" (Flags)			\
                             : "r" (reg[dest].I),	\
                               "r" (value),			\
                               "r" (C_FLAG << 29) 	\
                             );						\
                reg[dest].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define LSL_RD_RM_I5 \
            {\
                C_FLAG = (reg[source].I >> (32 - shift)) & 1 ? true : false;\
                value = reg[source].I << shift;\
            }
            #define LSL_RD_RS \
            {\
                C_FLAG = (reg[dest].I >> (32 - value)) & 1 ? true : false;\
                value = reg[dest].I << value;\
            }
            #define LSR_RD_RM_I5 \
            {\
                C_FLAG = (reg[source].I >> (shift - 1)) & 1 ? true : false;\
                value = reg[source].I >> shift;\
            }
            #define LSR_RD_RS \
            {\
                C_FLAG = (reg[dest].I >> (value - 1)) & 1 ? true : false;\
                value = reg[dest].I >> value;\
            }
            #define ASR_RD_RM_I5 \
            {\
                C_FLAG = ((s32)reg[source].I >> (int)(shift - 1)) & 1 ? true : false;\
                value = (s32)reg[source].I >> (int)shift;\
            }
            #define ASR_RD_RS \
            {\
                C_FLAG = ((s32)reg[dest].I >> (int)(value - 1)) & 1 ? true : false;\
                value = (s32)reg[dest].I >> (int)value;\
            }
            #define ROR_RD_RS \
            {\
                C_FLAG = (reg[dest].I >> (value - 1)) & 1 ? true : false;\
                value = ((reg[dest].I << (32 - value)) |\
                        (reg[dest].I >> value));\
            }
            #define NEG_RD_RS \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("subfco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[source].I), 	\
                              "r" (0)				\
                            );						\
                reg[dest].I = Result;				\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
            #define CMP_RD_RS \
            {\
                register int Flags;					\
                register int Result;				\
                asm volatile("subco. %0, %2, %3\n"	\
                            "mcrxr cr1\n"			\
                            "mfcr %1\n"				\
                            : "=r" (Result), 		\
                              "=r" (Flags)			\
                            : "r" (reg[dest].I), 	\
                              "r" (value)			\
                            );						\
                Z_FLAG = (Flags >> 29) & 1;			\
                N_FLAG = (Flags >> 31) & 1;			\
                C_FLAG = (Flags >> 25) & 1;			\
                V_FLAG = (Flags >> 26) & 1;			\
            }
#else
#define ADD_RD_RS_RN \
     asm ("add %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setcb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[dest].I)\
          : "r" (value), "b" (reg[source].I));
#define ADD_RD_RS_O3 \
     asm ("add %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setcb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[dest].I)\
          : "r" (value), "b" (reg[source].I));
#define ADD_RN_O8(d) \
     asm ("add %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setcb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[(d)].I)\
          : "r" (opcode & 255), "b" (reg[(d)].I));
#define CMN_RD_RS \
     asm ("add %0, %1;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setcb C_FLAG;"\
          "setob V_FLAG;"\
          : \
          : "r" (value), "r" (reg[dest].I):"1");
#define ADC_RD_RS \
     asm ("bt $0, C_FLAG;"\
          "adc %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setcb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[dest].I)\
          : "r" (value), "b" (reg[dest].I));
#define SUB_RD_RS_RN \
     asm ("sub %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setncb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[dest].I)\
          : "r" (value), "b" (reg[source].I));
#define SUB_RD_RS_O3 \
     asm ("sub %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setncb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[dest].I)\
          : "r" (value), "b" (reg[source].I));
#define SUB_RN_O8(d) \
     asm ("sub %1, %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setncb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[(d)].I)\
          : "r" (opcode & 255), "b" (reg[(d)].I));
#define CMP_RN_O8(d) \
     asm ("sub %0, %1;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setncb C_FLAG;"\
          "setob V_FLAG;"\
          : \
          : "r" (opcode & 255), "r" (reg[(d)].I) : "1");
#define SBC_RD_RS \
     asm volatile ("bt $0, C_FLAG;"\
                   "cmc;"\
                   "sbb %1, %%ebx;"\
                   "setsb N_FLAG;"\
                   "setzb Z_FLAG;"\
                   "setncb C_FLAG;"\
                   "setob V_FLAG;"\
                   : "=b" (reg[dest].I)\
                   : "r" (value), "b" (reg[dest].I) : "cc", "memory");
#define LSL_RD_RM_I5 \
       asm ("shl %%cl, %%eax;"\
            "setcb C_FLAG;"\
            : "=a" (value)\
            : "a" (reg[source].I), "c" (shift));
#define LSL_RD_RS \
         asm ("shl %%cl, %%eax;"\
              "setcb C_FLAG;"\
              : "=a" (value)\
              : "a" (reg[dest].I), "c" (value));
#define LSR_RD_RM_I5 \
       asm ("shr %%cl, %%eax;"\
            "setcb C_FLAG;"\
            : "=a" (value)\
            : "a" (reg[source].I), "c" (shift));
#define LSR_RD_RS \
         asm ("shr %%cl, %%eax;"\
              "setcb C_FLAG;"\
              : "=a" (value)\
              : "a" (reg[dest].I), "c" (value));
#define ASR_RD_RM_I5 \
     asm ("sar %%cl, %%eax;"\
          "setcb C_FLAG;"\
          : "=a" (value)\
          : "a" (reg[source].I), "c" (shift));
#define ASR_RD_RS \
         asm ("sar %%cl, %%eax;"\
              "setcb C_FLAG;"\
              : "=a" (value)\
              : "a" (reg[dest].I), "c" (value));
#define ROR_RD_RS \
         asm ("ror %%cl, %%eax;"\
              "setcb C_FLAG;"\
              : "=a" (value)\
              : "a" (reg[dest].I), "c" (value));
#define NEG_RD_RS \
     asm ("neg %%ebx;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setncb C_FLAG;"\
          "setob V_FLAG;"\
          : "=b" (reg[dest].I)\
          : "b" (reg[source].I));
#define CMP_RD_RS \
     asm ("sub %0, %1;"\
          "setsb N_FLAG;"\
          "setzb Z_FLAG;"\
          "setncb C_FLAG;"\
          "setob V_FLAG;"\
          : \
          : "r" (value), "r" (reg[dest].I):"1");
#endif
#else
#define ADD_RD_RS_RN \
   {\
     __asm mov eax, source\
     __asm mov ebx, dword ptr [OFFSET reg+4*eax]\
     __asm add ebx, value\
     __asm mov eax, dest\
     __asm mov dword ptr [OFFSET reg+4*eax], ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define ADD_RD_RS_O3 \
   {\
     __asm mov eax, source\
     __asm mov ebx, dword ptr [OFFSET reg+4*eax]\
     __asm add ebx, value\
     __asm mov eax, dest\
     __asm mov dword ptr [OFFSET reg+4*eax], ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define ADD_RN_O8(d) \
   {\
     __asm mov ebx, opcode\
     __asm and ebx, 255\
     __asm add dword ptr [OFFSET reg+4*(d)], ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define CMN_RD_RS \
     {\
       __asm mov eax, dest\
       __asm mov ebx, dword ptr [OFFSET reg+4*eax]\
       __asm add ebx, value\
       __asm sets byte ptr N_FLAG\
       __asm setz byte ptr Z_FLAG\
       __asm setc byte ptr C_FLAG\
       __asm seto byte ptr V_FLAG\
     }
#define ADC_RD_RS \
     {\
       __asm mov ebx, dest\
       __asm mov ebx, dword ptr [OFFSET reg+4*ebx]\
       __asm bt word ptr C_FLAG, 0\
       __asm adc ebx, value\
       __asm mov eax, dest\
       __asm mov dword ptr [OFFSET reg+4*eax], ebx\
       __asm sets byte ptr N_FLAG\
       __asm setz byte ptr Z_FLAG\
       __asm setc byte ptr C_FLAG\
       __asm seto byte ptr V_FLAG\
     }
#define SUB_RD_RS_RN \
   {\
     __asm mov eax, source\
     __asm mov ebx, dword ptr [OFFSET reg+4*eax]\
     __asm sub ebx, value\
     __asm mov eax, dest\
     __asm mov dword ptr [OFFSET reg+4*eax], ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setnc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define SUB_RD_RS_O3 \
   {\
     __asm mov eax, source\
     __asm mov ebx, dword ptr [OFFSET reg+4*eax]\
     __asm sub ebx, value\
     __asm mov eax, dest\
     __asm mov dword ptr [OFFSET reg+4*eax], ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setnc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define SUB_RN_O8(d) \
   {\
     __asm mov ebx, opcode\
     __asm and ebx, 255\
     __asm sub dword ptr [OFFSET reg + 4*(d)], ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setnc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define CMP_RN_O8(d) \
   {\
     __asm mov eax, dword ptr [OFFSET reg+4*(d)]\
     __asm mov ebx, opcode\
     __asm and ebx, 255\
     __asm sub eax, ebx\
     __asm sets byte ptr N_FLAG\
     __asm setz byte ptr Z_FLAG\
     __asm setnc byte ptr C_FLAG\
     __asm seto byte ptr V_FLAG\
   }
#define SBC_RD_RS \
     {\
       __asm mov ebx, dest\
       __asm mov ebx, dword ptr [OFFSET reg + 4*ebx]\
       __asm mov eax, value\
       __asm bt word ptr C_FLAG, 0\
       __asm cmc\
       __asm sbb ebx, eax\
       __asm mov eax, dest\
       __asm mov dword ptr [OFFSET reg + 4*eax], ebx\
       __asm sets byte ptr N_FLAG\
       __asm setz byte ptr Z_FLAG\
       __asm setnc byte ptr C_FLAG\
       __asm seto byte ptr V_FLAG\
     }
#define LSL_RD_RM_I5 \
     {\
       __asm mov eax, source\
       __asm mov eax, dword ptr [OFFSET reg + 4 * eax]\
       __asm mov cl, byte ptr shift\
       __asm shl eax, cl\
       __asm mov value, eax\
       __asm setc byte ptr C_FLAG\
     }
#define LSL_RD_RS \
         {\
           __asm mov eax, dest\
           __asm mov eax, dword ptr [OFFSET reg + 4 * eax]\
           __asm mov cl, byte ptr value\
           __asm shl eax, cl\
           __asm mov value, eax\
           __asm setc byte ptr C_FLAG\
         }
#define LSR_RD_RM_I5 \
     {\
       __asm mov eax, source\
       __asm mov eax, dword ptr [OFFSET reg + 4 * eax]\
       __asm mov cl, byte ptr shift\
       __asm shr eax, cl\
       __asm mov value, eax\
       __asm setc byte ptr C_FLAG\
     }
#define LSR_RD_RS \
         {\
           __asm mov eax, dest\
           __asm mov eax, dword ptr [OFFSET reg + 4 * eax]\
           __asm mov cl, byte ptr value\
           __asm shr eax, cl\
           __asm mov value, eax\
           __asm setc byte ptr C_FLAG\
         }
#define ASR_RD_RM_I5 \
     {\
       __asm mov eax, source\
       __asm mov eax, dword ptr [OFFSET reg + 4*eax]\
       __asm mov cl, byte ptr shift\
       __asm sar eax, cl\
       __asm mov value, eax\
       __asm setc byte ptr C_FLAG\
     }
#define ASR_RD_RS \
         {\
           __asm mov eax, dest\
           __asm mov eax, dword ptr [OFFSET reg + 4*eax]\
           __asm mov cl, byte ptr value\
           __asm sar eax, cl\
           __asm mov value, eax\
           __asm setc byte ptr C_FLAG\
         }
#define ROR_RD_RS \
         {\
           __asm mov eax, dest\
           __asm mov eax, dword ptr [OFFSET reg + 4*eax]\
           __asm mov cl, byte ptr value\
           __asm ror eax, cl\
           __asm mov value, eax\
           __asm setc byte ptr C_FLAG\
         }
#define NEG_RD_RS \
     {\
       __asm mov ebx, source\
       __asm mov ebx, dword ptr [OFFSET reg+4*ebx]\
       __asm neg ebx\
       __asm mov eax, dest\
       __asm mov dword ptr [OFFSET reg+4*eax],ebx\
       __asm sets byte ptr N_FLAG\
       __asm setz byte ptr Z_FLAG\
       __asm setnc byte ptr C_FLAG\
       __asm seto byte ptr V_FLAG\
     }
#define CMP_RD_RS \
     {\
       __asm mov eax, dest\
       __asm mov ebx, dword ptr [OFFSET reg+4*eax]\
       __asm sub ebx, value\
       __asm sets byte ptr N_FLAG\
       __asm setz byte ptr Z_FLAG\
       __asm setnc byte ptr C_FLAG\
       __asm seto byte ptr V_FLAG\
     }
#endif
#endif
#endif

