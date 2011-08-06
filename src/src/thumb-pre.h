/*
 * ===========================================================================
 *
 *       Filename:  thumb-pre.h
 *
 *    Description:  Thumb ARM implementations
 *
 *        Version:  1.0
 *        Created:  01/19/2010 02:37:32 AM
 *
 *         Author:  Will Dietz (WD), w@wdtz.org
 *        Company:  dtzTech
 *
 * ===========================================================================
 */

#include <stdio.h>

/*
 * similar to arm-new-pre.h, this file contains
 * the c implementation, the x86 implementation, and a
 * WIP arm implementation.
 * This is for my own convenience, and to assist the porting
 * and catching of bugs, even if it's a bit cluttered.
 */

#include "arm-common.h"

/*-----------------------------------------------------------------------------
 *  Thumb macro definitions
 *  Note that we aren't actually using host thumb mode
 *-----------------------------------------------------------------------------*/



//=============================================================================
#define ADD_RD_RS_RN ADD_RD_RS_RN_impl(dest, source, value)
static inline void ADD_RD_RS_RN_impl(u32 dest, u32 source, u32 value)
{
  asm( "adds %0, %6, %5;"
       GETCONDFLAGS(%1, %2, %3, %4)
       : "=r" (reg[dest].I),
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG)
       : "r" (value), "r" (reg[source].I)
       : GETCONDFLAGS_REGS );
}
//static inline void ADD_RD_RS_RN_impl(u32 dest, u32 source, u32 value)
//{
//   {\
//     u32 lhs = reg[source].I;\
//     u32 rhs = value;\
//     u32 res = lhs + rhs;\
//     reg[dest].I = res;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     ADDCARRY(lhs, rhs, res);\
//     ADDOVERFLOW(lhs, rhs, res);\
//   }
//}
//static inline void ADD_RD_RS_RN_impl(u32 dest, u32 source, u32 value)
//{
//     asm ("add %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setcb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[dest].I)\
//          : "r" (value), "b" (reg[source].I));
//}
//=============================================================================
#define ADD_RD_RS_O3 ADD_RD_RS_O3_impl(dest, source, value)
static inline void ADD_RD_RS_O3_impl(u32 dest, u32 source, u32 value)
{
     asm( "adds %0, %6, %5;" \
     GETCONDFLAGS(%1, %2, %3, %4) \
       : "=r" (reg[dest].I), \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (value), "r" (reg[source].I) \
       : GETCONDFLAGS_REGS );
}
//#define ADD_RD_RS_O3 ADD_RD_RS_O3_impl(dest, source, value)
//static inline void ADD_RD_RS_O3_impl(u32 dest, u32 source, u32 value)
//{
//   {\
//     u32 lhs = reg[source].I;\
//     u32 rhs = value;\
//     u32 res = lhs + rhs;\
//     reg[dest].I = res;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     ADDCARRY(lhs, rhs, res);\
//     ADDOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define ADD_RD_RS_O3 ADD_RD_RS_O3_impl(dest, source, value)
//static inline void ADD_RD_RS_O3_impl(u32 dest, u32 source, u32 value)
//{
//     asm ("add %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setcb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[dest].I)\
//          : "r" (value), "b" (reg[source].I));
//}
//=============================================================================
#define ADD_RN_O8(d) ADD_RN_O8_impl(opcode, d)
static inline void ADD_RN_O8_impl(u32 opcode, u32 d)
{
     asm( "adds %0, %6, %5;" \
     GETCONDFLAGS(%1, %2, %3, %4) \
       : "=r" (reg[(d)].I), \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (opcode & 255), "r" (reg[(d)].I) \
       : GETCONDFLAGS_REGS );
}
//#define ADD_RN_O8(d) ADD_RN_O8_impl(opcode, d)
//static inline void ADD_RN_O8_impl(u32 opcode, u32 d)
//{
//   {\
//     u32 lhs = reg[(d)].I;\
//     u32 rhs = (opcode & 255);\
//     u32 res = lhs + rhs;\
//     reg[(d)].I = res;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     ADDCARRY(lhs, rhs, res);\
//     ADDOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define ADD_RN_O8(d) ADD_RN_O8_impl(opcode, d)
//static inline void ADD_RN_O8_impl(u32 opcode, u32 d)
//{
//     asm ("add %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setcb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[(d)].I)\
//          : "r" (opcode & 255), "b" (reg[(d)].I));
//}
//=============================================================================
#define CMN_RD_RS CMN_RD_RS_impl(dest, value)
static inline void CMN_RD_RS_impl(u32 dest, u32 value)
{
    asm ( "cmn %5, %4;" \
     GETCONDFLAGS(%0, %1, %2, %3) \
       : \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (value), "r" (reg[dest].I) \
       : GETCONDFLAGS_REGS );
}
//#define CMN_RD_RS CMN_RD_RS_impl(dest, value)
//static inline void CMN_RD_RS_impl(u32 dest, u32 value)
//{
//   {\
//     u32 lhs = reg[dest].I;\
//     u32 rhs = value;\
//     u32 res = lhs + rhs;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     ADDCARRY(lhs, rhs, res);\
//     ADDOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define CMN_RD_RS CMN_RD_RS_impl(dest, value)
//static inline void CMN_RD_RS_impl(u32 dest, u32 value)
//{
//     asm ("add %0, %1;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setcb C_FLAG;"\
//          "setob V_FLAG;"\
//          : \
//          : "r" (value), "r" (reg[dest].I):"1");
//}
//=============================================================================
#define ADC_RD_RS ADC_RD_RS_impl(dest, value)
static inline void ADC_RD_RS_impl(u32 dest, u32 value)
{
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
}
//#define ADC_RD_RS ADC_RD_RS_impl(dest, value)
//static inline void ADC_RD_RS_impl(u32 dest, u32 value)
//{
//     asm ("bt $0, C_FLAG;"\
//          "adc %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setcb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[dest].I)\
//          : "r" (value), "b" (reg[dest].I));
//}
//=============================================================================
#define SUB_RD_RS_RN SUB_RD_RS_RN_impl(dest, source, value)
static inline void SUB_RD_RS_RN_impl(u32 dest, u32 source, u32 value)
{
     asm( "subs %0, %6, %5;" \
     GETCONDFLAGS(%1, %2, %3, %4) \
       : "=r" (reg[dest].I), \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (value), "r" (reg[source].I) \
       : GETCONDFLAGS_REGS );
}
//#define SUB_RD_RS_RN SUB_RD_RS_RN_impl(dest, source, value)
//static inline void SUB_RD_RS_RN_impl(u32 dest, u32 source, u32 value)
//{
//   {\
//     u32 lhs = reg[source].I;\
//     u32 rhs = value;\
//     u32 res = lhs - rhs;\
//     reg[dest].I = res;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     SUBCARRY(lhs, rhs, res);\
//     SUBOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define SUB_RD_RS_RN SUB_RD_RS_RN_impl(dest, source, value)
//static inline void SUB_RD_RS_RN_impl(u32 dest, u32 source, u32 value)
//{
//     asm ("sub %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setncb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[dest].I)\
//          : "r" (value), "b" (reg[source].I));
//}
//=============================================================================
#define SUB_RD_RS_O3 SUB_RD_RS_O3_impl(dest, source, value)
static inline void SUB_RD_RS_O3_impl(u32 dest, u32 source, u32 value)
{
     asm( "subs %0, %6, %5;" \
     GETCONDFLAGS(%1, %2, %3, %4) \
       : "=r" (reg[dest].I), \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (value), "r" (reg[source].I) \
       : GETCONDFLAGS_REGS );
}
//#define SUB_RD_RS_O3 SUB_RD_RS_O3_impl(dest, source, value)
//static inline void SUB_RD_RS_O3_impl(u32 dest, u32 source, u32 value)
//{
//   {\
//     u32 lhs = reg[source].I;\
//     u32 rhs = value;\
//     u32 res = lhs - rhs;\
//     reg[dest].I = res;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     SUBCARRY(lhs, rhs, res);\
//     SUBOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define SUB_RD_RS_O3 SUB_RD_RS_O3_impl(dest, source, value)
//static inline void SUB_RD_RS_O3_impl(u32 dest, u32 source, u32 value)
//{
//     asm ("sub %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setncb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[dest].I)\
//          : "r" (value), "b" (reg[source].I));
//}
//=============================================================================
#define SUB_RN_O8(d) SUB_RN_O8_impl(opcode, d)
static inline void SUB_RN_O8_impl(u32 opcode, u32 d)
{
     asm( "subs %0, %6, %5;" \
     GETCONDFLAGS(%1, %2, %3, %4) \
       : "=r" (reg[(d)].I), \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (opcode & 255), "r" (reg[(d)].I) \
       : GETCONDFLAGS_REGS );
}
//#define SUB_RN_O8(d) SUB_RN_O8_impl(opcode, d)
//static inline void SUB_RN_O8_impl(u32 opcode, u32 d)
//{
//   {\
//     u32 lhs = reg[(d)].I;\
//     u32 rhs = (opcode & 255);\
//     u32 res = lhs - rhs;\
//     reg[(d)].I = res;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     SUBCARRY(lhs, rhs, res);\
//     SUBOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define SUB_RN_O8(d) SUB_RN_O8_impl(opcode, d)
//static inline void SUB_RN_O8_impl(u32 opcode, u32 d)
//{
//     asm ("sub %1, %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setncb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[(d)].I)\
//          : "r" (opcode & 255), "b" (reg[(d)].I));
//}
//=============================================================================
#define CMP_RN_O8(d) CMP_RN_O8_impl(opcode, d)
static inline void CMP_RN_O8_impl(u32 opcode, u32 d)
{
    asm ( "cmp %5, %4;" \
     GETCONDFLAGS(%0, %1, %2, %3) \
       : \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (opcode & 255), "r" (reg[(d)].I) \
       : GETCONDFLAGS_REGS );
}
//#define CMP_RN_O8(d) CMP_RN_O8_impl(opcode, d)
//static inline void CMP_RN_O8_impl(u32 opcode, u32 d)
//{
//   {\
//     u32 lhs = reg[(d)].I;\
//     u32 rhs = (opcode & 255);\
//     u32 res = lhs - rhs;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     SUBCARRY(lhs, rhs, res);\
//     SUBOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define CMP_RN_O8(d) CMP_RN_O8_impl(opcode, d)
//static inline void CMP_RN_O8_impl(u32 opcode, u32 d)
//{
//     asm ("sub %0, %1;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setncb C_FLAG;"\
//          "setob V_FLAG;"\
//          : \
//          : "r" (opcode & 255), "r" (reg[(d)].I) : "1");
//}
//=============================================================================
#define SBC_RD_RS SBC_RD_RS_impl(dest, value)
static inline void SBC_RD_RS_impl(u32 dest, u32 value)
{
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
}
//#define SBC_RD_RS SBC_RD_RS_impl(dest, value)
//static inline void SBC_RD_RS_impl(u32 dest, u32 value)
//{
//     asm volatile ("bt $0, C_FLAG;"\
//                   "cmc;"\
//                   "sbb %1, %%ebx;"\
//                   "setsb N_FLAG;"\
//                   "setzb Z_FLAG;"\
//                   "setncb C_FLAG;"\
//                   "setob V_FLAG;"\
//                   : "=b" (reg[dest].I)\
//                   : "r" (value), "b" (reg[dest].I) : "cc", "memory");
//}
//=============================================================================
#define LSL_RD_RM_I5 LSL_RD_RM_I5_impl(value, source, shift)
static inline void LSL_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
{
    asm( "lsls %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[source].I), "r" (shift) );
}
//#define LSL_RD_RM_I5 LSL_RD_RM_I5_impl(value, source, shift)
//static inline void LSL_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
//{
//   {\
//     C_FLAG = (reg[source].I >> (32 - shift)) & 1 ? true : false;\
//     value = reg[source].I << shift;\
//   }
//}
//#define LSL_RD_RM_I5 LSL_RD_RM_I5_impl(value, source, shift)
//static inline void LSL_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
//{
//       asm ("shl %%cl, %%eax;"\
//            "setcb C_FLAG;"\
//            : "=a" (value)\
//            : "a" (reg[source].I), "c" (shift));
//}
//=============================================================================
#define LSL_RD_RS LSL_RD_RS_impl(value, dest)
static inline void LSL_RD_RS_impl(u32& value, u32 dest)
{
    asm( "lsls %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[dest].I), "r" (value) );
}
//#define LSL_RD_RS LSL_RD_RS_impl(value, dest)
//static inline void LSL_RD_RS_impl(u32& value, u32 dest)
//{
//   {\
//     C_FLAG = (reg[dest].I >> (32 - value)) & 1 ? true : false;\
//     value = reg[dest].I << value;\
//   }
//}
//#define LSL_RD_RS LSL_RD_RS_impl(value, dest)
//static inline void LSL_RD_RS_impl(u32& value, u32 dest)
//{
//         asm ("shl %%cl, %%eax;"\
//              "setcb C_FLAG;"\
//              : "=a" (value)\
//              : "a" (reg[dest].I), "c" (value));
//}
//=============================================================================
#define LSR_RD_RM_I5 LSR_RD_RM_I5_impl(value, source, shift)
static inline void LSR_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
{
    asm( "lsrs %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[source].I), "r" (shift) );
}
//#define LSR_RD_RM_I5 LSR_RD_RM_I5_impl(value, source, shift)
//static inline void LSR_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
//{
//   {\
//     C_FLAG = (reg[source].I >> (shift - 1)) & 1 ? true : false;\
//     value = reg[source].I >> shift;\
//   }
//}
//#define LSR_RD_RM_I5 LSR_RD_RM_I5_impl(value, source, shift)
//static inline void LSR_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
//{
//       asm ("shr %%cl, %%eax;"\
//            "setcb C_FLAG;"\
//            : "=a" (value)\
//            : "a" (reg[source].I), "c" (shift));
//}
//=============================================================================
#define LSR_RD_RS LSR_RD_RS_impl(value, dest)
static inline void LSR_RD_RS_impl(u32& value, u32 dest)
{
    asm( "lsrs %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[dest].I), "r" (value) );
}
//#define LSR_RD_RS LSR_RD_RS_impl(value, dest)
//static inline void LSR_RD_RS_impl(u32& value, u32 dest)
//{
//   {\
//     C_FLAG = (reg[dest].I >> (value - 1)) & 1 ? true : false;\
//     value = reg[dest].I >> value;\
//   }
//}
//#define LSR_RD_RS LSR_RD_RS_impl(value, dest)
//static inline void LSR_RD_RS_impl(u32& value, u32 dest)
//{
//         asm ("shr %%cl, %%eax;"\
//              "setcb C_FLAG;"\
//              : "=a" (value)\
//              : "a" (reg[dest].I), "c" (value));
//}
//=============================================================================
#define ASR_RD_RM_I5 ASR_RD_RM_I5_impl(value, source, shift)
static inline void ASR_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
{
    asm( "asrs %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[source].I), "r" (shift) );
}
//#define ASR_RD_RM_I5 ASR_RD_RM_I5_impl(value, source, shift)
//static inline void ASR_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
//{
//   {\
//     C_FLAG = ((s32)reg[source].I >> (int)(shift - 1)) & 1 ? true : false;\
//     value = (s32)reg[source].I >> (int)shift;\
//   }
//}
//#define ASR_RD_RM_I5 ASR_RD_RM_I5_impl(value, source, shift)
//static inline void ASR_RD_RM_I5_impl(u32& value, u32 source, u32 shift)
//{
//     asm ("sar %%cl, %%eax;"\
//          "setcb C_FLAG;"\
//          : "=a" (value)\
//          : "a" (reg[source].I), "c" (shift));
//}
//=============================================================================
#define ASR_RD_RS ASR_RD_RS_impl(value, dest)
static inline void ASR_RD_RS_impl(u32& value, u32 dest)
{
    asm( "asrs %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[dest].I), "r" (value) );
}
//#define ASR_RD_RS ASR_RD_RS_impl(value, dest)
//static inline void ASR_RD_RS_impl(u32& value, u32 dest)
//{
//   {\
//     C_FLAG = ((s32)reg[dest].I >> (int)(value - 1)) & 1 ? true : false;\
//     value = (s32)reg[dest].I >> (int)value;\
//   }
//}
//#define ASR_RD_RS ASR_RD_RS_impl(value, dest)
//static inline void ASR_RD_RS_impl(u32& value, u32 dest)
//{
//         asm ("sar %%cl, %%eax;"\
//              "setcb C_FLAG;"\
//              : "=a" (value)\
//              : "a" (reg[dest].I), "c" (value));
//}
//=============================================================================
#define ROR_RD_RS ROR_RD_RS_impl(value, dest)
static inline void ROR_RD_RS_impl(u32& value, u32 dest)
{
    asm( "rors %0, %2, %3;" \
     "mov %1, #0;" \
     "movcs %1, #1;" \
     : "=r" (value), "=r" (C_FLAG) \
     : "r" (reg[dest].I), "r" (value) );
}
//#define ROR_RD_RS ROR_RD_RS_impl(value, dest)
//static inline void ROR_RD_RS_impl(u32& value, u32 dest)
//{
//   {\
//     C_FLAG = (reg[dest].I >> (value - 1)) & 1 ? true : false;\
//     value = ((reg[dest].I << (32 - value)) |\
//              (reg[dest].I >> value));\
//   }
//}
//#define ROR_RD_RS ROR_RD_RS_impl(value, dest)
//static inline void ROR_RD_RS_impl(u32& value, u32 dest)
//{
//         asm ("ror %%cl, %%eax;"\
//              "setcb C_FLAG;"\
//              : "=a" (value)\
//              : "a" (reg[dest].I), "c" (value));
//}
//=============================================================================
#define NEG_RD_RS NEG_RD_RS_impl(dest, source)
static inline void NEG_RD_RS_impl(u32 dest, u32 source)
{
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
}
//#define NEG_RD_RS NEG_RD_RS_impl(dest, source)
//static inline void NEG_RD_RS_impl(u32 dest, u32 source)
//{
//     asm ("neg %%ebx;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setncb C_FLAG;"\
//          "setob V_FLAG;"\
//          : "=b" (reg[dest].I)\
//          : "b" (reg[source].I));
//}
//=============================================================================
#define CMP_RD_RS CMP_RD_RS_impl(dest, value)
static inline void CMP_RD_RS_impl(u32 dest, u32 value)
{
    asm ( "cmp %5, %4;" \
     GETCONDFLAGS(%0, %1, %2, %3) \
       : \
        "=r" (N_FLAG), "=r" (Z_FLAG), "=r" (C_FLAG), "=r" (V_FLAG) \
       : "r" (value), "r" (reg[dest].I) \
       : GETCONDFLAGS_REGS );
}
//#define CMP_RD_RS CMP_RD_RS_impl(dest, value)
//static inline void CMP_RD_RS_impl(u32 dest, u32 value)
//{
//   {\
//     u32 lhs = reg[dest].I;\
//     u32 rhs = value;\
//     u32 res = lhs - rhs;\
//     Z_FLAG = (res == 0) ? true : false;\
//     N_FLAG = NEG(res) ? true : false;\
//     SUBCARRY(lhs, rhs, res);\
//     SUBOVERFLOW(lhs, rhs, res);\
//   }
//}
//#define CMP_RD_RS CMP_RD_RS_impl(dest, value)
//static inline void CMP_RD_RS_impl(u32 dest, u32 value)
//{
//     asm ("sub %0, %1;"\
//          "setsb N_FLAG;"\
//          "setzb Z_FLAG;"\
//          "setncb C_FLAG;"\
//          "setob V_FLAG;"\
//          : \
//          : "r" (value), "r" (reg[dest].I):"1");
//}
//=============================================================================
