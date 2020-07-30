/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Properties/ComplexPropertyRule2.h"

class GetPropertyRule : public kodgen::ComplexPropertyRule
{
	public:
		GetPropertyRule()						= default;
		GetPropertyRule(GetPropertyRule const&)	= default;
		GetPropertyRule(GetPropertyRule&&)		= default;
		virtual ~GetPropertyRule()				= default;

		virtual bool	isMainPropSyntaxValid(std::string const&			mainProperty,
											  kodgen::EntityInfo::EType		entityType)				const noexcept override;

		virtual bool	isSubPropSyntaxValid(std::string const& subProperty,
											 kodgen::uint8		subPropIndex,
											 std::string&		out_errorDescription)				const noexcept override;

		virtual bool	isPropertyGroupValid(kodgen::PropertyGroup const&	propertyGroup,
											 kodgen::uint8					propertyIndex,
											 std::string&					out_errorDescription)	const noexcept override;

		virtual bool	isEntityValid(kodgen::EntityInfo const& entity,
									  kodgen::uint8				propertyIndex,
									  std::string&				out_errorDescription)				const noexcept override;
};