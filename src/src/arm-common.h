// Copright (C) 2011 Simon Ruggier
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#ifndef ARM_COMMON_H
#define ARM_COMMON_H

// Details about the native architecture
# if defined(__ARM_ARCH_7__) || \
     defined(__ARM_ARCH_7A__) || \
     defined(__ARM_ARCH_7R__) || \
     defined(__ARM_ARCH_7M__) || \
     defined(__ARM_ARCH_7EM__) || \
     defined(__ARM_ARCH_6T2__)
# define _ARM_THUMB2_
#endif

//Some c-core helper macros
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

#if defined(_ARM_THUMB2_)
# define GETCONDFLAGS(r1, r2, r3, r4) \
      "mrs "#r4", cpsr;" \
      "ubfx "#r1", "#r4", #31, #1;" \
      "ubfx "#r2", "#r4", #30, #1;" \
      "ubfx "#r3", "#r4", #29, #1;" \
      "ubfx "#r4", "#r4", #28, #1;"
#else
# define GETCONDFLAGS(r1, r2, r3, r4) \
      "mov "#r1", #0;" \
      "mov "#r2", #0;" \
      "mov "#r3", #0;" \
      "mov "#r4", #0;" \
      "movmi "#r1", #1;" \
      "moveq "#r2", #1;" \
      "movcs "#r3", #1;" \
      "movvs "#r4", #1;"
#endif

#endif
