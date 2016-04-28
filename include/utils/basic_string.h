#pragma once

#include <vector>
#include <string>
#include <utility>
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
	
}}// namespace utils::basic_string
