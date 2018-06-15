
//#include </usr/include/xercesc/util/PlatformUtils.hpp>
//#include </usr/include/xercesc/dom/DOM.hpp>
// Other include files, declarations, and non-Xerces-C++ initializations.

#include "TestCamera.h"

//using namespace xercesc;

int main(int argc, char* argv[]) {

	TestCamera cam;

	/*
	 try {
	 XMLPlatformUtils::Initialize();

	 //
	 //  Create a small document tree
	 //

	 {
	 XMLCh tempStr[100];

	 XMLString::transcode("Range", tempStr, 99);
	 DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(tempStr, 0);

	 XMLString::transcode("root", tempStr, 99);
	 DOMDocument*   doc = impl->createDocument(0, tempStr, 0);
	 DOMElement*   root = doc->getDocumentElement();

	 XMLString::transcode("FirstElement", tempStr, 99);
	 DOMElement*   e1 = doc->createElement(tempStr);
	 root->appendChild(e1);

	 XMLString::transcode("SecondElement", tempStr, 99);
	 DOMElement*   e2 = doc->createElement(tempStr);
	 root->appendChild(e2);

	 XMLString::transcode("aTextNode", tempStr, 99);
	 DOMText*       textNode = doc->createTextNode(tempStr);
	 e1->appendChild(textNode);

	 // optionally, call release() to release the resource associated with the range after done
	 DOMRange* range = doc->createRange();
	 range->release();

	 // removedElement is an orphaned node, optionally call release() to release associated resource
	 DOMElement* removedElement = root->removeChild(e2);
	 removedElement->release();

	 // no need to release this returned object which is owned by implementation
	 XMLString::transcode("*", tempStr, 99);
	 DOMNodeList*    nodeList = doc->getElementsByTagName(tempStr);

	 // done with the document, must call release() to release the entire document resources
	 doc->release();
	 };


	 }
	 catch (const XMLException& toCatch) {
	 // Do your failure processing here
	 return 1;
	 }

	 // Do your actual work with Xerces-C++ here.

	 XMLPlatformUtils::Terminate();
	 */

	// Other terminations and cleanup.

	// TestCamera will exit on its own
	//return 0;
}


