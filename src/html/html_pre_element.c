/*
 * This file is part of libdom.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 Bo Yang <struggleyb.nku@gmail.com>
 * Copyright 2014 Rupinder Singh Khokhar<rsk1coder99@gmail.com>
 */
#include <assert.h>
#include <stdlib.h>

#include <dom/html/html_pre_element.h>

#include "html/html_document.h"
#include "html/html_pre_element.h"

#include "core/node.h"
#include "core/attr.h"
#include "utils/utils.h"

static struct dom_element_protected_vtable _protect_vtable = {
	{
		DOM_NODE_PROTECT_VTABLE_HTML_PRE_ELEMENT
	},
	DOM_HTML_PRE_ELEMENT_PROTECT_VTABLE
};

/**
 * Create a dom_html_pre_element object
 *
 * \param doc  The document object
 * \param ele  The returned element object
 * \return DOM_NO_ERR on success, appropriate dom_exception on failure.
 */
dom_exception _dom_html_pre_element_create(struct dom_html_document *doc,
		dom_string *namespace, dom_string *prefix,
		struct dom_html_pre_element **ele)
{
	struct dom_node_internal *node;

	*ele = malloc(sizeof(dom_html_pre_element));
	if (*ele == NULL)
		return DOM_NO_MEM_ERR;

	/* Set up vtables */
	node = (struct dom_node_internal *) *ele;
	node->base.vtable = &_dom_html_element_vtable;
	node->vtable = &_protect_vtable;

	return _dom_html_pre_element_initialise(doc, namespace, prefix, *ele);
}

/**
 * Initialise a dom_html_pre_element object
 *
 * \param doc  The document object
 * \param ele  The dom_html_pre_element object
 * \return DOM_NO_ERR on success, appropriate dom_exception on failure.
 */
dom_exception _dom_html_pre_element_initialise(struct dom_html_document *doc,
		dom_string *namespace, dom_string *prefix,
		struct dom_html_pre_element *ele)
{
	return _dom_html_element_initialise(doc, &ele->base,
					    doc->memoised[hds_PRE],
					    namespace, prefix);
}

/**
 * Finalise a dom_html_pre_element object
 *
 * \param ele  The dom_html_pre_element object
 */
void _dom_html_pre_element_finalise(struct dom_html_pre_element *ele)
{
	_dom_html_element_finalise(&ele->base);
}

/**
 * Destroy a dom_html_pre_element object
 *
 * \param ele  The dom_html_pre_element object
 */
void _dom_html_pre_element_destroy(struct dom_html_pre_element *ele)
{
	_dom_html_pre_element_finalise(ele);
	free(ele);
}

/**
 * Get the width Property
 *
 * \param pre	The dom_html_pre_element object
 */
dom_exception dom_html_pre_element_get_width(
		        dom_html_pre_element *pre, int32_t *width)
{
	return dom_html_element_get_int32_t_property(&pre->base, "width",
			SLEN("width"), width);
}

/**
 * Set the width Property
 *
 * \param pre	The dom_html_pre_element object
 */
dom_exception dom_html_pre_element_set_width(
		        dom_html_pre_element *pre, uint32_t width)
{
	return dom_html_element_set_int32_t_property(&pre->base, "width",
			SLEN("width"), width);
}

/*------------------------------------------------------------------------*/
/* The protected virtual functions */

/* The virtual function used to parse attribute value, see src/core/element.c
 * for detail */
dom_exception _dom_html_pre_element_parse_attribute(dom_element *ele,
		dom_string *name, dom_string *value,
		dom_string **parsed)
{
	UNUSED(ele);
	UNUSED(name);

	dom_string_ref(value);
	*parsed = value;

	return DOM_NO_ERR;
}

/* The virtual destroy function, see src/core/node.c for detail */
void _dom_virtual_html_pre_element_destroy(dom_node_internal *node)
{
	_dom_html_pre_element_destroy((struct dom_html_pre_element *) node);
}

/* The virtual copy function, see src/core/node.c for detail */
dom_exception _dom_html_pre_element_copy(dom_node_internal *old,
		                dom_node_internal **copy)
{
	        return _dom_html_element_copy(old, copy);
}

