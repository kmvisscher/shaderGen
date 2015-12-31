#include "lexer.h"

#include "common/util.h"

#include "ast/abstractSyntaxTree.h"

#include "lex/zsl/zslTokenizer.h"
#include "lex/zsl/zslCompoundSection.h"
#include "lex/zsl/zslRegex.h"

#include <sstream>
#include <fstream>
#include <stack>

void ZslLexer::InterpetTokenStream( ASTDriver *driver, const Tokenizer &tokens )
{
    size_t sorigin = 0;

    ZslRegexStream regexStream( tokens );

    /*
    for ( auto it = tokens.Begin(), itend = tokens.End(); it != itend; ++it )
    {
        if ( HandleCompoundSection( driver, it ) )
        {
            continue;
        }
        //could not make sense out of this token, meaning that we have a problem
        else
        {

            if ( it->SourceLineOrigin() != sorigin )
            {
                std::cout << std::endl;

                sorigin = it->SourceLineOrigin();
            }

            std::cout << "[" << it->GetString() << "]   ";

        }
    }
    */

    // check for parsing errors
    if ( !driver->DriverIsValid() )
    {
        //invalidated driver
        const std::vector< ASTComment > &comments = driver->GetComments();

        for ( auto ct = comments.begin(), ctend = comments.end(); ct != ctend; ++ct )
        {
            std::cout << "Compiler; Level: " << ct->GetLevel() << "    SrcLine: " << ct->GetSourceLine() << "    Msg: \"" <<
                      ct->GetMsg() << "\"" << std::endl;
        }
    }
}

void ZslLexer::ProcessSourceFile( ASTDriver *driver, const std::string &file )
{
    Tokenizer tokenStream( file );

    std::ifstream infile( file );

    std::string line;
    U32 sourceLineIndex = 1;

    // Start by parsing the source file and dividing by ' ' and '\t'
    while ( std::getline( infile, line ) )
    {
        tokenStream.Tokenize( line, " \t", sourceLineIndex );

        sourceLineIndex++;
    }

    std::unordered_map< std::string, Token::TokenType > typeMap;
    typeMap["="] = Token::TokenType::Assignment;
    typeMap["=="] = Token::TokenType::Equal;
    typeMap["!="] = Token::TokenType::NotEqual;
    typeMap["<"] = Token::TokenType::LessThan;
    typeMap["<="] = Token::TokenType::LessOrEqual;
    typeMap[">"] = Token::TokenType::GreaterThan;
    typeMap[">="] = Token::TokenType::GreaterOrEqual;
    typeMap["("] = Token::TokenType::LeftParenthesis;
    typeMap[")"] = Token::TokenType::RightParenthesis;
    typeMap["{"] = Token::TokenType::LeftBracket;
    typeMap["}"] = Token::TokenType::RightBracket;
    typeMap["."] = Token::TokenType::Dot;
    typeMap[":"] = Token::TokenType::Colon;
    typeMap[","] = Token::TokenType::Comma;
    typeMap["+"] = Token::TokenType::Plus;
    typeMap["-"] = Token::TokenType::Minus;
    typeMap["*"] = Token::TokenType::Mul;
    typeMap["/"] = Token::TokenType::Div;
    typeMap["%"] = Token::TokenType::Modulo;
    typeMap["!"] = Token::TokenType::Not;
    typeMap["[["] = Token::TokenType::LeftMeta;
    typeMap["]]"] = Token::TokenType::RightMeta;
    typeMap["["] = Token::TokenType::LeftSquareBracket;
    typeMap["]"] = Token::TokenType::RightSquareBracket;
    typeMap["++"] = Token::TokenType::Increment;
    typeMap["--"] = Token::TokenType::Decrement;
    typeMap["~"] = Token::TokenType::Complement;
    typeMap["<<"] = Token::TokenType::LeftShift;
    typeMap[">>"] = Token::TokenType::RightShift;
    typeMap["&"] = Token::TokenType::And;
    typeMap["|"] = Token::TokenType::Or;
    typeMap["^"] = Token::TokenType::Xor;
    typeMap["%%"] = Token::TokenType::LogicalAnd;
    typeMap["||"] = Token::TokenType::LogicalOr;
    typeMap["*="] = Token::TokenType::MulAssignment;
    typeMap["/="] = Token::TokenType::DivAssignment;
    typeMap["%="] = Token::TokenType::ModAssignment;
    typeMap["+="] = Token::TokenType::AddAssignment;
    typeMap["-="] = Token::TokenType::SubAssignment;
    typeMap["<<="] = Token::TokenType::LeftShiftAssignment;
    typeMap[">>="] = Token::TokenType::RightShiftAssignment;
    typeMap["&="] = Token::TokenType::BitwiseANDAssignment;
    typeMap["|="] = Token::TokenType::BitwiseORAssingment;
    typeMap["^="] = Token::TokenType::BitwiseXORAssingment;
    typeMap["//"] = Token::TokenType::LineComment;
    typeMap["/*"] = Token::TokenType::LeftMultiLineComment;
    typeMap["*/"] = Token::TokenType::RightMultiLineComment;
    typeMap["return"] = Token::TokenType::Return;
    typeMap["class"] = Token::TokenType::Class;
    typeMap["alignas"] = Token::TokenType::Alignas;
    typeMap["bool"] = Token::TokenType::Bool;
    typeMap["break"] = Token::TokenType::Break;
    typeMap["case"] = Token::TokenType::Case;
    typeMap["const"] = Token::TokenType::Const;
    typeMap["continue"] = Token::TokenType::Continue;
    typeMap["default"] = Token::TokenType::Default;
    typeMap["do"] = Token::TokenType::Do;
    typeMap["double"] = Token::TokenType::Double;
    typeMap["else"] = Token::TokenType::Else;
    typeMap["enum"] = Token::TokenType::Enum;
    typeMap["explicit"] = Token::TokenType::Explicit;
    typeMap["extern"] = Token::TokenType::Extern;
    typeMap["false"] = Token::TokenType::False;
    typeMap["float"] = Token::TokenType::Float;
    typeMap["for"] = Token::TokenType::For;
    typeMap["if"] = Token::TokenType::If;
    typeMap["inline"] = Token::TokenType::Inline;
    typeMap["int"] = Token::TokenType::Int;
    typeMap["uint"] = Token::TokenType::Uint;
    typeMap["namespace"] = Token::TokenType::Namespace;
    typeMap["private"] = Token::TokenType::Private;
    typeMap["protected"] = Token::TokenType::Protected;
    typeMap["public"] = Token::TokenType::Public;
    typeMap["register"] = Token::TokenType::Register;
    typeMap["return"] = Token::TokenType::Return;
    typeMap["static"] = Token::TokenType::Static;
    typeMap["struct"] = Token::TokenType::Struct;
    typeMap["switch"] = Token::TokenType::Switch;
    typeMap["template"] = Token::TokenType::Template;
    typeMap["thread_local"] = Token::TokenType::Thread_local;
    typeMap["true"] = Token::TokenType::True;
    typeMap["typedef"] = Token::TokenType::Typedef;
    typeMap["union"] = Token::TokenType::Union;
    typeMap["virtual"] = Token::TokenType::Virtual;
    typeMap["void"] = Token::TokenType::Void;
    typeMap["while"] = Token::TokenType::While;

    // Then divide out all the special chars so that they are all in their own tokens
    tokenStream.SubdivideTokens( "!@#%$^&*()-+={}[]|\"\':;<>?/~`,", typeMap );

    // Process . in a seperate pass so that we can keep numerics intact
    tokenStream.SubdivideTokens( ".", typeMap );

    tokenStream.FilterComments( driver );

    InterpetTokenStream( driver, tokenStream );
}

ASTDriver *ZslLexer::ParseSource( const std::string &file )
{
    // read file line by line
    ASTDriver *driver = new ASTDriver;

    ProcessSourceFile( driver, file );

    return driver;
}


/*
// Group 1
typeMap["::"] = { Token::TokenType::ScopeResolution, 1, Token::TokenType::None };

// Group 2
typeMap["."] = { Token::TokenType::MemberSelection, 2, Token::TokenType::LeftToRight };
typeMap["["] = { Token::TokenType::ArraySubscriptStart, 2, Token::TokenType::LeftToRight };
typeMap["]"] = { Token::TokenType::ArraySubscriptEnd, 2, Token::TokenType::LeftToRight };
typeMap["("] = { Token::TokenType::FunctionCallStart, 2, Token::TokenType::LeftToRight };
typeMap[")"] = { Token::TokenType::FunctionCallEnd, 2, Token::TokenType::LeftToRight };
typeMap["EXP++"] = { Token::TokenType::PostIncrement, 2, Token::TokenType::LeftToRight };
typeMap["EXP--"] = { Token::TokenType::PostDecrement, 2, Token::TokenType::LeftToRight };

// Group 3
typeMap["++EXP"] = Token::TokenType( Token::TokenType::PreIncrement, 3, Token::TokenType::RightToLeft );
typeMap["--EXP"] = Token::TokenType( Token::TokenType::PreDecrement, 3, Token::TokenType::RightToLeft );
typeMap["~"] = Token::TokenType( Token::TokenType::Complement, 3, Token::TokenType::RightToLeft );
typeMap["!"] = Token::TokenType( Token::TokenType::LogicalNot, 3, Token::TokenType::RightToLeft );
typeMap["-EXP"] = Token::TokenType( Token::TokenType::UnaryNegation, 3, Token::TokenType::RightToLeft );
typeMap["+EXP"] = Token::TokenType( Token::TokenType::UnaryPlus, 3, Token::TokenType::RightToLeft );
typeMap["-EXP"] = Token::TokenType( Token::TokenType::UnaryNegation, 3, Token::TokenType::RightToLeft );
typeMap["+EXP"] = Token::TokenType( Token::TokenType::UnaryPlus, 3, Token::TokenType::RightToLeft );

typeMap["EXP*EXP"] = { Token::TokenType::Multiplication, 5, Token::TokenType::LeftToRight };
typeMap["EXP/EXP"] = { Token::TokenType::Division, 6, Token::TokenType::LeftToRight };
typeMap["EXP%EXP"] = { Token::TokenType::Modulus, 6, Token::TokenType::LeftToRight };
*/

/*

Group 5 precedence, left to right associativity
Multiplication
*
Division
/
Modulus
%
Group 6 precedence, left to right associativity
Addition
+
Subtraction
–
Group 7 precedence, left to right associativity
Left shift
<<
Right shift
>>
Group 8 precedence, left to right associativity
Less than
<
Greater than
>
Less than or equal to
<=
Greater than or equal to
>=
Group 9 precedence, left to right associativity
Equality
==
Inequality
!=
Group 10 precedence left to right associativity
Bitwise AND
&
Group 11 precedence, left to right associativity
Bitwise exclusive OR
^
Group 12 precedence, left to right associativity
Bitwise inclusive OR
|
Group 13 precedence, left to right associativity
Logical AND
&&
Group 14 precedence, left to right associativity
Logical OR
||
Group 15 precedence, right to left associativity
Conditional
? :
Group 16 precedence, right to left associativity
Assignment
=
Multiplication assignment
*=
Division assignment
/=
Modulus assignment
%=
Addition assignment
+=
Subtraction assignment
– =
Left - shift assignment
<<=
Right - shift assignment
>>=
Bitwise AND assignment
&=
Bitwise inclusive OR assignment
|=
Bitwise exclusive OR assignment
^=
Group 17 precedence, right to left associativity
throw expression
throw
Group 18 precedence, left to right associativity
Comma
,
*/