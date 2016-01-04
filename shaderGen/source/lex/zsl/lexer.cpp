#include "lexer.h"

#include "common/util.h"
#include "common/types.h"

#include "ast/abstractSyntaxTree.h"
#include "ast/abstractSyntaxLiteral.h"
#include "ast/abstractSyntaxReference.h"
#include "ast/abstractSyntaxUnary.h"
#include "ast/abstractSyntaxBinaryExpression.h"
#include "ast/abstractSyntaxComparison.h"
#include "ast/abstractSyntaxAssignment.h"

#include "lex/zsl/zslTokenizer.h"
#include "lex/zsl/zslCompoundSection.h"

#include <sstream>
#include <fstream>
#include <stack>


void ZslLexer::HandleBlock( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    for ( auto it = regexNodes.begin(), itend = regexNodes.end(); it != itend; ++it )
    {
        parent.AddChild( *it );
    }
}

void ZslLexer::HandleLiteral( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    ASTLiteral *literal = ( ASTLiteral * )parent.GetNodeLink();
    const Token *token = regexNodes[0].GetTokenLink();

    const std::string &valueString = token->GetString();

    if ( valueString.find( '.' ) != std::string::npos )
    {
        literal->SetData( token->GetValue<F32>() );
    }
    else if ( valueString.find( '-' ) != std::string::npos )
    {
        literal->SetData( token->GetValue<S32>() );
    }
    else
    {
        literal->SetData( token->GetValue<U32>() );
    }
}

void ZslLexer::HandleReference( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    ASTReference *reference = ( ASTReference * )parent.GetNodeLink();
    const Token *token = regexNodes[0].GetTokenLink();

    const std::string &valueString = token->GetString();

    reference->SetStringID( valueString );
}

void ZslLexer::ConvertUnary( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    // only performs a conversion step,
    // no target is assigned
    const Token *token = regexNodes[0].GetTokenLink();

    ASTUnary::ASTUnaryType type = ASTUnary::Unknown;

    switch ( token->GetType() )
    {
    case Token::TokenType::Increment:
        type = ASTUnary::Inc;
        break;

    case Token::TokenType::Decrement:
        type = ASTUnary::Decr;
        break;

    case Token::TokenType::Not:
        type = ASTUnary::Not;
        break;

    case Token::TokenType::Complement:
        type = ASTUnary::Complement;
        break;

    case Token::TokenType::Plus:
        type = ASTUnary::Plus;
        break;

    case Token::TokenType::Minus:
        type = ASTUnary::Minus;
        break;

    default:
        driver->ReportComment( ASTComment( ASTComment::Error, token->SourceLineOrigin(),
                                           Util::Format( "Unable to convert token type:%u to unary", ( U32 )token->GetType() ) ) );
        break;
    }

    ASTUnary *unary = ( ASTUnary * )parent.GetNodeLink();
    unary->SetUnaryType( type );
}

void ZslLexer::ConvertBinary( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    // only performs a conversion step,
    // no target is assigned
    const Token *token = regexNodes[0].GetTokenLink();

    ASTBinary::ASTBinaryType type = ASTBinary::Unknown;

    switch ( token->GetType() )
    {
    case Token::TokenType::And:
        type = ASTBinary::ASTBinaryType::ExprAnd;
        break;

    case Token::TokenType::Div:
        type = ASTBinary::ASTBinaryType::ExprDiv;
        break;

    case Token::TokenType::Mul:
        type = ASTBinary::ASTBinaryType::ExprMul;
        break;

    case Token::TokenType::Or:
        type = ASTBinary::ASTBinaryType::ExprOr;
        break;

    case Token::TokenType::Xor:
        type = ASTBinary::ASTBinaryType::ExprXor;
        break;

    default:
        driver->ReportComment( ASTComment( ASTComment::Error, token->SourceLineOrigin(),
                                           Util::Format( "Unable to convert token type:%u to binary", ( U32 )token->GetType() ) ) );
        break;
    }

    ASTBinary *binary = ( ASTBinary * )parent.GetNodeLink();
    binary->SetBinaryType( type );
}

void ZslLexer::ConvertComparison( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    // only performs a conversion step,
    // no target is assigned
    const Token *token = regexNodes[0].GetTokenLink();

    ASTComparison::ASTComparisonType type = ASTComparison::Unknown;

    switch ( token->GetType() )
    {
    case Token::TokenType::GreaterThan:
        type = ASTComparison::ASTComparisonType::CmpGT;
        break;

    case Token::TokenType::GreaterOrEqual:
        type = ASTComparison::ASTComparisonType::CmpGE;
        break;

    case Token::TokenType::Equal:
        type = ASTComparison::ASTComparisonType::CmpEQ;
        break;

    case Token::TokenType::NotEqual:
        type = ASTComparison::ASTComparisonType::CmpNEQ;
        break;

    case Token::TokenType::LessThan:
        type = ASTComparison::ASTComparisonType::CmpLT;
        break;

    case Token::TokenType::LessOrEqual:
        type = ASTComparison::ASTComparisonType::CmpLE;
        break;

    default:
        driver->ReportComment( ASTComment( ASTComment::Error, token->SourceLineOrigin(),
                                           Util::Format( "Unable to convert token type:%u to comparison", ( U32 )token->GetType() ) ) );
        break;
    }

    ASTComparison *binary = ( ASTComparison * )parent.GetNodeLink();
    binary->SetCompType( type );
}

void ZslLexer::ConvertAssignment( ASTDriver *driver, RegexNode &parent, const std::vector< RegexNode > &regexNodes )
{
    // only performs a conversion step,
    // no target is assigned
    const Token *token = regexNodes[0].GetTokenLink();

    ASTAssignment::ASTAssignmentType type = ASTAssignment::Unknown;

    switch ( token->GetType() )
    {
    case Token::TokenType::Assignment:
        type = ASTAssignment::ASTAssignmentType::Assignment;
        break;

    case Token::TokenType::AddAssignment:
        type = ASTAssignment::ASTAssignmentType::SumCompound;
        break;

    case Token::TokenType::SubAssignment:
        type = ASTAssignment::ASTAssignmentType::DifferenceCompound;
        break;

    case Token::TokenType::MulAssignment:
        type = ASTAssignment::ASTAssignmentType::ProductCompound;
        break;

    case Token::TokenType::DivAssignment:
        type = ASTAssignment::ASTAssignmentType::QuotientCompound;
        break;

    case Token::TokenType::ModAssignment:
        type = ASTAssignment::ASTAssignmentType::RemainderCompound;
        break;

    case Token::TokenType::LeftShiftAssignment:
        type = ASTAssignment::ASTAssignmentType::LeftShiftCompound;
        break;

    case Token::TokenType::RightShiftAssignment:
        type = ASTAssignment::ASTAssignmentType::RightShiftCompound;
        break;

    case Token::TokenType::BitwiseANDAssignment:
        type = ASTAssignment::ASTAssignmentType::BitwiseAndCompound;
        break;

    case Token::TokenType::BitwiseORAssingment:
        type = ASTAssignment::ASTAssignmentType::BitwiseOrCompound;
        break;

    case Token::TokenType::BitwiseXORAssingment:
        type = ASTAssignment::ASTAssignmentType::BitwiseXorCompound;
        break;

    default:
        driver->ReportComment( ASTComment( ASTComment::Error, token->SourceLineOrigin(),
                                           Util::Format( "Unable to convert token type:%u to assignment", ( U32 )token->GetType() ) ) );
        break;
    }

    ASTAssignment *assignment = ( ASTAssignment * )parent.GetNodeLink();
    assignment->SetAssignmentType( type );
}

ASTNode *ZslLexer::CreateBlock( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTHub >( sourceLine, sourceFile, "CodeBlock" );
}

ASTNode *ZslLexer::CreateLiteral( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTLiteral >( sourceLine, sourceFile );
}

ASTNode *ZslLexer::CreateReference( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTReference >( sourceLine, sourceFile );
}

ASTNode *ZslLexer::CreateUnary( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTUnary >( sourceLine, sourceFile );
}

ASTNode *ZslLexer::CreateBinary( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTBinary >( sourceLine, sourceFile );
}

ASTNode *ZslLexer::CreateComparison( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTComparison >( sourceLine, sourceFile );
}

ASTNode *ZslLexer::CreateAssignment( ASTDriver *driver, U32 sourceLine, const std::string &sourceFile )
{
    return driver->Create< ASTAssignment >( sourceLine, sourceFile );
}


void ZslLexer::InterpetGroup0( ASTDriver *driver, RegexStream &regexStream )
{


}

// Initial conversion
/*
void ZslLexer::InterpetGroup0( ASTDriver *driver, RegexStream &regexStream )
{
    RegexGroup regexGroup0( RegexGroup::None,
    {
        // numeric
        RegularExpression( "EXPR",
        {
            ExpressionBlock( {
                RegexStatement( {  Token::Numeric } )
            },
            &HandleLiteral )
        }, &CreateLiteral ),
        // Reference
        RegularExpression( "IDENTIFIER",
        {
            ExpressionBlock( {
                RegexStatement( {Token::Identifier } )
            },
            &HandleReference )
        }, &CreateReference ),

    } );

    regexStream.Digest( driver, regexGroup0 );
}


void ZslLexer::InterpetGroup1( ASTDriver *driver, RegexStream &regexStream )
{
    RegexGroup regexGroup1( RegexGroup::None,
    {
        // block
        RegularExpression( "BLOCK",
        {
            ExpressionBlock( {
                RegexStatement( { Token::LeftBracket } )

            },
            &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( {
                    "IDENTIFIER",
                    "EXPR",
                    "BLOCK"
                }, {
                    Token::LeftParenthesis,
                    Token::RightParenthesis,
                    Token::Numeric,
                    Token::Dot,
                    Token::Comma,
                    Token::Semicolon,
                    Token::Colon,
                    Token::LeftMeta,
                    Token::RightMeta,
                    Token::LeftSquareBracket,
                    Token::RightSquareBracket,
                    Token::Increment,
                    Token::Decrement,
                    Token::Complement,
                    Token::LeftShift,
                    Token::RightShift,
                    Token::And,
                    Token::Or,
                    Token::Xor,
                    Token::LogicalAnd,
                    Token::LogicalOr,
                    Token::Increment,
                    Token::Decrement,
                    Token::Not,
                    Token::Complement,
                    Token::Plus,
                    Token::Minus,
                    Token::Div,
                    Token::Mul,
                    Token::Modulo,
                    Token::LessThan,
                    Token::LessOrEqual,
                    Token::GreaterThan,
                    Token::GreaterOrEqual,
                    Token::Equal,
                    Token::NotEqual,
                    Token::Assignment,
                    Token::MulAssignment,
                    Token::DivAssignment,
                    Token::ModAssignment,
                    Token::AddAssignment,
                    Token::SubAssignment,
                    Token::LeftShiftAssignment,
                    Token::RightShiftAssignment,
                    Token::BitwiseANDAssignment,
                    Token::BitwiseORAssingment,
                    Token::BitwiseXORAssingment,
                    Token::Class,
                    Token::Alignas,
                    Token::Bool,
                    Token::Break,
                    Token::Case,
                    Token::Const,
                    Token::Continue,
                    Token::Default,
                    Token::Do,
                    Token::Double,
                    Token::Else,
                    Token::Enum,
                    Token::Explicit,
                    Token::False,
                    Token::Float,
                    Token::For,
                    Token::If,
                    Token::Inline,
                    Token::Int,
                    Token::Uint,
                    Token::Namespace,
                    Token::Private,
                    Token::Protected,
                    Token::Public,
                    Token::Register,
                    Token::Return,
                    Token::Static,
                    Token::Struct,
                    Token::Switch,
                    Token::Template,
                    Token::Thread_local,
                    Token::True,
                    Token::Typedef,
                    Token::Union,
                    Token::Void,
                    Token::While
                }, RegexAttributes::Optional )
            },
            &HandleBlock, RegexAttributes::Repeating ),
            ExpressionBlock( {
                RegexStatement( {  Token::RightBracket } )

            },
            &HandleDummy )
        }, &CreateBlock )
    } );

    regexStream.Digest( driver, regexGroup1 );
}

void ZslLexer::InterpetGroup2( ASTDriver *driver, RegexStream &regexStream )
{
    RegexGroup regexGroup2( RegexGroup::LeftToRight,
    {
        // block
        RegularExpression( "SCOPED_EXPR",
        {
            ExpressionBlock( {
                RegexStatement( { Token::LeftParenthesis } )

            },
            &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( {
                    "IDENTIFIER",
                    "EXPR"
                }, {
                    Token::Numeric,
                    Token::Dot,
                    //Token::Comma,
                    Token::LeftSquareBracket,
                    Token::RightSquareBracket,
                    Token::Increment,
                    Token::Decrement,
                    Token::Complement,
                    Token::LeftShift,
                    Token::RightShift,
                    Token::And,
                    Token::Or,
                    Token::Xor,
                    Token::LogicalAnd,
                    Token::LogicalOr,
                    Token::Increment,
                    Token::Decrement,
                    Token::Not,
                    Token::Plus,
                    Token::Minus,
                    Token::Div,
                    Token::Mul,
                    Token::Modulo,
                    Token::LessThan,
                    Token::LessOrEqual,
                    Token::GreaterThan,
                    Token::GreaterOrEqual,
                    Token::Equal,
                    Token::NotEqual
                }, RegexAttributes::Repeating )
            },
            &HandleBlock ),
            ExpressionBlock( {
                RegexStatement( { Token::RightParenthesis } )

            },
            &HandleDummy )
        }, &CreateBlock )
    } );

    regexStream.Digest( driver, regexGroup2 );

}

void ZslLexer::InterpetGroup3( ASTDriver *driver, RegexStream &regexStream )
{

    RegexGroup regexGroup3( RegexGroup::LeftToRight,
    {
        // block
        RegularExpression( "FUNCTION_CALL",
        {
            ExpressionBlock( {
                RegexStatement( { "IDENTIFIER" } )

            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( {Token::LeftParenthesis } )

            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( {
                    "IDENTIFIER",
                    "EXPR",
                }, {
                    Token::Numeric,
                    Token::Dot,
                    Token::LeftSquareBracket,
                    Token::RightSquareBracket,
                    Token::Increment,
                    Token::Decrement,
                    Token::Complement,
                    Token::LeftShift,
                    Token::RightShift,
                    Token::And,
                    Token::Or,
                    Token::Xor,
                    Token::LogicalAnd,
                    Token::LogicalOr,
                    Token::Increment,
                    Token::Decrement,
                    Token::Not,
                    Token::Plus,
                    Token::Minus,
                    Token::Div,
                    Token::Mul,
                    Token::Modulo,
                    Token::LessThan,
                    Token::LessOrEqual,
                    Token::GreaterThan,
                    Token::GreaterOrEqual,
                    Token::Equal,
                    Token::NotEqual
                }, RegexAttributes::Repeating ),
                RegexStatement( { Token::Comma }, RegexAttributes::Optional )
            }, &HandleDummy, RegexAttributes::Repeating ),
            ExpressionBlock( {
                RegexStatement( { Token::RightParenthesis } )
            }, &HandleDummy )
        }, &CreateBlock ),
        RegularExpression( "FUNCTION_CALL",
        {
            ExpressionBlock( {
                RegexStatement( { "IDENTIFIER" } )
            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( { "SCOPED_EXPR" } )
            }, &HandleDummy ),
        }, &CreateBlock ),
        RegularExpression( "FUNCTION_CALL",
        {
            ExpressionBlock( {
                RegexStatement( { "IDENTIFIER" } )
            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( { Token::LeftParenthesis } )
            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( { Token::RightParenthesis } )
            }, &HandleDummy ),
        }, &CreateBlock ),
        RegularExpression( "SCOPED_EXPR",
        {
            ExpressionBlock( {
                RegexStatement( {
                    "IDENTIFIER",
                    "EXPR",
                    "SCOPED_EXPR",
                    "FUNCTION_CALL"
                } )
            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( {
                    Token::LeftSquareBracket
                } )
            }, &HandleDummy ),
            ExpressionBlock( {

                RegexStatement( {
                    "IDENTIFIER",
                    "SCOPED_EXPR",
                    "FUNCTION_CALL",
                    "EXPR",
                }, {
                    Token::Numeric,
                    Token::Dot,
                    Token::Increment,
                    Token::Decrement,
                    Token::Complement,
                    Token::LeftShift,
                    Token::RightShift,
                    Token::And,
                    Token::Or,
                    Token::Xor,
                    Token::LogicalAnd,
                    Token::LogicalOr,
                    Token::Increment,
                    Token::Decrement,
                    Token::Not,
                    Token::Plus,
                    Token::Minus,
                    Token::Div,
                    Token::Mul,
                    Token::Modulo,
                    Token::LessThan,
                    Token::LessOrEqual,
                    Token::GreaterThan,
                    Token::GreaterOrEqual,
                    Token::Equal,
                    Token::NotEqual
                }, RegexAttributes::Repeating ),

            }, &HandleDummy ),
            ExpressionBlock( {
                RegexStatement( {
                    Token::RightSquareBracket
                } )
            }, &HandleDummy ),
        }, &CreateBlock ),

        RegularExpression( "UNARY_PLUSMINUS",
        {
            ExpressionBlock( {
                RegexStatement( {
                    Token::Plus,
                    Token::Minus
                } )
            }, &HandleDummy ),

            ExpressionBlock( {
                RegexStatement( {
                    "IDENTIFIER",
                    "EXPR",
                    "SCOPED_EXPR",
                    "FUNCTION_CALL"
                } )
            }, &HandleDummy ),
        }, &CreateBlock ),

    } );

    regexStream.Digest( driver, regexGroup3 );
}
*/

void ZslLexer::InterpetTokenStream( ASTDriver *driver, const Tokenizer &tokens )
{
    RegexStream regexStream( tokens );

    //InterpetGroup0( driver, regexStream );

    //InterpetGroup1( driver, regexStream );

    //InterpetGroup2( driver, regexStream );

    //InterpetGroup3( driver, regexStream );

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
    typeMap["for "] = Token::TokenType::For;
    typeMap["if "] = Token::TokenType::If;
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
    typeMap["switch "] = Token::TokenType::Switch;
    typeMap["template"] = Token::TokenType::Template;
    typeMap["thread_local"] = Token::TokenType::Thread_local;
    typeMap["true"] = Token::TokenType::True;
    typeMap["typedef"] = Token::TokenType::Typedef;
    typeMap["union"] = Token::TokenType::Union;
    typeMap["void"] = Token::TokenType::Void;
    typeMap["while "] = Token::TokenType::While;

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
