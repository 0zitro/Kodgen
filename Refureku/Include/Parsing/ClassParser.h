#pragma once

#include <clang-c/Index.h>

#include "Misc/FundamentalTypes.h"
#include "Misc/EAccessSpecifier.h"
#include "InfoStructures/ParsingInfo.h"
#include "Parsing/FieldParser.h"
#include "Parsing/MethodParser.h"

namespace refureku
{
	class ClassParser
	{
		private:
			bool					_shouldCheckValidity	= false;
			uint8					_classLevel				= 0u;
			CXCursor				_currentCursor;

			FieldParser				_fieldParser;
			MethodParser			_methodParser;

			CXChildVisitResult				tryToAddClass(CXCursor classAnnotationCursor, ParsingInfo& parsingInfo)	noexcept;
			std::optional<PropertyGroup>	isClassValid(CXCursor currentCursor, ParsingInfo& parsingInfo)			noexcept;
			void							endStructOrClassParsing(ParsingInfo& parsingInfo)						noexcept;
			void							updateAccessSpecifier(CXCursor cursor, ParsingInfo& parsingInfo)		noexcept;

		public:
			ClassParser()					= default;
			ClassParser(ClassParser const&) = default;
			ClassParser(ClassParser&&)		= default;
			~ClassParser()					= default;

			CXChildVisitResult	parse(CXCursor currentCursor, ParsingInfo& parsingInfo)						noexcept;
			void				startClassParsing(CXCursor currentCursor, ParsingInfo& parsingInfo)			noexcept;
			void				startStructParsing(CXCursor currentCursor, ParsingInfo& parsingInfo)		noexcept;

			void				updateParsingState(CXCursor parent, ParsingInfo& parsingInfo)				noexcept;

			bool				isCurrentlyParsing()												const	noexcept;
	};
}