#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/ParsingInfo.h"

namespace refureku
{
	class MethodParser
	{
		private:
			bool		_shouldCheckValidity	= false;
			bool		_isCurrentlyParsing		= false;

			CXCursor	_currentCursor;

			CXChildVisitResult				tryToAddMethod(CXCursor const& methodAnnotationCursor, ParsingInfo& parsingInfo)	noexcept;
			std::optional<PropertyGroup>	isMethodValid(CXCursor currentCursor, ParsingInfo& parsingInfo)						noexcept;
			void							setupMethod(CXCursor const& methodCursor, MethodInfo& methodInfo)					noexcept;

			void	endParsing()	noexcept;

		public:
			MethodParser()						= default;
			MethodParser(MethodParser const&)	= default;
			MethodParser(MethodParser&&)		= default;
			~MethodParser()						= default;

			CXChildVisitResult	parse(CXCursor cursor, ParsingInfo& parsingInfo)		noexcept;

			void				startParsing(CXCursor cursor)							noexcept;
			void				updateParsingState(CXCursor parent)						noexcept;

			bool				isCurrentlyParsing()							const	noexcept;
	};
}