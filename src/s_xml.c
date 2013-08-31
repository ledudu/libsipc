#include <assert.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>


xmlXPathObjectPtr get_node_set_by_xpath(xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr ctx;
	xmlXPathObjectPtr xpath_obj;

	ctx = xmlXPathNewContext(doc);
	if (NULL == ctx)
		return NULL;

	xpath_obj = xmlXPathEvalExpression(xpath, ctx);
	xmlXPathFreeContext(ctx);

	if (XPATH_NODESET != xpath_obj->type)
		return NULL;

	if (NULL == xpath_obj)
		return NULL;

	if (xmlXPathNodeSetIsEmpty(xpath_obj->nodesetval)) {
		xmlXPathFreeObject(xpath_obj);
		return NULL;
	}

	return xpath_obj;
}

xmlChar *get_node_content_by_xpath(xmlDocPtr doc, xmlChar *xpath)
{
	xmlChar *content;
	xmlXPathObjectPtr xpath_obj;

	xpath_obj = get_node_set_by_xpath(doc, xpath);
	if (NULL == xpath_obj)
		return NULL;

	assert(xpath_obj->type == XPATH_NODESET);
	assert(xpath_obj->nodesetval->nodeNr == 1);

	content = xmlNodeListGetString(doc, xpath_obj->nodesetval->nodeTab[0]->xmlChildrenNode, 1);
	xmlXPathFreeObject(xpath_obj);
	return content;
}

