/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace kodgen
{
	enum class ECodeGenLocation
	{
		/**
		*	Code will be generated at the very top of the generated file (without macro).
		*/
		HeaderFileHeader = 0,

		/**
		*	Code will be inserted in the ClassName_GENERATED macro (also works for structs).
		*/
		ClassFooter,

		/**
		*	Code will be inserted in the File_GENERATED macro (at the very end of a file).
		*/
		HeaderFileFooter,

		/**
		*	Code will be inserted at the top of the source file.
		*/
		SourceFileHeader,

		/**
		*	Internal use only.
		*/
		Count
	};
}