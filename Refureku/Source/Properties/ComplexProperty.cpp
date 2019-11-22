#include "Properties/ComplexProperty.h"

using namespace refureku;

std::ostream& refureku::operator<<(std::ostream& out_stream, ComplexProperty const& complexProp) noexcept
{
	std::string totalName = "ComplexProperty: " + complexProp.name + "[";

	for (std::string const& subProp : complexProp.subProperties)
	{
		totalName += subProp + ", ";
	}

	if (!complexProp.subProperties.empty())
	{
		//Remove ", "
		totalName.pop_back();
		totalName.pop_back();
	}

	totalName += "]";

	out_stream << std::move(totalName);

	return out_stream;
}