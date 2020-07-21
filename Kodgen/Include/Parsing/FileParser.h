#pragma once

#include <string>
#include <clang-c/Index.h>

#include "Misc/Filesystem.h"
#include "Misc/Optional.h"
#include "Misc/ILogger.h"
#include "InfoStructures/ParsingInfo.h"
#include "Parsing/NamespaceParser.h"
#include "Parsing/ClassParser.h"
#include "Parsing/EnumParser.h"
#include "Parsing/ParsingResults/FileParsingResult.h"
#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"

namespace kodgen
{
	class FileParser
	{
		private:
			static inline std::string const	_parsingMacro		= "KODGEN_PARSING";
			
			CXIndex						_clangIndex;
			
			NamespaceParser				_namespaceParser;
			ClassParser					_classParser;
			EnumParser					_enumParser;
			ParsingInfo					_parsingInfo;

			//Variables used to build command line
			std::string					_kodgenParsingMacro	= "-D" + _parsingMacro;
			std::vector<std::string>	_projectIncludeDirs;
			std::string					_classPropertyMacro;
			std::string					_structPropertyMacro;
			std::string					_fieldPropertyMacro;
			std::string					_methodPropertyMacro;
			std::string					_enumPropertyMacro;
			std::string					_enumValuePropertyMacro;

			static CXChildVisitResult	staticParseCursor(CXCursor c, CXCursor parent, CXClientData clientData)			noexcept;
			
			void						refreshBuildCommandStrings()													noexcept;
			std::vector<char const*>	makeParseArguments()															noexcept;

			CXChildVisitResult			parseCursor(CXCursor currentCursor)												noexcept;
			CXChildVisitResult			parseNamespace(CXCursor namespaceCursor)										noexcept;
			CXChildVisitResult			parseClass(CXCursor classCursor, bool isStruct)									noexcept;
			CXChildVisitResult			parseEnum(CXCursor enumCursor)													noexcept;

			/**
			*	Remove all previously parsed information from the class
			*/
			void	reset()																								noexcept;

		protected:
			/**
			*	Logger used to issue logs from the FileParser
			*/
			ILogger*	_logger	= nullptr;

			/**
			*	@brief Overridable method called just before starting the parsing process of a file
			*
			*	@param parseFile Path to the file which is about to be parsed
			*/
			virtual void preParse(fs::path const& parseFile)								noexcept;

			/**
			*	@brief Overridable method called just after the parsing process has been finished
			*	@brief Even if the parsing process ended prematurely, this method is called
			*
			*	@param parseFile Path to the file which has been parsed
			*	@param result Result of the parsing
			*/
			virtual void postParse(fs::path const& parseFile, FileParsingResult const& result)	noexcept;

		public:
			FileParser()					noexcept;
			FileParser(FileParser const&)	= default;
			FileParser(FileParser&&)		= default;
			virtual ~FileParser()			noexcept;

			/**
			*	Get the name of the macro which is set when parsing the source code
			*/
			static std::string const&	getParsingMacro()												noexcept;

			/**
			*	Get the parsing settings of the parser to setup it
			*/
			ParsingSettings&			getParsingSettings()											noexcept;

			/**
			*	Parse a file
			*
			*	@param parseFile Path to the file to parse
			*	@param out_result Result filled with the collected information
			*
			*	@return true if the parsing process finished without error, else false
			*/
			bool						parse(fs::path const& parseFile, FileParsingResult& out_result)		noexcept;

			/**
			*	@brief Setup this object's parameters with the provided toml file. Unset settings remain unchanged.
			*
			*	@param pathToSettingsFile Path to the toml file.
			*
			*	@return true if a file could be loaded, else false.
			*/
			bool						loadSettings(fs::path const& pathToSettingsFile)				noexcept;

			/**
			*	\brief Setup the logger used by this parser.
			*
			*	\param logger Instance of the logger to use.
			*/
			void						provideLogger(ILogger& logger)									noexcept;
	};
}

#include "Parsing/NamespaceParser.h"

namespace kodgen
{
	class FileParser2 : public NamespaceParser2
	{
		private:
			static inline std::string const	_parsingMacro		= "KODGEN_PARSING";

			CXIndex						_clangIndex;

			ParsingSettings				_parsingSettings;

			//Variables used to build command line
			std::string					_kodgenParsingMacro	= "-D" + _parsingMacro;
			std::vector<std::string>	_projectIncludeDirs;

			std::string					_namespacePropertyMacro;
			std::string					_classPropertyMacro;
			std::string					_structPropertyMacro;
			std::string					_fieldPropertyMacro;
			std::string					_methodPropertyMacro;
			std::string					_enumPropertyMacro;
			std::string					_enumValuePropertyMacro;

			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain a FileParser*.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			static CXChildVisitResult	parseEntity(CXCursor		cursor,
													CXCursor		parentCursor,
													CXClientData	clientData)							noexcept;

			/**
			*	@brief Refresh all internal compilation macros to pass to the compiler.
			*/
			void						refreshBuildCommandStrings()									noexcept;

			/**
			*	@brief Make a list of all arguments to pass to the compilation command.
			*
			*	@return A vector of all compilation commands.
			*/
			std::vector<char const*>	makeCompilationArguments()										noexcept;

			/**
			*	//TODO
			*/
			CXChildVisitResult			parseNamespace(CXCursor const& namespaceCursor)					noexcept;
			CXChildVisitResult			parseClass(CXCursor const& classCursor)							noexcept;
			CXChildVisitResult			parseEnum(CXCursor const& enumCursor)							noexcept;

			/**
			*	@brief Add the provided namespace result to the current file context result.
			*
			*	@param result NamespaceParsingResult to add.
			*/
			void							addNamespaceResult(NamespaceParsingResult&& result)			noexcept;

			/**
			*	@brief Add the provided struct/class result to the current file context result.
			*
			*	@param result ClassParsingResult to add.
			*/
			void							addClassResult(ClassParsingResult&& result)					noexcept;

			///**
			//*	@brief Add the provided enum result to the current file context result.
			//*
			//*	@param result EnumParsingResult to add.
			//*/
			//void							addEnumResult(EnumParsingResult&& result)				noexcept;

			/**
			*	@brief Log the diagnostic of the provided translation units.
			*
			*	@param translationUnit Translation unit we want to log the diagnostic of.
			*/
			void						logDiagnostic(CXTranslationUnit const& translationUnit)	const	noexcept;

			/**
			*	@brief Log the compilation command arguments.
			*/
			void						logCompilationArguments()										noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a FileParsingResult.
			*
			*	@return The cast FileParsingResult.
			*/
			inline FileParsingResult*	getParsingResult()												noexcept;

		protected:
			/** Logger used to issue logs from the FileParser. */
			ILogger*	logger	= nullptr;

			/**
			*	@brief Overridable method called just before starting the parsing process of a file
			*
			*	@param parseFile Path to the file which is about to be parsed
			*/
			virtual void preParse(fs::path const& parseFile)								noexcept;

			/**
			*	@brief Overridable method called just after the parsing process has been finished
			*	@brief Even if the parsing process ended prematurely, this method is called
			*
			*	@param parseFile Path to the file which has been parsed
			*	@param result Result of the parsing
			*/
			virtual void postParse(fs::path const& parseFile, FileParsingResult const& result)	noexcept;

		public:
			FileParser2()					noexcept;
			FileParser2(FileParser2 const&)	= default;
			FileParser2(FileParser2&&)		= default;
			virtual ~FileParser2()			noexcept;

			/**
			*	@brief Parse the file and fill the FileParsingResult.
			*
			*	@param toParseFile	Path to the file to parse.
			*	@param out_result	Result filled while parsing the file.
			*
			*	@return true if the parsing process finished without error, else false
			*/
			bool	parse(fs::path const&		toParseFile, 
						  FileParsingResult&	out_result)		noexcept;
	};

	#include "Parsing/FileParser.inl"
}