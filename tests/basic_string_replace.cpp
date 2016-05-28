#include "_UtilsTestHelper.h"

UTILS_TEST() {
	
	const char* string_to_replace = "SOmething other than; whatever is == aa";
	
	std::string replacedStr1 = utils::replace_string(string_to_replace, " ", "");
	std::string replacedStr2 = utils::replace_string(string_to_replace, " ", "oriented ponderer ; savage");
	std::string replacedStr3 = utils::replace_string(string_to_replace, "SO", "");
	std::string replacedStr4 = utils::replace_string(string_to_replace, "SO", "So");
	std::string replacedStr5 = utils::replace_string(replacedStr2, "ponderer ; savage", "<-- winner -->");
	
	UTIL_ASSERT_STRING_COMPARE(replacedStr1, "SOmethingotherthan;whateveris==aa");
	UTIL_ASSERT_STRING_COMPARE(replacedStr2, "SOmethingoriented ponderer ; savageotheroriented ponderer ; savagethan;oriented ponderer ; savagewhateveroriented ponderer ; savageisoriented ponderer ; savage==oriented ponderer ; savageaa");
	UTIL_ASSERT_STRING_COMPARE(replacedStr3, "mething other than; whatever is == aa");
	UTIL_ASSERT_STRING_COMPARE(replacedStr4, "Something other than; whatever is == aa");
	UTIL_ASSERT_STRING_COMPARE(replacedStr5, "SOmethingoriented <-- winner -->otheroriented <-- winner -->than;oriented <-- winner -->whateveroriented <-- winner -->isoriented <-- winner -->==oriented <-- winner -->aa");
	
	TEST_SUCCESS();
}
