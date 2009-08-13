/*
 * This file is part of libdom test suite.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 Bo Yang <struggleyb.nku@gmail.com>
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <dom/dom.h>

#include "domts.h"

extern dom_implementation *doc_impl;

void __assert2(const char *expr, const char *function,
		const char *file, int line)
{
	UNUSED(function);
	UNUSED(file);

	printf("FAIL - %s at line %d\n", expr, line);

	exit(EXIT_FAILURE);
}

/**
 * Following are the test conditions which defined in the DOMTS, please refer
 * the DOM Test Suite for details
 */

bool is_true(bool arg)
{
	return arg == true;
}

bool is_null(void *arg)
{
	return arg == NULL;
}

bool is_same(void *excepted, void *actual)
{
	return excepted == actual;
}

bool is_same_int(int excepted, int actual)
{
	return excepted == actual;
}

bool is_same_unsigned_long(unsigned long excepted, unsigned long actual)
{
	return excepted == actual;
}

bool is_equals_int(int excepted, int actual, bool dummy)
{
	UNUSED(dummy);
	
	return excepted == actual;
}

bool is_equals_unsigned_long(unsigned long excepted, unsigned long actual, bool dummy)
{
	UNUSED(dummy);

	return excepted == actual;
}

/**
 * Test whether two string are equal
 * 
 * \param excepted	The excepted string
 * \param actual	The actual string
 * \param ignoreCase	Whether to ignore letter case
 */
bool is_equals_string(const char *excepted, dom_string *actual, 
		bool ignoreCase)
{
	dom_string *exp;
	dom_exception err;
	bool ret;

	err = dom_string_create(myrealloc, NULL, excepted, strlen(excepted),
			&exp);
	if (err != DOM_NO_ERR)
		return false;

	if (ignoreCase == true)
		ret = dom_string_icmp(exp, actual) == 0;
	else
		ret = dom_string_cmp(exp, actual) == 0;
	
	dom_string_unref(exp);
	return ret;
}

/* Compare whether two dom_string are equal */
bool is_equals_domstring(dom_string *excepted, dom_string *actual, 
		bool ignoreCase)
{
	if (ignoreCase == true)
		return dom_string_icmp(excepted, actual) == 0;
	else
		return dom_string_cmp(excepted, actual) == 0;
}

/* The param actual should always contain dom_sting and expectd should
 * contain char * */
bool is_equals_list(list *expected, list *actual, bool ignoreCase)
{
	assert((expected->type && 0xff00) == (actual->type && 0xff00));

	comparator cmp = NULL;
	comparator rcmp = NULL;

	if (expected->type == INT)
		cmp = int_comparator;
	if (expected->type == STRING) {
		if (actual->type == DOM_STRING) {
			cmp = ignoreCase? str_icmp : str_cmp;
			rcmp = ignoreCase? str_icmp_r : str_cmp_r;
		}
	}
	if (expected->type == DOM_STRING) {
		if (actual->type == STRING) {
			cmp = ignoreCase? str_icmp_r : str_cmp_r;
			rcmp = ignoreCase? str_icmp : str_cmp;
		}
	}

	assert(cmp != NULL);

	bool ret = list_contains_all(expected, actual, cmp);
	if (ret)
		return list_contains_all(actual, expected, rcmp);
}



bool is_instanceof(const char *type, dom_node *node)
{
	assert("There is no instanceOf in the test-suite" == NULL);

	return false;
}


bool is_size_domnamednodemap(int size, dom_namednodemap *map)
{
	unsigned long len;
	dom_exception err;

	err = dom_namednodemap_get_length(map, &len);
	if (err != DOM_NO_ERR) {
		assert("Exception occured" == NULL);
		return false;
	}

	return size == len;
}

bool is_size_domnodelist(int size, dom_nodelist *list)
{
	unsigned long len;
	dom_exception err;

	err = dom_nodelist_get_length(list, &len);
	if (err != DOM_NO_ERR) {
		assert("Exception occured" == NULL);
		return false;
	}

	return size == len;
}

bool is_size_list(int size, list *list)
{
	return size == list->size;
}


bool is_uri_equals(char *scheme, char *path, char *host, 
		char *file, char *query, char *fragment, 
		bool isAbsolute, dom_string *actual)
{
	UNUSED(scheme);
	UNUSED(path);
	UNUSED(host);
	UNUSED(file);
	UNUSED(query);
	UNUSED(fragment);
	UNUSED(isAbsolute);
	UNUSED(actual);

	return false;
}


bool is_contenttype(const char *type)
{
	/* Now, we use the libxml2 parser for DOM parsing, so the content type
	 * is always "text/xml" */
	if (strcmp(type, "text/xml") == 0)
		return true;
	else
		return false;
}

bool has_feature(char *feature, char *version)
{
	dom_exception err;
	bool ret;
	dom_string *df, *dv;

	err = dom_string_create(myrealloc, NULL, feature, 
			feature == NULL ? 0 : strlen(feature), &df);
	if (err != DOM_NO_ERR)
		return false;
	
	err = dom_string_create(myrealloc, NULL, version, 
			version == NULL ? 0 : strlen(version), &dv);
	if (err != DOM_NO_ERR) {
		dom_string_unref(df);
		return false;
	}

	err = dom_implementation_has_feature(doc_impl, df, dv, &ret);
	/* Here, when we come with exception, we should return false,
	 * TODO: this need to be improved, but I can't figure out how */
	if (err != DOM_NO_ERR) {
		dom_string_unref(df);
		dom_string_unref(dv);
		return false;
	}

	dom_string_unref(df);
	dom_string_unref(dv);
	return ret;
}

bool implementation_attribute(char *name, bool value)
{
	/* We didnot support DOMConfigure for implementation now */
	UNUSED(name);
	UNUSED(value);

	return true;
}