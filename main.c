# 1 "m_stacktrace.c"
# 1 "/home/kats/zspace/valgrind/coregrind//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "m_stacktrace.c"
# 31 "m_stacktrace.c"
# 1 "pub_core_basics.h" 1
# 40 "pub_core_basics.h"
# 1 "../include/pub_tool_basics.h" 1
# 47 "../include/pub_tool_basics.h"
# 1 "../VEX/pub/libvex_basictypes.h" 1
# 44 "../VEX/pub/libvex_basictypes.h"
typedef unsigned char UChar;
typedef signed char Char;
typedef char HChar;




typedef unsigned short UShort;
typedef signed short Short;


typedef unsigned int UInt;
typedef signed int Int;


typedef unsigned long long int ULong;
typedef signed long long int Long;


typedef UInt U128[4];


typedef UInt U256[8];


typedef
   union {
      UChar w8[16];
      UShort w16[8];
      UInt w32[4];
      ULong w64[2];
   }
   V128;


typedef float Float;
typedef double Double;


typedef unsigned char Bool;






static inline Bool toBool ( Int x ) {
   Int r = (x == 0) ? ((Bool)0) : ((Bool)1);
   return (Bool)r;
}
static inline UChar toUChar ( Int x ) {
   x &= 0xFF;
   return (UChar)x;
}
static inline HChar toHChar ( Int x ) {
   x &= 0xFF;
   return (HChar)x;
}
static inline UShort toUShort ( Int x ) {
   x &= 0xFFFF;
   return (UShort)x;
}
static inline Short toShort ( Int x ) {
   x &= 0xFFFF;
   return (Short)x;
}
static inline UInt toUInt ( Long x ) {
   x &= 0xFFFFFFFFLL;
   return (UInt)x;
}


typedef UInt Addr32;
typedef ULong Addr64;





typedef unsigned long HWord;
# 194 "../VEX/pub/libvex_basictypes.h"
   static inline ULong Ptr_to_ULong ( void* p ) {
      UInt w = (UInt)p;
      return (ULong)w;
   }
   static inline void* ULong_to_Ptr ( ULong n ) {
      UInt w = (UInt)n;
      return (void*)w;
   }
# 48 "../include/pub_tool_basics.h" 2


# 1 "/home/kats/android/ndk-r8/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/include/stdarg.h" 1 3 4
# 40 "/home/kats/android/ndk-r8/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 102 "/home/kats/android/ndk-r8/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/../lib/gcc/arm-linux-androideabi/4.4.3/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 51 "../include/pub_tool_basics.h" 2
# 86 "../include/pub_tool_basics.h"
typedef unsigned long UWord;
typedef signed long Word;





typedef UWord Addr;
typedef UWord AddrH;




typedef UWord SizeT;
typedef Word SSizeT;





typedef Word PtrdiffT;
# 115 "../include/pub_tool_basics.h"
typedef Word OffT;





typedef Long Off64T;






typedef struct { UWord uw1; UWord uw2; } UWordPair;
# 139 "../include/pub_tool_basics.h"
typedef UInt ThreadId;
# 163 "../include/pub_tool_basics.h"
typedef
   struct {
      UWord _val;
      UWord _valEx;
      Bool _isError;
   }
   SysRes;
# 195 "../include/pub_tool_basics.h"
static inline Bool sr_isError ( SysRes sr ) {
   return sr._isError;
}
static inline UWord sr_Res ( SysRes sr ) {
   return sr._isError ? 0 : sr._val;
}
static inline UWord sr_ResEx ( SysRes sr ) {
   return sr._isError ? 0 : sr._valEx;
}
static inline UWord sr_ResHI ( SysRes sr ) {
   return 0;
}
static inline UWord sr_Err ( SysRes sr ) {
   return sr._isError ? sr._val : 0;
}
static inline Bool sr_EQ ( SysRes sr1, SysRes sr2 ) {
   return sr1._val == sr2._val
          && ((sr1._isError && sr2._isError)
              || (!sr1._isError && !sr2._isError));
}
# 41 "pub_core_basics.h" 2
# 49 "pub_core_basics.h"
# 1 "../VEX/pub/libvex.h" 1
# 40 "../VEX/pub/libvex.h"
# 1 "../VEX/pub/libvex_basictypes.h" 1
# 41 "../VEX/pub/libvex.h" 2
# 1 "../VEX/pub/libvex_ir.h" 1
# 219 "../VEX/pub/libvex_ir.h"
typedef
   enum {
      Ity_INVALID=0x11000,
      Ity_I1,
      Ity_I8,
      Ity_I16,
      Ity_I32,
      Ity_I64,
      Ity_I128,
      Ity_F32,
      Ity_F64,
      Ity_D32,
      Ity_D64,
      Ity_D128,
      Ity_F128,
      Ity_V128,
      Ity_V256
   }
   IRType;


extern void ppIRType ( IRType );


extern Int sizeofIRType ( IRType );





typedef
   enum {
      Iend_LE=0x12000,
      Iend_BE
   }
   IREndness;







typedef
   enum {
      Ico_U1=0x13000,
      Ico_U8,
      Ico_U16,
      Ico_U32,
      Ico_U64,
      Ico_F32,
      Ico_F32i,

      Ico_F64,
      Ico_F64i,

      Ico_V128,

      Ico_V256

   }
   IRConstTag;





typedef
   struct _IRConst {
      IRConstTag tag;
      union {
         Bool U1;
         UChar U8;
         UShort U16;
         UInt U32;
         ULong U64;
         Float F32;
         UInt F32i;
         Double F64;
         ULong F64i;
         UShort V128;
         UInt V256;
      } Ico;
   }
   IRConst;


extern IRConst* IRConst_U1 ( Bool );
extern IRConst* IRConst_U8 ( UChar );
extern IRConst* IRConst_U16 ( UShort );
extern IRConst* IRConst_U32 ( UInt );
extern IRConst* IRConst_U64 ( ULong );
extern IRConst* IRConst_F32 ( Float );
extern IRConst* IRConst_F32i ( UInt );
extern IRConst* IRConst_F64 ( Double );
extern IRConst* IRConst_F64i ( ULong );
extern IRConst* IRConst_V128 ( UShort );
extern IRConst* IRConst_V256 ( UInt );


extern IRConst* deepCopyIRConst ( IRConst* );


extern void ppIRConst ( IRConst* );


extern Bool eqIRConst ( IRConst*, IRConst* );
# 345 "../VEX/pub/libvex_ir.h"
typedef
   struct {
      Int regparms;
      HChar* name;
      void* addr;
      UInt mcx_mask;
   }
   IRCallee;


extern IRCallee* mkIRCallee ( Int regparms, HChar* name, void* addr );


extern IRCallee* deepCopyIRCallee ( IRCallee* );


extern void ppIRCallee ( IRCallee* );







typedef
   struct {
      Int base;
      IRType elemTy;
      Int nElems;
   }
   IRRegArray;

extern IRRegArray* mkIRRegArray ( Int, IRType, Int );

extern IRRegArray* deepCopyIRRegArray ( IRRegArray* );

extern void ppIRRegArray ( IRRegArray* );
extern Bool eqIRRegArray ( IRRegArray*, IRRegArray* );







typedef UInt IRTemp;


extern void ppIRTemp ( IRTemp );
# 410 "../VEX/pub/libvex_ir.h"
typedef
   enum {



      Iop_INVALID=0x14000,
      Iop_Add8, Iop_Add16, Iop_Add32, Iop_Add64,
      Iop_Sub8, Iop_Sub16, Iop_Sub32, Iop_Sub64,

      Iop_Mul8, Iop_Mul16, Iop_Mul32, Iop_Mul64,
      Iop_Or8, Iop_Or16, Iop_Or32, Iop_Or64,
      Iop_And8, Iop_And16, Iop_And32, Iop_And64,
      Iop_Xor8, Iop_Xor16, Iop_Xor32, Iop_Xor64,
      Iop_Shl8, Iop_Shl16, Iop_Shl32, Iop_Shl64,
      Iop_Shr8, Iop_Shr16, Iop_Shr32, Iop_Shr64,
      Iop_Sar8, Iop_Sar16, Iop_Sar32, Iop_Sar64,

      Iop_CmpEQ8, Iop_CmpEQ16, Iop_CmpEQ32, Iop_CmpEQ64,
      Iop_CmpNE8, Iop_CmpNE16, Iop_CmpNE32, Iop_CmpNE64,

      Iop_Not8, Iop_Not16, Iop_Not32, Iop_Not64,






      Iop_CasCmpEQ8, Iop_CasCmpEQ16, Iop_CasCmpEQ32, Iop_CasCmpEQ64,
      Iop_CasCmpNE8, Iop_CasCmpNE16, Iop_CasCmpNE32, Iop_CasCmpNE64,




      Iop_MullS8, Iop_MullS16, Iop_MullS32, Iop_MullS64,
      Iop_MullU8, Iop_MullU16, Iop_MullU32, Iop_MullU64,


      Iop_Clz64, Iop_Clz32,
      Iop_Ctz64, Iop_Ctz32,





      Iop_CmpLT32S, Iop_CmpLT64S,
      Iop_CmpLE32S, Iop_CmpLE64S,
      Iop_CmpLT32U, Iop_CmpLT64U,
      Iop_CmpLE32U, Iop_CmpLE64U,


      Iop_CmpNEZ8, Iop_CmpNEZ16, Iop_CmpNEZ32, Iop_CmpNEZ64,
      Iop_CmpwNEZ32, Iop_CmpwNEZ64,
      Iop_Left8, Iop_Left16, Iop_Left32, Iop_Left64,
      Iop_Max32U,







      Iop_CmpORD32U, Iop_CmpORD64U,
      Iop_CmpORD32S, Iop_CmpORD64S,



      Iop_DivU32,
      Iop_DivS32,
      Iop_DivU64,
      Iop_DivS64,
      Iop_DivU64E,
      Iop_DivS64E,
      Iop_DivU32E,
      Iop_DivS32E,

      Iop_DivModU64to32,

      Iop_DivModS64to32,

      Iop_DivModU128to64,

      Iop_DivModS128to64,

      Iop_DivModS64to64,
# 502 "../VEX/pub/libvex_ir.h"
      Iop_8Uto16, Iop_8Uto32, Iop_8Uto64,
                  Iop_16Uto32, Iop_16Uto64,
                               Iop_32Uto64,
      Iop_8Sto16, Iop_8Sto32, Iop_8Sto64,
                  Iop_16Sto32, Iop_16Sto64,
                               Iop_32Sto64,


      Iop_64to8, Iop_32to8, Iop_64to16,

      Iop_16to8,
      Iop_16HIto8,
      Iop_8HLto16,

      Iop_32to16,
      Iop_32HIto16,
      Iop_16HLto32,

      Iop_64to32,
      Iop_64HIto32,
      Iop_32HLto64,

      Iop_128to64,
      Iop_128HIto64,
      Iop_64HLto128,

      Iop_Not1,
      Iop_32to1,
      Iop_64to1,
      Iop_1Uto8,
      Iop_1Uto32,
      Iop_1Uto64,
      Iop_1Sto8,
      Iop_1Sto16,
      Iop_1Sto32,
      Iop_1Sto64,







      Iop_AddF64, Iop_SubF64, Iop_MulF64, Iop_DivF64,


      Iop_AddF32, Iop_SubF32, Iop_MulF32, Iop_DivF32,




      Iop_AddF64r32, Iop_SubF64r32, Iop_MulF64r32, Iop_DivF64r32,



      Iop_NegF64, Iop_AbsF64,


      Iop_NegF32, Iop_AbsF32,



      Iop_SqrtF64,


      Iop_SqrtF32,
# 578 "../VEX/pub/libvex_ir.h"
      Iop_CmpF64,
      Iop_CmpF32,
      Iop_CmpF128,
# 623 "../VEX/pub/libvex_ir.h"
      Iop_F64toI16S,
      Iop_F64toI32S,
      Iop_F64toI64S,
      Iop_F64toI64U,

      Iop_F64toI32U,

      Iop_I32StoF64,
      Iop_I64StoF64,
      Iop_I64UtoF64,
      Iop_I64UtoF32,

      Iop_I32UtoF32,
      Iop_I32UtoF64,

      Iop_F32toI32S,
      Iop_F32toI64S,
      Iop_F32toI32U,
      Iop_F32toI64U,

      Iop_I32StoF32,
      Iop_I64StoF32,


      Iop_F32toF64,
      Iop_F64toF32,



      Iop_ReinterpF64asI64, Iop_ReinterpI64asF64,
      Iop_ReinterpF32asI32, Iop_ReinterpI32asF32,


      Iop_F64HLtoF128,
      Iop_F128HItoF64,
      Iop_F128LOtoF64,


      Iop_AddF128, Iop_SubF128, Iop_MulF128, Iop_DivF128,


      Iop_NegF128, Iop_AbsF128,


      Iop_SqrtF128,

      Iop_I32StoF128,
      Iop_I64StoF128,
      Iop_I32UtoF128,
      Iop_I64UtoF128,
      Iop_F32toF128,
      Iop_F64toF128,

      Iop_F128toI32S,
      Iop_F128toI64S,
      Iop_F128toI32U,
      Iop_F128toI64U,
      Iop_F128toF64,
      Iop_F128toF32,





      Iop_AtanF64,
      Iop_Yl2xF64,
      Iop_Yl2xp1F64,
      Iop_PRemF64,
      Iop_PRemC3210F64,
      Iop_PRem1F64,
      Iop_PRem1C3210F64,
      Iop_ScaleF64,






      Iop_SinF64,
      Iop_CosF64,
      Iop_TanF64,
      Iop_2xm1F64,
      Iop_RoundF64toInt,

      Iop_RoundF32toInt,







      Iop_MAddF32, Iop_MSubF32,
# 725 "../VEX/pub/libvex_ir.h"
      Iop_MAddF64, Iop_MSubF64,




      Iop_MAddF64r32, Iop_MSubF64r32,


      Iop_Est5FRSqrt,
      Iop_RoundF64toF64_NEAREST,
      Iop_RoundF64toF64_NegINF,
      Iop_RoundF64toF64_PosINF,
      Iop_RoundF64toF64_ZERO,


      Iop_TruncF64asF32,


      Iop_RoundF64toF32,






      Iop_QAdd32S,
      Iop_QSub32S,


      Iop_Add16x2, Iop_Sub16x2,
      Iop_QAdd16Sx2, Iop_QAdd16Ux2,
      Iop_QSub16Sx2, Iop_QSub16Ux2,




      Iop_HAdd16Ux2, Iop_HAdd16Sx2,
      Iop_HSub16Ux2, Iop_HSub16Sx2,


      Iop_Add8x4, Iop_Sub8x4,
      Iop_QAdd8Sx4, Iop_QAdd8Ux4,
      Iop_QSub8Sx4, Iop_QSub8Ux4,




      Iop_HAdd8Ux4, Iop_HAdd8Sx4,
      Iop_HSub8Ux4, Iop_HSub8Sx4,


      Iop_Sad8Ux4,


      Iop_CmpNEZ16x2, Iop_CmpNEZ8x4,




      Iop_I32UtoFx2, Iop_I32StoFx2,
      Iop_FtoI32Ux2_RZ, Iop_FtoI32Sx2_RZ,



      Iop_F32ToFixed32Ux2_RZ, Iop_F32ToFixed32Sx2_RZ,
      Iop_Fixed32UToF32x2_RN, Iop_Fixed32SToF32x2_RN,


      Iop_Max32Fx2, Iop_Min32Fx2,


      Iop_PwMax32Fx2, Iop_PwMin32Fx2,


      Iop_CmpEQ32Fx2, Iop_CmpGT32Fx2, Iop_CmpGE32Fx2,




      Iop_Recip32Fx2,




      Iop_Recps32Fx2,



      Iop_Rsqrte32Fx2,




      Iop_Rsqrts32Fx2,


      Iop_Neg32Fx2, Iop_Abs32Fx2,




      Iop_CmpNEZ8x8, Iop_CmpNEZ16x4, Iop_CmpNEZ32x2,


      Iop_Add8x8, Iop_Add16x4, Iop_Add32x2,
      Iop_QAdd8Ux8, Iop_QAdd16Ux4, Iop_QAdd32Ux2, Iop_QAdd64Ux1,
      Iop_QAdd8Sx8, Iop_QAdd16Sx4, Iop_QAdd32Sx2, Iop_QAdd64Sx1,




      Iop_PwAdd8x8, Iop_PwAdd16x4, Iop_PwAdd32x2,
      Iop_PwMax8Sx8, Iop_PwMax16Sx4, Iop_PwMax32Sx2,
      Iop_PwMax8Ux8, Iop_PwMax16Ux4, Iop_PwMax32Ux2,
      Iop_PwMin8Sx8, Iop_PwMin16Sx4, Iop_PwMin32Sx2,
      Iop_PwMin8Ux8, Iop_PwMin16Ux4, Iop_PwMin32Ux2,





      Iop_PwAddL8Ux8, Iop_PwAddL16Ux4, Iop_PwAddL32Ux2,
      Iop_PwAddL8Sx8, Iop_PwAddL16Sx4, Iop_PwAddL32Sx2,


      Iop_Sub8x8, Iop_Sub16x4, Iop_Sub32x2,
      Iop_QSub8Ux8, Iop_QSub16Ux4, Iop_QSub32Ux2, Iop_QSub64Ux1,
      Iop_QSub8Sx8, Iop_QSub16Sx4, Iop_QSub32Sx2, Iop_QSub64Sx1,


      Iop_Abs8x8, Iop_Abs16x4, Iop_Abs32x2,


      Iop_Mul8x8, Iop_Mul16x4, Iop_Mul32x2,
      Iop_Mul32Fx2,
      Iop_MulHi16Ux4,
      Iop_MulHi16Sx4,


      Iop_PolynomialMul8x8,







      Iop_QDMulHi16Sx4, Iop_QDMulHi32Sx2,
      Iop_QRDMulHi16Sx4, Iop_QRDMulHi32Sx2,


      Iop_Avg8Ux8,
      Iop_Avg16Ux4,


      Iop_Max8Sx8, Iop_Max16Sx4, Iop_Max32Sx2,
      Iop_Max8Ux8, Iop_Max16Ux4, Iop_Max32Ux2,
      Iop_Min8Sx8, Iop_Min16Sx4, Iop_Min32Sx2,
      Iop_Min8Ux8, Iop_Min16Ux4, Iop_Min32Ux2,


      Iop_CmpEQ8x8, Iop_CmpEQ16x4, Iop_CmpEQ32x2,
      Iop_CmpGT8Ux8, Iop_CmpGT16Ux4, Iop_CmpGT32Ux2,
      Iop_CmpGT8Sx8, Iop_CmpGT16Sx4, Iop_CmpGT32Sx2,



      Iop_Cnt8x8,
      Iop_Clz8Sx8, Iop_Clz16Sx4, Iop_Clz32Sx2,
      Iop_Cls8Sx8, Iop_Cls16Sx4, Iop_Cls32Sx2,


      Iop_Shl8x8, Iop_Shl16x4, Iop_Shl32x2,
      Iop_Shr8x8, Iop_Shr16x4, Iop_Shr32x2,
      Iop_Sar8x8, Iop_Sar16x4, Iop_Sar32x2,
      Iop_Sal8x8, Iop_Sal16x4, Iop_Sal32x2, Iop_Sal64x1,


      Iop_ShlN8x8, Iop_ShlN16x4, Iop_ShlN32x2,
      Iop_ShrN8x8, Iop_ShrN16x4, Iop_ShrN32x2,
      Iop_SarN8x8, Iop_SarN16x4, Iop_SarN32x2,


      Iop_QShl8x8, Iop_QShl16x4, Iop_QShl32x2, Iop_QShl64x1,
      Iop_QSal8x8, Iop_QSal16x4, Iop_QSal32x2, Iop_QSal64x1,

      Iop_QShlN8Sx8, Iop_QShlN16Sx4, Iop_QShlN32Sx2, Iop_QShlN64Sx1,
      Iop_QShlN8x8, Iop_QShlN16x4, Iop_QShlN32x2, Iop_QShlN64x1,
      Iop_QSalN8x8, Iop_QSalN16x4, Iop_QSalN32x2, Iop_QSalN64x1,
# 936 "../VEX/pub/libvex_ir.h"
      Iop_QNarrowBin16Sto8Ux8,
      Iop_QNarrowBin16Sto8Sx8, Iop_QNarrowBin32Sto16Sx4,
      Iop_NarrowBin16to8x8, Iop_NarrowBin32to16x4,





      Iop_InterleaveHI8x8, Iop_InterleaveHI16x4, Iop_InterleaveHI32x2,
      Iop_InterleaveLO8x8, Iop_InterleaveLO16x4, Iop_InterleaveLO32x2,



      Iop_InterleaveOddLanes8x8, Iop_InterleaveEvenLanes8x8,
      Iop_InterleaveOddLanes16x4, Iop_InterleaveEvenLanes16x4,






      Iop_CatOddLanes8x8, Iop_CatOddLanes16x4,
      Iop_CatEvenLanes8x8, Iop_CatEvenLanes16x4,





      Iop_GetElem8x8, Iop_GetElem16x4, Iop_GetElem32x2,
      Iop_SetElem8x8, Iop_SetElem16x4, Iop_SetElem32x2,


      Iop_Dup8x8, Iop_Dup16x4, Iop_Dup32x2,






      Iop_Extract64,







      Iop_Reverse16_8x8,
      Iop_Reverse32_8x8, Iop_Reverse32_16x4,
      Iop_Reverse64_8x8, Iop_Reverse64_16x4, Iop_Reverse64_32x2,






      Iop_Perm8x8,



      Iop_Recip32x2, Iop_Rsqrte32x2,







      Iop_AddD64, Iop_SubD64, Iop_MulD64, Iop_DivD64,





      Iop_AddD128, Iop_SubD128, Iop_MulD128, Iop_DivD128,
# 1020 "../VEX/pub/libvex_ir.h"
      Iop_ShlD64, Iop_ShrD64,


      Iop_ShlD128, Iop_ShrD128,





      Iop_D32toD64,


      Iop_D64toD128,


      Iop_I64StoD128,


      Iop_D64toD32,


      Iop_D128toD64,


      Iop_I64StoD64,


      Iop_D64toI64S,


      Iop_D128toI64S,





      Iop_RoundD64toInt,


      Iop_RoundD128toInt,



      Iop_CmpD64,


      Iop_CmpD128,
# 1077 "../VEX/pub/libvex_ir.h"
      Iop_QuantizeD64,


      Iop_QuantizeD128,






      Iop_SignificanceRoundD64,


      Iop_SignificanceRoundD128,






      Iop_ExtractExpD64,


      Iop_ExtractExpD128,







      Iop_InsertExpD64,


      Iop_InsertExpD128,


      Iop_D64HLtoD128, Iop_D128HItoD64, Iop_D128LOtoD64,




      Iop_DPBtoBCD,




      Iop_BCDtoDPB,


      Iop_ReinterpI64asD64,


      Iop_ReinterpD64asI64,






      Iop_Add32Fx4, Iop_Sub32Fx4, Iop_Mul32Fx4, Iop_Div32Fx4,
      Iop_Max32Fx4, Iop_Min32Fx4,
      Iop_Add32Fx2, Iop_Sub32Fx2,


      Iop_CmpEQ32Fx4, Iop_CmpLT32Fx4, Iop_CmpLE32Fx4, Iop_CmpUN32Fx4,
      Iop_CmpGT32Fx4, Iop_CmpGE32Fx4,


      Iop_Abs32Fx4,


      Iop_PwMax32Fx4, Iop_PwMin32Fx4,


      Iop_Sqrt32Fx4, Iop_RSqrt32Fx4,
      Iop_Neg32Fx4,




      Iop_Recip32Fx4,




      Iop_Recps32Fx4,



      Iop_Rsqrte32Fx4,




      Iop_Rsqrts32Fx4,






      Iop_I32UtoFx4, Iop_I32StoFx4,
      Iop_FtoI32Ux4_RZ, Iop_FtoI32Sx4_RZ,
      Iop_QFtoI32Ux4_RZ, Iop_QFtoI32Sx4_RZ,
      Iop_RoundF32x4_RM, Iop_RoundF32x4_RP,
      Iop_RoundF32x4_RN, Iop_RoundF32x4_RZ,



      Iop_F32ToFixed32Ux4_RZ, Iop_F32ToFixed32Sx4_RZ,
      Iop_Fixed32UToF32x4_RN, Iop_Fixed32SToF32x4_RN,



      Iop_F32toF16x4, Iop_F16toF32x4,







      Iop_Add32F0x4, Iop_Sub32F0x4, Iop_Mul32F0x4, Iop_Div32F0x4,
      Iop_Max32F0x4, Iop_Min32F0x4,
      Iop_CmpEQ32F0x4, Iop_CmpLT32F0x4, Iop_CmpLE32F0x4, Iop_CmpUN32F0x4,


      Iop_Recip32F0x4, Iop_Sqrt32F0x4, Iop_RSqrt32F0x4,




      Iop_Add64Fx2, Iop_Sub64Fx2, Iop_Mul64Fx2, Iop_Div64Fx2,
      Iop_Max64Fx2, Iop_Min64Fx2,
      Iop_CmpEQ64Fx2, Iop_CmpLT64Fx2, Iop_CmpLE64Fx2, Iop_CmpUN64Fx2,


      Iop_Recip64Fx2, Iop_Sqrt64Fx2, Iop_RSqrt64Fx2,







      Iop_Add64F0x2, Iop_Sub64F0x2, Iop_Mul64F0x2, Iop_Div64F0x2,
      Iop_Max64F0x2, Iop_Min64F0x2,
      Iop_CmpEQ64F0x2, Iop_CmpLT64F0x2, Iop_CmpLE64F0x2, Iop_CmpUN64F0x2,


      Iop_Recip64F0x2, Iop_Sqrt64F0x2, Iop_RSqrt64F0x2,




      Iop_V128to64,
      Iop_V128HIto64,
      Iop_64HLtoV128,

      Iop_64UtoV128,
      Iop_SetV128lo64,


      Iop_32UtoV128,
      Iop_V128to32,
      Iop_SetV128lo32,




      Iop_NotV128,
      Iop_AndV128, Iop_OrV128, Iop_XorV128,


      Iop_ShlV128, Iop_ShrV128,


      Iop_CmpNEZ8x16, Iop_CmpNEZ16x8, Iop_CmpNEZ32x4, Iop_CmpNEZ64x2,


      Iop_Add8x16, Iop_Add16x8, Iop_Add32x4, Iop_Add64x2,
      Iop_QAdd8Ux16, Iop_QAdd16Ux8, Iop_QAdd32Ux4, Iop_QAdd64Ux2,
      Iop_QAdd8Sx16, Iop_QAdd16Sx8, Iop_QAdd32Sx4, Iop_QAdd64Sx2,


      Iop_Sub8x16, Iop_Sub16x8, Iop_Sub32x4, Iop_Sub64x2,
      Iop_QSub8Ux16, Iop_QSub16Ux8, Iop_QSub32Ux4, Iop_QSub64Ux2,
      Iop_QSub8Sx16, Iop_QSub16Sx8, Iop_QSub32Sx4, Iop_QSub64Sx2,


      Iop_Mul8x16, Iop_Mul16x8, Iop_Mul32x4,
                    Iop_MulHi16Ux8, Iop_MulHi32Ux4,
                    Iop_MulHi16Sx8, Iop_MulHi32Sx4,

      Iop_MullEven8Ux16, Iop_MullEven16Ux8,
      Iop_MullEven8Sx16, Iop_MullEven16Sx8,

      Iop_Mull8Ux8, Iop_Mull8Sx8,
      Iop_Mull16Ux4, Iop_Mull16Sx4,
      Iop_Mull32Ux2, Iop_Mull32Sx2,






      Iop_QDMulHi16Sx8, Iop_QDMulHi32Sx4,
      Iop_QRDMulHi16Sx8, Iop_QRDMulHi32Sx4,

      Iop_QDMulLong16Sx4, Iop_QDMulLong32Sx2,


      Iop_PolynomialMul8x16,
      Iop_PolynomialMull8x8,




      Iop_PwAdd8x16, Iop_PwAdd16x8, Iop_PwAdd32x4,
      Iop_PwAdd32Fx2,





      Iop_PwAddL8Ux16, Iop_PwAddL16Ux8, Iop_PwAddL32Ux4,
      Iop_PwAddL8Sx16, Iop_PwAddL16Sx8, Iop_PwAddL32Sx4,


      Iop_Abs8x16, Iop_Abs16x8, Iop_Abs32x4,


      Iop_Avg8Ux16, Iop_Avg16Ux8, Iop_Avg32Ux4,
      Iop_Avg8Sx16, Iop_Avg16Sx8, Iop_Avg32Sx4,


      Iop_Max8Sx16, Iop_Max16Sx8, Iop_Max32Sx4,
      Iop_Max8Ux16, Iop_Max16Ux8, Iop_Max32Ux4,
      Iop_Min8Sx16, Iop_Min16Sx8, Iop_Min32Sx4,
      Iop_Min8Ux16, Iop_Min16Ux8, Iop_Min32Ux4,


      Iop_CmpEQ8x16, Iop_CmpEQ16x8, Iop_CmpEQ32x4, Iop_CmpEQ64x2,
      Iop_CmpGT8Sx16, Iop_CmpGT16Sx8, Iop_CmpGT32Sx4, Iop_CmpGT64Sx2,
      Iop_CmpGT8Ux16, Iop_CmpGT16Ux8, Iop_CmpGT32Ux4,



      Iop_Cnt8x16,
      Iop_Clz8Sx16, Iop_Clz16Sx8, Iop_Clz32Sx4,
      Iop_Cls8Sx16, Iop_Cls16Sx8, Iop_Cls32Sx4,


      Iop_ShlN8x16, Iop_ShlN16x8, Iop_ShlN32x4, Iop_ShlN64x2,
      Iop_ShrN8x16, Iop_ShrN16x8, Iop_ShrN32x4, Iop_ShrN64x2,
      Iop_SarN8x16, Iop_SarN16x8, Iop_SarN32x4, Iop_SarN64x2,


      Iop_Shl8x16, Iop_Shl16x8, Iop_Shl32x4, Iop_Shl64x2,
      Iop_Shr8x16, Iop_Shr16x8, Iop_Shr32x4, Iop_Shr64x2,
      Iop_Sar8x16, Iop_Sar16x8, Iop_Sar32x4, Iop_Sar64x2,
      Iop_Sal8x16, Iop_Sal16x8, Iop_Sal32x4, Iop_Sal64x2,
      Iop_Rol8x16, Iop_Rol16x8, Iop_Rol32x4,


      Iop_QShl8x16, Iop_QShl16x8, Iop_QShl32x4, Iop_QShl64x2,
      Iop_QSal8x16, Iop_QSal16x8, Iop_QSal32x4, Iop_QSal64x2,

      Iop_QShlN8Sx16, Iop_QShlN16Sx8, Iop_QShlN32Sx4, Iop_QShlN64Sx2,
      Iop_QShlN8x16, Iop_QShlN16x8, Iop_QShlN32x4, Iop_QShlN64x2,
      Iop_QSalN8x16, Iop_QSalN16x8, Iop_QSalN32x4, Iop_QSalN64x2,




      Iop_QNarrowBin16Sto8Ux16, Iop_QNarrowBin32Sto16Ux8,
      Iop_QNarrowBin16Sto8Sx16, Iop_QNarrowBin32Sto16Sx8,
      Iop_QNarrowBin16Uto8Ux16, Iop_QNarrowBin32Uto16Ux8,
      Iop_NarrowBin16to8x16, Iop_NarrowBin32to16x8,


      Iop_NarrowUn16to8x8, Iop_NarrowUn32to16x4, Iop_NarrowUn64to32x2,

      Iop_QNarrowUn16Sto8Sx8, Iop_QNarrowUn32Sto16Sx4, Iop_QNarrowUn64Sto32Sx2,
      Iop_QNarrowUn16Sto8Ux8, Iop_QNarrowUn32Sto16Ux4, Iop_QNarrowUn64Sto32Ux2,

      Iop_QNarrowUn16Uto8Ux8, Iop_QNarrowUn32Uto16Ux4, Iop_QNarrowUn64Uto32Ux2,
# 1374 "../VEX/pub/libvex_ir.h"
      Iop_Widen8Uto16x8, Iop_Widen16Uto32x4, Iop_Widen32Uto64x2,
      Iop_Widen8Sto16x8, Iop_Widen16Sto32x4, Iop_Widen32Sto64x2,





      Iop_InterleaveHI8x16, Iop_InterleaveHI16x8,
      Iop_InterleaveHI32x4, Iop_InterleaveHI64x2,
      Iop_InterleaveLO8x16, Iop_InterleaveLO16x8,
      Iop_InterleaveLO32x4, Iop_InterleaveLO64x2,


      Iop_InterleaveOddLanes8x16, Iop_InterleaveEvenLanes8x16,
      Iop_InterleaveOddLanes16x8, Iop_InterleaveEvenLanes16x8,
      Iop_InterleaveOddLanes32x4, Iop_InterleaveEvenLanes32x4,



      Iop_CatOddLanes8x16, Iop_CatOddLanes16x8, Iop_CatOddLanes32x4,
      Iop_CatEvenLanes8x16, Iop_CatEvenLanes16x8, Iop_CatEvenLanes32x4,




      Iop_GetElem8x16, Iop_GetElem16x8, Iop_GetElem32x4, Iop_GetElem64x2,


      Iop_Dup8x16, Iop_Dup16x8, Iop_Dup32x4,






      Iop_ExtractV128,






      Iop_Reverse16_8x16,
      Iop_Reverse32_8x16, Iop_Reverse32_16x8,
      Iop_Reverse64_8x16, Iop_Reverse64_16x8, Iop_Reverse64_32x4,






      Iop_Perm8x16,
      Iop_Perm32x4,



      Iop_Recip32x4, Iop_Rsqrte32x4,




      Iop_V256to64_0,
      Iop_V256to64_1,
      Iop_V256to64_2,
      Iop_V256to64_3,

      Iop_64x4toV256,


      Iop_V256toV128_0,
      Iop_V256toV128_1,
      Iop_V128HLtoV256,

      Iop_AndV256,
      Iop_OrV256,
      Iop_XorV256,
      Iop_NotV256,


      Iop_CmpNEZ32x8, Iop_CmpNEZ64x4,


      Iop_Add64Fx4,
      Iop_Sub64Fx4,
      Iop_Mul64Fx4,
      Iop_Div64Fx4,
      Iop_Add32Fx8,
      Iop_Sub32Fx8,
      Iop_Mul32Fx8,
      Iop_Div32Fx8,

      Iop_Sqrt32Fx8,
      Iop_Sqrt64Fx4,
      Iop_RSqrt32Fx8,
      Iop_Recip32Fx8,

      Iop_Max32Fx8, Iop_Min32Fx8,
      Iop_Max64Fx4, Iop_Min64Fx4,
      Iop_LAST
   }
   IROp;


extern void ppIROp ( IROp );






typedef
   enum {
      Irrm_NEAREST = 0,
      Irrm_NegINF = 1,
      Irrm_PosINF = 2,
      Irrm_ZERO = 3
   }
   IRRoundingMode;
# 1500 "../VEX/pub/libvex_ir.h"
typedef
   enum {
      Irrm_DFP_NEAREST = 0,
      Irrm_DFP_NegINF = 1,
      Irrm_DFP_PosINF = 2,
      Irrm_DFP_ZERO = 3,
      Irrm_DFP_NEAREST_TIE_AWAY_0 = 4,
      Irrm_DFP_PREPARE_SHORTER = 5,

      Irrm_DFP_AWAY_FROM_ZERO = 6,
      Irrm_DFP_NEAREST_TIE_TOWARD_0 = 7
   }
   IRRoundingModeDFP;



typedef
   enum {
      Ircr_UN = 0x45,
      Ircr_LT = 0x01,
      Ircr_GT = 0x00,
      Ircr_EQ = 0x40
   }
   IRCmpF64Result;

typedef IRCmpF64Result IRCmpF32Result;
typedef IRCmpF64Result IRCmpF128Result;



typedef struct _IRQop IRQop;
typedef struct _IRTriop IRTriop;




typedef
   enum {
      Iex_Binder=0x15000,
      Iex_Get,
      Iex_GetI,
      Iex_RdTmp,
      Iex_Qop,
      Iex_Triop,
      Iex_Binop,
      Iex_Unop,
      Iex_Load,
      Iex_Const,
      Iex_Mux0X,
      Iex_CCall
   }
   IRExprTag;
# 1562 "../VEX/pub/libvex_ir.h"
typedef
   struct _IRExpr
   IRExpr;

struct _IRExpr {
   IRExprTag tag;
   union {


      struct {
         Int binder;
      } Binder;




      struct {
         Int offset;
         IRType ty;
      } Get;
# 1619 "../VEX/pub/libvex_ir.h"
      struct {
         IRRegArray* descr;
         IRExpr* ix;
         Int bias;
      } GetI;




      struct {
         IRTemp tmp;
      } RdTmp;





      struct {
        IRQop* details;
      } Qop;





      struct {
        IRTriop* details;
      } Triop;




      struct {
         IROp op;
         IRExpr* arg1;
         IRExpr* arg2;
      } Binop;




      struct {
         IROp op;
         IRExpr* arg;
      } Unop;







      struct {
         IREndness end;
         IRType ty;
         IRExpr* addr;
      } Load;




      struct {
         IRConst* con;
      } Const;
# 1726 "../VEX/pub/libvex_ir.h"
      struct {
         IRCallee* cee;
         IRType retty;
         IRExpr** args;
      } CCall;
# 1739 "../VEX/pub/libvex_ir.h"
      struct {
         IRExpr* cond;
         IRExpr* expr0;
         IRExpr* exprX;
      } Mux0X;
   } Iex;
};


struct _IRTriop {
   IROp op;
   IRExpr* arg1;
   IRExpr* arg2;
   IRExpr* arg3;
};


struct _IRQop {
   IROp op;
   IRExpr* arg1;
   IRExpr* arg2;
   IRExpr* arg3;
   IRExpr* arg4;
};


extern IRExpr* IRExpr_Binder ( Int binder );
extern IRExpr* IRExpr_Get ( Int off, IRType ty );
extern IRExpr* IRExpr_GetI ( IRRegArray* descr, IRExpr* ix, Int bias );
extern IRExpr* IRExpr_RdTmp ( IRTemp tmp );
extern IRExpr* IRExpr_Qop ( IROp op, IRExpr* arg1, IRExpr* arg2,
                                        IRExpr* arg3, IRExpr* arg4 );
extern IRExpr* IRExpr_Triop ( IROp op, IRExpr* arg1,
                                        IRExpr* arg2, IRExpr* arg3 );
extern IRExpr* IRExpr_Binop ( IROp op, IRExpr* arg1, IRExpr* arg2 );
extern IRExpr* IRExpr_Unop ( IROp op, IRExpr* arg );
extern IRExpr* IRExpr_Load ( IREndness end, IRType ty, IRExpr* addr );
extern IRExpr* IRExpr_Const ( IRConst* con );
extern IRExpr* IRExpr_CCall ( IRCallee* cee, IRType retty, IRExpr** args );
extern IRExpr* IRExpr_Mux0X ( IRExpr* cond, IRExpr* expr0, IRExpr* exprX );


extern IRExpr* deepCopyIRExpr ( IRExpr* );


extern void ppIRExpr ( IRExpr* );



extern IRExpr** mkIRExprVec_0 ( void );
extern IRExpr** mkIRExprVec_1 ( IRExpr* );
extern IRExpr** mkIRExprVec_2 ( IRExpr*, IRExpr* );
extern IRExpr** mkIRExprVec_3 ( IRExpr*, IRExpr*, IRExpr* );
extern IRExpr** mkIRExprVec_4 ( IRExpr*, IRExpr*, IRExpr*, IRExpr* );
extern IRExpr** mkIRExprVec_5 ( IRExpr*, IRExpr*, IRExpr*, IRExpr*,
                                IRExpr* );
extern IRExpr** mkIRExprVec_6 ( IRExpr*, IRExpr*, IRExpr*, IRExpr*,
                                IRExpr*, IRExpr* );
extern IRExpr** mkIRExprVec_7 ( IRExpr*, IRExpr*, IRExpr*, IRExpr*,
                                IRExpr*, IRExpr*, IRExpr* );
extern IRExpr** mkIRExprVec_8 ( IRExpr*, IRExpr*, IRExpr*, IRExpr*,
                                IRExpr*, IRExpr*, IRExpr*, IRExpr*);





extern IRExpr** shallowCopyIRExprVec ( IRExpr** );
extern IRExpr** deepCopyIRExprVec ( IRExpr** );



extern IRExpr* mkIRExpr_HWord ( HWord );


extern
IRExpr* mkIRExprCCall ( IRType retty,
                        Int regparms, HChar* name, void* addr,
                        IRExpr** args );




static inline Bool isIRAtom ( IRExpr* e ) {
   return toBool(e->tag == Iex_RdTmp || e->tag == Iex_Const);
}



extern Bool eqIRAtom ( IRExpr*, IRExpr* );
# 1858 "../VEX/pub/libvex_ir.h"
typedef
   enum {
      Ijk_INVALID=0x16000,
      Ijk_Boring,
      Ijk_Call,
      Ijk_Ret,
      Ijk_ClientReq,
      Ijk_Yield,
      Ijk_EmWarn,
      Ijk_EmFail,
      Ijk_NoDecode,
      Ijk_MapFail,
      Ijk_TInval,
      Ijk_NoRedir,
      Ijk_SigTRAP,
      Ijk_SigSEGV,
      Ijk_SigBUS,


      Ijk_Sys_syscall,
      Ijk_Sys_int32,
      Ijk_Sys_int128,
      Ijk_Sys_int129,
      Ijk_Sys_int130,
      Ijk_Sys_sysenter

   }
   IRJumpKind;

extern void ppIRJumpKind ( IRJumpKind );
# 1935 "../VEX/pub/libvex_ir.h"
typedef
   enum {
      Ifx_None = 0x1700,
      Ifx_Read,
      Ifx_Write,
      Ifx_Modify,
   }
   IREffect;


extern void ppIREffect ( IREffect );


typedef
   struct _IRDirty {






      IRCallee* cee;
      IRExpr* guard;
      IRExpr** args;
      IRTemp tmp;


      IREffect mFx;
      IRExpr* mAddr;
      Int mSize;


      Bool needsBBP;
      Int nFxState;
      struct {
         IREffect fx:16;
         UShort offset;
         UShort size;
         UChar nRepeats;
         UChar repeatLen;
      } fxState[7];
# 1990 "../VEX/pub/libvex_ir.h"
   }
   IRDirty;


extern void ppIRDirty ( IRDirty* );


extern IRDirty* emptyIRDirty ( void );


extern IRDirty* deepCopyIRDirty ( IRDirty* );







extern
IRDirty* unsafeIRDirty_0_N ( Int regparms, HChar* name, void* addr,
                             IRExpr** args );



extern
IRDirty* unsafeIRDirty_1_N ( IRTemp dst,
                             Int regparms, HChar* name, void* addr,
                             IRExpr** args );




typedef
   enum {
      Imbe_Fence=0x18000,



      Imbe_CancelReservation
   }
   IRMBusEvent;

extern void ppIRMBusEvent ( IRMBusEvent );
# 2100 "../VEX/pub/libvex_ir.h"
typedef
   struct {
      IRTemp oldHi;
      IRTemp oldLo;
      IREndness end;
      IRExpr* addr;
      IRExpr* expdHi;
      IRExpr* expdLo;
      IRExpr* dataHi;
      IRExpr* dataLo;
   }
   IRCAS;

extern void ppIRCAS ( IRCAS* cas );

extern IRCAS* mkIRCAS ( IRTemp oldHi, IRTemp oldLo,
                        IREndness end, IRExpr* addr,
                        IRExpr* expdHi, IRExpr* expdLo,
                        IRExpr* dataHi, IRExpr* dataLo );

extern IRCAS* deepCopyIRCAS ( IRCAS* );



typedef
   struct {
      IRRegArray* descr;
      IRExpr* ix;
      Int bias;
      IRExpr* data;
   } IRPutI;

extern void ppIRPutI ( IRPutI* puti );

extern IRPutI* mkIRPutI ( IRRegArray* descr, IRExpr* ix,
                          Int bias, IRExpr* data );

extern IRPutI* deepCopyIRPutI ( IRPutI* );
# 2152 "../VEX/pub/libvex_ir.h"
typedef
   enum {
      Ist_NoOp=0x19000,
      Ist_IMark,
      Ist_AbiHint,
      Ist_Put,
      Ist_PutI,
      Ist_WrTmp,
      Ist_Store,
      Ist_CAS,
      Ist_LLSC,
      Ist_Dirty,
      Ist_MBE,
      Ist_Exit
   }
   IRStmtTag;
# 2178 "../VEX/pub/libvex_ir.h"
typedef
   struct _IRStmt {
      IRStmtTag tag;
      union {





         struct {
  } NoOp;
# 2212 "../VEX/pub/libvex_ir.h"
         struct {
            Addr64 addr;
            Int len;
            UChar delta;

         } IMark;
# 2233 "../VEX/pub/libvex_ir.h"
         struct {
            IRExpr* base;
            Int len;
            IRExpr* nia;
         } AbiHint;




         struct {
            Int offset;
            IRExpr* data;
         } Put;
# 2254 "../VEX/pub/libvex_ir.h"
         struct {
            IRPutI* details;
         } PutI;
# 2265 "../VEX/pub/libvex_ir.h"
         struct {
            IRTemp tmp;
            IRExpr* data;
         } WrTmp;






         struct {
            IREndness end;
            IRExpr* addr;
            IRExpr* data;
         } Store;
# 2295 "../VEX/pub/libvex_ir.h"
         struct {
            IRCAS* details;
         } CAS;
# 2343 "../VEX/pub/libvex_ir.h"
         struct {
            IREndness end;
            IRTemp result;
            IRExpr* addr;
            IRExpr* storedata;
         } LLSC;
# 2361 "../VEX/pub/libvex_ir.h"
         struct {
            IRDirty* details;
         } Dirty;







         struct {
            IRMBusEvent event;
         } MBE;
# 2382 "../VEX/pub/libvex_ir.h"
         struct {
            IRExpr* guard;
            IRConst* dst;
            IRJumpKind jk;
            Int offsIP;
         } Exit;
      } Ist;
   }
   IRStmt;


extern IRStmt* IRStmt_NoOp ( void );
extern IRStmt* IRStmt_IMark ( Addr64 addr, Int len, UChar delta );
extern IRStmt* IRStmt_AbiHint ( IRExpr* base, Int len, IRExpr* nia );
extern IRStmt* IRStmt_Put ( Int off, IRExpr* data );
extern IRStmt* IRStmt_PutI ( IRPutI* details );
extern IRStmt* IRStmt_WrTmp ( IRTemp tmp, IRExpr* data );
extern IRStmt* IRStmt_Store ( IREndness end, IRExpr* addr, IRExpr* data );
extern IRStmt* IRStmt_CAS ( IRCAS* details );
extern IRStmt* IRStmt_LLSC ( IREndness end, IRTemp result,
                                IRExpr* addr, IRExpr* storedata );
extern IRStmt* IRStmt_Dirty ( IRDirty* details );
extern IRStmt* IRStmt_MBE ( IRMBusEvent event );
extern IRStmt* IRStmt_Exit ( IRExpr* guard, IRJumpKind jk, IRConst* dst,
                                Int offsIP );


extern IRStmt* deepCopyIRStmt ( IRStmt* );


extern void ppIRStmt ( IRStmt* );
# 2423 "../VEX/pub/libvex_ir.h"
typedef
   struct {
      IRType* types;
      Int types_size;
      Int types_used;
   }
   IRTypeEnv;


extern IRTemp newIRTemp ( IRTypeEnv*, IRType );


extern IRTypeEnv* deepCopyIRTypeEnv ( IRTypeEnv* );


extern void ppIRTypeEnv ( IRTypeEnv* );
# 2456 "../VEX/pub/libvex_ir.h"
typedef
   struct {
      IRTypeEnv* tyenv;
      IRStmt** stmts;
      Int stmts_size;
      Int stmts_used;
      IRExpr* next;
      IRJumpKind jumpkind;
      Int offsIP;
   }
   IRSB;


extern IRSB* emptyIRSB ( void );


extern IRSB* deepCopyIRSB ( IRSB* );



extern IRSB* deepCopyIRSBExceptStmts ( IRSB* );


extern void ppIRSB ( IRSB* );


extern void addStmtToIRSB ( IRSB*, IRStmt* );







extern IRTypeEnv* emptyIRTypeEnv ( void );


extern IRType typeOfIRConst ( IRConst* );
extern IRType typeOfIRTemp ( IRTypeEnv*, IRTemp );
extern IRType typeOfIRExpr ( IRTypeEnv*, IRExpr* );


extern void sanityCheckIRSB ( IRSB* bb,
                              HChar* caller,
                              Bool require_flatness,
                              IRType guest_word_size );
extern Bool isFlatIRStmt ( IRStmt* );


extern Bool isPlausibleIRType ( IRType ty );





void vex_inject_ir(IRSB *, IREndness);
# 42 "../VEX/pub/libvex.h" 2
# 52 "../VEX/pub/libvex.h"
typedef
   enum {
      VexArch_INVALID,
      VexArchX86,
      VexArchAMD64,
      VexArchARM,
      VexArchPPC32,
      VexArchPPC64,
      VexArchS390X,
      VexArchMIPS32
   }
   VexArch;
# 181 "../VEX/pub/libvex.h"
extern const HChar* LibVEX_ppVexArch ( VexArch );
extern const HChar* LibVEX_ppVexHwCaps ( VexArch, UInt );






typedef
   struct {

      UInt hwcaps;

      Int ppc_cache_line_szB;


      UInt ppc_dcbz_szB;
      UInt ppc_dcbzl_szB;
   }
   VexArchInfo;


extern
void LibVEX_default_VexArchInfo ( VexArchInfo* vai );
# 263 "../VEX/pub/libvex.h"
typedef
   struct {


      Int guest_stack_redzone_size;




      Bool guest_amd64_assume_fs_is_zero;




      Bool guest_amd64_assume_gs_is_0x60;



      Bool guest_ppc_zap_RZ_at_blr;





      Bool (*guest_ppc_zap_RZ_at_bl)(Addr64);




      Bool guest_ppc_sc_continues_at_LR;




      Bool host_ppc_calls_use_fndescrs;




      Bool host_ppc32_regalign_int64_args;
   }
   VexAbiInfo;


extern
void LibVEX_default_VexAbiInfo ( VexAbiInfo* vbi );
# 332 "../VEX/pub/libvex.h"
typedef enum { VexRegUpdSpAtMemAccess,
               VexRegUpdUnwindregsAtMemAccess,
               VexRegUpdAllregsAtMemAccess,
               VexRegUpdAllregsAtEachInsn } VexRegisterUpdates;



typedef
   struct {

      Int iropt_verbosity;


      Int iropt_level;

      VexRegisterUpdates iropt_register_updates;



      Int iropt_unroll_thresh;



      Int guest_max_insns;





      Int guest_chase_thresh;


      Bool guest_chase_cond;
   }
   VexControl;




extern
void LibVEX_default_VexControl ( VexControl* vcon );
# 385 "../VEX/pub/libvex.h"
extern HChar* private_LibVEX_alloc_first;
extern HChar* private_LibVEX_alloc_curr;
extern HChar* private_LibVEX_alloc_last;
extern void private_LibVEX_alloc_OOM(void) __attribute__((noreturn));

static inline void* LibVEX_Alloc ( Int nbytes )
{
   struct align {
      char c;
      union {
         char c;
         short s;
         int i;
         long l;
         long long ll;
         float f;
         double d;



         void *pto;
         void (*ptf)(void);
      } x;
   };





   HChar* curr;
   HChar* next;
   Int ALIGN;
   ALIGN = ((Int)(HWord)&((struct align*)0)->x) - 1;
   nbytes = (nbytes + ALIGN) & ~ALIGN;
   curr = private_LibVEX_alloc_curr;
   next = curr + nbytes;
   if (next >= private_LibVEX_alloc_last)
      private_LibVEX_alloc_OOM();
   private_LibVEX_alloc_curr = next;
   return curr;

}


extern void LibVEX_ShowAllocStats ( void );
# 443 "../VEX/pub/libvex.h"
typedef
   struct {


      Int total_sizeB;

      Int offset_SP;
      Int sizeof_SP;

      Int offset_FP;
      Int sizeof_FP;

      Int offset_IP;
      Int sizeof_IP;


      Int n_alwaysDefd;
      struct {
         Int offset;
         Int size;
      } alwaysDefd[24];
   }
   VexGuestLayout;
# 493 "../VEX/pub/libvex.h"
extern void LibVEX_Init (






   __attribute__ ((noreturn))

   void (*failure_exit) ( void ),


   void (*log_bytes) ( HChar*, Int nbytes ),


   Int debuglevel,


   Bool valgrind_support,


               VexControl* vcon
);







typedef
   struct {

      enum { VexTransOK,
             VexTransAccessFail, VexTransOutputFull } status;

      UInt n_sc_extents;


      Int offs_profInc;


      UInt n_guest_instrs;
   }
   VexTranslateResult;
# 548 "../VEX/pub/libvex.h"
typedef
   struct {
      Addr64 base[3];
      UShort len[3];
      UShort n_used;
   }
   VexGuestExtents;




typedef
   struct {


      VexArch arch_guest;
      VexArchInfo archinfo_guest;
      VexArch arch_host;
      VexArchInfo archinfo_host;
      VexAbiInfo abiinfo_both;




      void* callback_opaque;



      UChar* guest_bytes;




      Addr64 guest_bytes_addr;



      Bool (*chase_into_ok) ( void*, Addr64 );


      VexGuestExtents* guest_extents;


      UChar* host_bytes;
      Int host_bytes_size;

      Int* host_bytes_used;



      IRSB* (*instrument1) ( void*,
                               IRSB*,
                               VexGuestLayout*,
                               VexGuestExtents*,
                               IRType gWordTy, IRType hWordTy );
      IRSB* (*instrument2) ( void*,
                               IRSB*,
                               VexGuestLayout*,
                               VexGuestExtents*,
                               IRType gWordTy, IRType hWordTy );

      IRSB* (*finaltidy) ( IRSB* );






      UInt (*needs_self_check)( void*,
                                VexGuestExtents* );
# 628 "../VEX/pub/libvex.h"
      Bool (*preamble_function)( void*, IRSB*);


      Int traceflags;



      Bool addProfInc;
# 672 "../VEX/pub/libvex.h"
      void* disp_cp_chain_me_to_slowEP;
      void* disp_cp_chain_me_to_fastEP;
      void* disp_cp_xindir;
      void* disp_cp_xassisted;
   }
   VexTranslateArgs;


extern
VexTranslateResult LibVEX_Translate ( VexTranslateArgs* );
# 706 "../VEX/pub/libvex.h"
typedef
   struct {
      HWord start;
      HWord len;
   }
   VexInvalRange;





extern
VexInvalRange LibVEX_Chain ( VexArch arch_host,
                             void* place_to_chain,
                             void* disp_cp_chain_me_EXPECTED,
                             void* place_to_jump_to );





extern
VexInvalRange LibVEX_UnChain ( VexArch arch_host,
                               void* place_to_unchain,
                               void* place_to_jump_to_EXPECTED,
                               void* disp_cp_chain_me );





extern
Int LibVEX_evCheckSzB ( VexArch arch_host );




extern
VexInvalRange LibVEX_PatchProfInc ( VexArch arch_host,
                                    void* place_to_patch,
                                    ULong* location_of_counter );






extern void LibVEX_ShowStats ( void );
# 763 "../VEX/pub/libvex.h"
typedef
   struct {
      IROp op;
      HWord result;
      HWord opnd1;
      HWord opnd2;
      HWord opnd3;
      HWord opnd4;
      IRType t_result;
      IRType t_opnd1;
      IRType t_opnd2;
      IRType t_opnd3;
      IRType t_opnd4;
      UInt rounding_mode;
      UInt num_operands;
      Bool shift_amount_is_immediate;
   }
   IRICB;

extern void LibVEX_InitIRI ( const IRICB * );
# 50 "pub_core_basics.h" 2
# 60 "pub_core_basics.h"
# 1 "../VEX/pub/libvex_guest_arm.h" 1
# 35 "../VEX/pub/libvex_guest_arm.h"
# 1 "../VEX/pub/libvex_emnote.h" 1
# 58 "../VEX/pub/libvex_emnote.h"
typedef
   enum {

      EmNote_NONE=0,


      EmWarn_X86_x87exns,


      EmWarn_X86_x87precision,


      EmWarn_X86_sseExns,


      EmWarn_X86_fz,


      EmWarn_X86_daz,


      EmWarn_X86_acFlag,


      EmWarn_PPCexns,


      EmWarn_PPC64_redir_overflow,
      EmWarn_PPC64_redir_underflow,




      EmWarn_S390X_fpext_rounding,


      EmFail_S390X_stfle,


      EmFail_S390X_stckf,


      EmFail_S390X_ecag,



      EmFail_S390X_fpext,

      EmNote_NUMBER
   }
   VexEmNote;



extern HChar* LibVEX_EmNote_string ( VexEmNote );
# 36 "../VEX/pub/libvex_guest_arm.h" 2






typedef
   struct {


      UInt host_EvC_FAILADDR;
      UInt host_EvC_COUNTER;
      UInt guest_R0;
      UInt guest_R1;
      UInt guest_R2;
      UInt guest_R3;
      UInt guest_R4;
      UInt guest_R5;
      UInt guest_R6;
      UInt guest_R7;
      UInt guest_R8;
      UInt guest_R9;
      UInt guest_R10;
      UInt guest_R11;
      UInt guest_R12;
      UInt guest_R13;
      UInt guest_R14;
      UInt guest_R15T;
# 76 "../VEX/pub/libvex_guest_arm.h"
      UInt guest_CC_OP;
      UInt guest_CC_DEP1;
      UInt guest_CC_DEP2;
      UInt guest_CC_NDEP;





      UInt guest_QFLAG32;



      UInt guest_GEFLAG0;
      UInt guest_GEFLAG1;
      UInt guest_GEFLAG2;
      UInt guest_GEFLAG3;



      UInt guest_EMNOTE;


      UInt guest_TISTART;
      UInt guest_TILEN;







      UInt guest_NRADDR;






      UInt guest_IP_AT_SYSCALL;



      ULong guest_D0;
      ULong guest_D1;
      ULong guest_D2;
      ULong guest_D3;
      ULong guest_D4;
      ULong guest_D5;
      ULong guest_D6;
      ULong guest_D7;
      ULong guest_D8;
      ULong guest_D9;
      ULong guest_D10;
      ULong guest_D11;
      ULong guest_D12;
      ULong guest_D13;
      ULong guest_D14;
      ULong guest_D15;
      ULong guest_D16;
      ULong guest_D17;
      ULong guest_D18;
      ULong guest_D19;
      ULong guest_D20;
      ULong guest_D21;
      ULong guest_D22;
      ULong guest_D23;
      ULong guest_D24;
      ULong guest_D25;
      ULong guest_D26;
      ULong guest_D27;
      ULong guest_D28;
      ULong guest_D29;
      ULong guest_D30;
      ULong guest_D31;
      UInt guest_FPSCR;
# 160 "../VEX/pub/libvex_guest_arm.h"
      UInt guest_TPIDRURO;
# 195 "../VEX/pub/libvex_guest_arm.h"
      UInt guest_ITSTATE;


      UInt padding1;
      UInt padding2;
      UInt padding3;
      UInt padding4;
      UInt padding5;
   }
   VexGuestARMState;
# 215 "../VEX/pub/libvex_guest_arm.h"
extern
void LibVEX_GuestARM_initialise ( VexGuestARMState* vex_state );



extern
UInt LibVEX_GuestARM_get_cpsr ( VexGuestARMState* vex_state );
# 61 "pub_core_basics.h" 2
# 86 "pub_core_basics.h"
typedef
   struct {
      ULong r_pc;
      ULong r_sp;
      union {
         struct {
            UInt r_ebp;
         } X86;
         struct {
            ULong r_rbp;
         } AMD64;
         struct {
            UInt r_lr;
         } PPC32;
         struct {
            ULong r_lr;
         } PPC64;
         struct {
            UInt r14;
            UInt r12;
            UInt r11;
            UInt r7;
         } ARM;
         struct {
            ULong r_fp;
            ULong r_lr;
         } S390X;
         struct {
            UInt r30;
            UInt r31;
            UInt r28;
         } MIPS32;
      } misc;
   }
   UnwindStartRegs;
# 32 "m_stacktrace.c" 2
# 1 "pub_core_vki.h" 1
# 44 "pub_core_vki.h"
# 1 "../include/pub_tool_vki.h" 1
# 49 "../include/pub_tool_vki.h"
# 1 "../include/vki/vki-linux.h" 1
# 91 "../include/vki/vki-linux.h"
# 1 "../include/vki/vki-posixtypes-arm-linux.h" 1
# 39 "../include/vki/vki-posixtypes-arm-linux.h"
typedef unsigned short __vki_kernel_mode_t;
typedef long __vki_kernel_off_t;
typedef int __vki_kernel_pid_t;
typedef unsigned short __vki_kernel_ipc_pid_t;
typedef unsigned short __vki_kernel_uid_t;
typedef unsigned short __vki_kernel_gid_t;
typedef unsigned int __vki_kernel_size_t;
typedef long __vki_kernel_time_t;
typedef long __vki_kernel_suseconds_t;
typedef long __vki_kernel_clock_t;
typedef int __vki_kernel_timer_t;
typedef int __vki_kernel_clockid_t;
typedef char * __vki_kernel_caddr_t;
typedef unsigned int __vki_kernel_uid32_t;
typedef unsigned int __vki_kernel_gid32_t;

typedef unsigned short __vki_kernel_old_uid_t;
typedef unsigned short __vki_kernel_old_gid_t;

typedef long long __vki_kernel_loff_t;

typedef struct {
 int val[2];
} __vki_kernel_fsid_t;
# 92 "../include/vki/vki-linux.h" 2
# 161 "../include/vki/vki-linux.h"
typedef struct {
 unsigned long fds_bits [(1024/(8 * sizeof(unsigned long)))];
} __vki_kernel_fd_set;

typedef int __vki_kernel_key_t;
typedef int __vki_kernel_mqd_t;





typedef __vki_kernel_fd_set vki_fd_set;
typedef __vki_kernel_mode_t vki_mode_t;
typedef __vki_kernel_off_t vki_off_t;
typedef __vki_kernel_pid_t vki_pid_t;
typedef __vki_kernel_key_t vki_key_t;
typedef __vki_kernel_suseconds_t vki_suseconds_t;
typedef __vki_kernel_timer_t vki_timer_t;
typedef __vki_kernel_clockid_t vki_clockid_t;
typedef __vki_kernel_mqd_t vki_mqd_t;


typedef __vki_kernel_uid32_t vki_uid_t;
typedef __vki_kernel_gid32_t vki_gid_t;

typedef __vki_kernel_old_uid_t vki_old_uid_t;
typedef __vki_kernel_old_gid_t vki_old_gid_t;

typedef __vki_kernel_loff_t vki_loff_t;

typedef __vki_kernel_size_t vki_size_t;
typedef __vki_kernel_time_t vki_time_t;
typedef __vki_kernel_clock_t vki_clock_t;
typedef __vki_kernel_caddr_t vki_caddr_t;

typedef unsigned long vki_u_long;

typedef unsigned int vki_uint;
# 213 "../include/vki/vki-linux.h"
# 1 "../include/vki/vki-arm-linux.h" 1
# 45 "../include/vki/vki-arm-linux.h"
typedef unsigned char __vki_u8;

typedef __signed__ short __vki_s16;
typedef unsigned short __vki_u16;

typedef __signed__ int __vki_s32;
typedef unsigned int __vki_u32;

typedef __signed__ long long __vki_s64;
typedef unsigned long long __vki_u64;

typedef unsigned short vki_u16;

typedef unsigned int vki_u32;
# 87 "../include/vki/vki-arm-linux.h"
typedef void __vki_signalfn_t(int);
typedef __vki_signalfn_t *__vki_sighandler_t;

typedef void __vki_restorefn_t(void);
typedef __vki_restorefn_t *__vki_sigrestore_t;
# 100 "../include/vki/vki-arm-linux.h"
typedef unsigned long vki_old_sigset_t;

typedef struct {
 unsigned long sig[(64 / 32)];
} vki_sigset_t;
# 162 "../include/vki/vki-arm-linux.h"
struct vki_old_sigaction {




        __vki_sighandler_t ksa_handler;
        vki_old_sigset_t sa_mask;
        unsigned long sa_flags;
        __vki_sigrestore_t sa_restorer;
};

struct vki_sigaction_base {

 __vki_sighandler_t ksa_handler;
 unsigned long sa_flags;
 __vki_sigrestore_t sa_restorer;
 vki_sigset_t sa_mask;
};



typedef struct vki_sigaction_base vki_sigaction_toK_t;
typedef struct vki_sigaction_base vki_sigaction_fromK_t;


typedef struct vki_sigaltstack {
 void *ss_sp;
 int ss_flags;
 vki_size_t ss_size;
} vki_stack_t;





struct vki_sigcontext {
  unsigned long trap_no;
  unsigned long error_code;
  unsigned long oldmask;
  unsigned long arm_r0;
  unsigned long arm_r1;
  unsigned long arm_r2;
  unsigned long arm_r3;
  unsigned long arm_r4;
  unsigned long arm_r5;
  unsigned long arm_r6;
  unsigned long arm_r7;
  unsigned long arm_r8;
  unsigned long arm_r9;
  unsigned long arm_r10;
  unsigned long arm_fp;
  unsigned long arm_ip;
  unsigned long arm_sp;
  unsigned long arm_lr;
  unsigned long arm_pc;
  unsigned long arm_cpsr;
  unsigned long fault_address;
};
# 280 "../include/vki/vki-arm-linux.h"
struct vki_f_owner_ex {
 int type;
 __vki_kernel_pid_t pid;
};
# 320 "../include/vki/vki-arm-linux.h"
struct vki_stat {
 unsigned long st_dev;
 unsigned long st_ino;
 unsigned short st_mode;
 unsigned short st_nlink;
 unsigned short st_uid;
 unsigned short st_gid;
 unsigned long st_rdev;
 unsigned long st_size;
 unsigned long st_blksize;
 unsigned long st_blocks;
 unsigned long st_atime;
 unsigned long st_atime_nsec;
 unsigned long st_mtime;
 unsigned long st_mtime_nsec;
 unsigned long st_ctime;
 unsigned long st_ctime_nsec;
 unsigned long __unused4;
 unsigned long __unused5;
};

struct vki_stat64 {
 unsigned long long st_dev;
 unsigned char __pad0[4];


 unsigned long __st_ino;

 unsigned int st_mode;
 unsigned int st_nlink;

 unsigned long st_uid;
 unsigned long st_gid;

 unsigned long long st_rdev;
 unsigned char __pad3[4];

 long long st_size;
 unsigned long st_blksize;

 unsigned long st_blocks;
 unsigned long __pad4;

 unsigned long st_atime;
 unsigned long st_atime_nsec;

 unsigned long st_mtime;
 unsigned int st_mtime_nsec;

 unsigned long st_ctime;
 unsigned long st_ctime_nsec;

 unsigned long long st_ino;
};






struct vki_statfs {
 __vki_u32 f_type;
 __vki_u32 f_bsize;
 __vki_u32 f_blocks;
 __vki_u32 f_bfree;
 __vki_u32 f_bavail;
 __vki_u32 f_files;
 __vki_u32 f_ffree;
 __vki_kernel_fsid_t f_fsid;
 __vki_u32 f_namelen;
 __vki_u32 f_frsize;
 __vki_u32 f_spare[5];
};





struct vki_winsize {
 unsigned short ws_row;
 unsigned short ws_col;
 unsigned short ws_xpixel;
 unsigned short ws_ypixel;
};


struct vki_termio {
 unsigned short c_iflag;
 unsigned short c_oflag;
 unsigned short c_cflag;
 unsigned short c_lflag;
 unsigned char c_line;
 unsigned char c_cc[8];
};






typedef unsigned char vki_cc_t;
typedef unsigned int vki_tcflag_t;


struct vki_termios {
 vki_tcflag_t c_iflag;
 vki_tcflag_t c_oflag;
 vki_tcflag_t c_cflag;
 vki_tcflag_t c_lflag;
 vki_cc_t c_line;
 vki_cc_t c_cc[19];
};
# 524 "../include/vki/vki-arm-linux.h"
struct vki_pollfd {
 int fd;
 short events;
 short revents;
};





struct vki_user_fp {
 struct vki_fp_reg {
  unsigned int sign1:1;
  unsigned int unused:15;
  unsigned int sign2:1;
  unsigned int exponent:14;
  unsigned int j:1;
  unsigned int mantissa1:31;
  unsigned int mantissa0:32;
 } fpregs[8];
 unsigned int fpsr:32;
 unsigned int fpcr:32;
 unsigned char ftype[8];
 unsigned int init_flag;
};

struct vki_user_vfp {
 unsigned long long fpregs[32];
 unsigned long fpscr;
};



struct vki_iwmmxt_struct {
 unsigned int save[0x98 / sizeof(unsigned int)];
};

struct vki_crunch_state {
 unsigned int mvdx[16][2];
 unsigned int mvax[4][3];
 unsigned int dspsc[2];
};



struct vki_user_regs_struct {
    long uregs[18];
};
# 594 "../include/vki/vki-arm-linux.h"
typedef unsigned long vki_elf_greg_t;


typedef vki_elf_greg_t vki_elf_gregset_t[(sizeof (struct vki_user_regs_struct) / sizeof(vki_elf_greg_t))];

typedef struct vki_user_fp vki_elf_fpregset_t;







struct vki_ucontext {
 unsigned long uc_flags;
 struct vki_ucontext *uc_link;
 vki_stack_t uc_stack;
 struct vki_sigcontext uc_mcontext;
 vki_sigset_t uc_sigmask;
 int __unused[32 - (sizeof (vki_sigset_t) / sizeof (int))];
 unsigned long uc_regspace[128] __attribute__((__aligned__(8)));

};
# 634 "../include/vki/vki-arm-linux.h"
struct vki_user_desc {
 unsigned int entry_number;
 unsigned long base_addr;
 unsigned int limit;
 unsigned int seg_32bit:1;
 unsigned int contents:2;
 unsigned int read_exec_only:1;
 unsigned int limit_in_pages:1;
 unsigned int seg_not_present:1;
 unsigned int useable:1;





 unsigned int reserved:25;
};


typedef struct vki_user_desc vki_modify_ldt_t;





struct vki_ipc64_perm
{
 __vki_kernel_key_t key;
 __vki_kernel_uid32_t uid;
 __vki_kernel_gid32_t gid;
 __vki_kernel_uid32_t cuid;
 __vki_kernel_gid32_t cgid;
 __vki_kernel_mode_t mode;
 unsigned short __pad1;
 unsigned short seq;
 unsigned short __pad2;
 unsigned long __unused1;
 unsigned long __unused2;
};





struct vki_semid64_ds {
 struct vki_ipc64_perm sem_perm;
 __vki_kernel_time_t sem_otime;
 unsigned long __unused1;
 __vki_kernel_time_t sem_ctime;
 unsigned long __unused2;
 unsigned long sem_nsems;
 unsigned long __unused3;
 unsigned long __unused4;
};





struct vki_msqid64_ds {
 struct vki_ipc64_perm msg_perm;
 __vki_kernel_time_t msg_stime;
 unsigned long __unused1;
 __vki_kernel_time_t msg_rtime;
 unsigned long __unused2;
 __vki_kernel_time_t msg_ctime;
 unsigned long __unused3;
 unsigned long msg_cbytes;
 unsigned long msg_qnum;
 unsigned long msg_qbytes;
 __vki_kernel_pid_t msg_lspid;
 __vki_kernel_pid_t msg_lrpid;
 unsigned long __unused4;
 unsigned long __unused5;
};





struct vki_ipc_kludge {
 struct vki_msgbuf *msgp;
 long msgtyp;
};
# 736 "../include/vki/vki-arm-linux.h"
struct vki_shmid64_ds {
 struct vki_ipc64_perm shm_perm;
 vki_size_t shm_segsz;
 __vki_kernel_time_t shm_atime;
 unsigned long __unused1;
 __vki_kernel_time_t shm_dtime;
 unsigned long __unused2;
 __vki_kernel_time_t shm_ctime;
 unsigned long __unused3;
 __vki_kernel_pid_t shm_cpid;
 __vki_kernel_pid_t shm_lpid;
 unsigned long shm_nattch;
 unsigned long __unused4;
 unsigned long __unused5;
};

struct vki_shminfo64 {
 unsigned long shmmax;
 unsigned long shmmin;
 unsigned long shmmni;
 unsigned long shmseg;
 unsigned long shmall;
 unsigned long __unused1;
 unsigned long __unused2;
 unsigned long __unused3;
 unsigned long __unused4;
};
# 817 "../include/vki/vki-arm-linux.h"
struct vki_vm86_regs {



 long ebx;
 long ecx;
 long edx;
 long esi;
 long edi;
 long ebp;
 long eax;
 long __null_ds;
 long __null_es;
 long __null_fs;
 long __null_gs;
 long orig_eax;
 long eip;
 unsigned short cs, __csh;
 long eflags;
 long esp;
 unsigned short ss, __ssh;



 unsigned short es, __esh;
 unsigned short ds, __dsh;
 unsigned short fs, __fsh;
 unsigned short gs, __gsh;
};

struct vki_revectored_struct {
 unsigned long __map[8];
};

struct vki_vm86_struct {
 struct vki_vm86_regs regs;
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct vki_revectored_struct int_revectored;
 struct vki_revectored_struct int21_revectored;
};

struct vki_vm86plus_info_struct {
 unsigned long force_return_for_pic:1;
 unsigned long vm86dbg_active:1;
 unsigned long vm86dbg_TFpendig:1;
 unsigned long unused:28;
 unsigned long is_vm86pus:1;
 unsigned char vm86dbg_intxxtab[32];
};

struct vki_vm86plus_struct {
 struct vki_vm86_regs regs;
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct vki_revectored_struct int_revectored;
 struct vki_revectored_struct int21_revectored;
 struct vki_vm86plus_info_struct vm86plus;
};
# 214 "../include/vki/vki-linux.h" 2
# 226 "../include/vki/vki-linux.h"
typedef __vki_s32 vki_int32_t;
typedef __vki_s64 vki_int64_t;

typedef __vki_u8 vki_uint8_t;
typedef __vki_u16 vki_uint16_t;
typedef __vki_u32 vki_uint32_t;

typedef __vki_u16 __vki_le16;
# 245 "../include/vki/vki-linux.h"
struct vki_sysinfo {
 long uptime;
 unsigned long loads[3];
 unsigned long totalram;
 unsigned long freeram;
 unsigned long sharedram;
 unsigned long bufferram;
 unsigned long totalswap;
 unsigned long freeswap;
 unsigned short procs;
 unsigned short pad;
 unsigned long totalhigh;
 unsigned long freehigh;
 unsigned int mem_unit;
 char _f[20-2*sizeof(long)-sizeof(int)];
};
# 271 "../include/vki/vki-linux.h"
struct vki_timespec {
 vki_time_t tv_sec;
 long tv_nsec;
};

struct vki_timeval {
 vki_time_t tv_sec;
 vki_suseconds_t tv_usec;
};

struct vki_timezone {
 int tz_minuteswest;
 int tz_dsttime;
};

struct vki_itimerspec {
        struct vki_timespec it_interval;
        struct vki_timespec it_value;
};

struct vki_itimerval {
 struct vki_timeval it_interval;
 struct vki_timeval it_value;
};





struct vki_timex {
 unsigned int modes;
 long offset;
 long freq;
 long maxerror;
 long esterror;
 int status;
 long constant;
 long precision;
 long tolerance;


 struct vki_timeval time;
 long tick;

 long ppsfreq;
 long jitter;
 int shift;
 long stabil;
 long jitcnt;
 long calcnt;
 long errcnt;
 long stbcnt;

 int :32; int :32; int :32; int :32;
 int :32; int :32; int :32; int :32;
 int :32; int :32; int :32; int :32;
};
# 345 "../include/vki/vki-linux.h"
struct vki_tms {
 vki_clock_t tms_utime;
 vki_clock_t tms_stime;
 vki_clock_t tms_cutime;
 vki_clock_t tms_cstime;
};





struct vki_utimbuf {
 vki_time_t actime;
 vki_time_t modtime;
};
# 380 "../include/vki/vki-linux.h"
struct vki_sched_param {
 int sched_priority;
};
# 392 "../include/vki/vki-linux.h"
typedef union vki_sigval {
 int sival_int;
 void *sival_ptr;
} vki_sigval_t;
# 417 "../include/vki/vki-linux.h"
typedef struct vki_siginfo {
 int si_signo;
 int si_errno;
 int si_code;

 union {
  int _pad[((128 - (3 * sizeof(int))) / sizeof(int))];


  struct {
   vki_pid_t _pid;
   vki_uid_t _uid;
  } _kill;


  struct {
   vki_timer_t _tid;
   int _overrun;
   char _pad[sizeof( vki_uid_t) - sizeof(int)];
   vki_sigval_t _sigval;
   int _sys_private;
  } _timer;


  struct {
   vki_pid_t _pid;
   vki_uid_t _uid;
   vki_sigval_t _sigval;
  } _rt;


  struct {
   vki_pid_t _pid;
   vki_uid_t _uid;
   int _status;
   vki_clock_t _utime;
   vki_clock_t _stime;
  } _sigchld;


  struct {
   void *_addr;



  } _sigfault;


  struct {
   long _band;
   int _fd;
  } _sigpoll;
 } _sifields;
} vki_siginfo_t;
# 537 "../include/vki/vki-linux.h"
typedef struct vki_sigevent {
 vki_sigval_t sigev_value;
 int sigev_signo;
 int sigev_notify;
 union {
  int _pad[((64 - (sizeof(int) * 2 + sizeof(vki_sigval_t))) / sizeof(int))];
   int _tid;

  struct {
   void (*_function)(vki_sigval_t);
   void *_attribute;
  } _sigev_thread;
 } _sigev_un;
} vki_sigevent_t;
# 585 "../include/vki/vki-linux.h"
enum vki_sock_type {
 VKI_SOCK_STREAM = 1,

};





struct vki_iovec
{
 void *iov_base;
 __vki_kernel_size_t iov_len;
};
# 608 "../include/vki/vki-linux.h"
typedef unsigned short vki_sa_family_t;

struct vki_sockaddr {
 vki_sa_family_t sa_family;
 char sa_data[14];
};

struct vki_msghdr {
 void * msg_name;
 int msg_namelen;
 struct vki_iovec * msg_iov;
 __vki_kernel_size_t msg_iovlen;
 void * msg_control;
 __vki_kernel_size_t msg_controllen;
 unsigned msg_flags;
};

struct vki_mmsghdr {
 struct vki_msghdr msg_hdr;
 unsigned msg_len;
};

struct vki_cmsghdr {
 __vki_kernel_size_t cmsg_len;
        int cmsg_level;
        int cmsg_type;
};
# 649 "../include/vki/vki-linux.h"
static __inline__ struct vki_cmsghdr * __vki_cmsg_nxthdr(void *__ctl, __vki_kernel_size_t __size,
            struct vki_cmsghdr *__cmsg)
{
 struct vki_cmsghdr * __ptr;

 __ptr = (struct vki_cmsghdr*)(((unsigned char *) __cmsg) + ( ((__cmsg->cmsg_len)+sizeof(long)-1) & ~(sizeof(long)-1) ));
 if ((unsigned long)((char*)(__ptr+1) - (char *) __ctl) > __size)
  return (struct vki_cmsghdr *)0;

 return __ptr;
}

static __inline__ struct vki_cmsghdr * vki_cmsg_nxthdr (struct vki_msghdr *__msg, struct vki_cmsghdr *__cmsg)
{
 return __vki_cmsg_nxthdr(__msg->msg_control, __msg->msg_controllen, __cmsg);
}
# 680 "../include/vki/vki-linux.h"
struct vki_in_addr {
 __vki_u32 s_addr;
};



struct vki_sockaddr_in {
  vki_sa_family_t sin_family;
  unsigned short int sin_port;
  struct vki_in_addr sin_addr;


  unsigned char __pad[16 - sizeof(short int) -
   sizeof(unsigned short int) - sizeof(struct vki_in_addr)];
};





struct vki_in6_addr
{
 union
 {
  __vki_u8 u6_addr8[16];
  __vki_u16 u6_addr16[8];
  __vki_u32 u6_addr32[4];
 } vki_in6_u;



};

struct vki_sockaddr_in6 {
 unsigned short int sin6_family;
 __vki_u16 sin6_port;
 __vki_u32 sin6_flowinfo;
 struct vki_in6_addr sin6_addr;
 __vki_u32 sin6_scope_id;
};







struct vki_sockaddr_un {
 vki_sa_family_t sun_family;
 char sun_path[108];
};







struct vki_ifmap
{
 unsigned long mem_start;
 unsigned long mem_end;
 unsigned short base_addr;
 unsigned char irq;
 unsigned char dma;
 unsigned char port;

};

struct vki_if_settings
{
 unsigned int type;
 unsigned int size;
 union {



  void *raw_hdlc;
  void *cisco;
  void *fr;
  void *fr_pvc;
  void *fr_pvc_info;


  void *sync;
  void *te1;
 } ifs_ifsu;
};

struct vki_ifreq
{

 union
 {
  char ifrn_name[16];
 } ifr_ifrn;

 union {
  struct vki_sockaddr ifru_addr;
  struct vki_sockaddr ifru_dstaddr;
  struct vki_sockaddr ifru_broadaddr;
  struct vki_sockaddr ifru_netmask;
  struct vki_sockaddr ifru_hwaddr;
  short ifru_flags;
  int ifru_ivalue;
  int ifru_mtu;
  struct vki_ifmap ifru_map;
  char ifru_slave[16];
  char ifru_newname[16];
  void * ifru_data;
  struct vki_if_settings ifru_settings;
 } ifr_ifru;
};
# 812 "../include/vki/vki-linux.h"
struct vki_ifconf
{
 int ifc_len;
 union
 {
  char *ifcu_buf;
  struct vki_ifreq *ifcu_req;
 } ifc_ifcu;
};






struct vki_arpreq {
  struct vki_sockaddr arp_pa;
  struct vki_sockaddr arp_ha;
  int arp_flags;
  struct vki_sockaddr arp_netmask;
  char arp_dev[16];
};





struct vki_rtentry
{
 unsigned long rt_pad1;
 struct vki_sockaddr rt_dst;
 struct vki_sockaddr rt_gateway;
 struct vki_sockaddr rt_genmask;
 unsigned short rt_flags;
 short rt_pad2;
 unsigned long rt_pad3;
 void *rt_pad4;
 short rt_metric;
 char *rt_dev;
 unsigned long rt_mtu;




 unsigned long rt_window;
 unsigned short rt_irtt;
};





typedef __vki_s32 vki_sctp_assoc_t;

enum vki_sctp_optname {
 VKI_SCTP_RTOINFO,

 VKI_SCTP_ASSOCINFO,

 VKI_SCTP_INITMSG,

 VKI_SCTP_NODELAY,

 VKI_SCTP_AUTOCLOSE,

 VKI_SCTP_SET_PEER_PRIMARY_ADDR,

 VKI_SCTP_PRIMARY_ADDR,

 VKI_SCTP_ADAPTION_LAYER,

 VKI_SCTP_DISABLE_FRAGMENTS,

 VKI_SCTP_PEER_ADDR_PARAMS,

 VKI_SCTP_DEFAULT_SEND_PARAM,

 VKI_SCTP_EVENTS,

 VKI_SCTP_I_WANT_MAPPED_V4_ADDR,

 VKI_SCTP_MAXSEG,

 VKI_SCTP_STATUS,

 VKI_SCTP_GET_PEER_ADDR_INFO,





 VKI_SCTP_SOCKOPT_BINDX_ADD = 100,

 VKI_SCTP_SOCKOPT_BINDX_REM,

 VKI_SCTP_SOCKOPT_PEELOFF,

 VKI_SCTP_GET_PEER_ADDRS_NUM,

 VKI_SCTP_GET_PEER_ADDRS,

 VKI_SCTP_GET_LOCAL_ADDRS_NUM,

 VKI_SCTP_GET_LOCAL_ADDRS,

 VKI_SCTP_SOCKOPT_CONNECTX,

};

struct vki_sctp_getaddrs {
 vki_sctp_assoc_t assoc_id;
 int addr_num;
 struct vki_sockaddr *addrs;
};





struct vki_rusage {
 struct vki_timeval ru_utime;
 struct vki_timeval ru_stime;
 long ru_maxrss;
 long ru_ixrss;
 long ru_idrss;
 long ru_isrss;
 long ru_minflt;
 long ru_majflt;
 long ru_nswap;
 long ru_inblock;
 long ru_oublock;
 long ru_msgsnd;
 long ru_msgrcv;
 long ru_nsignals;
 long ru_nvcsw;
 long ru_nivcsw;
};

struct vki_rlimit {
 unsigned long rlim_cur;
 unsigned long rlim_max;
};

struct vki_rlimit64 {
 __vki_u64 rlim_cur;
 __vki_u64 rlim_max;
};





struct vki_elf_siginfo
{
 int si_signo;
 int si_code;
 int si_errno;
};


struct vki_elf_prstatus
{
 struct vki_elf_siginfo pr_info;
 short pr_cursig;
 unsigned long pr_sigpend;
 unsigned long pr_sighold;
 vki_pid_t pr_pid;
 vki_pid_t pr_ppid;
 vki_pid_t pr_pgrp;
 vki_pid_t pr_sid;
 struct vki_timeval pr_utime;
 struct vki_timeval pr_stime;
 struct vki_timeval pr_cutime;
 struct vki_timeval pr_cstime;
 vki_elf_gregset_t pr_reg;
 int pr_fpvalid;
};



struct vki_elf_prpsinfo
{
 char pr_state;
 char pr_sname;
 char pr_zomb;
 char pr_nice;
 unsigned long pr_flag;
 __vki_kernel_uid_t pr_uid;
 __vki_kernel_gid_t pr_gid;
 vki_pid_t pr_pid, pr_ppid, pr_pgrp, pr_sid;

 char pr_fname[16];
 char pr_psargs[(80)];
};
# 1022 "../include/vki/vki-linux.h"
struct vki_epoll_event {
 __vki_u32 events;
 __vki_u64 data;
} ;






struct vki_mq_attr {
 long mq_flags;
 long mq_maxmsg;
 long mq_msgsize;
 long mq_curmsgs;
 long __reserved[4];
};





struct vki_new_utsname {
 char sysname[65];
 char nodename[65];
 char release[65];
 char version[65];
 char machine[65];
 char domainname[65];
};






struct vki_mii_ioctl_data {
 vki_u16 phy_id;
 vki_u16 reg_num;
 vki_u16 val_in;
 vki_u16 val_out;
};
# 1077 "../include/vki/vki-linux.h"
typedef struct __vki_user_cap_header_struct {
 __vki_u32 version;
 int pid;
} *vki_cap_user_header_t;

typedef struct __vki_user_cap_data_struct {
        __vki_u32 effective;
        __vki_u32 permitted;
        __vki_u32 inheritable;
} *vki_cap_user_data_t;
# 1101 "../include/vki/vki-linux.h"
struct vki_ipc_perm
{
 __vki_kernel_key_t key;
 __vki_kernel_uid_t uid;
 __vki_kernel_gid_t gid;
 __vki_kernel_uid_t cuid;
 __vki_kernel_gid_t cgid;
 __vki_kernel_mode_t mode;
 unsigned short seq;
};
# 1136 "../include/vki/vki-linux.h"
struct vki_semid_ds {
 struct vki_ipc_perm sem_perm;
 __vki_kernel_time_t sem_otime;
 __vki_kernel_time_t sem_ctime;

 void *sem_base;
 void *sem_pending;
 void **sem_pending_last;
 void *undo;
 unsigned short sem_nsems;
};

struct vki_sembuf {
 unsigned short sem_num;
 short sem_op;
 short sem_flg;
};

union vki_semun {
 int val;
 struct vki_semid_ds *buf;
 unsigned short *array;
 struct vki_seminfo *__buf;
 void *__pad;
};

struct vki_seminfo {
 int semmap;
 int semmni;
 int semmns;
 int semmnu;
 int semmsl;
 int semopm;
 int semume;
 int semusz;
 int semvmx;
 int semaem;
};
# 1259 "../include/vki/vki-linux.h"
struct vki_robust_list {
 struct vki_robust_list *next;
};

struct vki_robust_list_head {



 struct vki_robust_list list;







 long futex_offset;
# 1287 "../include/vki/vki-linux.h"
 struct vki_robust_list *list_op_pending;
};
# 1339 "../include/vki/vki-linux.h"
struct vki_dirent {
 long d_ino;
 __vki_kernel_off_t d_off;
 unsigned short d_reclen;
 char d_name[256];
};
# 1366 "../include/vki/vki-linux.h"
struct __vki_sysctl_args {
 int *name;
 int nlen;
 void *oldval;
 vki_size_t *oldlenp;
 void *newval;
 vki_size_t newlen;
 unsigned long __unused[4];
};





typedef unsigned long vki_aio_context_t;

enum {
 VKI_IOCB_CMD_PREAD = 0,
 VKI_IOCB_CMD_PWRITE = 1,
 VKI_IOCB_CMD_FSYNC = 2,
 VKI_IOCB_CMD_FDSYNC = 3,
 VKI_IOCB_CMD_PREADV = 7,
 VKI_IOCB_CMD_PWRITEV = 8,
};


struct vki_io_event {
 __vki_u64 data;
 __vki_u64 obj;


 __vki_s64 result;
 __vki_s64 result2;
};
# 1409 "../include/vki/vki-linux.h"
struct vki_iocb {

 __vki_u64 aio_data;
 __vki_u32 aio_key, aio_reserved1;



 __vki_u16 aio_lio_opcode;
 __vki_s16 aio_reqprio;
 __vki_u32 aio_fildes;

 __vki_u64 aio_buf;
 __vki_u64 aio_nbytes;
 __vki_s64 aio_offset;


 __vki_u64 aio_reserved2;
 __vki_u64 aio_reserved3;
};





struct vki_aio_ring {
 unsigned id;
 unsigned nr;
 unsigned head;
 unsigned tail;

 unsigned magic;
 unsigned compat_features;
 unsigned incompat_features;
 unsigned header_length;

 struct vki_io_event io_events[0];
};
# 1454 "../include/vki/vki-linux.h"
struct vki_msqid_ds {
 struct vki_ipc_perm msg_perm;
 struct vki_msg *msg_first;
 struct vki_msg *msg_last;
 __vki_kernel_time_t msg_stime;
 __vki_kernel_time_t msg_rtime;
 __vki_kernel_time_t msg_ctime;
 unsigned long msg_lcbytes;
 unsigned long msg_lqbytes;
 unsigned short msg_cbytes;
 unsigned short msg_qnum;
 unsigned short msg_qbytes;
 __vki_kernel_ipc_pid_t msg_lspid;
 __vki_kernel_ipc_pid_t msg_lrpid;
};

struct vki_msgbuf {
 long mtype;
 char mtext[1];
};

struct vki_msginfo {
 int msgpool;
 int msgmap;
 int msgmax;
 int msgmnb;
 int msgmni;
 int msgssz;
 int msgtql;
 unsigned short msgseg;
};





struct vki_shmid_ds {
 struct vki_ipc_perm shm_perm;
 int shm_segsz;
 __vki_kernel_time_t shm_atime;
 __vki_kernel_time_t shm_dtime;
 __vki_kernel_time_t shm_ctime;
 __vki_kernel_ipc_pid_t shm_cpid;
 __vki_kernel_ipc_pid_t shm_lpid;
 unsigned short shm_nattch;
 unsigned short shm_unused;
 void *shm_unused2;
 void *shm_unused3;
};
# 1511 "../include/vki/vki-linux.h"
struct vki_shminfo {
 int shmmax;
 int shmmin;
 int shmmni;
 int shmseg;
 int shmall;
};

struct vki_shm_info {
 int used_ids;
 unsigned long shm_tot;
 unsigned long shm_rss;
 unsigned long shm_swp;
 unsigned long swap_attempts;
 unsigned long swap_successes;
};





struct vki_rtc_time {
 int tm_sec;
 int tm_min;
 int tm_hour;
 int tm_mday;
 int tm_mon;
 int tm_year;
 int tm_wday;
 int tm_yday;
 int tm_isdst;
};
# 1572 "../include/vki/vki-linux.h"
typedef struct {
  char name[10];
  char phone[32];
  int outgoing;
} vki_isdn_net_ioctl_phone;
# 1646 "../include/vki/vki-linux.h"
struct vki_ppdev_frob_struct {
 unsigned char mask;
 unsigned char val;
};
# 1720 "../include/vki/vki-linux.h"
typedef struct vki_sg_io_hdr
{
    int interface_id;
    int dxfer_direction;
    unsigned char cmd_len;
    unsigned char mx_sb_len;
    unsigned short iovec_count;
    unsigned int dxfer_len;
    void *dxferp;

    unsigned char *cmdp;
    void *sbp;
    unsigned int timeout;
    unsigned int flags;
    int pack_id;
    void * usr_ptr;
    unsigned char status;
    unsigned char masked_status;
    unsigned char msg_status;
    unsigned char sb_len_wr;
    unsigned short host_status;
    unsigned short driver_status;
    int resid;
    unsigned int duration;
    unsigned int info;
} vki_sg_io_hdr_t;

typedef struct vki_sg_scsi_id {
    int host_no;
    int channel;
    int scsi_id;
    int lun;
    int scsi_type;
    short h_cmd_per_lun;
    short d_queue_depth;
    int unused[2];
} vki_sg_scsi_id_t;
# 1786 "../include/vki/vki-linux.h"
struct vki_scsi_idlun {
 __vki_u32 dev_id;
 __vki_u32 host_unique_id;
};
# 1820 "../include/vki/vki-linux.h"
struct vki_cdrom_msf0
{
 __vki_u8 minute;
 __vki_u8 second;
 __vki_u8 frame;
};

union vki_cdrom_addr
{
 struct vki_cdrom_msf0 msf;
 int lba;
};

struct vki_cdrom_msf
{
 __vki_u8 cdmsf_min0;
 __vki_u8 cdmsf_sec0;
 __vki_u8 cdmsf_frame0;
 __vki_u8 cdmsf_min1;
 __vki_u8 cdmsf_sec1;
 __vki_u8 cdmsf_frame1;
};

struct vki_cdrom_tochdr
{
 __vki_u8 cdth_trk0;
 __vki_u8 cdth_trk1;
};

struct vki_cdrom_volctrl
{
 __vki_u8 channel0;
 __vki_u8 channel1;
 __vki_u8 channel2;
 __vki_u8 channel3;
};

struct vki_cdrom_subchnl
{
 __vki_u8 cdsc_format;
 __vki_u8 cdsc_audiostatus;
 __vki_u8 cdsc_adr: 4;
 __vki_u8 cdsc_ctrl: 4;
 __vki_u8 cdsc_trk;
 __vki_u8 cdsc_ind;
 union vki_cdrom_addr cdsc_absaddr;
 union vki_cdrom_addr cdsc_reladdr;
};

struct vki_cdrom_tocentry
{
 __vki_u8 cdte_track;
 __vki_u8 cdte_adr :4;
 __vki_u8 cdte_ctrl :4;
 __vki_u8 cdte_format;
 union vki_cdrom_addr cdte_addr;
 __vki_u8 cdte_datamode;
};

struct vki_cdrom_read
{
 int cdread_lba;
 char *cdread_bufaddr;
 int cdread_buflen;
};

struct vki_cdrom_read_audio
{
 union vki_cdrom_addr addr;
 __vki_u8 addr_format;
 int nframes;
 __vki_u8 *buf;
};

struct vki_cdrom_multisession
{
 union vki_cdrom_addr addr;


 __vki_u8 xa_flag;
 __vki_u8 addr_format;
};

struct vki_cdrom_mcn
{
  __vki_u8 medium_catalog_number[14];
};



struct vki_cdrom_generic_command
{
 unsigned char cmd[12];
 unsigned char *buffer;
 unsigned int buflen;
 int stat;

 void *sense;
 unsigned char data_direction;
 int quiet;
 int timeout;
 void *reserved[1];
};
# 1977 "../include/vki/vki-linux.h"
typedef struct vki_audio_buf_info {
   int fragments;
   int fragstotal;
   int fragsize;

   int bytes;

  } vki_audio_buf_info;
# 2014 "../include/vki/vki-linux.h"
struct vki_hd_geometry {
      unsigned char heads;
      unsigned char sectors;
      unsigned short cylinders;
      unsigned long start;
};
# 2038 "../include/vki/vki-linux.h"
struct vki_fb_fix_screeninfo {
 char id[16];
 unsigned long smem_start;

 __vki_u32 smem_len;
 __vki_u32 type;
 __vki_u32 type_aux;
 __vki_u32 visual;
 __vki_u16 xpanstep;
 __vki_u16 ypanstep;
 __vki_u16 ywrapstep;
 __vki_u32 line_length;
 unsigned long mmio_start;

 __vki_u32 mmio_len;
 __vki_u32 accel;

 __vki_u16 reserved[3];
};

struct vki_fb_bitfield {
 __vki_u32 offset;
 __vki_u32 length;
 __vki_u32 msb_right;

};

struct vki_fb_var_screeninfo {
 __vki_u32 xres;
 __vki_u32 yres;
 __vki_u32 xres_virtual;
 __vki_u32 yres_virtual;
 __vki_u32 xoffset;
 __vki_u32 yoffset;

 __vki_u32 bits_per_pixel;
 __vki_u32 grayscale;

 struct vki_fb_bitfield red;
 struct vki_fb_bitfield green;
 struct vki_fb_bitfield blue;
 struct vki_fb_bitfield transp;

 __vki_u32 nonstd;

 __vki_u32 activate;

 __vki_u32 height;
 __vki_u32 width;

 __vki_u32 accel_flags;


 __vki_u32 pixclock;
 __vki_u32 left_margin;
 __vki_u32 right_margin;
 __vki_u32 upper_margin;
 __vki_u32 lower_margin;
 __vki_u32 hsync_len;
 __vki_u32 vsync_len;
 __vki_u32 sync;
 __vki_u32 vmode;
 __vki_u32 rotate;
 __vki_u32 reserved[5];
};
# 2113 "../include/vki/vki-linux.h"
struct vki_consolefontdesc {
 unsigned short charcount;
 unsigned short charheight;
 char *chardata;
};
# 2150 "../include/vki/vki-linux.h"
struct vki_unipair {
 unsigned short unicode;
 unsigned short fontpos;
};
struct vki_unimapdesc {
 unsigned short entry_ct;
 struct vki_unipair *entries;
};


struct vki_unimapinit {
 unsigned short advised_hashsize;
 unsigned short advised_hashstep;
 unsigned short advised_hashlevel;
};
# 2175 "../include/vki/vki-linux.h"
struct vki_kbentry {
 unsigned char kb_table;
 unsigned char kb_index;
 unsigned short kb_value;
};



struct vki_kbsentry {
 unsigned char kb_func;
 unsigned char kb_string[512];
};



struct vki_kbdiacr {
        unsigned char diacr, base, result;
};
struct vki_kbdiacrs {
        unsigned int kb_cnt;
 struct vki_kbdiacr kbdiacr[256];
};



struct vki_kbkeycode {
 unsigned int scancode, keycode;
};





struct vki_kbd_repeat {
 int delay;
 int period;

};





struct vki_console_font_op {
 unsigned int op;
 unsigned int flags;
 unsigned int width, height;
 unsigned int charcount;
 unsigned char *data;
};
# 2235 "../include/vki/vki-linux.h"
typedef __vki_kernel_uid32_t vki_qid_t;
# 2257 "../include/vki/vki-linux.h"
enum {
 VKI_SNDRV_PCM_IOCTL_HW_FREE = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x12)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_HWSYNC = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x22)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_PREPARE = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x40)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_RESET = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x41)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_START = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x42)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_DROP = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x43)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_DRAIN = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x44)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_PAUSE = (((1U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x45)) << 0) | (((((sizeof(struct { int:-!((sizeof(int) == sizeof(int[1]) && sizeof(int) < (1 << 14))); })) + sizeof(int)))) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_RESUME = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x47)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_XRUN = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x48)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_LINK = (((1U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x60)) << 0) | (((((sizeof(struct { int:-!((sizeof(int) == sizeof(int[1]) && sizeof(int) < (1 << 14))); })) + sizeof(int)))) << ((0 +8)+8))),
 VKI_SNDRV_PCM_IOCTL_UNLINK = (((0U) << (((0 +8)+8)+14)) | ((('A')) << (0 +8)) | (((0x61)) << 0) | ((0) << ((0 +8)+8))),
};

enum {
 VKI_SNDRV_TIMER_IOCTL_START = (((0U) << (((0 +8)+8)+14)) | ((('T')) << (0 +8)) | (((0xa0)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_TIMER_IOCTL_STOP = (((0U) << (((0 +8)+8)+14)) | ((('T')) << (0 +8)) | (((0xa1)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_TIMER_IOCTL_CONTINUE = (((0U) << (((0 +8)+8)+14)) | ((('T')) << (0 +8)) | (((0xa2)) << 0) | ((0) << ((0 +8)+8))),
 VKI_SNDRV_TIMER_IOCTL_PAUSE = (((0U) << (((0 +8)+8)+14)) | ((('T')) << (0 +8)) | (((0xa3)) << 0) | ((0) << ((0 +8)+8))),
};





struct vki_serial_icounter_struct {
 int cts, dsr, rng, dcd;
 int rx, tx;
 int frame, overrun, parity, brk;
 int buf_overrun;
 int reserved[9];
};







struct vki_vt_mode {
 char mode;
 char waitv;
 short relsig;
 short acqsig;
 short frsig;
};



struct vki_vt_stat {
 unsigned short v_active;
 unsigned short v_signal;
 unsigned short v_state;
};
# 2321 "../include/vki/vki-linux.h"
struct vki_vt_sizes {
 unsigned short v_rows;
 unsigned short v_cols;
 unsigned short v_scrollsize;
};


struct vki_vt_consize {
 unsigned short v_rows;
 unsigned short v_cols;
 unsigned short v_vlin;
 unsigned short v_clin;
 unsigned short v_vcol;
 unsigned short v_ccol;
};
# 2396 "../include/vki/vki-linux.h"
struct vki_usbdevfs_ctrltransfer {
 __vki_u8 bRequestType;
 __vki_u8 bRequest;
 __vki_u16 wValue;
 __vki_u16 wIndex;
 __vki_u16 wLength;
 __vki_u32 timeout;
  void *data;
};

struct vki_usbdevfs_bulktransfer {
 unsigned int ep;
 unsigned int len;
 unsigned int timeout;
 void *data;
};



struct vki_usbdevfs_getdriver {
 unsigned int interface;
 char driver[255 + 1];
};

struct vki_usbdevfs_connectinfo {
 unsigned int devnum;
 unsigned char slow;
};

struct vki_usbdevfs_iso_packet_desc {
 unsigned int length;
 unsigned int actual_length;
 unsigned int status;
};

struct vki_usbdevfs_urb {
 unsigned char type;
 unsigned char endpoint;
 int status;
 unsigned int flags;
 void *buffer;
 int buffer_length;
 int actual_length;
 int start_frame;
 int number_of_packets;
 int error_count;
 unsigned int signr;
 void *usercontext;
 struct vki_usbdevfs_iso_packet_desc iso_frame_desc[0];
};

struct vki_usbdevfs_ioctl {
 int ifno;
 int ioctl_code;

 void *data;
};
# 2471 "../include/vki/vki-linux.h"
struct vki_usbdevfs_setuppacket {
       __vki_u8 bRequestType;
       __vki_u8 bRequest;
       __vki_u16 wValue;
       __vki_u16 wIndex;
       __vki_u16 wLength;
};
# 2494 "../include/vki/vki-linux.h"
struct vki_i2c_msg {
 __vki_u16 addr;
 __vki_u16 flags;







 __vki_u16 len;
 __vki_u8 *buf;
};

struct vki_i2c_rdwr_ioctl_data {
 struct vki_i2c_msg *msgs;
 __vki_u32 nmsgs;
};
# 2541 "../include/vki/vki-linux.h"
typedef vki_int32_t vki_key_serial_t;


typedef vki_uint32_t vki_key_perm_t;
# 2638 "../include/vki/vki-linux.h"
struct vki_iw_param
{
  __vki_s32 value;
  __vki_u8 fixed;
  __vki_u8 disabled;
  __vki_u16 flags;
};

struct vki_iw_point
{
  void *pointer;
  __vki_u16 length;
  __vki_u16 flags;
};

struct vki_iw_freq
{
 __vki_s32 m;
 __vki_s16 e;
 __vki_u8 i;
 __vki_u8 flags;
};

struct vki_iw_quality
{
 __vki_u8 qual;

 __vki_u8 level;
 __vki_u8 noise;
 __vki_u8 updated;
};

union vki_iwreq_data
{

 char name[16];



 struct vki_iw_point essid;
 struct vki_iw_param nwid;
 struct vki_iw_freq freq;



 struct vki_iw_param sens;
 struct vki_iw_param bitrate;
 struct vki_iw_param txpower;
 struct vki_iw_param rts;
 struct vki_iw_param frag;
 __vki_u32 mode;
 struct vki_iw_param retry;

 struct vki_iw_point encoding;
 struct vki_iw_param power;
 struct vki_iw_quality qual;

 struct vki_sockaddr ap_addr;
 struct vki_sockaddr addr;

 struct vki_iw_param param;
 struct vki_iw_point data;
};

struct vki_iwreq
{
 union
 {
  char ifrn_name[16];
 } ifr_ifrn;


 union vki_iwreq_data u;
};





struct vki_perf_event_attr {




 __vki_u32 type;




 __vki_u32 size;




 __vki_u64 config;

 union {
  __vki_u64 sample_period;
  __vki_u64 sample_freq;
 };

 __vki_u64 sample_type;
 __vki_u64 read_format;

 __vki_u64 disabled : 1,
     inherit : 1,
     pinned : 1,
     exclusive : 1,
     exclude_user : 1,
     exclude_kernel : 1,
     exclude_hv : 1,
     exclude_idle : 1,
     mmap : 1,
     comm : 1,
     freq : 1,
     inherit_stat : 1,
     enable_on_exec : 1,
     task : 1,
     watermark : 1,
# 2767 "../include/vki/vki-linux.h"
     precise_ip : 2,
     mmap_data : 1,
     sample_id_all : 1,

     __reserved_1 : 45;

 union {
  __vki_u32 wakeup_events;
  __vki_u32 wakeup_watermark;
 };

 __vki_u32 bp_type;
 union {
  __vki_u64 bp_addr;
  __vki_u64 config1;
 };
 union {
  __vki_u64 bp_len;
  __vki_u64 config2;
 };
};





struct vki_getcpu_cache {
 unsigned long blob[128 / sizeof(long)];
};
# 2859 "../include/vki/vki-linux.h"
struct vki_ashmem_pin {
   vki_uint32_t offset;
   vki_uint32_t len;
};
# 2881 "../include/vki/vki-linux.h"
struct vki_binder_write_read {
 signed long write_size;
 signed long write_consumed;
 unsigned long write_buffer;
 signed long read_size;
 signed long read_consumed;
 unsigned long read_buffer;
};

struct vki_binder_version {
 signed long protocol_version;
};
# 2908 "../include/vki/vki-linux.h"
typedef struct {
   __vki_u8 b[6];
} __attribute__((packed)) vki_bdaddr_t;
# 2942 "../include/vki/vki-linux.h"
struct vki_inquiry_info {
   vki_bdaddr_t bdaddr;
   __vki_u8 pscan_rep_mode;
   __vki_u8 pscan_period_mode;
   __vki_u8 pscan_mode;
   __vki_u8 dev_class[3];
   __vki_le16 clock_offset;
} __attribute__((packed));

struct vki_hci_inquiry_req {
   __vki_u16 dev_id;
   __vki_u16 flags;
   __vki_u8 lap[3];
   __vki_u8 length;
   __vki_u8 num_rsp;
};
# 2987 "../include/vki/vki-linux.h"
struct vki_hwtstamp_config {
 int flags;
 int tx_type;
 int rx_filter;
};
# 3016 "../include/vki/vki-linux.h"
typedef unsigned long __vki_xen_pfn_t;

struct vki_xen_privcmd_hypercall {
       __vki_u64 op;
       __vki_u64 arg[5];
};

struct vki_xen_privcmd_mmap_entry {
        __vki_u64 va;
        __vki_u64 mfn;
        __vki_u64 npages;
};

struct vki_xen_privcmd_mmap {
        int num;
        __vki_u16 dom;
        struct vki_xen_privcmd_mmap_entry *entry;
};

struct vki_xen_privcmd_mmapbatch {
        int num;
        __vki_u16 dom;
        __vki_u64 addr;
        __vki_xen_pfn_t *arr;
};

struct vki_xen_privcmd_mmapbatch_v2 {
        unsigned int num;
        __vki_u16 dom;
        __vki_u64 addr;
        const __vki_xen_pfn_t *arr;
        int *err;
};
# 50 "../include/pub_tool_vki.h" 2
# 1 "../include/vki/vki-xen.h" 1
# 51 "../include/pub_tool_vki.h" 2
# 45 "pub_core_vki.h" 2





void vgPlain_vki_do_initial_consistency_checks(void);
# 33 "m_stacktrace.c" 2
# 1 "pub_core_libcsetjmp.h" 1
# 43 "pub_core_libcsetjmp.h"
# 1 "../include/pub_tool_libcsetjmp.h" 1
# 53 "../include/pub_tool_libcsetjmp.h"
# 1 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/setjmp.h" 1 3 4
# 43 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/setjmp.h" 3 4
# 1 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/sys/cdefs.h" 1 3 4
# 65 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/sys/cdefs.h" 3 4
# 1 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/sys/cdefs_elf.h" 1 3 4
# 66 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/sys/cdefs.h" 2 3 4
# 506 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/sys/cdefs.h" 3 4
# 1 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/android/api-level.h" 1 3 4
# 507 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/sys/cdefs.h" 2 3 4
# 44 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/setjmp.h" 2 3 4
# 1 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/machine/setjmp.h" 1 3 4
# 45 "/home/kats/android/ndk-r8/platforms/android-3/arch-arm/usr/include/setjmp.h" 2 3 4

typedef long sigjmp_buf[64 + 1];
typedef long jmp_buf[64];



int _setjmp(jmp_buf);
void _longjmp(jmp_buf, int);
void longjmperror(void);

int setjmp(jmp_buf);
void longjmp(jmp_buf, int);

int sigsetjmp(sigjmp_buf, int);
void siglongjmp(sigjmp_buf, int);


# 54 "../include/pub_tool_libcsetjmp.h" 2
# 44 "pub_core_libcsetjmp.h" 2
# 34 "m_stacktrace.c" 2
# 1 "pub_core_threadstate.h" 1
# 42 "pub_core_threadstate.h"
# 1 "../include/pub_tool_threadstate.h" 1
# 47 "../include/pub_tool_threadstate.h"
extern ThreadId vgPlain_get_running_tid ( void );
# 43 "pub_core_threadstate.h" 2
# 55 "pub_core_threadstate.h"
typedef
   enum ThreadStatus {
      VgTs_Empty,
      VgTs_Init,
      VgTs_Runnable,
      VgTs_WaitSys,
      VgTs_Yielding,
      VgTs_Zombie,
   }
   ThreadStatus;


typedef
   enum {
      VgSrc_None,
      VgSrc_ExitThread,
      VgSrc_ExitProcess,
      VgSrc_FatalSig

   }
   VgSchedReturnCode;
# 87 "pub_core_threadstate.h"
   typedef VexGuestARMState VexGuestArchState;
# 97 "pub_core_threadstate.h"
struct SyscallStatus;
struct SyscallArgs;


typedef
   struct {
# 112 "pub_core_threadstate.h"
      VexGuestArchState vex __attribute__((aligned(16)));


      VexGuestArchState vex_shadow1 __attribute__((aligned(16)));
      VexGuestArchState vex_shadow2 __attribute__((aligned(16)));


      UChar vex_spill[4096] __attribute__((aligned(16)));


   }
   ThreadArchState;





typedef
   struct {

      Int lwpid;
      Int threadgroup;

      ThreadId parent;


      Addr valgrind_stack_base;
      Addr valgrind_stack_init_SP;


      Word exitcode;
      Int fatalsig;
# 273 "pub_core_threadstate.h"
   }
   ThreadOSstate;



typedef struct {







   ThreadId tid;


   ThreadStatus status;




   VgSchedReturnCode exitreason;


   ThreadArchState arch;







   vki_sigset_t sig_mask;







   vki_sigset_t tmp_sig_mask;




   struct SigQueue *sig_queue;
# 331 "pub_core_threadstate.h"
   SizeT client_stack_szB;





   Addr client_stack_highest_word;


   vki_stack_t altstack;


   ThreadOSstate os_state;







   UInt err_disablement_level;


   Bool sched_jmpbuf_valid;
   jmp_buf sched_jmpbuf;
}
ThreadState;
# 367 "pub_core_threadstate.h"
extern ThreadState vgPlain_threads[500];



extern ThreadId vgPlain_running_tid;







void vgPlain_init_Threads(void);


const HChar* vgPlain_name_of_ThreadStatus ( ThreadStatus status );


extern ThreadState *vgPlain_get_ThreadState ( ThreadId tid );


extern Bool vgPlain_is_valid_tid ( ThreadId tid );


extern Bool vgPlain_is_running_thread(ThreadId tid);


extern Bool vgPlain_is_exiting(ThreadId tid);


extern Int vgPlain_count_living_threads(void);


extern Int vgPlain_count_runnable_threads(void);



extern ThreadId vgPlain_lwpid_to_vgtid(Int lwpid);
# 35 "m_stacktrace.c" 2
# 1 "pub_core_debuginfo.h" 1
# 40 "pub_core_debuginfo.h"
# 1 "../include/pub_tool_debuginfo.h" 1
# 44 "../include/pub_tool_debuginfo.h"
extern Bool vgPlain_get_filename ( Addr a, Char* filename, Int n_filename );
extern Bool vgPlain_get_fnname ( Addr a, Char* fnname, Int n_fnname );
extern Bool vgPlain_get_linenum ( Addr a, UInt* linenum );
extern Bool vgPlain_get_fnname_w_offset
                              ( Addr a, Char* fnname, Int n_fnname );
# 61 "../include/pub_tool_debuginfo.h"
extern Bool vgPlain_get_filename_linenum
                              ( Addr a,
                                       Char* filename, Int n_filename,
                                       Char* dirname, Int n_dirname,
                                       Bool* dirname_available,
                                       UInt* linenum );
# 75 "../include/pub_tool_debuginfo.h"
extern Bool vgPlain_get_fnname_if_entry ( Addr a, Char* fnname, Int n_fnname );

typedef
   enum {
      Vg_FnNameNormal,
      Vg_FnNameMain,
      Vg_FnNameBelowMain
   } Vg_FnNameKind;


extern Vg_FnNameKind vgPlain_get_fnname_kind ( Char* name );


extern Vg_FnNameKind vgPlain_get_fnname_kind_from_IP ( Addr ip );





extern Bool vgPlain_get_datasym_and_offset( Addr data_addr,
                                                Char* dname, Int n_dname,
                                                PtrdiffT* offset );
# 111 "../include/pub_tool_debuginfo.h"
Bool vgPlain_get_data_description(
                void* dname1v,
                void* dname2v,
        Addr data_addr
     );



extern Bool vgPlain_get_objname ( Addr a, Char* objname, Int n_objname );
# 128 "../include/pub_tool_debuginfo.h"
extern Char* vgPlain_describe_IP(Addr eip, Char* buf, Int n_buf);







typedef
   struct {
      PtrdiffT base;
      SizeT szB;
      Bool spRel;
      Bool isVec;
      HChar name[16];
   }
   StackBlock;

extern void*
             vgPlain_di_get_stack_blocks_at_ip( Addr ip, Bool arrays_only );
# 157 "../include/pub_tool_debuginfo.h"
typedef
   struct {
      Addr addr;
      SizeT szB;
      Bool isVec;
      HChar name[16];
      HChar soname[16];
   }
   GlobalBlock;

extern void*
vgPlain_di_get_global_blocks_from_dihandle ( ULong di_handle,
                                          Bool arrays_only );
# 178 "../include/pub_tool_debuginfo.h"
typedef struct _DebugInfo DebugInfo;



DebugInfo* vgPlain_find_DebugInfo ( Addr a );


Addr vgPlain_DebugInfo_get_text_avma ( const DebugInfo *di );
SizeT vgPlain_DebugInfo_get_text_size ( const DebugInfo *di );
Addr vgPlain_DebugInfo_get_plt_avma ( const DebugInfo *di );
SizeT vgPlain_DebugInfo_get_plt_size ( const DebugInfo *di );
Addr vgPlain_DebugInfo_get_gotplt_avma ( const DebugInfo *di );
SizeT vgPlain_DebugInfo_get_gotplt_size ( const DebugInfo *di );
Addr vgPlain_DebugInfo_get_got_avma ( const DebugInfo *di );
SizeT vgPlain_DebugInfo_get_got_size ( const DebugInfo *di );
const UChar* vgPlain_DebugInfo_get_soname ( const DebugInfo *di );
const UChar* vgPlain_DebugInfo_get_filename ( const DebugInfo *di );
PtrdiffT vgPlain_DebugInfo_get_text_bias ( const DebugInfo *di );
# 204 "../include/pub_tool_debuginfo.h"
const DebugInfo* vgPlain_next_DebugInfo ( const DebugInfo *di );
# 213 "../include/pub_tool_debuginfo.h"
Int vgPlain_DebugInfo_syms_howmany ( const DebugInfo *di );
void vgPlain_DebugInfo_syms_getidx ( const DebugInfo *di,
                                   Int idx,
                                          Addr* avma,
                                          Addr* tocptr,
                                          UInt* size,
                                          UChar** pri_name,
                                          UChar*** sec_names,
                                          Bool* isText,
                                          Bool* isIFunc );



typedef
   enum {
      Vg_SectUnknown,
      Vg_SectText,
      Vg_SectData,
      Vg_SectBSS,
      Vg_SectGOT,
      Vg_SectPLT,
      Vg_SectGOTPLT,
      Vg_SectOPD
   }
   VgSectKind;



const HChar* vgPlain_pp_SectKind( VgSectKind kind );





VgSectKind vgPlain_DebugInfo_sect_kind( UChar* name, SizeT n_name,
                                     Addr a);
# 41 "pub_core_debuginfo.h" 2


extern void vgPlain_di_initialise ( void );
# 66 "pub_core_debuginfo.h"
extern ULong vgPlain_di_notify_mmap( Addr a, Bool allow_SkFileV, Int use_fd );

extern void vgPlain_di_notify_munmap( Addr a, SizeT len );

extern void vgPlain_di_notify_mprotect( Addr a, SizeT len, UInt prot );


extern void vgPlain_di_notify_pdb_debuginfo( Int fd, Addr avma,
                                          SizeT total_size,
                                          PtrdiffT bias );


extern void vgPlain_di_notify_vm_protect( Addr a, SizeT len, UInt prot );


extern void vgPlain_di_discard_ALL_debuginfo( void );






extern
Bool vgPlain_get_fnname_raw ( Addr a, Char* buf, Int nbuf );



extern
Bool vgPlain_get_fnname_no_cxx_demangle ( Addr a, Char* buf, Int nbuf );




extern
Bool vgPlain_get_inst_offset_in_function( Addr a, PtrdiffT* offset );
# 112 "pub_core_debuginfo.h"
typedef
   struct { Addr r15; Addr r14; Addr r13; Addr r12; Addr r11; Addr r7; }
   D3UnwindRegs;
# 131 "pub_core_debuginfo.h"
extern Bool vgPlain_use_CF_info ( D3UnwindRegs* uregs,
                               Addr min_accessible,
                               Addr max_accessible );



extern Bool vgPlain_use_FPO_info ( Addr* ipP,
                                       Addr* spP,
                                       Addr* fpP,
                                Addr min_accessible,
                                Addr max_accessible );




extern Addr vgPlain_get_tocptr ( Addr guest_code_addr );
# 155 "pub_core_debuginfo.h"
extern
Bool vgPlain_lookup_symbol_SLOW(UChar* sopatt, UChar* name, Addr* pEnt, Addr* pToc);
# 36 "m_stacktrace.c" 2
# 1 "pub_core_aspacemgr.h" 1
# 42 "pub_core_aspacemgr.h"
# 1 "../include/pub_tool_aspacemgr.h" 1
# 39 "../include/pub_tool_aspacemgr.h"
typedef
   enum {
      SkFree,
      SkAnonC,
      SkAnonV,
      SkFileC,
      SkFileV,
      SkShmC,
      SkResvn
   }
   SegKind;


typedef
   enum {
      SmLower,
      SmFixed,
      SmUpper
   }
   ShrinkMode;
# 93 "../include/pub_tool_aspacemgr.h"
typedef
   struct {
      SegKind kind;

      Addr start;
      Addr end;

      ShrinkMode smode;

      ULong dev;
      ULong ino;
      Off64T offset;
      UInt mode;
      Int fnIdx;

      Bool hasR;
      Bool hasW;
      Bool hasX;
      Bool hasT;

      Bool isCH;

      Bool mark;
   }
   NSegment;
# 133 "../include/pub_tool_aspacemgr.h"
extern Int vgPlain_am_get_segment_starts( Addr* starts, Int nStarts );



extern NSegment const * vgPlain_am_find_nsegment ( Addr a );


extern HChar* vgPlain_am_get_filename( NSegment const * );


extern Bool vgPlain_am_is_valid_for_client ( Addr start, SizeT len,
                                          UInt prot );



extern void* vgPlain_am_shadow_alloc(SizeT size);



extern SysRes vgPlain_am_munmap_valgrind( Addr start, SizeT length );
# 43 "pub_core_aspacemgr.h" 2
# 62 "pub_core_aspacemgr.h"
extern Addr vgPlain_am_startup ( Addr sp_at_startup );
# 76 "pub_core_aspacemgr.h"
extern NSegment const* vgPlain_am_next_nsegment ( NSegment* here, Bool fwds );
# 92 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_is_valid_for_client_or_free_or_resvn
   ( Addr start, SizeT len, UInt prot );




extern ULong vgPlain_am_get_anonsize_total( void );


extern void vgPlain_am_show_nsegments ( Int logLevel, HChar* who );
# 120 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_do_sync_check ( const HChar* fn,
                                    const HChar* file, Int line );







typedef
   struct {
      enum { MFixed, MHint, MAny } rkind;
      Addr start;
      Addr len;
   }
   MapRequest;
# 144 "pub_core_aspacemgr.h"
extern Addr vgPlain_am_get_advisory
   ( MapRequest* req, Bool forClient, Bool* ok );





extern Addr vgPlain_am_get_advisory_client_simple
   ( Addr start, SizeT len, Bool* ok );
# 162 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_covered_by_single_free_segment
   ( Addr start, SizeT len);





extern Bool vgPlain_am_notify_client_mmap
   ( Addr a, SizeT len, UInt prot, UInt flags, Int fd, Off64T offset );





extern Bool vgPlain_am_notify_client_shmat( Addr a, SizeT len, UInt prot );
# 187 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_notify_mprotect( Addr start, SizeT len, UInt prot );







extern Bool vgPlain_am_notify_munmap( Addr start, SizeT len );






extern SysRes vgPlain_am_do_mmap_NO_NOTIFY
   ( Addr start, SizeT length, UInt prot, UInt flags, Int fd, Off64T offset);
# 216 "pub_core_aspacemgr.h"
extern SysRes vgPlain_am_mmap_file_fixed_client
   ( Addr start, SizeT length, UInt prot, Int fd, Off64T offset );
extern SysRes vgPlain_am_mmap_named_file_fixed_client
   ( Addr start, SizeT length, UInt prot, Int fd, Off64T offset, const HChar *name );



extern SysRes vgPlain_am_mmap_anon_fixed_client
   ( Addr start, SizeT length, UInt prot );




extern SysRes vgPlain_am_mmap_anon_float_client ( SizeT length, Int prot );
# 239 "pub_core_aspacemgr.h"
extern SysRes vgPlain_am_sbrk_anon_float_client ( SizeT length, Int prot );





extern SysRes vgPlain_am_mmap_anon_float_valgrind( SizeT cszB );



extern SysRes vgPlain_am_sbrk_anon_float_valgrind( SizeT cszB );





extern SysRes vgPlain_am_mmap_file_float_valgrind
   ( SizeT length, UInt prot, Int fd, Off64T offset );




extern SysRes vgPlain_am_shared_mmap_file_float_valgrind
   ( SizeT length, UInt prot, Int fd, Off64T offset );






extern SysRes vgPlain_am_munmap_client( Bool* need_discard,
                                     Addr start, SizeT length );





extern Bool vgPlain_am_change_ownership_v_to_c( Addr start, SizeT len );







extern void vgPlain_am_set_segment_isCH_if_SkAnonC( NSegment* seg );




extern void vgPlain_am_set_segment_hasT_if_SkFileC_or_SkAnonC( NSegment* );
# 301 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_create_reservation
   ( Addr start, SizeT length, ShrinkMode smode, SSizeT extra );
# 314 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_extend_into_adjacent_reservation_client
   ( NSegment* seg, SSizeT delta );
# 326 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_extend_map_client( Bool* need_discard,
                                       NSegment* seg, SizeT delta );
# 337 "pub_core_aspacemgr.h"
extern Bool vgPlain_am_relocate_nooverlap_client( Bool* need_discard,
                                               Addr old_addr, SizeT old_len,
                                               Addr new_addr, SizeT new_len );
# 355 "pub_core_aspacemgr.h"
typedef
   struct {
      HChar bytes[8192
                  + (4096 * 256)
                  + 8192];
   }
   VgStack;
# 370 "pub_core_aspacemgr.h"
extern VgStack* vgPlain_am_alloc_VgStack( Addr* initial_sp );




extern SizeT vgPlain_am_get_VgStack_unused_szB( VgStack* stack, SizeT limit );
# 37 "m_stacktrace.c" 2
# 1 "pub_core_libcbase.h" 1
# 40 "pub_core_libcbase.h"
# 1 "../include/pub_tool_libcbase.h" 1
# 38 "../include/pub_tool_libcbase.h"
extern Bool vgPlain_isspace ( Char c );
extern Bool vgPlain_isdigit ( Char c );
extern Char vgPlain_tolower ( Char c );
# 64 "../include/pub_tool_libcbase.h"
extern Long vgPlain_strtoll10 ( Char* str, Char** endptr );
extern Long vgPlain_strtoll16 ( Char* str, Char** endptr );
extern ULong vgPlain_strtoull10 ( Char* str, Char** endptr );
extern ULong vgPlain_strtoull16 ( Char* str, Char** endptr );





extern double vgPlain_strtod ( Char* str, Char** endptr );
# 85 "../include/pub_tool_libcbase.h"
extern SizeT vgPlain_strlen ( const Char* str );
extern Char* vgPlain_strcat ( Char* dest, const Char* src );
extern Char* vgPlain_strncat ( Char* dest, const Char* src, SizeT n );
extern Char* vgPlain_strpbrk ( const Char* s, const Char* accpt );
extern Char* vgPlain_strcpy ( Char* dest, const Char* src );
extern Char* vgPlain_strncpy ( Char* dest, const Char* src, SizeT ndest );
extern Int vgPlain_strcmp ( const Char* s1, const Char* s2 );
extern Int vgPlain_strcasecmp ( const Char* s1, const Char* s2 );
extern Int vgPlain_strncmp ( const Char* s1, const Char* s2, SizeT nmax );
extern Int vgPlain_strncasecmp ( const Char* s1, const Char* s2, SizeT nmax );
extern Char* vgPlain_strstr ( const Char* haystack, Char* needle );
extern Char* vgPlain_strcasestr ( const Char* haystack, Char* needle );
extern Char* vgPlain_strchr ( const Char* s, Char c );
extern Char* vgPlain_strrchr ( const Char* s, Char c );
extern SizeT vgPlain_strspn ( const Char* s, const Char* accpt );
extern SizeT vgPlain_strcspn ( const Char* s, const char* reject );


extern Char* vgPlain_strtok_r (Char* s, const Char* delim, Char** saveptr);
extern Char* vgPlain_strtok (Char* s, const Char* delim);





extern Bool vgPlain_parse_Addr ( UChar** ppc, Addr* result );



extern void vgPlain_strncpy_safely ( Char* dest, const Char* src, SizeT ndest );





extern void* vgPlain_memcpy ( void *d, const void *s, SizeT sz );
extern void* vgPlain_memmove( void *d, const void *s, SizeT sz );
extern void* vgPlain_memset ( void *s, Int c, SizeT sz );
extern Int vgPlain_memcmp ( const void* s1, const void* s2, SizeT n );





inline __attribute__((always_inline))
static void vgPlain_bzero_inline ( void* s, SizeT sz )
{
   if (__builtin_expect(!!(0 == (((Addr)sz) & (Addr)(sizeof(UWord)-1))), 1)
       && __builtin_expect(!!(0 == (((Addr)s) & (Addr)(sizeof(UWord)-1))), 1)) {
      UWord* p = (UWord*)s;
      switch (sz / (SizeT)sizeof(UWord)) {
          case 8: p[0] = p[1] = p[2] = p[3]
                  = p[4] = p[5] = p[6] = p[7] = 0UL; return;
          case 7: p[0] = p[1] = p[2] = p[3]
                  = p[4] = p[5] = p[6] = 0UL; return;
          case 6: p[0] = p[1] = p[2] = p[3]
                  = p[4] = p[5] = 0UL; return;
          case 5: p[0] = p[1] = p[2] = p[3] = p[4] = 0UL; return;
          case 4: p[0] = p[1] = p[2] = p[3] = 0UL; return;
          case 3: p[0] = p[1] = p[2] = 0UL; return;
          case 2: p[0] = p[1] = 0UL; return;
          case 1: p[0] = 0UL; return;
          case 0: return;
          default: break;
      }
   }
   vgPlain_memset(s, 0, sz);
}
# 181 "../include/pub_tool_libcbase.h"
extern void vgPlain_ssort( void* base, SizeT nmemb, SizeT size,
                        Int (*compar)(void*, void*) );



extern Int vgPlain_log2 ( UInt x );


extern Int vgPlain_log2_64( ULong x );




extern UInt vgPlain_random ( UInt* pSeed );
# 41 "pub_core_libcbase.h" 2
# 38 "m_stacktrace.c" 2
# 1 "pub_core_libcassert.h" 1
# 39 "pub_core_libcassert.h"
# 1 "../include/pub_tool_libcassert.h" 1
# 50 "../include/pub_tool_libcassert.h"
__attribute__ ((__noreturn__))
extern void vgPlain_exit( Int status );


__attribute__ ((__noreturn__))
extern void vgPlain_tool_panic ( Char* str );

__attribute__ ((__noreturn__))
extern void vgPlain_assert_fail ( Bool isCore, const Char* expr, const Char* file,
                               Int line, const Char* fn,
                               const HChar* format, ... );
# 40 "pub_core_libcassert.h" 2
# 63 "pub_core_libcassert.h"
__attribute__ ((__noreturn__))
extern void vgPlain_core_panic ( Char* str );
__attribute__ ((__noreturn__))
extern void vgPlain_core_panic_at ( Char* str, UnwindStartRegs* );



extern void vgPlain_unimplemented ( Char* msg )
            __attribute__((__noreturn__));


extern void vgPlain_show_sched_status ( void );
# 39 "m_stacktrace.c" 2
# 1 "pub_core_libcprint.h" 1
# 39 "pub_core_libcprint.h"
# 1 "../include/pub_tool_libcprint.h" 1
# 38 "../include/pub_tool_libcprint.h"
extern UInt vgPlain_sprintf ( Char* buf, const HChar* format, ... )
                          __attribute__((format(__printf__, 2, 3)));

extern UInt vgPlain_vsprintf ( Char* buf, const HChar* format, va_list vargs )
                          __attribute__((format(__printf__, 2, 0)));

extern UInt vgPlain_snprintf ( Char* buf, Int size,
                                       const HChar *format, ... )
                          __attribute__((format(__printf__, 3, 4)));

extern UInt vgPlain_vsnprintf( Char* buf, Int size,
                                       const HChar *format, va_list vargs )
                          __attribute__((format(__printf__, 3, 0)));



extern void vgPlain_percentify(ULong n, ULong m, UInt d, Int n_buf, char buf[]);
# 73 "../include/pub_tool_libcprint.h"
typedef
   enum {
      Vg_FailMsg,
      Vg_UserMsg,
      Vg_DebugMsg,
      Vg_ClientMsg
   }
   VgMsgKind;



extern UInt vgPlain_printf ( const HChar *format, ... )
                          __attribute__((format(__printf__, 1, 2)));
extern UInt vgPlain_vprintf ( const HChar *format, va_list vargs )
                          __attribute__((format(__printf__, 1, 0)));

extern UInt vgPlain_printf_xml ( const HChar *format, ... )
                             __attribute__((format(__printf__, 1, 2)));

extern UInt vgPlain_vprintf_xml ( const HChar *format, va_list vargs )
                             __attribute__((format(__printf__, 1, 0)));



extern void vgPlain_vcbprintf( void(*char_sink)(HChar, void* opaque),
                            void* opaque,
                            const HChar* format, va_list vargs );

extern UInt vgPlain_message( VgMsgKind kind, const HChar* format, ... )
   __attribute__((format(__printf__, 2, 3)));

extern UInt vgPlain_vmessage( VgMsgKind kind, const HChar* format, va_list vargs )
   __attribute__((format(__printf__, 2, 0)));





extern UInt vgPlain_fmsg( const HChar* format, ... ) __attribute__((format(__printf__, 1, 2)));






__attribute__((noreturn))
extern void vgPlain_fmsg_bad_option ( HChar* opt, const HChar* format, ... )
   __attribute__((format(__printf__, 2, 3)));




extern UInt vgPlain_umsg( const HChar* format, ... ) __attribute__((format(__printf__, 1, 2)));


extern UInt vgPlain_dmsg( const HChar* format, ... ) __attribute__((format(__printf__, 1, 2)));


extern void vgPlain_message_flush ( void );
# 40 "pub_core_libcprint.h" 2



typedef
   struct { Int fd; Bool is_socket; }
   OutputSink;


extern OutputSink vgPlain_log_output_sink;
extern OutputSink vgPlain_xml_output_sink;





void vgPlain_elapsed_wallclock_time ( HChar* buf );



__attribute__((noreturn))
extern void vgPlain_err_missing_prog ( void );



__attribute__((noreturn))
extern void vgPlain_err_config_error ( Char* format, ... );
# 40 "m_stacktrace.c" 2
# 1 "pub_core_machine.h" 1
# 40 "pub_core_machine.h"
# 1 "../include/pub_tool_machine.h" 1
# 99 "../include/pub_tool_machine.h"
Addr vgPlain_get_IP ( ThreadId tid );
Addr vgPlain_get_SP ( ThreadId tid );
# 109 "../include/pub_tool_machine.h"
void
vgPlain_get_shadow_regs_area ( ThreadId tid,
                                   UChar* dst,
                                   Int shadowNo, PtrdiffT offset, SizeT size );
void
vgPlain_set_shadow_regs_area ( ThreadId tid,
                                   Int shadowNo, PtrdiffT offset, SizeT size,
                                   const UChar* src );



void vgPlain_set_syscall_return_shadows ( ThreadId tid,

                                       UWord s1res, UWord s2res,

                                       UWord s1err, UWord s2err );





extern void vgPlain_apply_to_GP_regs(void (*f)(ThreadId tid,
                                            HChar* regname, UWord val));




extern void vgPlain_thread_stack_reset_iter ( ThreadId* tid );
extern Bool vgPlain_thread_stack_next ( ThreadId* tid,
                                                  Addr* stack_min,
                                                  Addr* stack_max );


extern Addr vgPlain_thread_get_stack_max ( ThreadId tid );


extern SizeT vgPlain_thread_get_stack_size ( ThreadId tid );



extern Addr vgPlain_thread_get_altstack_min ( ThreadId tid );



extern SizeT vgPlain_thread_get_altstack_size ( ThreadId tid );





extern void* vgPlain_fnptr_to_fnentry( void* );





extern Int vgPlain_machine_get_size_of_largest_guest_register ( void );
# 41 "pub_core_machine.h" 2
# 139 "pub_core_machine.h"
Addr vgPlain_get_FP ( ThreadId tid );

void vgPlain_set_IP ( ThreadId tid, Addr encip );
void vgPlain_set_SP ( ThreadId tid, Addr sp );





void vgPlain_get_UnwindStartRegs ( UnwindStartRegs* regs,
                                ThreadId tid );
# 200 "pub_core_machine.h"
extern Bool vgPlain_machine_get_hwcaps( void );


extern void vgPlain_machine_get_VexArchInfo( VexArch*,
                                                 VexArchInfo* );
# 216 "pub_core_machine.h"
extern void vgPlain_machine_arm_set_has_NEON( Bool );
# 248 "pub_core_machine.h"
extern Int vgPlain_machine_arm_archlevel;
# 41 "m_stacktrace.c" 2
# 1 "pub_core_options.h" 1
# 40 "pub_core_options.h"
# 1 "../include/pub_tool_options.h" 1
# 146 "../include/pub_tool_options.h"
extern Int vgPlain_clo_verbosity;


extern Bool vgPlain_clo_stats;





extern Int vgPlain_clo_vgdb_error;




extern Bool vgPlain_clo_xml;



extern HChar* vgPlain_clo_xml_user_comment;



extern VexControl vgPlain_clo_vex_control;


extern Int vgPlain_clo_backtrace_size;


extern Bool vgPlain_clo_show_below_main;
# 195 "../include/pub_tool_options.h"
extern Char* vgPlain_expand_file_name(Char* option_name, Char* format);
# 41 "pub_core_options.h" 2
# 52 "pub_core_options.h"
extern Bool vgPlain_clo_error_limit;



extern Int vgPlain_clo_error_exitcode;

typedef
   enum {
      Vg_VgdbNo,
      Vg_VgdbYes,
      Vg_VgdbFull,


   }
   VgVgdb;

extern VgVgdb vgPlain_clo_vgdb;

extern Int vgPlain_clo_vgdb_poll;

extern HChar* vgPlain_clo_vgdb_prefix;


extern Bool vgPlain_clo_vgdb_shadow_registers;


extern Bool vgPlain_clo_db_attach;

extern Char* vgPlain_clo_db_command;


extern Int vgPlain_clo_gen_suppressions;

extern Int vgPlain_clo_sanity_level;

extern Bool vgPlain_clo_demangle;




extern HChar* vgPlain_clo_soname_synonyms;
extern Bool vgPlain_clo_trace_children;


extern HChar* vgPlain_clo_trace_children_skip;



extern HChar* vgPlain_clo_trace_children_skip_by_arg;






extern Bool vgPlain_clo_child_silent_after_fork;



extern Char* vgPlain_clo_log_fname_expanded;
extern Char* vgPlain_clo_xml_fname_expanded;


extern Bool vgPlain_clo_time_stamp;


extern Int vgPlain_clo_input_fd;


extern Int vgPlain_clo_n_suppressions;

extern Char* vgPlain_clo_suppressions[100];


extern Int vgPlain_clo_n_fullpath_after;
extern Char* vgPlain_clo_fullpath_after[100];


extern UChar vgPlain_clo_trace_flags;

extern UChar vgPlain_clo_profile_flags;

extern Int vgPlain_clo_trace_notbelow;

extern Int vgPlain_clo_trace_notabove;

extern Bool vgPlain_clo_trace_syscalls;

extern Bool vgPlain_clo_trace_signals;

extern Bool vgPlain_clo_trace_symtab;

extern HChar* vgPlain_clo_trace_symtab_patt;

extern Bool vgPlain_clo_trace_cfi;

extern Bool vgPlain_clo_debug_dump_syms;

extern Bool vgPlain_clo_debug_dump_line;

extern Bool vgPlain_clo_debug_dump_frames;

extern Bool vgPlain_clo_trace_redir;

enum FairSchedType { disable_fair_sched, enable_fair_sched, try_fair_sched };
extern enum FairSchedType vgPlain_clo_fair_sched;

extern Bool vgPlain_clo_trace_sched;

extern Bool vgPlain_clo_profile_heap;
# 170 "pub_core_options.h"
extern Int vgPlain_clo_core_redzone_size;


extern Int vgPlain_clo_redzone_size;


extern Int vgPlain_clo_dump_error;

extern Char* vgPlain_clo_sim_hints;

extern Bool vgPlain_clo_sym_offsets;

extern Bool vgPlain_clo_read_var_info;

extern Char* vgPlain_clo_prefix_to_strip;
# 216 "pub_core_options.h"
extern Int vgPlain_clo_n_req_tsyms;
extern HChar* vgPlain_clo_req_tsyms[100];


extern Bool vgPlain_clo_track_fds;






extern Bool vgPlain_clo_run_libc_freeres;


extern Bool vgPlain_clo_show_emwarns;




extern Word vgPlain_clo_max_stackframe;


extern Word vgPlain_clo_main_stacksize;


extern Bool vgPlain_clo_wait_for_gdb;




typedef
   enum {
      Vg_SmcNone,
      Vg_SmcStack,

      Vg_SmcAll,
      Vg_SmcAllNonFile

   }
   VgSmc;



extern VgSmc vgPlain_clo_smc_check;



extern HChar* vgPlain_clo_kernel_variant;



extern Bool vgPlain_clo_dsymutil;







extern Bool vgPlain_should_we_trace_this_child ( HChar* child_exe_name,
                                              HChar** child_argv );
# 42 "m_stacktrace.c" 2
# 1 "pub_core_stacks.h" 1
# 39 "pub_core_stacks.h"
extern UWord vgPlain_register_stack ( Addr start, Addr end );
extern void vgPlain_deregister_stack ( UWord id );
extern void vgPlain_change_stack ( UWord id, Addr start, Addr end );
extern void vgPlain_stack_limits ( Addr SP, Addr *start, Addr *end );

extern
       void vgPlain_unknown_SP_update ( Addr old_SP, Addr new_SP, UInt otag );
# 43 "m_stacktrace.c" 2
# 1 "pub_core_stacktrace.h" 1
# 39 "pub_core_stacktrace.h"
# 1 "../include/pub_tool_stacktrace.h" 1
# 35 "../include/pub_tool_stacktrace.h"
typedef Addr* StackTrace;
# 59 "../include/pub_tool_stacktrace.h"
extern UInt vgPlain_get_StackTrace ( ThreadId tid,
                                         StackTrace ips, UInt n_ips,
                                         StackTrace sps,
                                         StackTrace fps,
                                  Word first_ip_delta );






extern void vgPlain_apply_StackTrace(
               void(*action)(UInt n, Addr ip, void* opaque),
               void* opaque,
               StackTrace ips, UInt n_ips
            );


extern void vgPlain_pp_StackTrace ( StackTrace ips, UInt n_ips );



extern void vgPlain_get_and_pp_StackTrace ( ThreadId tid, UInt n_ips );
# 40 "pub_core_stacktrace.h" 2
# 53 "pub_core_stacktrace.h"
UInt vgPlain_get_StackTrace_wrk ( ThreadId tid_if_known,
                                      Addr* ips, UInt n_ips,
                                      Addr* sps, Addr* fps,
                               UnwindStartRegs* startRegs,
                               Addr fp_max_orig );
# 44 "m_stacktrace.c" 2
# 1 "pub_core_xarray.h" 1
# 43 "pub_core_xarray.h"
# 1 "../include/pub_tool_xarray.h" 1
# 47 "../include/pub_tool_xarray.h"
typedef struct _XArray XArray;




extern XArray* vgPlain_newXA ( void*(*alloc_fn)(HChar*,SizeT),
                            HChar* cc,
                            void(*free_fn)(void*),
                            Word elemSzB );


extern void vgPlain_deleteXA ( XArray* );




extern void vgPlain_setCmpFnXA ( XArray*, Int (*compar)(void*,void*) );




extern Word vgPlain_addToXA ( XArray*, void* elem );




extern Word vgPlain_addBytesToXA ( XArray* xao, void* bytesV, Word nbytes );



extern void vgPlain_sortXA ( XArray* );






extern Bool vgPlain_lookupXA ( XArray*, void* key,
                                   Word* first, Word* last );
# 95 "../include/pub_tool_xarray.h"
extern Bool vgPlain_lookupXA_UNSAFE ( XArray* xao, void* key,
                                          Word* first, Word* last,
                                   Int(*cmpFn)(void*,void*) );


extern Word vgPlain_sizeXA ( XArray* );
# 109 "../include/pub_tool_xarray.h"
extern void* vgPlain_indexXA ( XArray*, Word );



extern void vgPlain_dropTailXA ( XArray*, Word );




extern void vgPlain_dropHeadXA ( XArray*, Word );





extern void vgPlain_removeIndexXA( XArray*, Word );







extern XArray* vgPlain_cloneXA( HChar* cc, XArray* xa );







extern void vgPlain_getContentsXA_UNSAFE( XArray* sr,
                                              void** ctsP,
                                              Word* usedP );





extern void vgPlain_xaprintf( XArray* dst, const HChar* format, ... )
                         __attribute__((format(__printf__, 2, 3)));
# 44 "pub_core_xarray.h" 2
# 45 "m_stacktrace.c" 2
# 1 "pub_core_clientstate.h" 1
# 41 "pub_core_clientstate.h"
# 1 "../include/pub_tool_clientstate.h" 1
# 41 "../include/pub_tool_clientstate.h"
extern XArray* vgPlain_args_for_client;
# 55 "../include/pub_tool_clientstate.h"
extern XArray* vgPlain_args_for_valgrind;



extern Int vgPlain_args_for_valgrind_noexecpass;



extern const HChar* vgPlain_args_the_exename;
# 42 "pub_core_clientstate.h" 2



extern Addr vgPlain_clstk_base;
extern Addr vgPlain_clstk_end;
extern UWord vgPlain_clstk_id;



extern UWord* vgPlain_client_auxv;

extern Addr vgPlain_brk_base;
extern Addr vgPlain_brk_limit;


extern Int vgPlain_cl_exec_fd;
# 68 "pub_core_clientstate.h"
extern Int vgPlain_cl_cmdline_fd;


extern struct vki_rlimit vgPlain_client_rlimit_data;
extern struct vki_rlimit vgPlain_client_rlimit_stack;



extern HChar* vgPlain_name_of_launcher;


extern Int vgPlain_fd_soft_limit;
extern Int vgPlain_fd_hard_limit;



extern Addr vgPlain_client___libc_freeres_wrapper;





extern Addr vgPlain_client__dl_sysinfo_int80;
# 46 "m_stacktrace.c" 2
# 1 "pub_core_trampoline.h" 1
# 56 "pub_core_trampoline.h"
extern Addr vgPlain_trampoline_stuff_start;
extern Addr vgPlain_trampoline_stuff_end;
# 97 "pub_core_trampoline.h"
extern Addr vgPlain_arm_linux_SUBST_FOR_sigreturn;
extern Addr vgPlain_arm_linux_SUBST_FOR_rt_sigreturn;
extern UInt vgPlain_arm_linux_REDIR_FOR_strlen( void* );

extern void* vgPlain_arm_linux_REDIR_FOR_memcpy( void*, void*, Int );
# 47 "m_stacktrace.c" 2
# 578 "m_stacktrace.c"
static Bool in_same_fn ( Addr a1, Addr a2 )
{

   UChar buf_a1[500], buf_a2[500];


   if (vgPlain_get_fnname_raw (a1, buf_a1, 500))
      if (vgPlain_get_fnname_raw (a2, buf_a2, 500))
         if (vgPlain_strncmp(buf_a1, buf_a2, 500))
            return ((Bool)1);

   return ((Bool)0);
}

static Bool in_same_page ( Addr a1, Addr a2 ) {
   return (a1 & ~0xFFF) == (a2 & ~0xFFF);
}

static Addr abs_diff ( Addr a1, Addr a2 ) {
   return (Addr)(a1 > a2 ? a1 - a2 : a2 - a1);
}

static Bool has_XT_perms ( Addr a )
{
   NSegment const* seg = vgPlain_am_find_nsegment(a);
   return seg && seg->hasX && seg->hasT;
}

static Bool looks_like_Thumb_call32 ( UShort w0, UShort w1 )
{
   if (0)
      vgPlain_printf("isT32call %04x %04x\n", (UInt)w0, (UInt)w1);

   if ((w0 & 0xF800) == 0xF000 && (w1 & 0xC000) == 0xC000) return ((Bool)1);

   if ((w0 & 0xF800) == 0xF000 && (w1 & 0xC000) == 0xC000) return ((Bool)1);
   return ((Bool)0);
}

static Bool looks_like_Thumb_call16 ( UShort w0 )
{
   return ((Bool)0);
}

static Bool looks_like_ARM_call ( UInt a0 )
{
   if (0)
      vgPlain_printf("isA32call %08x\n", a0);

   if ((a0 & 0xFF000000) == 0xEB000000) return ((Bool)1);
   return ((Bool)0);
}

static Bool looks_like_RA ( Addr ra )
{


   Bool isT = (ra & 1);
   if (isT) {

      ra &= ~1;
      ra -= 4;
      if (has_XT_perms(ra)) {
         UShort w0 = *(UShort*)ra;
         UShort w1 = in_same_page(ra, ra+2) ? *(UShort*)(ra+2) : 0;
         if (looks_like_Thumb_call16(w1) || looks_like_Thumb_call32(w0,w1))
            return ((Bool)1);
      }
   } else {

      ra &= ~3;
      ra -= 4;
      if (has_XT_perms(ra)) {
         UInt a0 = *(UInt*)ra;
         if (looks_like_ARM_call(a0))
            return ((Bool)1);
      }
   }
   return ((Bool)0);
}

UInt vgPlain_get_StackTrace_wrk ( ThreadId tid_if_known,
                                      Addr* ips, UInt max_n_ips,
                                      Addr* sps, Addr* fps,
                               UnwindStartRegs* startRegs,
                               Addr fp_max_orig )
{
   Bool debug = ((Bool)0);
   Int i;
   Addr fp_max;
   UInt n_found = 0;

   ((void) (__builtin_expect(!!(sizeof(Addr) == sizeof(UWord)), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "sizeof(Addr) == sizeof(UWord)", "m_stacktrace.c", 670, __PRETTY_FUNCTION__, ""), 0)));
   ((void) (__builtin_expect(!!(sizeof(Addr) == sizeof(void*)), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "sizeof(Addr) == sizeof(void*)", "m_stacktrace.c", 671, __PRETTY_FUNCTION__, ""), 0)));

   D3UnwindRegs uregs;
   uregs.r15 = startRegs->r_pc & 0xFFFFFFFE;
   uregs.r14 = startRegs->misc.ARM.r14;
   uregs.r13 = startRegs->r_sp;
   uregs.r12 = startRegs->misc.ARM.r12;
   uregs.r11 = startRegs->misc.ARM.r11;
   uregs.r7 = startRegs->misc.ARM.r7;
   Addr fp_min = uregs.r13;
# 689 "m_stacktrace.c"
   fp_max = ((Addr)((fp_max_orig)+((1UL << 12))-1) & ~((Addr)(((1UL << 12)))-1));
   if (fp_max >= sizeof(Addr))
      fp_max -= sizeof(Addr);

   if (debug)
      vgPlain_printf("\nmax_n_ips=%d fp_min=0x%lx fp_max_orig=0x%lx, "
                  "fp_max=0x%lx r15=0x%lx r13=0x%lx\n",
                  max_n_ips, fp_min, fp_max_orig, fp_max,
                  uregs.r15, uregs.r13);






   if (fp_min + 512 >= fp_max) {


      if (sps) sps[0] = uregs.r13;
      if (fps) fps[0] = 0;
      ips[0] = uregs.r15;
      return 1;
   }



   if (sps) sps[0] = uregs.r13;
   if (fps) fps[0] = 0;
   ips[0] = uregs.r15;
   i = 1;


   Bool do_stack_scan = ((Bool)0);

   while (((Bool)1)) {
      if (debug) {
         vgPlain_printf("i: %d, r15: 0x%lx, r13: 0x%lx\n",
                     i, uregs.r15, uregs.r13);
      }

      if (i >= max_n_ips)
         break;

      if (vgPlain_use_CF_info( &uregs, fp_min, fp_max )) {
         if (sps) sps[i] = uregs.r13;
         if (fps) fps[i] = 0;
         ips[i++] = (uregs.r15 & 0xFFFFFFFE) - 1;
         if (debug)
            vgPlain_printf("USING CFI: r15: 0x%lx, r13: 0x%lx\n",
                        uregs.r15, uregs.r13);
         uregs.r15 = (uregs.r15 & 0xFFFFFFFE) - 1;
         continue;
      }

      do_stack_scan = ((Bool)1);
      break;
   }

   if (0 && do_stack_scan && i < max_n_ips && i <= 2) {
      Int nByStackScan = 0;
      Addr lr = uregs.r14;
      Addr sp = uregs.r13 & ~3;
      Addr pc = uregs.r15;


      if (!in_same_fn(lr, pc) && looks_like_RA(lr)) {


         Addr cand = (lr & 0xFFFFFFFE) - 1;
         if (abs_diff(cand, ips[i-1]) > 1) {
            if (sps) sps[i] = 0;
            if (fps) fps[i] = 0;
            ips[i++] = cand;
            nByStackScan++;
         }
      }
      while (in_same_page(sp, uregs.r13)) {
         if (i >= max_n_ips)
            break;

         UWord w = *(UWord*)(sp & ~0x3);
         if (looks_like_RA(w)) {
            Addr cand = (w & 0xFFFFFFFE) - 1;


            if (abs_diff(cand, ips[i-1]) > 1) {
               if (sps) sps[i] = 0;
               if (fps) fps[i] = 0;
               ips[i++] = cand;
               if (++nByStackScan >= 5) break;
            }
         }
         sp += 4;
      }
   }

   n_found = i;
   return n_found;
}
# 1034 "m_stacktrace.c"
UInt vgPlain_get_StackTrace ( ThreadId tid,
                                  StackTrace ips, UInt max_n_ips,
                                  StackTrace sps,
                                  StackTrace fps,
                           Word first_ip_delta )
{

   UnwindStartRegs startRegs;
   vgPlain_memset( &startRegs, 0, sizeof(startRegs) );
   vgPlain_get_UnwindStartRegs( &startRegs, tid );

   Addr stack_highest_word = vgPlain_threads[tid].client_stack_highest_word;
   Addr stack_lowest_word = 0;
# 1077 "m_stacktrace.c"
   vgPlain_stack_limits( (Addr)startRegs.r_sp,
                      &stack_lowest_word, &stack_highest_word );


   startRegs.r_pc += (Long)(Word)first_ip_delta;

   if (0)
      vgPlain_printf("tid %d: stack_highest=0x%08lx ip=0x%010llx "
                  "sp=0x%010llx\n",
    tid, stack_highest_word,
                  startRegs.r_pc, startRegs.r_sp);

   return vgPlain_get_StackTrace_wrk(tid, ips, max_n_ips,
                                       sps, fps,
                                       &startRegs,
                                       stack_highest_word);
}

static void printIpDesc(UInt n, Addr ip, void* uu_opaque)
{


   static UChar buf[4096];

   vgPlain_describe_IP(ip, buf, 4096);

   if (vgPlain_clo_xml) {
      vgPlain_printf_xml("    %s\n", buf);
   } else {
      vgPlain_message(Vg_UserMsg, "   %s %s\n", ( n == 0 ? "at" : "by" ), buf);
   }
}


void vgPlain_pp_StackTrace ( StackTrace ips, UInt n_ips )
{
   ((void) (__builtin_expect(!!(n_ips > 0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "n_ips > 0", "m_stacktrace.c", 1113, __PRETTY_FUNCTION__, ""), 0)));

   if (vgPlain_clo_xml)
      vgPlain_printf_xml("  <stack>\n");

   vgPlain_apply_StackTrace( printIpDesc, ((void*)0), ips, n_ips );

   if (vgPlain_clo_xml)
      vgPlain_printf_xml("  </stack>\n");
}


void vgPlain_get_and_pp_StackTrace ( ThreadId tid, UInt max_n_ips )
{
   Addr ips[max_n_ips];
   UInt n_ips
      = vgPlain_get_StackTrace(tid, ips, max_n_ips,
                            ((void*)0) ,
                            ((void*)0) ,
                            0 );
   vgPlain_pp_StackTrace(ips, n_ips);
}

void vgPlain_apply_StackTrace(
        void(*action)(UInt n, Addr ip, void* opaque),
        void* opaque,
        StackTrace ips, UInt n_ips
     )
{
   Bool main_done = ((Bool)0);
   Int i = 0;

   ((void) (__builtin_expect(!!(n_ips > 0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "n_ips > 0", "m_stacktrace.c", 1145, __PRETTY_FUNCTION__, ""), 0)));
   do {
      Addr ip = ips[i];




      if ( ! vgPlain_clo_show_below_main ) {
         Vg_FnNameKind kind = vgPlain_get_fnname_kind_from_IP(ip);
         if (Vg_FnNameMain == kind || Vg_FnNameBelowMain == kind) {
            main_done = ((Bool)1);
         }
      }


      action(i, ip, opaque);

      i++;
   } while (i < n_ips && !main_done);


}

Bool vgPlain_clo_xml = 0;
Bool vgPlain_clo_show_below_main = 1;

int main(int argc, char** argv) {
    vgPlain_get_and_pp_StackTrace(0, 15);
    return 0;
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// strncmp

Int vgPlain_strncmp ( const Char* s1, const Char* s2, SizeT nmax ) {
    return strncmp(s1, s2, nmax);
}

// printf

UInt vgPlain_printf ( const HChar *format, ... ) {
    va_list vargs;
    va_start(vargs, format);
    UInt ret = vprintf(format, vargs);
    va_end(vargs);
    return ret;
}

// memset

void* vgPlain_memset ( void *s, Int c, SizeT sz ) {
    return memset(s, c, sz);
}

// printf_xml

UInt vgPlain_printf_xml ( const HChar *format, ... ) {
    return 0;
}

// assert_fail

void vgPlain_assert_fail ( Bool isCore, const Char* expr, const Char* file,
                               Int line, const Char* fn,
                               const HChar* format, ... ) {
    exit(1);
}

// message

UInt vgPlain_message( VgMsgKind kind, const HChar* format, ... ) {
    va_list vargs;
    va_start(vargs, format);
    UInt ret = vprintf(format, vargs);
    va_end(vargs);
    return ret;
}

// get_fnname_kind_from_IP

Vg_FnNameKind vgPlain_get_fnname_kind_from_IP ( Addr ip ) {
    return Vg_FnNameNormal;
}

// describe_IP

Char* vgPlain_describe_IP(Addr eip, Char* buf, Int n_buf) {
    snprintf(buf, n_buf, "0x%010lx", eip);
    return buf;
}

// use_CF_info

typedef
   struct {
      Addr base;
      UInt len;
      UChar cfa_how;
      UChar ra_how;
      UChar r14_how;
      UChar r13_how;
      UChar r12_how;
      UChar r11_how;
      UChar r7_how;
      Int cfa_off;
      Int ra_off;
      Int r14_off;
      Int r13_off;
      Int r12_off;
      Int r11_off;
      Int r7_off;
   }
   DiCfSI;

typedef
   enum {
      Cop_Add=0x321,
      Cop_Sub,
      Cop_And,
      Cop_Mul,
      Cop_Shl,
      Cop_Shr,
      Cop_Eq,
      Cop_Ge,
      Cop_Gt,
      Cop_Le,
      Cop_Lt,
      Cop_Ne
   }
   CfiOp;

typedef
   enum {
      Creg_IA_SP=0x213,
      Creg_IA_BP,
      Creg_IA_IP,
      Creg_ARM_R13,
      Creg_ARM_R12,
      Creg_ARM_R15,
      Creg_ARM_R14,
      Creg_S390_R14,
      Creg_MIPS_RA
   }
   CfiReg;

typedef
   enum {
      Cex_Undef=0x123,
      Cex_Deref,
      Cex_Const,
      Cex_Binop,
      Cex_CfiReg,
      Cex_DwReg
   }
   CfiExprTag;

typedef
   struct {
      CfiExprTag tag;
      union {
         struct {
         } Undef;
         struct {
            Int ixAddr;
         } Deref;
         struct {
            UWord con;
         } Const;
         struct {
            CfiOp op;
            Int ixL;
            Int ixR;
         } Binop;
         struct {
            CfiReg reg;
         } CfiReg;
         struct {
            Int reg;
         } DwReg;
      }
      Cex;
   }
   CfiExpr;
typedef
   struct { Addr ip; DebugInfo* di; Word ix; }
   CFSICacheEnt;

typedef
   struct {
      D3UnwindRegs* uregs;
      Addr min_accessible;
      Addr max_accessible;
   }
   CfiExprEvalContext;

static CFSICacheEnt cfsi_cache[511];
static DebugInfo* debugInfo_list = ((void*)0);

struct _DebugInfoFSM
{
   UChar* filename;
   XArray* maps;
   Bool have_rx_map;
   Bool have_rw_map;
   Bool have_ro_map;
};

typedef
   struct {
      Addr addr;
      Addr tocptr;
      UChar* pri_name;
      UChar** sec_names;





      UInt size;
      Bool isText;
      Bool isIFunc;
   }
   DiSym;

typedef
   struct {

      Addr addr;

      UShort size:(32 - 20);
      UInt lineno:20;

      UChar* filename;

      UChar* dirname;
   }
   DiLoc;

typedef
   struct _FPO_DATA {
      UInt ulOffStart;
      UInt cbProcSize;
      UInt cdwLocals;
      UShort cdwParams;
      UChar cbProlog;
      UChar cbRegs :3;
      UChar fHasSEH:1;
      UChar fUseBP :1;
      UChar reserved:1;
      UChar cbFrame:2;
   }
   FPO_DATA;

struct _DebugInfo {



   struct _DebugInfo* next;
   Bool mark;
# 490 "m_debuginfo/priv_storage.h"
   ULong handle;







   Bool trace_symtab;
   Bool trace_cfi;
   Bool ddump_syms;
   Bool ddump_line;
   Bool ddump_frames;





   struct _DebugInfoFSM fsm;
# 518 "m_debuginfo/priv_storage.h"
   Bool have_dinfo;






   UChar* soname;
# 658 "m_debuginfo/priv_storage.h"
   Bool text_present;
   Addr text_avma;
   Addr text_svma;
   SizeT text_size;
   PtrdiffT text_bias;
   Addr text_debug_svma;
   PtrdiffT text_debug_bias;

   Bool data_present;
   Addr data_svma;
   Addr data_avma;
   SizeT data_size;
   PtrdiffT data_bias;
   Addr data_debug_svma;
   PtrdiffT data_debug_bias;

   Bool sdata_present;
   Addr sdata_svma;
   Addr sdata_avma;
   SizeT sdata_size;
   PtrdiffT sdata_bias;
   Addr sdata_debug_svma;
   PtrdiffT sdata_debug_bias;

   Bool rodata_present;
   Addr rodata_svma;
   Addr rodata_avma;
   SizeT rodata_size;
   PtrdiffT rodata_bias;
   Addr rodata_debug_svma;
   PtrdiffT rodata_debug_bias;

   Bool bss_present;
   Addr bss_svma;
   Addr bss_avma;
   SizeT bss_size;
   PtrdiffT bss_bias;
   Addr bss_debug_svma;
   PtrdiffT bss_debug_bias;

   Bool sbss_present;
   Addr sbss_svma;
   Addr sbss_avma;
   SizeT sbss_size;
   PtrdiffT sbss_bias;
   Addr sbss_debug_svma;
   PtrdiffT sbss_debug_bias;

   Bool plt_present;
   Addr plt_avma;
   SizeT plt_size;

   Bool got_present;
   Addr got_avma;
   SizeT got_size;

   Bool gotplt_present;
   Addr gotplt_avma;
   SizeT gotplt_size;

   Bool opd_present;
   Addr opd_avma;
   SizeT opd_size;


   UInt n_ehframe;
   Addr ehframe_avma[2];
   SizeT ehframe_size[2];






   DiSym* symtab;
   UWord symtab_used;
   UWord symtab_size;

   DiLoc* loctab;
   UWord loctab_used;
   UWord loctab_size;





   DiCfSI* cfsi;
   UWord cfsi_used;
   UWord cfsi_size;
   Addr cfsi_minavma;
   Addr cfsi_maxavma;
   XArray* cfsi_exprs;



   FPO_DATA* fpo;
   UWord fpo_size;
   Addr fpo_minavma;
   Addr fpo_maxavma;
   Addr fpo_base_avma;



   struct strchunk {
      UInt strtab_used;
      struct strchunk* next;
      UChar strtab[(64*1024)];
   } *strchunks;
# 788 "m_debuginfo/priv_storage.h"
   XArray* varinfo;
# 798 "m_debuginfo/priv_storage.h"
   XArray* admin_tyents;


   XArray* admin_gexprs;




   struct _DebugInfoMapping* last_rx_map;
};

struct _XArray {
   void* (*alloc) ( HChar*, SizeT );
   HChar* cc;
   void (*free) ( void* );
   Int (*cmpFn) ( void*, void* );
   Word elemSzB;
   void* arr;
   Word usedsizeE;
   Word totsizeE;
   Bool sorted;
};

static inline Bool host_is_little_endian ( void ) {
   UInt x = 0x76543210;
   UChar* p = (UChar*)(&x);
   return toBool(*p == 0x10);
}

UInt vgModuleLocal_read_UInt ( UChar* data );
UInt vgModuleLocal_read_UInt ( UChar* data ) {
   UInt r = 0;
   if (host_is_little_endian()) {
      r = data[0]
          | ( ((UInt)data[1]) << 8 )
          | ( ((UInt)data[2]) << 16 )
          | ( ((UInt)data[3]) << 24 );
   } else {
      r = data[3]
          | ( ((UInt)data[2]) << 8 )
          | ( ((UInt)data[1]) << 16 )
          | ( ((UInt)data[0]) << 24 );
   }
   return r;
}

ULong vgModuleLocal_read_ULong ( UChar* data );
ULong vgModuleLocal_read_ULong ( UChar* data ) {
   ULong r = 0;
   if (host_is_little_endian()) {
      r = data[0]
       | ( ((ULong)data[1]) << 8 )
       | ( ((ULong)data[2]) << 16 )
       | ( ((ULong)data[3]) << 24 )
       | ( ((ULong)data[4]) << 32 )
       | ( ((ULong)data[5]) << 40 )
       | ( ((ULong)data[6]) << 48 )
       | ( ((ULong)data[7]) << 56 );
   } else {
      r = data[7]
       | ( ((ULong)data[6]) << 8 )
       | ( ((ULong)data[5]) << 16 )
       | ( ((ULong)data[4]) << 24 )
       | ( ((ULong)data[3]) << 32 )
       | ( ((ULong)data[2]) << 40 )
       | ( ((ULong)data[1]) << 48 )
       | ( ((ULong)data[0]) << 56 );
   }
   return r;
}

Addr vgModuleLocal_read_Addr ( UChar* data );
Addr vgModuleLocal_read_Addr ( UChar* data ) {
   if (sizeof(Addr) == sizeof(UInt)) {
      return vgModuleLocal_read_UInt(data);
   } else if (sizeof(Addr) == sizeof(ULong)) {
      return vgModuleLocal_read_ULong(data);
   } else {
      ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/misc.c", 253, __PRETTY_FUNCTION__, ""), 0)));
   }
}

UWord vgModuleLocal_read_UWord ( UChar* data );
UWord vgModuleLocal_read_UWord ( UChar* data ) {
   if (sizeof(UWord) == sizeof(UInt)) {
      return vgModuleLocal_read_UInt(data);
   } else if (sizeof(UWord) == sizeof(ULong)) {
      return vgModuleLocal_read_ULong(data);
   } else {
      ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/misc.c", 156, __PRETTY_FUNCTION__, ""), 0)));
   }
}

Word vgModuleLocal_search_one_cfitab ( struct _DebugInfo* di, Addr ptr );
Word vgModuleLocal_search_one_cfitab ( struct _DebugInfo* di, Addr ptr )
{
   Addr a_mid_lo, a_mid_hi;
   Word mid, size,
        lo = 0,
        hi = di->cfsi_used-1;
   while (((Bool)1)) {

      if (lo > hi) return -1;
      mid = (lo + hi) / 2;
      a_mid_lo = di->cfsi[mid].base;
      size = di->cfsi[mid].len;
      a_mid_hi = a_mid_lo + size - 1;
      ((void) (__builtin_expect(!!(a_mid_hi >= a_mid_lo), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "a_mid_hi >= a_mid_lo", "m_debuginfo/storage.c", 1856, __PRETTY_FUNCTION__, ""), 0)));
      if (ptr < a_mid_lo) { hi = mid-1; continue; }
      if (ptr > a_mid_hi) { lo = mid+1; continue; }
      ((void) (__builtin_expect(!!(ptr >= a_mid_lo && ptr <= a_mid_hi), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "ptr >= a_mid_lo && ptr <= a_mid_hi", "m_debuginfo/storage.c", 1859, __PRETTY_FUNCTION__, ""), 0)));
      return mid;
   }
}

inline void* vgPlain_indexXA ( XArray* xao, Word n );
inline void* vgPlain_indexXA ( XArray* xao, Word n )
{
   struct _XArray* xa = (struct _XArray*)xao;
   ((void) (__builtin_expect(!!(xa), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "xa", "m_xarray.c", 140, __PRETTY_FUNCTION__, ""), 0)));
   ((void) (__builtin_expect(!!(n >= 0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "n >= 0", "m_xarray.c", 141, __PRETTY_FUNCTION__, ""), 0)));
   ((void) (__builtin_expect(!!(n < xa->usedsizeE), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "n < xa->usedsizeE", "m_xarray.c", 142, __PRETTY_FUNCTION__, ""), 0)));
   return ((char*)xa->arr) + n * xa->elemSzB;
}

__attribute__((noinline))
static
UWord evalCfiExpr ( XArray* exprs, Int ix,
                    CfiExprEvalContext* eec, Bool* ok )
{
   UWord wL, wR;
   Addr a;
   CfiExpr* e;
   ((void) (__builtin_expect(!!(sizeof(Addr) == sizeof(UWord)), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "sizeof(Addr) == sizeof(UWord)", "m_debuginfo/debuginfo.c", 2057, __PRETTY_FUNCTION__, ""), 0)));
   e = vgPlain_indexXA( exprs, ix );
   switch (e->tag) {
      case Cex_Binop:
         wL = evalCfiExpr( exprs, e->Cex.Binop.ixL, eec, ok );
         if (!(*ok)) return 0;
         wR = evalCfiExpr( exprs, e->Cex.Binop.ixR, eec, ok );
         if (!(*ok)) return 0;
         switch (e->Cex.Binop.op) {
            case Cop_Add: return wL + wR;
            case Cop_Sub: return wL - wR;
            case Cop_And: return wL & wR;
            case Cop_Mul: return wL * wR;
            case Cop_Shl: return wL << wR;
            case Cop_Shr: return wL >> wR;
            case Cop_Eq: return wL == wR ? 1 : 0;
            case Cop_Ge: return (Word) wL >= (Word) wR ? 1 : 0;
            case Cop_Gt: return (Word) wL > (Word) wR ? 1 : 0;
            case Cop_Le: return (Word) wL <= (Word) wR ? 1 : 0;
            case Cop_Lt: return (Word) wL < (Word) wR ? 1 : 0;
            case Cop_Ne: return wL != wR ? 1 : 0;
            default: goto unhandled;
         }

      case Cex_CfiReg:
         switch (e->Cex.CfiReg.reg) {





            case Creg_ARM_R15: return eec->uregs->r15;
            case Creg_ARM_R14: return eec->uregs->r14;
            case Creg_ARM_R13: return eec->uregs->r13;
            case Creg_ARM_R12: return eec->uregs->r12;
# 2106 "m_debuginfo/debuginfo.c"
            default: goto unhandled;
         }

      case Cex_Const:
         return e->Cex.Const.con;
      case Cex_Deref:
         a = evalCfiExpr( exprs, e->Cex.Deref.ixAddr, eec, ok );
         if (!(*ok)) return 0;
         if (a < eec->min_accessible
             || a > eec->max_accessible - sizeof(UWord) + 1) {
            *ok = ((Bool)0);
            return 0;
         }

         return vgModuleLocal_read_UWord((void *)a);
      default:
         goto unhandled;
   }

  unhandled:
   vgPlain_printf("\n\nevalCfiExpr: unhandled\n");
   ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2129, __PRETTY_FUNCTION__, ""), 0)));

   return 0;
}

inline
static Addr compute_cfa ( D3UnwindRegs* uregs,
                          Addr min_accessible, Addr max_accessible,
                          DebugInfo* di, DiCfSI* cfsi )
{
   CfiExprEvalContext eec;
   Addr cfa;
   Bool ok;


   cfa = 0;
   switch (cfsi->cfa_how) {
# 2300 "m_debuginfo/debuginfo.c"
      case ((UChar)4):
         cfa = cfsi->cfa_off + uregs->r13;
         break;
      case ((UChar)5):
         cfa = cfsi->cfa_off + uregs->r12;
         break;
      case ((UChar)6):
         cfa = cfsi->cfa_off + uregs->r11;
         break;
      case ((UChar)7):
         cfa = cfsi->cfa_off + uregs->r7;
         break;
# 2344 "m_debuginfo/debuginfo.c"
      case ((UChar)8):
         eec.uregs = uregs;
         eec.min_accessible = min_accessible;
         eec.max_accessible = max_accessible;
         ok = ((Bool)1);
         cfa = evalCfiExpr(di->cfsi_exprs, cfsi->cfa_off, &eec, &ok );
         if (!ok) return 0;
         break;
      default:
         ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2358, __PRETTY_FUNCTION__, ""), 0)));
   }
   return cfa;
}

static void move_DebugInfo_one_step_forward ( DebugInfo* di )
{
   DebugInfo *di0, *di1, *di2;
   if (di == debugInfo_list)
      return;
   ((void) (__builtin_expect(!!(di != ((void*)0)), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "di != NULL", "m_debuginfo/debuginfo.c", 125, __PRETTY_FUNCTION__, ""), 0)));
   di0 = debugInfo_list;
   di1 = ((void*)0);
   di2 = ((void*)0);
   while (((Bool)1)) {
      if (di0 == ((void*)0) || di0 == di) break;
      di2 = di1;
      di1 = di0;
      di0 = di0->next;
   }
   ((void) (__builtin_expect(!!(di0 == di), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "di0 == di", "m_debuginfo/debuginfo.c", 135, __PRETTY_FUNCTION__, ""), 0)));
   if (di0 != ((void*)0) && di1 != ((void*)0) && di2 != ((void*)0)) {
      DebugInfo* tmp;



      ((void) (__builtin_expect(!!(di2->next == di1), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "di2->next == di1", "m_debuginfo/debuginfo.c", 141, __PRETTY_FUNCTION__, ""), 0)));
      ((void) (__builtin_expect(!!(di1->next == di0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "di1->next == di0", "m_debuginfo/debuginfo.c", 142, __PRETTY_FUNCTION__, ""), 0)));
      tmp = di0->next;
      di2->next = di0;
      di0->next = di1;
      di1->next = tmp;
   }
   else
   if (di0 != ((void*)0) && di1 != ((void*)0) && di2 == ((void*)0)) {

      ((void) (__builtin_expect(!!(debugInfo_list == di1), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "debugInfo_list == di1", "m_debuginfo/debuginfo.c", 151, __PRETTY_FUNCTION__, ""), 0)));
      ((void) (__builtin_expect(!!(di1->next == di0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "di1->next == di0", "m_debuginfo/debuginfo.c", 152, __PRETTY_FUNCTION__, ""), 0)));
      di1->next = di0->next;
      di0->next = di1;
      debugInfo_list = di0;
   }
}

__attribute__((noinline))
static void find_DiCfSI ( DebugInfo** diP,
                                 Word* ixP,
                          Addr ip )
{
   DebugInfo* di;
   Word i = -1;

   static UWord n_search = 0;
   static UWord n_steps = 0;
   n_search++;

   for (di = debugInfo_list; di != ((void*)0); di = di->next) {
      Word j;
      n_steps++;



      if (di->cfsi_used == 0)
         continue;
      if (ip < di->cfsi_minavma || ip > di->cfsi_maxavma)
         continue;


      j = vgModuleLocal_search_one_cfitab( di, ip );
      ((void) (__builtin_expect(!!(j >= -1 && j < (Word)di->cfsi_used), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "j >= -1 && j < (Word)di->cfsi_used", "m_debuginfo/debuginfo.c", 2170, __PRETTY_FUNCTION__, ""), 0)));

      if (j != -1) {
         i = j;
         break;
      }
   }

   if (i == -1) {


      *diP = (DebugInfo*)1;
      *ixP = 0;

   } else {




      ((void) (__builtin_expect(!!(di && (0 == (((Addr)(di)) & ((Addr)0x3)))), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "di && VG_IS_4_ALIGNED(di)", "m_debuginfo/debuginfo.c", 2189, __PRETTY_FUNCTION__, ""), 0)));
      ((void) (__builtin_expect(!!(i >= 0 && i < di->cfsi_used), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "i >= 0 && i < di->cfsi_used", "m_debuginfo/debuginfo.c", 2190, __PRETTY_FUNCTION__, ""), 0)));
      *diP = di;
      *ixP = i;
# 2201 "m_debuginfo/debuginfo.c"
      if ((n_search & 0xF) == 0) {

         move_DebugInfo_one_step_forward( di );
      }


      if (0 && ((n_search & 0x7FFFF) == 0))
         vgPlain_printf("find_DiCfSI: %lu searches, "
                     "%lu DebugInfos looked at\n",
                     n_search, n_steps);

   }

}

static inline CFSICacheEnt* cfsi_cache__find ( Addr ip )
{
   UWord hash = ip % 511;
   CFSICacheEnt* ce = &cfsi_cache[hash];
   static UWord n_q = 0, n_m = 0;

   n_q++;
   if (0 && 0 == (n_q & 0x1FFFFF))
      vgPlain_printf("QQQ %lu %lu\n", n_q, n_m);

   if (__builtin_expect(!!(ce->ip == ip), 1) && __builtin_expect(!!(ce->di != ((void*)0)), 1)) {

   } else {

      n_m++;
      ce->ip = ip;
      find_DiCfSI( &ce->di, &ce->ix, ip );
   }

   if (__builtin_expect(!!(ce->di == (DebugInfo*)1), 0)) {

      return ((void*)0);
   } else {

      return ce;
   }
}

Bool vgPlain_use_CF_info ( D3UnwindRegs* uregsHere,
                        Addr min_accessible,
                        Addr max_accessible ) {
   DebugInfo* di;
   DiCfSI* cfsi = ((void*)0);
   Addr cfa, ipHere = 0;
   CFSICacheEnt* ce;
   CfiExprEvalContext eec __attribute__((unused));
   D3UnwindRegs uregsPrev;




   ipHere = uregsHere->r15;
# 2440 "m_debuginfo/debuginfo.c"
   ce = cfsi_cache__find(ipHere);

   if (__builtin_expect(!!(ce == ((void*)0)), 0))
      return ((Bool)0);

   di = ce->di;
   cfsi = &di->cfsi[ ce->ix ];

   vgPlain_bzero_inline(&uregsPrev, sizeof(uregsPrev));


   cfa = compute_cfa(uregsHere,
                     min_accessible, max_accessible, di, cfsi);
   if (__builtin_expect(!!(cfa == 0), 0))
      return ((Bool)0);
# 2502 "m_debuginfo/debuginfo.c"
   do { switch (cfsi->ra_how) { case ((UChar)64): return ((Bool)0); case ((UChar)65): uregsPrev.r15 = uregsHere->r15; break; case ((UChar)67): { Addr a = cfa + (Word)cfsi->ra_off; if (a < min_accessible || a > max_accessible-sizeof(Addr)) return ((Bool)0); uregsPrev.r15 = vgModuleLocal_read_Addr((void *)a); break; } case ((UChar)66): uregsPrev.r15 = cfa + (Word)cfsi->ra_off; break; case ((UChar)68): eec.uregs = uregsHere; eec.min_accessible = min_accessible; eec.max_accessible = max_accessible; Bool ok = ((Bool)1); uregsPrev.r15 = evalCfiExpr(di->cfsi_exprs, cfsi->ra_off, &eec, &ok ); if (!ok) return ((Bool)0); break; default: ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2502, __PRETTY_FUNCTION__, ""), 0))); } } while (0);
   do { switch (cfsi->r14_how) { case ((UChar)64): return ((Bool)0); case ((UChar)65): uregsPrev.r14 = uregsHere->r14; break; case ((UChar)67): { Addr a = cfa + (Word)cfsi->r14_off; if (a < min_accessible || a > max_accessible-sizeof(Addr)) return ((Bool)0); uregsPrev.r14 = vgModuleLocal_read_Addr((void *)a); break; } case ((UChar)66): uregsPrev.r14 = cfa + (Word)cfsi->r14_off; break; case ((UChar)68): eec.uregs = uregsHere; eec.min_accessible = min_accessible; eec.max_accessible = max_accessible; Bool ok = ((Bool)1); uregsPrev.r14 = evalCfiExpr(di->cfsi_exprs, cfsi->r14_off, &eec, &ok ); if (!ok) return ((Bool)0); break; default: ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2503, __PRETTY_FUNCTION__, ""), 0))); } } while (0);
   do { switch (cfsi->r13_how) { case ((UChar)64): return ((Bool)0); case ((UChar)65): uregsPrev.r13 = uregsHere->r13; break; case ((UChar)67): { Addr a = cfa + (Word)cfsi->r13_off; if (a < min_accessible || a > max_accessible-sizeof(Addr)) return ((Bool)0); uregsPrev.r13 = vgModuleLocal_read_Addr((void *)a); break; } case ((UChar)66): uregsPrev.r13 = cfa + (Word)cfsi->r13_off; break; case ((UChar)68): eec.uregs = uregsHere; eec.min_accessible = min_accessible; eec.max_accessible = max_accessible; Bool ok = ((Bool)1); uregsPrev.r13 = evalCfiExpr(di->cfsi_exprs, cfsi->r13_off, &eec, &ok ); if (!ok) return ((Bool)0); break; default: ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2504, __PRETTY_FUNCTION__, ""), 0))); } } while (0);
   do { switch (cfsi->r12_how) { case ((UChar)64): return ((Bool)0); case ((UChar)65): uregsPrev.r12 = uregsHere->r12; break; case ((UChar)67): { Addr a = cfa + (Word)cfsi->r12_off; if (a < min_accessible || a > max_accessible-sizeof(Addr)) return ((Bool)0); uregsPrev.r12 = vgModuleLocal_read_Addr((void *)a); break; } case ((UChar)66): uregsPrev.r12 = cfa + (Word)cfsi->r12_off; break; case ((UChar)68): eec.uregs = uregsHere; eec.min_accessible = min_accessible; eec.max_accessible = max_accessible; Bool ok = ((Bool)1); uregsPrev.r12 = evalCfiExpr(di->cfsi_exprs, cfsi->r12_off, &eec, &ok ); if (!ok) return ((Bool)0); break; default: ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2505, __PRETTY_FUNCTION__, ""), 0))); } } while (0);
   do { switch (cfsi->r11_how) { case ((UChar)64): return ((Bool)0); case ((UChar)65): uregsPrev.r11 = uregsHere->r11; break; case ((UChar)67): { Addr a = cfa + (Word)cfsi->r11_off; if (a < min_accessible || a > max_accessible-sizeof(Addr)) return ((Bool)0); uregsPrev.r11 = vgModuleLocal_read_Addr((void *)a); break; } case ((UChar)66): uregsPrev.r11 = cfa + (Word)cfsi->r11_off; break; case ((UChar)68): eec.uregs = uregsHere; eec.min_accessible = min_accessible; eec.max_accessible = max_accessible; Bool ok = ((Bool)1); uregsPrev.r11 = evalCfiExpr(di->cfsi_exprs, cfsi->r11_off, &eec, &ok ); if (!ok) return ((Bool)0); break; default: ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2506, __PRETTY_FUNCTION__, ""), 0))); } } while (0);
   do { switch (cfsi->r7_how) { case ((UChar)64): return ((Bool)0); case ((UChar)65): uregsPrev.r7 = uregsHere->r7; break; case ((UChar)67): { Addr a = cfa + (Word)cfsi->r7_off; if (a < min_accessible || a > max_accessible-sizeof(Addr)) return ((Bool)0); uregsPrev.r7 = vgModuleLocal_read_Addr((void *)a); break; } case ((UChar)66): uregsPrev.r7 = cfa + (Word)cfsi->r7_off; break; case ((UChar)68): eec.uregs = uregsHere; eec.min_accessible = min_accessible; eec.max_accessible = max_accessible; Bool ok = ((Bool)1); uregsPrev.r7 = evalCfiExpr(di->cfsi_exprs, cfsi->r7_off, &eec, &ok ); if (!ok) return ((Bool)0); break; default: ((void) (__builtin_expect(!!(0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "0", "m_debuginfo/debuginfo.c", 2507, __PRETTY_FUNCTION__, ""), 0))); } } while (0);
# 2523 "m_debuginfo/debuginfo.c"
   *uregsHere = uregsPrev;
   return ((Bool)1);
}

// get_UnwindStartRegs

void vgPlain_get_UnwindStartRegs ( UnwindStartRegs* regs,
                                ThreadId tid )
{
# 89 "m_machine.c"
   regs->r_pc = (ULong)vgPlain_threads[tid].arch.vex.guest_R15T;
   regs->r_sp = (ULong)vgPlain_threads[tid].arch.vex.guest_R13;
   regs->misc.ARM.r14
      = vgPlain_threads[tid].arch.vex.guest_R14;
   regs->misc.ARM.r12
      = vgPlain_threads[tid].arch.vex.guest_R12;
   regs->misc.ARM.r11
      = vgPlain_threads[tid].arch.vex.guest_R11;
   regs->misc.ARM.r7
      = vgPlain_threads[tid].arch.vex.guest_R7;
# 118 "m_machine.c"
}

// stack_limits

typedef struct _Stack {
   UWord id;
   Addr start;
   Addr end;
   struct _Stack *next;
} Stack;

static Stack *stacks;

static void move_Stack_one_step_forward ( Stack* st )
{
   Stack *st0, *st1, *st2;
   if (st == stacks)
      return;
   ((void) (__builtin_expect(!!(st != ((void*)0)), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "st != NULL", "m_stacks.c", 110, __PRETTY_FUNCTION__, ""), 0)));
   st0 = stacks;
   st1 = ((void*)0);
   st2 = ((void*)0);
   while (((Bool)1)) {
      if (st0 == ((void*)0) || st0 == st) break;
      st2 = st1;
      st1 = st0;
      st0 = st0->next;
   }
   ((void) (__builtin_expect(!!(st0 == st), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "st0 == st", "m_stacks.c", 120, __PRETTY_FUNCTION__, ""), 0)));
   if (st0 != ((void*)0) && st1 != ((void*)0) && st2 != ((void*)0)) {
      Stack* tmp;



      ((void) (__builtin_expect(!!(st2->next == st1), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "st2->next == st1", "m_stacks.c", 126, __PRETTY_FUNCTION__, ""), 0)));
      ((void) (__builtin_expect(!!(st1->next == st0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "st1->next == st0", "m_stacks.c", 127, __PRETTY_FUNCTION__, ""), 0)));
      tmp = st0->next;
      st2->next = st0;
      st0->next = st1;
      st1->next = tmp;
   }
   else
   if (st0 != ((void*)0) && st1 != ((void*)0) && st2 == ((void*)0)) {

      ((void) (__builtin_expect(!!(stacks == st1), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "stacks == st1", "m_stacks.c", 136, __PRETTY_FUNCTION__, ""), 0)));
      ((void) (__builtin_expect(!!(st1->next == st0), 1) ? 0 : (vgPlain_assert_fail ( ((Bool)1), "st1->next == st0", "m_stacks.c", 137, __PRETTY_FUNCTION__, ""), 0)));
      st1->next = st0->next;
      st0->next = st1;
      stacks = st0;
   }
}

static Stack* find_stack_by_addr(Addr sp)
{
   static UWord n_fails = 0;
   static UWord n_searches = 0;
   static UWord n_steps = 0;
   Stack *i = stacks;
   n_searches++;
   if (0 && 0 == (n_searches % 10000))
      vgPlain_printf("(hgdev) %lu searches, %lu steps, %lu fails\n",
                  n_searches, n_steps+1, n_fails);

   if (i && sp >= i->start && sp <= i->end)
      return i;

   while (i) {
      n_steps++;
      if (sp >= i->start && sp <= i->end) {
         if (1 && (n_searches & 0x3F) == 0) {
            move_Stack_one_step_forward( i );
         }
         return i;
      }
      i = i->next;
   }
   n_fails++;
   return ((void*)0);
}


void vgPlain_stack_limits(Addr SP, Addr *start, Addr *end )
{
   Stack* stack = find_stack_by_addr(SP);

   if (stack) {
      *start = stack->start;
      *end = stack->end;
   }
}

// threads

ThreadState vgPlain_threads[500];
