#pragma once
#ifndef __AST_NODE_H__
#define __AST_NODE_H__

#include "abstractSyntaxSourceCompound.h"

#include <iostream>

class ASTDriver;

class ASTNode : public ASTSourceCompound
{
public:

    typedef size_t ASTNodeIndex;

    enum ASTNodeType                    // Implemented ?
    {
        OpUnknown,                      // X
        OpConnector,                    // X
        OpDeclaration,                  // X
        OpLoop,                         // X
        OpLoopMod,                      // X
        OpReturn,                       // X
        OpComparisonOperator,           // X
        OpFunctionDeclaration,          // X
        OpFunctionCall,                 // X
        OpBinaryExpression,             // X
        OpUnaryExpression,              // X
        OpAssignmentExpression,         // X
        OpTernaryExpression,            // X
        OpTypeCaseExpression,           // X
        OpLiteralExpression             // X
    };

    enum ASTDataType
    {
        TypeUnknown,
        TypeVoid,
        TypeBool,
        TypeInt32,
        TypeUint32,
        TypeFloat,
        TypeHalf,
        TypeDouble,
        TypeComplex
    };


    virtual ~ASTNode() {}

    virtual const std::string GetNodeName() const = 0;
    virtual bool IsLvalue() const = 0;
    virtual bool IsRvalue() const = 0;

    ASTNodeType GetNodeType() const
    {
        return mNodeType;
    }

    ASTNodeIndex GetNodeIndex() const
    {
        return mIndex;
    }

    ASTDataType GetDataType() const
    {
        return mNodeDataType;
    }

    size_t NumChilderen() const
    {
        return mChilderen.size();
    }

    void AddChild( ASTNode *child )
    {
        mChilderen.emplace_back( child );
    }

    ASTNode *GetChild( size_t i ) const
    {
        return mChilderen[i];
    }

    void Print( const std::string &prefix ) const
    {
        const std::string name = this->GetNodeName();
        const size_t nodeIndex = ( size_t ) GetNodeIndex();
        const size_t nodeType = ( size_t ) GetNodeType();

        std::cout << prefix << "[ " << name << ", " << nodeIndex << ", " << mStringID << " ]" << std::endl;

        for ( size_t i = 0, iend = NumChilderen(); i < iend; ++i )
        {
            const ASTNode *child = GetChild( i );

            child->Print( prefix + "  " );
        }
    }

protected:

    ASTNode( ASTDriver *, const ASTNodeIndex &index,
             const U32 &line, const std::string &file,
             const ASTNodeType &type, const std::string &stringID,
             const ASTDataType &dataType )
        : ASTSourceCompound( line , file ), mNodeType( type ), mStringID( stringID ),
          mIndex( index ), mNodeDataType( dataType )
    {

    }

private:

    ASTNodeType mNodeType;
    ASTNodeIndex mIndex;
    ASTDataType mNodeDataType;
    std::string mStringID;

    std::vector< ASTNode * > mChilderen;
};



#endif