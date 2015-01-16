/*
 * DATFile.cpp
 *
 *  Created on: 07/gen/2015
 *      Author: stefano
 */

#include "DATFile.h"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>
#include <sstream>

XERCES_CPP_NAMESPACE_USE

class XMLDATHandler : public DefaultHandler {
public:
	XMLDATHandler();
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
	  std::ostringstream fCharacters;
};


DATFile::DATFile(const char* xmlFile)
{
	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Error during initialization! :\n"
				<< message << "\n";
		XMLString::release(&message);

		return;
	}

	std::cout << "Loading DAT File " << xmlFile << "... " ;
	std::flush(std::cout);

	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

	DefaultHandler* defaultHandler = new XMLDATHandler();
	parser->setContentHandler(defaultHandler);
	parser->setErrorHandler(defaultHandler);

	try {
			parser->parse(xmlFile);
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return;
	} catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n"
			 << message << "\n";
		XMLString::release(&message);
		return;
	} catch (...) {
		std::cout << "Unexpected Exception \n" ;
		return;
	}

	std::cout << "OK!" << std::endl;


	/*int status = XMLDoc.LoadFile(file);
	if (status == tinyxml2::XML_NO_ERROR) {
		std::cout << "OK!" << std::endl;
	} else {
		std::cout << "Failed!: " << XMLDoc.GetErrorStr1() << std::endl;
	}*/

	delete parser;
	delete defaultHandler;

	XMLPlatformUtils::Terminate();
}


DATFile::~DATFile()
{
}


int
DATFile::Parse()
{
	return -1;
}


// XMLDATHandler
XMLDATHandler::XMLDATHandler()
	:
	DefaultHandler()
{
}


void
XMLDATHandler::startElement(const XMLCh* const uri,
	    const XMLCh* const localname,
	    const XMLCh* const qname,
	    const Attributes&  attrs)
{
	fCharacters.str("");
	char* string = XMLString::transcode(localname);
	std::cout << string << ":" << std::endl;
	XMLString::release(&string);

	for (uint i = 0; i< attrs.getLength(); i++) {
		string = XMLString::transcode(attrs.getQName(i));
	    std::cout << "\t" << string << ": ";
	    XMLString::release(&string);
	    string = XMLString::transcode(attrs.getValue(i));
	    std::cout << string << std::endl;
	    XMLString::release(&string);
	}
}


void
XMLDATHandler::endElement(const XMLCh* const uri,
	    const XMLCh* const localname,
	    const XMLCh* const qname)
{
	char* string = XMLString::transcode(localname);
	//std::cout << "endElement(" << string << ")" << std::endl;
	XMLString::release(&string);
	std::cout << fCharacters.str() << std::endl;
}


void
XMLDATHandler::characters(
	    const XMLCh* const chars,
	    const unsigned int length)
{
	char* string = XMLString::transcode(chars);
	fCharacters << string;
	XMLString::release(&string);
}
