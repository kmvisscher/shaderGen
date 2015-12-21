#pragma once
#ifndef __AST_HUB_H__
#define __AST_HUB_H__

class ASTHub : public ASTNode
{
public:

    static ASTNodeType ConstType() 
    {
        return ASTNodeType::OpConnector;
    }

    static std::string ConstName() 
    {
        return "ASTHub";
    }

    virtual const std::string &GetNodeName() const override
    {
        return ConstName();
    }

    ASTHub( ASTDriver *driver, const ASTNodeIndex &index, const U32 &line, const std::string &file ) :
            ASTNode( driver, index, line, file, ConstType(), ASTDataType::TypeUnknown )
    {
    }   
};


#endif