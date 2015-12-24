#pragma once
#ifndef __AST_SYNTAX_LOOP_H__
#define __AST_SYNTAX_LOOP_H__

#include "abstractSyntaxNode.h"
#include "abstractSyntaxTree.h"
#include "abstractSyntaxHub.h"

class ASTLoop : public ASTNode
{
public:

    static ASTNodeType ConstType()
    {
        return ASTNodeType::OpLoop;
    }

    static std::string ConstName()
    {
        return "ASTLoop";
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

    enum ASTLoopType
    {
        LoopFor,
        LoopWhile,
        LoopDo
    };


    ASTLoop(ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file, ASTLoopType loopType, ASTNode *conditional) :
        ASTNode(driver, index, line, file, ConstType(), "Loop", ASTDataType::TypeUnknown ), mLoopType( loopType )
    {
        // Add a child node for the init
        AddChild(driver->Create< ASTHub >(line, file, "InitializerList"));

        // Add a child for the statements
        AddChild(driver->Create< ASTHub >(line, file, "Statements"));

        // Add a child for the meta data
        AddChild(driver->Create< ASTHub >(line, file, "MetaData"));

        // Add conditional for loop continuation
        AddChild(conditional);
    }

    ASTHub * GetInitializerHub() const
    {
        return (ASTHub *)GetChild(0);
    }

    ASTHub * GetStatementHub() const
    {
        return (ASTHub *)GetChild(1);
    }

    ASTHub * GetMetaDataHub() const
    {
        return (ASTHub *)GetChild(2);
    }

private:

    ASTLoopType mLoopType;
};

#endif