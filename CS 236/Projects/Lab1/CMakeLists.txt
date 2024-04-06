cmake_minimum_required(VERSION 3.16)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp Token.h Automaton.h Lexer.h ColonAutomaton.h ColonDashAutomaton.h UndefinedCharacterAutomaton.h IDAutomaton.h CommaAutomaton.h PeriodAutomaton.h Q_MarkAutomaton.h Left_ParenAutomaton.h Right_ParenAutomaton.h MultiplyAutomaton.h AddAutomaton.h SchemesAutomaton.h FactsAutomaton.h RulesAutomaton.h QueriesAutomaton.h StringAutomaton.h UndefinedStringAutomaton.h SingleLineCommentAutomaton.h UndefinedBlockCommentAutomaton.h BlockCommentAutomaton.h EOFAutomaton.h)
