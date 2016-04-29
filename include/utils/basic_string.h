#pragma once

#include <vector>
#include <string>
#include <utility>
#include <initializer_list>
#include <type_traits>

namespace utils { inline namespace basic_string {
	
	/////////////////////////////////////
	//// utils::basic_string DETAIL
	namespace detail {
		
		template<typename charT, typename traitsT = std::char_traits<charT>, typename allocatorT = std::allocator<charT>>
		struct basic_string_utils {
			
			using string_type = std::basic_string<charT, traitsT, allocatorT>;
			using size_type = typename string_type::size_type;
			
			template<typename delimiterT>
			static std::vector<string_type> split_string(const string_type&, delimiterT);
			
			template<typename delimiterT>
			static std::pair<string_type, string_type> split_string_once(const string_type&, delimiterT);
			
			template<typename character_setT>
			static string_type trim_string(const string_type&, character_setT,
				typename std::enable_if<std::is_member_function_pointer<decltype(&character_setT::is_character)>::value>::type* = nullptr);
				
			template<typename character_setT>
			static string_type trim_string(const string_type&, character_setT,
				typename std::enable_if<std::is_integral<character_setT>::value>::type* = nullptr);
		};
		
		template<typename delimiterT>
		inline std::size_t _delimiter_size(const delimiterT& delimiter) {
			return delimiter.size();
		}
		
		template<typename delimiterT>
		inline std::size_t delimiter_size(delimiterT& delimiter) {
			using delimiter_type = typename std::remove_const<delimiterT>::type;
			return _delimiter_size<delimiter_type>(delimiter);
		}
					
		template<> inline std::size_t _delimiter_size<char>(const char&) {return sizeof(char);}
		template<> inline std::size_t _delimiter_size<wchar_t>(const wchar_t&) {return sizeof(wchar_t);}
		template<> inline std::size_t _delimiter_size<char16_t>(const char16_t&) {return sizeof(char16_t);}
		template<> inline std::size_t _delimiter_size<char32_t>(const char32_t&) {return sizeof(char32_t);}
		
		template<> inline std::size_t delimiter_size<const char*>(const char*& cstr) { return std::string{cstr}.size(); }
		template<> inline std::size_t delimiter_size<const wchar_t*>(const wchar_t*& cstr) { return std::wstring{cstr}.size(); }
		template<> inline std::size_t delimiter_size<const char16_t*>(const char16_t*& cstr) { return std::u16string{cstr}.size(); }
		template<> inline std::size_t delimiter_size<const char32_t*>(const char32_t*& cstr) { return std::u32string{cstr}.size(); }
		
	}
	
	/////////////////////////////////////
	//// utils::basic_string DECLARATIONS
	
	template<typename charT>
	class single_character_set {
		const charT& c_;
	public:
		single_character_set(const charT& c)
			: c_(c) { }
			
		inline bool is_character(charT in_c) const { return in_c == c_; }
	};
	
	template<typename charT>
	class basic_character_set {
		const std::initializer_list<charT> characters_;
	public:
		basic_character_set(std::initializer_list<charT> chars)
			: characters_(chars) { }
		
		inline bool is_character(charT in_c) const {
			for(charT c : characters_) {
				if(c == in_c) return true;
			}
			
			return false;
		}
	};
	
	template<typename charT>
	class whitespace_character_set;
	
	template<>
	class whitespace_character_set<char> {
	public:
		
		bool is_character(char c) const {
			// TODO: Make this complete.
			return false
				|| c == ' '
				|| c == '\n'
				|| c == '\r'
				|| c == '\t';
		}
		
	};
	
#ifdef __cpp_variable_templates
	
	template<typename charT>
	constexpr whitespace_character_set<charT> whitespace_characters;
	
#endif
	
	/** Splits the string by a delimiter and returns the string split in a vector. The delimiter type
	    can be a single character or an entire string. */
	template<typename stringT, typename delimiterT = typename stringT::value_type>
	inline std::vector<stringT> split_string(const stringT& str, delimiterT delimiter) {
		return detail::basic_string_utils<
			typename stringT::value_type,
			typename stringT::traits_type,
			typename stringT::allocator_type
		>::split_string(str, delimiter);
	}
	
	template<typename delimiterT = std::string::value_type>
	inline std::vector<std::string> split_string(const char* str, delimiterT delimiter) {
		return split_string<std::string, delimiterT>(std::string{str}, delimiter);
	}
	
	template<typename stringT, typename delimiterT = typename stringT::value_type>
	inline std::pair<stringT, stringT> split_string_once(const stringT& str, delimiterT delimiter) {
		return detail::basic_string_utils<
			typename stringT::value_type,
			typename stringT::traits_type,
			typename stringT::allocator_type
		>::split_string_once(str, delimiter);
	}
	
	template<typename delimiterT = std::string::value_type>
	inline std::pair<std::string, std::string> split_string_once(const char* str, delimiterT delimiter) {
		return split_string_once<std::string, delimiterT>(std::string(str), delimiter);
	}
	
	template<typename stringT, typename character_setT = basic_character_set<typename stringT::value_type>>
	inline stringT trim_string(const stringT& str, const character_setT& character_set) {
		return detail::basic_string_utils<
			typename stringT::value_type,
			typename stringT::traits_type,
			typename stringT::allocator_type
		>::trim_string(str, character_set);
	}
	
	template<typename character_setT = basic_character_set<typename std::string::value_type>>
	inline std::string trim_string(const char* str, const character_setT& character_set) {
		return trim_string<std::string, character_setT>(std::string(str), character_set);
	}
	
	////////////////////////////////////
	//// utils::basic_string DEFINITIONS
	
	template<typename charT, typename traitsT, typename allocatorT>
	template<typename delimiterT>
	std::vector<std::basic_string<charT, traitsT, allocatorT>> detail::basic_string_utils<charT, traitsT, allocatorT>
	::split_string(const string_type& str, delimiterT delimiter) {
		constexpr auto npos = string_type::npos;
		std::size_t delimiterSz = delimiter_size(delimiter);
		
		std::vector<std::basic_string<charT>> outSplit;
		
		size_type index = 0;
		size_type lastIndex = 0;
		while( (index=str.find(delimiter, lastIndex + delimiterSz) ) != npos ) {
			
			outSplit.push_back(str.substr(lastIndex, index - lastIndex));
			
			lastIndex = index + delimiterSz;
		}
		
		outSplit.push_back( str.substr(lastIndex) );
		
		return outSplit;
	}
	
	template<typename charT, typename traitsT, typename allocatorT>
	template<typename delimiterT>
	std::pair<std::basic_string<charT, traitsT, allocatorT>, std::basic_string<charT, traitsT, allocatorT>> detail::basic_string_utils<charT, traitsT, allocatorT>
	::split_string_once(const string_type& str, delimiterT delimiter) {
		constexpr auto npos = string_type::npos;
		std::size_t delimiterSz = delimiter_size(delimiter);
		
		std::pair<string_type, string_type> outPair;
		
		std::size_t index = str.find(delimiter);
		if(index != npos) {
			outPair.first = str.substr(0, index);
			outPair.second = str.substr(index + delimiterSz);
		} else {
			outPair.first = str;
		}
		
		return outPair;
	}
	
	template<typename charT, typename traitsT, typename allocatorT>
	template<typename character_setT>
	std::basic_string<charT, traitsT, allocatorT> detail::basic_string_utils<charT, traitsT, allocatorT>
	::trim_string(const string_type& str, character_setT characterSet,
		typename std::enable_if<std::is_member_function_pointer<decltype(&character_setT::is_character)>::value>::type*) {
		constexpr auto npos = string_type::npos;
		
		std::size_t startIndex = 0;
		std::size_t endIndex = npos;
		
		for(auto i=0; str.length() > i; i++) {
			auto c = str[i];
			
			if(!characterSet.is_character(c)) {
				startIndex = i;
				break;
			}
		}
		
		for(auto i=str.length()-1; i != 0; i--) {
			auto c = str[i];
			if(!characterSet.is_character(c)) {
				endIndex = i+1;
				break;
			}
		}
		
		return str.substr(startIndex, endIndex - startIndex);
	}
	
	template<typename charT, typename traitsT, typename allocatorT>
	template<typename character_setT>
	std::basic_string<charT, traitsT, allocatorT> detail::basic_string_utils<charT, traitsT, allocatorT>
	::trim_string(const string_type& str, character_setT characterSet,
		typename std::enable_if<std::is_integral<character_setT>::value>::type*) {
		return trim_string(str, single_character_set<character_setT>(characterSet));
	}
	
}}// namespace utils::basic_string
