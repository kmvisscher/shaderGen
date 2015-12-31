#include "zslRegex.h"

#include "lex/zsl/zslTokenizer.h"

ZslLexer::ZslRegexStream::ZslRegexStream( const Tokenizer &tokens )
{
    for ( auto it = tokens.Begin(), itend = tokens.End(); it != itend; ++it )
    {
        mRegexStream.push_back( RegexNode( it->GetType(), &( *it ) ) );
    }
}
