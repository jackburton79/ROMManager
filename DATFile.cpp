/*
 * DATFile.cpp
 *
 *  Created on: 07/gen/2015
 *      Author: stefano
 */

#include "DATFile.h"
#include "database/Database.h"
#include "database/Schema.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>
#include <map>
#include <sstream>
#include <string>

XERCES_CPP_NAMESPACE_USE

class Element {
public:
	std::map<std::string, std::string> values;
};


class GameElement : public Element {
public:
	GameElement();
};


class RomElement : public Element {
public:
	RomElement();
};


class MAMEDATHandler : public DefaultHandler {
public:
	MAMEDATHandler(Database& database);
	void startElement(
	    const XMLCh* const uri,
	    const XMLCh* const localname,
	    const XMLCh* const qname,
	    const Attributes&  attrs
	  );

	  void endElement(
	    const XMLCh* const uri,
	    const XMLCh* const localname,
	    const XMLCh* const qname
	  );

	  void characters(
	    const XMLCh* const chars,
	    const unsigned int length
	  );

private:
	  Database& fDatabase;
	  std::ostringstream fCharacters;
	  GameElement* fGameElement;
	  RomElement* fRomElement;
};


DATFile::DATFile(const char* xmlFile)
	:
	fName(xmlFile)
{
}


DATFile::~DATFile()
{
}


int
DATFile::ParseInto(Database& database)
{
	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Error during initialization! :\n"
				<< message << "\n";
		XMLString::release(&message);

		return -1;
	}

	std::cout << "Parsing DAT File " << fName << "... " ;
	std::flush(std::cout);

	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

	DefaultHandler* defaultHandler = new MAMEDATHandler(database);
	parser->setContentHandler(defaultHandler);
	parser->setErrorHandler(defaultHandler);

	try {
		parser->parse(fName.c_str());
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return -1;
	} catch (...) {
		std::cout << "Unexpected Exception \n" ;
		return -1;
	}

	std::cout << "OK!" << std::endl;


	delete parser;
	delete defaultHandler;

	XMLPlatformUtils::Terminate();
	return 0;
}



// XMLDATHandler
MAMEDATHandler::MAMEDATHandler(Database& database)
	:
	DefaultHandler(),
	fDatabase(database),
	fGameElement(NULL),
	fRomElement(NULL)
{
}


void
MAMEDATHandler::startElement(const XMLCh* const uri,
	    const XMLCh* const localname,
	    const XMLCh* const qname,
	    const Attributes&  attrs)
{
	fCharacters.str("");
	char* string = XMLString::transcode(localname);
	if (!strcasecmp(string, "game")) {
		assert(fGameElement == NULL);
		fGameElement = new GameElement;
	} else if (!strcasecmp(string, "rom")) {
		assert(fRomElement == NULL);
		fRomElement = new RomElement;
	}
	std::cout << string << ":" << std::endl;
	for (uint i = 0; i < attrs.getLength(); i++) {
		char* attrName = XMLString::transcode(attrs.getQName(i));
	    char* attrValue = XMLString::transcode(attrs.getValue(i));
	    if (!strcasecmp(string, "rom") && fRomElement != NULL) {
	    	fRomElement->values[attrName] = attrValue;
	    } else if (!strcasecmp(string, "game") && fGameElement != NULL) {
	    	std::cout << "\t" << attrName << ": ";
	    	std::cout << attrValue << std::endl;
	    	fGameElement->values[attrName] = attrValue;
	    }
	    XMLString::release(&attrName);
	    XMLString::release(&attrValue);
	}
	XMLString::release(&string);
}


void
MAMEDATHandler::endElement(const XMLCh* const uri,
	    const XMLCh* const localname,
	    const XMLCh* const qname)
{
	char* string = XMLString::transcode(localname);
	//std::cout << "endElement(" << string << ")" << std::endl;
	//std::cout << fCharacters.str() << std::endl;

	if (!strcasecmp(string, "game")) {
		Schema::InsertGameRow(fDatabase, fGameElement->values);
		delete fGameElement;
		fGameElement = NULL;
	} else if (!strcasecmp(string, "rom")) {
		Schema::InsertRomRow(fDatabase, fRomElement->values);
		delete fRomElement;
		fRomElement = NULL;
	}
	XMLString::release(&string);
}


void
MAMEDATHandler::characters(
	    const XMLCh* const chars,
	    const unsigned int length)
{
	char* string = XMLString::transcode(chars);
	fCharacters << string;
	XMLString::release(&string);
}


// GameElement
GameElement::GameElement()
{

}


// RomElement
RomElement::RomElement()
{

}
