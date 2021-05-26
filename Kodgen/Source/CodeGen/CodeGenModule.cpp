#include "Kodgen/CodeGen/CodeGenModule.h"

#include <algorithm>

#include "Kodgen/CodeGen/PropertyCodeGen.h"
#include "Kodgen/CodeGen/CodeGenData.h"

using namespace kodgen;

void CodeGenModule::addPropertyRule(PropertyCodeGen const& propertyRule) noexcept
{
	_propertyCodeGenerators.push_back(&propertyRule);
}

bool CodeGenModule::removePropertyRule(PropertyCodeGen const& propertyRule) noexcept
{
	auto it = std::find(_propertyCodeGenerators.cbegin(), _propertyCodeGenerators.cend(), &propertyRule);

	if (it != _propertyCodeGenerators.cend())
	{
		_propertyCodeGenerators.erase(it);

		return true;
	}

	return false;
}

bool CodeGenModule::generateCode(EntityInfo const* entity, CodeGenData& data, std::string& inout_result) const noexcept
{
	if (entity != nullptr)
	{
		return runPropertyCodeGenerators(*entity, data, inout_result);
	}

	return true;
}

int32 CodeGenModule::getGenerationOrder() const noexcept
{
	return 0u;
}

bool CodeGenModule::runPropertyCodeGenerators(EntityInfo const& entity, CodeGenData& data, std::string& inout_result) const noexcept
{
	Property const* currentProperty;

	//Iterate over all entity's properties
	for (uint8 i = 0u; i < entity.propertyGroup.properties.size(); i++)
	{
		currentProperty = &entity.propertyGroup.properties[i];

		//Try to generate code with each registered property generator
		for (PropertyCodeGen const* propertyCodeGen : _propertyCodeGenerators)
		{
			if (propertyCodeGen->shouldGenerateCode(entity, *currentProperty, i))
			{
				if (!propertyCodeGen->generateCode(entity, *currentProperty, i, data, inout_result))
				{
					return false;
				}
			}
		}
	}

	return true;
}

std::vector<PropertyCodeGen const*> const& CodeGenModule::getPropertyRules() const noexcept
{
	return _propertyCodeGenerators;
}