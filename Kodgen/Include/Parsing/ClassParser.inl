
inline ClassParsingResult* ClassParser2::getParsingResult() noexcept
{
	return reinterpret_cast<ClassParsingResult*>(getContext().parsingResult);
}