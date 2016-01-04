#pragma once
#ifndef __ZSL_TOKEN_H__
#define __ZSL_TOKEN_H__

#include <vector>
#include <string>

#include "common/types.h"
#include "common/util.h"

namespace ZslLexer
{
    class Token
    {
    public:

        enum TokenType
        {
            // Operators
            Equal,
            NotEqual,
            LessThan,
            LessOrEqual,
            GreaterThan,
            GreaterOrEqual,
            LeftParenthesis,
            RightParenthesis,
            LeftBracket,
            RightBracket,
            Dot,
            Comma,
            Semicolon,
            Colon,
            Plus,
            Minus,
            Mul,
            Div,
            Modulo,
            Not,
            LeftMeta,
            RightMeta,
            LeftSquareBracket,
            RightSquareBracket,
            Increment,
            Decrement,
            Complement,
            LeftShift,
            RightShift,
            And,
            Or,
            Xor,
            LogicalAnd,
            LogicalOr,
            Assignment,
            MulAssignment,
            DivAssignment,
            ModAssignment,
            AddAssignment,
            SubAssignment,
            LeftShiftAssignment,
            RightShiftAssignment,
            BitwiseANDAssignment,
            BitwiseORAssingment,
            BitwiseXORAssingment,
            LineComment,
            LeftMultiLineComment,
            RightMultiLineComment,
            Identifier,
            Numeric,

            // Keywords
            Class,
            Alignas,
            Bool,
            Break,
            Case,
            Const,
            Continue,
            Default,
            Do,
            Double,
            Else,
            Enum,
            Explicit,
            Extern,
            False,
            Float,
            For,
            If,
            Inline,
            Int,
            Uint,
            Namespace,
            Private,
            Protected,
            Public,
            Register,
            Return,
            Static,
            Struct,
            Switch,
            Template,
            Thread_local,
            True,
            Typedef,
            Union,
            Void,
            While,
        };

        explicit Token( const std::string &token, const std::string &file, U32 sli );

        Token &operator=( Token const &rhs );

        template< class T >
        T  GetValue() const
        {
            return Util::FromString< T >( mToken );
        }

        size_t Size() const;
        U32 SourceLineOrigin() const;

        const std::string &GetString() const;
        const std::string &SourceFileOrigin() const;

        void SetType( const TokenType &type );
        TokenType GetType() const;

        bool Equals( const std::string &comp ) const;
        bool IsChar() const;

        static std::string FromType( TokenType type );

    private:

        TokenType mTokenType;
        std::string mToken;
        std::string mSourceFile;
        U32 mSourceLineIndex;
    };

}

#endif