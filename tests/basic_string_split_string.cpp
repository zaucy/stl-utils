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
	
	std::vector<std::string> csetStr = utils::split_string(string_to_split, {'o', 'i'});
	
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(0), "W");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(1), "nderful;ways;");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(2), "f;th");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(3), "nk");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(4), "ng;th");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(5), "sw");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(6), "rld");
	UTIL_ASSERT_STRING_COMPARE(csetStr.at(7), "s;great");
	
	const char* string_to_split2 = "maaany charac  as of \n\n \t of tsome";
	
	std::vector<std::string> csetStr2 = utils::split_string(string_to_split2, utils::whitespace_character_set<char>());
	
	UTIL_ASSERT_STRING_COMPARE(csetStr2.at(0), "maaany");
	UTIL_ASSERT_STRING_COMPARE(csetStr2.at(1), "charac");
	UTIL_ASSERT_STRING_COMPARE(csetStr2.at(2), "as");
	UTIL_ASSERT_STRING_COMPARE(csetStr2.at(3), "of");
	UTIL_ASSERT_STRING_COMPARE(csetStr2.at(4), "of");
	UTIL_ASSERT_STRING_COMPARE(csetStr2.at(5), "tsome");
	
	TEST_SUCCESS();
}
