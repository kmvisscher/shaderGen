#include "zslRegex.h"

#include "lex/zsl/zslTokenizer.h"

ZslLexer::RegexNode::RegexNode( const std::string &name, ASTNode *node ) :
    mName( name ), mNodeLink( node ), mTokenLink( nullptr )
{

}

ZslLexer::RegexNode::RegexNode( Token::TokenType type, const Token *token ) :
    mName( Util::Format( "type:%u", ( U32 )type ) ), mNodeLink( nullptr ), mTokenLink( token )
{

}

const std::string &ZslLexer::RegexNode::GetName() const
{
    return mName;
}

ASTNode *ZslLexer::RegexNode::GetNodeLink() const
{
    return mNodeLink;
}

const ZslLexer::Token *ZslLexer::RegexNode::GetTokenLink() const
{
    return mTokenLink;
}

ZslLexer::RegexNode::iterator ZslLexer::RegexNode::Begin() const
{
    return mChildren.begin();
}

ZslLexer::RegexNode::iterator ZslLexer::RegexNode::End() const
{
    return mChildren.end();
}

void ZslLexer::RegexNode::AddChild( const RegexNode &child )
{
    mChildren.push_back( child );
}

const ZslLexer::RegexNode &ZslLexer::RegexNode::GetChild( size_t i )
{
    return mChildren[i];
}

std::vector< ZslLexer::RegexNode > &ZslLexer::RegexNode::GetChilderen()
{
    return mChildren;
}

void ZslLexer::RegexNode::SetChilderen( const std::vector< RegexNode > &children )
{
    mChildren = children;
}

ZslLexer::RegexStatement::RegexStatement( const std::vector< std::string > &names,
                                          const std::vector<Token::TokenType > &types,
                                          U32 attribues /*= RegexAttributes::None */ ) :
    mNames( names ), mAttributes( attribues )
{
    for ( auto it = types.begin(), itend = types.end(); it != itend; ++it )
    {
        mNames.push_back( Token::FromType( *it ) );
    }
}

ZslLexer::RegexStatement::RegexStatement( const std::vector< std::string > &names,
                                          U32 attribues /*= RegexAttributes::None */ ) :
    mNames( names ), mAttributes( attribues )
{
}

ZslLexer::RegexStatement::RegexStatement( const std::vector<Token::TokenType > &types,
                                          U32 attribues /*= RegexAttributes::None */ ) :
    mAttributes( attribues )
{
    for ( auto it = types.begin(), itend = types.end(); it != itend; ++it )
    {
        mNames.push_back( Token::FromType( *it ) );
    }
}

ZslLexer::RegexStatement::iterator ZslLexer::RegexStatement::Begin() const
{
    return mNames.begin();
}

ZslLexer::RegexStatement::iterator ZslLexer::RegexStatement::End() const
{
    return mNames.end();
}

U32 ZslLexer::RegexStatement::GetAttributes() const
{
    return mAttributes;
}


ZslLexer::ExpressionBlock::ExpressionBlock( const std::vector< RegexStatement > &parts, codegenFunction func,
                                            U32 attribues /*= RegexAttributes::None */ ) :
    mRegexStatements( parts ), mFunc( func ), mAttributes( attribues )
{

}

ZslLexer::ExpressionBlock::iterator ZslLexer::ExpressionBlock::Begin() const
{
    return mRegexStatements.begin();
}

ZslLexer::ExpressionBlock::iterator ZslLexer::ExpressionBlock::End() const
{
    return mRegexStatements.end();
}

U32 ZslLexer::ExpressionBlock::GetAttributes() const
{
    return mAttributes;
}

void ZslLexer::ExpressionBlock::CodeGen( ASTDriver *driver, RegexNode &parent,
                                         const std::vector< RegexNode > &nodes ) const
{
    mFunc( driver, parent, nodes );
}

ZslLexer::RegularExpression::iterator ZslLexer::RegularExpression::Begin() const
{
    return mBlocks.begin();
}

ZslLexer::RegularExpression::iterator ZslLexer::RegularExpression::End() const
{
    return mBlocks.end();
}

std::string ZslLexer::RegularExpression::GetResult() const
{
    return mResult;
}

ASTNode *ZslLexer::RegularExpression::CodeGen( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile ) const
{
    return mFunc( driver, sourceLine, sourceFile );
}

ZslLexer::RegexGroup::iterator ZslLexer::RegexGroup::Begin() const
{
    return mExpressions.begin();
}

ZslLexer::RegexGroup::iterator ZslLexer::RegexGroup::End() const
{
    return mExpressions.end();
}

ZslLexer::RegexGroup::Associativity ZslLexer::RegexGroup::GetAssociativity() const
{
    return mAssoc;
}

ZslLexer::RegexStream::RegexStream( const Tokenizer &tokens )
{
    for ( auto it = tokens.Begin(), itend = tokens.End(); it != itend; ++it )
    {
        mRegexStream.push_back( RegexNode( it->GetType(), &( *it ) ) );
    }
}

ZslLexer::RegexStream::iterator ZslLexer::RegexStream::Begin() const
{
    return mRegexStream.begin();
}

ZslLexer::RegexStream::iterator ZslLexer::RegexStream::End() const
{
    return mRegexStream.end();
}

void ZslLexer::RegexStream::Digest( ASTDriver *driver, const RegexGroup &regexGroup )
{
    std::vector< RegexNode > result;

    // find the parse direction
    if ( regexGroup.GetAssociativity() == RegexGroup::None ||
            regexGroup.GetAssociativity() == RegexGroup::LeftToRight
       )
    {
        for ( iterator it = Begin(), itend = End(); it != itend; )
        {
            const iterator currentIt = it;

            DigestNode( it, itend, regexGroup, driver, result );

            if ( it == currentIt )
            {
                // the code couldnt advance the read stream so do that here
                ++it;
            }
        }
    }

    mRegexStream = result;
}

void ZslLexer::RegexStream::DigestNode( iterator &it, const iterator itend, const RegexGroup &regexGroup,
                                        ASTDriver *driver, std::vector< RegexNode > &result )
{
    RegexNode regexNode = ( *it );

    // Test this node for all regular expressions
    for ( RegexGroup::iterator rgit = regexGroup.Begin(), rgitend = regexGroup.End(); rgit != rgitend; ++rgit )
    {
        // test if this expression matches
        RegexPlayback playBack = TestExpression( driver, rgit, it, itend );

        if ( playBack.GetRegexPtr() != nullptr )
        {
            regexNode = ProcessExpression( driver, playBack, it, itend );

            break;
        }
    }

    // Also perform the digest for the children
    std::vector< RegexNode > childResult;

    for ( auto jt = regexNode.Begin(), jtend = regexNode.End(); jt != jtend; ++jt )
    {
        DigestNode( jt, jtend, regexGroup, driver, childResult );
    }

    regexNode.SetChilderen( childResult );

    result.push_back( regexNode );
}

void ZslLexer::RegexStream::ProcessSubExpression( ASTDriver *driver, const ExpressionBlock &subExpr,
                                                  iterator &stream, const iterator streamEnd, RegexNode &parent )
{
    std::vector< RegexNode > nodeGather;

    // match the individual tokens
    for ( auto it = subExpr.Begin(), itend = subExpr.End(); it != itend; ++it )
    {
        const RegexStatement &refToken = ( *it );

        // then test for a match
        // its possible to give a list of tokens that may match!
        do
        {
            if ( stream == streamEnd )
            {
                break;
            }

            const RegexNode &streamToken = ( *stream );

            bool foundTokenMatch = false;

            for ( auto jt = refToken.Begin(), jtend = refToken.End(); jt != jtend; ++jt )
            {
                const std::string &option = ( *jt );

                if ( option == streamToken.GetName() )
                {
                    foundTokenMatch = true;

                    break;
                }
            }

            // if the ref was optional
            if ( foundTokenMatch )
            {
                stream++;

                nodeGather.push_back( streamToken );

                continue;
            }
            else if ( IS_SET( refToken.GetAttributes(), RegexAttributes::Optional ) )
            {
                // this statement is not present but we can still continue
                break;
            }
            else
            {
                break;
            }
        }
        while ( IS_SET( refToken.GetAttributes(), RegexAttributes::Repeating ) );
    }

    // call the processor
    subExpr.CodeGen( driver, parent, nodeGather );
}

ZslLexer::RegexNode ZslLexer::RegexStream::ProcessExpression( ASTDriver *driver, const RegexPlayback &playBack,
                                                              iterator &stream, const iterator streamEnd )
{
    const RegularExpression *regExpr = playBack.GetRegexPtr();

    U32 sourceLine = 0xFFFFFFFF;
    std::string sourceFile = "UNDEFINED_SRC";

    if ( stream->GetNodeLink() != nullptr )
    {
        sourceLine = stream->GetNodeLink()->GetSourceLine();
        sourceFile = stream->GetNodeLink()->GetSourceFile();
    }
    else if ( stream->GetNodeLink() != nullptr )
    {
        sourceLine = stream->GetTokenLink()->SourceLineOrigin();
        sourceFile = stream->GetTokenLink()->SourceFileOrigin();
    }

    ASTNode *currentNode = regExpr->CodeGen( driver, sourceLine, sourceFile );
    RegexNode parentRegexNode( regExpr->GetResult(), currentNode );

    // in order for this expression to match we need each subexpression to also match
    //for ( auto it = regExpr->Begin(), itend = regExpr.End(); it != itend; ++it )
    for ( auto it = playBack.Begin(), itend = playBack.End(); it != itend; ++it )
    {
        const ExpressionBlock *block = it->first;
        const size_t repeatCount = it->second;

        for ( size_t repeat = 0; repeat < repeatCount; ++repeat )
        {
            ProcessSubExpression( driver, *block, stream, streamEnd, parentRegexNode );
        }
    }

    return parentRegexNode;
}

bool ZslLexer::RegexStream::TestSubExpression( ASTDriver *driver, const RegularExpression::iterator &sexpr,
                                               iterator &stream, const iterator streamEnd, size_t &numMatches )
{
    const ExpressionBlock &subExpr = ( *sexpr );

    // match the individual tokens
    bool foundMatch = true;

    for ( auto it = subExpr.Begin(), itend = subExpr.End(); it != itend; ++it )
    {
        const RegexStatement &refToken = ( *it );

        if ( !foundMatch )
        {
            break;
        }

        // then go for a series of possible iterations
        size_t loopCount = 0;

        do
        {
            // first test if this still fits in the stream
            // only become angry if this is the first loop :)
            if ( stream == streamEnd )
            {
                if ( loopCount == 0 )
                {
                    foundMatch = false;
                }

                break;
            }

            const RegexNode &streamToken = ( *stream );

            bool foundTokenMatch = false;

            // its possible to give a list of tokens that may match!
            for ( auto jt = refToken.Begin(), jtend = refToken.End(); jt != jtend; ++jt )
            {
                const std::string &option = ( *jt );

                if ( option == streamToken.GetName() )
                {
                    foundTokenMatch = true;
                    numMatches++;

                    break;
                }
            }

            // if the ref was optional
            if ( foundTokenMatch )
            {
                stream++;
            }
            // if the ref was optional
            else if ( IS_SET( refToken.GetAttributes(), RegexAttributes::Optional ) )
            {
                // this subExpr is not present but we can still continue to the other sub expr
                break;
            }
            else
            {
                // only become angry if this is the first loop :)
                if ( loopCount == 0 )
                {
                    foundMatch = false;
                }

                break;
            }

            loopCount++;
        }
        while ( IS_SET( refToken.GetAttributes(), RegexAttributes::Repeating ) );
    }

    return foundMatch;
}

ZslLexer::RegexPlayback ZslLexer::RegexStream::TestExpression( ASTDriver *driver, const RegexGroup::iterator &expr,
                                                               const iterator &stream, const iterator streamEnd )
{
    iterator streamCopy = stream;

    const RegularExpression &regExpr = ( *expr );

    RegexPlayback playBack( &regExpr );

    // in order for this expression to match we need each subexpression to also match
    for ( auto it = regExpr.Begin(), itend = regExpr.End(); it != itend; ++it )
    {
        size_t numMatches = 0;

        if ( !TestSubExpression( driver, it, streamCopy, streamEnd, numMatches ) )
        {
            // was this whole subexpression optional?
            if ( !IS_SET( it->GetAttributes(), RegexAttributes::Optional ) )
            {
                //return an empty playback!
                playBack = RegexPlayback( nullptr );

                break;
            }
        }
        else
        {
            size_t numSubRepeats = 1;

            // If repeating case
            if ( IS_SET( it->GetAttributes(), RegexAttributes::Repeating ) )
            {
                bool contRepeat = true;

                while ( contRepeat )
                {
                    size_t numRepeatMatches = 0;

                    contRepeat = TestSubExpression( driver, it, streamCopy, streamEnd, numRepeatMatches );

                    // due to the optional option it can still be possible to have a valid match, while not gaining any
                    // ground. if thats the case abort here
                    if ( contRepeat && ( numRepeatMatches > 0 ) )
                    {
                        numSubRepeats++;
                    }
                    else
                    {
                        contRepeat = false;
                    }
                }
            }

            playBack.AddBlockPlayback( std::make_pair( &( *it ), numSubRepeats ) );
        }
    }

    return playBack;
}
