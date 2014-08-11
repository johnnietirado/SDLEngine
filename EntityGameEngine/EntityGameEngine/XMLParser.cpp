#include "XMLParser.h"

XMLParser* XMLParser::mInstance = NULL;

XMLParser* XMLParser::Instance()
{
	if (!mInstance)
		mInstance = new XMLParser;
	return mInstance;
}