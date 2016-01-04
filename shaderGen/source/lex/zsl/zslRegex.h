#pragma once
#ifndef __ZSL_REGEXPR_H__
#define __ZSL_REGEXPR_H__

#include <vector>
#include <string>
#include <list>
#include <functional>

#include "common/types.h"
#include "common/util.h"

#include "zslToken.h"

#include "ast/abstractSyntaxNode.h"

namespace ZslLexer
{
    class Tokenizer;
    class RegexGroup;
    class RegularExpression;

    enum RegexAttributes
    {
        None = 0,
        Optional = 1,
        Repeating = 2
    };

    class RegexNode
    {
    public:

        typedef std::vector < RegexNode >::const_iterator iterator;

        RegexNode( Token::TokenType type, const Token *token );
        RegexNode( const std::string &name, ASTNode *node );

        const std::string &GetName() const;
        ASTNode *GetNodeLink() const;
        const Token *GetTokenLink() const;

        iterator Begin() const;
        iterator End() const;

        void AddChild( const RegexNode &child );
        const RegexNode &GetChild( size_t i );

        std::vector< RegexNode > &GetChilderen();
        void SetChilderen( const std::vector< RegexNode > &children );

    private:

        std::string mName;
        ASTNode *mNodeLink;
        const Token *mTokenLink;

        std::vector< RegexNode > mChildren;
    };

    class RegexStatement
    {
    public:

        typedef std::vector < std::string >::const_iterator iterator;

        RegexStatement( const std::vector< std::string > &names, const std::vector<Token::TokenType > &types,
                        U32 attribues = RegexAttributes::None );

        RegexStatement( const std::vector< std::string > &names,
                        U32 attribues = RegexAttributes::None );

        RegexStatement( const std::vector<Token::TokenType > &types,
                        U32 attribues = RegexAttributes::None );

        iterator Begin() const;
        iterator End() const;

        U32 GetAttributes() const;

    private:

        std::vector< std::string > mNames;
        U32 mAttributes;
    };

    void HandleDummy( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
    {
        // Pass;
    }

    class ExpressionBlock
    {
    public:

        typedef std::vector < RegexStatement >::const_iterator iterator;
        typedef std::function < void( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > & ) >
        codegenFunction;

        ExpressionBlock( RegularExpression &parent,
                         codegenFunction func, U32 attribues = RegexAttributes::None );


        /*
        ExpressionBlock( const std::vector< RegexStatement > &parts,
                         codegenFunction func, U32 attribues = RegexAttributes::None );
                         */
        iterator Begin() const;
        iterator End() const;

        U32 GetAttributes() const;

        void CodeGen( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > & ) const;

    private:

        RegularExpression &mParent;
        std::vector< RegexStatement > mRegexStatements;
        codegenFunction mFunc;
        U32 mAttributes;
    };

    class RegularExpression
    {
    public:

        typedef std::list < ExpressionBlock >::const_iterator iterator;
        typedef std::function < ASTNode *( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile ) > codegenFunction;

        RegularExpression( RegexGroup &parent, const std::string &result, codegenFunction func ) :
            mParent( mParent ), mResult( result ), mFunc( func )
        {

        }

        iterator Begin() const;
        iterator End() const;

        std::string GetResult() const;

        ExpressionBlock SubExpr( ExpressionBlock::codegenFunction func = &HandleDummy )
        {
            mBlocks.push_back()
        }

        RegexGroup &EndExpr()
        {
            return mParent;
        }

        ASTNode *CodeGen( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile ) const;

    private:

        RegexGroup &mParent;
        std::string mResult;
        codegenFunction mFunc;
        std::list < ExpressionBlock > mBlocks;
    };

    class RegexGroup
    {
    public:

        typedef std::list < RegularExpression >::const_iterator iterator;

        enum Associativity
        {
            None,
            LeftToRight,
            RightToLeft
        };

        RegexGroup( Associativity assoc ) :
            mAssoc( assoc )
        {

        }

        iterator Begin() const;
        iterator End() const;

        Associativity GetAssociativity() const;

        RegularExpression &Expr( const std::string &str, RegularExpression::codegenFunction &func )
        {
            mExpressions.push_back( RegularExpression( *this, str, func ) );

            return mExpressions.back();
        }

    private:

        Associativity mAssoc;
        std::list < RegularExpression > mExpressions;
    };

    class RegexPlayback
    {
    public:

        typedef std::vector< std::pair< const ExpressionBlock *, size_t > >::const_iterator iterator;

        RegexPlayback( const RegularExpression *regExpr ):
            mRegex( regExpr )
        {}

        void AddBlockPlayback( const std::pair< const ExpressionBlock *, size_t > &block )
        {
            mSubRegexes.push_back( block );
        }

        const RegularExpression *GetRegexPtr() const
        {
            return mRegex;
        }

        iterator Begin() const
        {
            return mSubRegexes.begin();
        }

        iterator End() const
        {
            return mSubRegexes.end();
        }

    private:

        const RegularExpression *mRegex;
        std::vector< std::pair< const ExpressionBlock *, size_t > > mSubRegexes;
    };

    class RegexStream
    {
    public:

        typedef std::vector < RegexNode >::const_iterator iterator;

        RegexStream( const Tokenizer &tokens );

        iterator Begin() const;
        iterator End() const;

        void Digest( ASTDriver *driver, const RegexGroup &regexGroup );

        void DigestNode( iterator &it, const iterator itend, const RegexGroup &regexGroup, ASTDriver *driver,
                         std::vector< RegexNode > &result );

    private:

        void ProcessSubExpression( ASTDriver *driver, const ExpressionBlock &block, iterator &stream,
                                   const iterator streamEnd, RegexNode &parent );
        RegexNode ProcessExpression( ASTDriver *driver, const RegexPlayback &playBack, iterator &stream,
                                     const iterator streamEnd );

        bool TestSubExpression( ASTDriver *driver, const RegularExpression::iterator &expr, iterator &stream,
                                const iterator streamEnd, size_t &numMatches );
        RegexPlayback TestExpression( ASTDriver *driver, const RegexGroup::iterator &expr, const iterator &stream,
                                      const iterator streamEnd );

        std::vector< RegexNode > mRegexStream;
    };

}

#endif