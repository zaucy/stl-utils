#include "_UtilsTestHelper.h"

UTILS_TEST() {
	
	UTIL_ASSERT_STRING_COMPARE(utils::trim_string("  HELLO WORLD   \n\n\n\n\n", '\n'), "  HELLO WORLD   ");
	UTIL_ASSERT_STRING_COMPARE(utils::trim_string("  HELLO WORLD\n\n\n\n\n     ", {' ', '\n'}), "HELLO WORLD");
	UTIL_ASSERT_STRING_COMPARE(utils::trim_string("  HELLO WORLD   \n\nd     ", {' ', '\n'}), "HELLO WORLD   \n\nd");
	
	
#ifdef __cpp_variable_templates

	UTIL_ASSERT_STRING_COMPARE(utils::trim_string("\t\t HELLO PEOPLE  \n\r\t  ", utils::whitespace_characters<char>), "HELLO PEOPLE");
	
#else
	
	UTIL_ASSERT_STRING_COMPARE(utils::trim_string("\t\t HELLO PEOPLE  \n\r\t  ", utils::whitespace_character_set<char>()), "HELLO PEOPLE");
	
#endif
	
	TEST_SUCCESS();
}
