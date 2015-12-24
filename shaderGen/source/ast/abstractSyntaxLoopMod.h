#pragma once
#ifndef __AST_LOOPMOD_H__
#define __AST_LOOPMOD_H__


#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTLoopMod : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpLoopMod;
    }

    static std::string ConstName()
    {
        return "ASTLoopMod";
    }

    virtual const std::string GetNodeName() const override
    {
        return ConstName();
    }

    virtual bool IsLvalue() const override
    {
        return false;
    }

    virtual bool IsRvalue() const override
    {
        return false;
    }

    enum ASTLoopModType
    {
        LoopBreak,
        LoopContinue
    };


    ASTLoopMod(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, ASTLoopModType modType) :
        ASTNode(driver, index, line, file, ConstType(), "LoopMod", ASTDataType::TypeUnknown), mModType( modType )
    {
    }

private:

    ASTLoopModType mModType;
};

#endif