#include "_UtilsTestHelper.h"

UTILS_TEST() {
	
	const char* string_to_split = "something=thething=other";
	
	std::pair<std::string, std::string> str = utils::split_string_once(string_to_split, "thing");
	std::pair<std::string, std::string> str2 = utils::split_string_once(string_to_split, '=');
	
	UTIL_ASSERT_STRING_COMPARE(str.first, "some");
	UTIL_ASSERT_STRING_COMPARE(str.second, "=thething=other");
		
	UTIL_ASSERT_STRING_COMPARE(str2.first, "something");
	UTIL_ASSERT_STRING_COMPARE(str2.second, "thething=other");
	
	TEST_SUCCESS();
}
