#include "_UtilsTestHelper.h"

UTILS_TEST() {
	
	const char* string_to_split = "Wonderful;ways;of;thinking;thisworldis;great";
	
	std::vector<std::string> str = utils::split_string(string_to_split, ';');
	std::vector<std::string> str2 = utils::split_string(string_to_split, "world");
	
	UTIL_ASSERT_STRING_COMPARE(str.at(0), "Wonderful");
	UTIL_ASSERT_STRING_COMPARE(str.at(1), "ways");
	UTIL_ASSERT_STRING_COMPARE(str.at(2), "of");
	UTIL_ASSERT_STRING_COMPARE(str.at(3), "thinking");
	UTIL_ASSERT_STRING_COMPARE(str.at(4), "thisworldis");
	UTIL_ASSERT_STRING_COMPARE(str.at(5), "great");
	
	UTIL_ASSERT_STRING_COMPARE(str2.at(0), "Wonderful;ways;of;thinking;this");
	UTIL_ASSERT_STRING_COMPARE(str2.at(1), "is;great");
}
