#include "Parser.h"

using namespace refureku;

//
//CXChildVisitResult visitor( CXCursor cursor, CXCursor /* parent */, CXClientData clientData )
//{
//	CXSourceLocation location = clang_getCursorLocation( cursor );
//	if( clang_Location_isFromMainFile( location ) == 0 )
//		return CXChildVisit_Continue;
//
//	CXCursorKind cursorKind = clang_getCursorKind( cursor );
//
//	unsigned int curLevel  = *( reinterpret_cast<unsigned int*>( clientData ) );
//	unsigned int nextLevel = curLevel + 1;
//
//	std::cout << std::string( curLevel, '-' ) << " " << getString(clang_getCursorKindSpelling(cursorKind)) << " (" << getString(clang_getCursorSpelling(cursor)) << ")" << std::endl;
//
//	clang_visitChildren(cursor, visitor, &nextLevel); 
//
//	return CXChildVisit_Continue;
//}
//
//void clangTest()
//{
//	fs::path includeDirPath	= fs::current_path().parent_path().parent_path().parent_path() / "Include";
//	fs::path pathToFile		= includeDirPath / "TestClass.h";
//
//	std::cout << includeDirPath.string() << std::endl;
//
//	char* commandLine[] = { "-x", "c++", "-D", "PARSER" };
//
//	CXIndex				index	= clang_createIndex(0, 0);
//	CXTranslationUnit	unit	= clang_parseTranslationUnit(index, pathToFile.string().c_str(), commandLine, sizeof(commandLine) / sizeof(char*), nullptr, 0, CXTranslationUnit_None);
//
//	if (unit != nullptr)
//	{
//		CXCursor cursor = clang_getTranslationUnitCursor(unit);
//		clang_visitChildren(cursor, [](CXCursor c, CXCursor parent, CXClientData clientData)
//							{
//								std::string cursorName = getString(clang_getCursorSpelling(c));
//								std::string cursorKind = getString(clang_getCursorKindSpelling(clang_getCursorKind(c)));
//
//								std::cout << "Cursor kind : " << cursorKind << " : " << cursorName << std::endl;
//								return CXChildVisit_Recurse;
//
//							}, nullptr);
//	}
//	else
//	{
//		std::cerr << "Unable to parse translation unit" << std::endl;
//		//exit(-1);
//	}
//
//	/*CXIndex index        = clang_createIndex(0, 0);
//	CXTranslationUnit tu = clang_parseTranslationUnit(index, pathToFile.string().c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);
//
//	if( !tu )
//	exit(-2);
//
//	CXCursor rootCursor  = clang_getTranslationUnitCursor( tu );
//
//	unsigned int treeLevel = 0;
//
//	clang_visitChildren( rootCursor, visitor, &treeLevel );
//
//	*/
//
//	clang_disposeTranslationUnit(unit);
//	clang_disposeIndex(index);
//}

Parser::Parser() noexcept:
	_clangIndex{clang_createIndex(0, 0)}
{
}

Parser::~Parser() noexcept
{
	clang_disposeIndex(_clangIndex);
}

std::string getString(CXString& clangString)
{
	std::string result = clang_getCString(clangString);
	clang_disposeString(clangString);

	return std::move(result);
}

bool Parser::Parse(fs::path const& parseFile) const noexcept
{
	if (fs::exists(parseFile) && !fs::is_directory(parseFile))
	{
		

		return true;
	}

	return false;
}