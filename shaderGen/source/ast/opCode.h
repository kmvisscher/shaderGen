#pragma once
#ifndef __SHADERGEN_OPCODE_H__
#define __SHADERGEN_OPCODE_H__

#include <assert.h>

#include "common/types.h"

typedef S32 OpID;

#define OP_NUM_INPUTS 20
#define OP_NUM_PAYLOADS 4

enum SgOpGroupTypes
{
    SgOpNULL = 0x01,
    SgOpAssignment = 0x02,
    SgOpDeclaration = 0x04,
    SgOpFlowControl = 0x08,
    SgOpComparisonOperator = 0x10,
    SgOpMathOperator = 0x20,
    SgOpIntrinsic = 0x40,
    SgOpFunctionCall = 0x80
};

enum SgDeclarationTypes
{
    SgDeclConstant = 0x01,
    SgDeclArray = 0x02
};

enum SgMathOperators
{
    SgAddOperator = 0x01,
    SgSubOperator = 0x02,
    SgMulOperator = 0x04,
    SgDivOperator = 0x08
};

enum SgComparisonOperators
{
    SgLtComp = 0x01,
    SgLeComp = 0x02,
    SgEqualComp = 0x04,
    SgGtComp = 0x08,
    SgGeComp = 0x10
};

enum SgFlowControlOperators
{
    SgBreakFlow = 0x01,    //1
    SgContinueFlow = 0x02, //2
    SgDiscardFlow = 0x04,  //4
    SgDoFlow = 0x08,       //8
    SgForFlow = 0x10,      //16
    SgIfFlow = 0x20,       //32
    SgWhileFlow = 0x40,    //64
    SgFlowTerminate = 0x80 //128
};

enum SgFunctionParameters
{
    SgFunctionStart = 0x01,
    SgFunctionTerminate = 0x02,
    SgFunctionParameter = 0x04
};

enum class SgIntrinsics : U64
{
    SgAbs   = (S64)1 << 0,
    SgAcos  = (S64)1 << 1,
    SgAsin  = (S64)1 << 2,
    SgAtan  = (S64)1 << 3,
    SgAtan2 = (S64)1 << 4,
    SgCeil  = (S64)1 << 5,
    SgClamp = (S64)1 << 6,
    SgClip  = (S64)1 << 7,
    SgCos   = (S64)1 << 8,
    SgCosh  = (S64)1 << 9,
    
    //10
    SgCross = (S64)1 << 10,
    SgDdx   = (S64)1 << 11,
    SgDdy   = (S64)1 << 12,
    SgDegrees = (S64)1 << 13,
    SgDeterminant = (S64)1 << 14,
    SgDistance = (S64)1 << 15,
    SgDot   = (S64)1 << 16,
    SgDst   = (S64)1 << 17,
    SgExp   = (S64)1 << 18,
    SgExp2  = (S64)1 << 19,

    //20
    SgFloor = (S64)1 << 20,
    SgMod   = (S64)1 << 21,
    SgFrac  = (S64)1 << 22,
    SgWidth = (S64)1 << 23,
    SgLength = (S64)1 << 24,
    SgLerp  = (S64)1 << 25,
    SgLog   = (S64)1 << 26,
    SgLog10 = (S64)1 << 27,
    SgLog2  = (S64)1 << 28,
    SgMax   = (S64)1 << 29,

    //30
    SgMin   = (S64)1 << 30,
    SgMul   = (S64)1 << 31,
    SgNormalize = (S64)1 << 32,
    SgPow   = (S64)1 << 33,
    SgRcp   = (S64)1 << 34,
    SgReflect = (S64)1 << 35,
    SgRefract = (S64)1 << 36,
    SgRound = (S64)1 << 37,
    SgRsqrt = (S64)1 << 38,
    SgSaturate = (S64)1 << 39,

    //40
    SgSign = (S64)1 << 40,
    SgSin  = (S64)1 << 41,
    SgSinCos = (S64)1 << 42,
    SgSinh = (S64)1 << 43,
    SgSmoothstep = (S64)1 << 44,
    SgSqrt = (S64)1 << 45,
    SgStep = (S64)1 << 46,
    SgTan = (S64)1 << 47,
    SgTanh = (S64)1 << 48,
    SgTranspose = (S64)1 << 49,
};

class SgOpCode
{
public:

    SgOpCode() : mType( SgOpNULL ), mOutput( -1 ), mNumInputs( 0 ), mNumPayloads( 0 )
    {

    }

    SgOpCode( SgOpGroupTypes type, OpID out ) : mType( type ), mOutput( out ), mNumInputs( 0 ), mNumPayloads( 0 )
    {

    }

    inline void SetInput( OpID p1 )
    {
        assert( mNumInputs < OP_NUM_INPUTS );

        mInputs[mNumInputs++] = p1;
    }

    inline void SetPayload( S32 p1 )
    {
        assert( mNumPayloads < OP_NUM_PAYLOADS );

        mPayLoad[mNumPayloads++].i = p1;
    }

    inline void SetPayload( U32 p1 )
    {
        assert( mNumPayloads < OP_NUM_PAYLOADS );

        mPayLoad[mNumPayloads++].u = p1;
    }

    inline void SetPayload( S64 p1)
    {
        assert(mNumPayloads < OP_NUM_PAYLOADS);

        mPayLoad[mNumPayloads++].l = p1;
    }

    inline void SetPayload( F32 p1 )
    {
        assert( mNumPayloads < OP_NUM_PAYLOADS );

        mPayLoad[mNumPayloads++].f = p1;
    }

    inline OpID GetInput( U8 loc ) const
    {
        assert( loc < mNumInputs );

        return mInputs[loc];
    }

    inline OpID GetOutput() const
    {
        return mOutput;
    }

    inline U32 GetNumInputs() const
    {
        return mNumInputs;
    }

    inline F32 GetFloatData( U8 index ) const
    {
        assert( index < OP_NUM_PAYLOADS );

        return mPayLoad[index].f;
    }

    inline S32 GetIntData( U8 index ) const
    {
        assert( index < OP_NUM_PAYLOADS );

        return mPayLoad[index].i;
    }

    inline U32 GetUintData( U8 index ) const
    {
        assert( index < OP_NUM_PAYLOADS );

        return mPayLoad[index].u;
    }

private:

    SgOpGroupTypes mType;
    OpID mOutput;
    U32 mNumInputs;
    OpID mInputs[OP_NUM_INPUTS];
    U32 mNumPayloads;

    union DataStorage
    {
        S32 i;
        U32 u;
        F32 f;
        S64 l;
    } mPayLoad[OP_NUM_PAYLOADS];
};

#endif