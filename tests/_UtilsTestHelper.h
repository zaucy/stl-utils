#pragma once

#include <iostream>
#include <string>

#include <utils.h>

#ifndef UTILS_TEST_NAME
	#error UTILS_TEST_NAME NOT DEFINED
#endif

#define UTILS_TEST() bool UTILS_TEST_NAME() noexcept 
#define TEST_FAILED() return false
#define TEST_SUCCESS() return true

#define UTIL_ASSERT_STRING_COMPARE(str1, str2) if(str1 != str2) { std::cout << "ASSERT_STRING FAILED: " << str1 << " != " << str2 << std::endl; return false; } ((void)0)
