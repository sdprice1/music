#ifndef _STRINGUTILS_HPP_
#define _STRINGUTILS_HPP_

/*!
 * Copyright (c) 2022 Steve Price.
 * All Rights Reserved
 *
 * \file      StringUtils.hpp
 * \brief     A collection of string helper functions used to manipulate the contents of std::string
 *
 * \date      1 Aug 2022
 * \author    steve price
 *
 * \details   A collection of string helper functions used to manipulate the contents of std::string
 *
 */

#include <string>
#include <sstream>
#include <vector>

class StringUtils {
public:

	/**
	 * Convert string to lowercase
	 * @param str
	 * @return copy of str with all chars converted to lowercase
	 */
	static std::string toLower(const std::string& str)
	{
		if (str.empty())
			return str ;

		char* strcopy( (char*)calloc(str.size()+1, 1) ) ;
		if (!strcopy)
			return "" ;

	    char *p(strcopy) ;

	    const char *cp(str.c_str()) ;
	    while (*cp)
	    {
	    	if (*cp>='A' && *cp<='Z')
	    	{
	    		*p++ = *cp++ | 0x20;
	    	}
	    	else
	    	{
	    		*p++ = *cp++ ;
	    	}
	    }
	    *p = '\0' ;
	    std::string ret( strcopy );
	    free(strcopy) ;

	    return ret ;
	}

	/**
	 * Convert string to uppercase
	 * @param str
	 * @return copy of str with all chars converted to uppercase
	 */
	static std::string toUpper(const std::string& str)
	{
		if (str.empty())
			return str ;

		char* strcopy( (char*)calloc(str.size()+1, 1) ) ;
		if (!strcopy)
			return "" ;

	    char *p(strcopy) ;

	    const char *cp(str.c_str()) ;
	    while (*cp)
	    {
	    	if (*cp>='a' && *cp<='z')
	    	{
	    		*p++ = *cp++ & ~0x20;
	    	}
	    	else
	    	{
	    		*p++ = *cp++ ;
	    	}
	    }
	    *p = '\0' ;
	    std::string ret( strcopy );
	    free(strcopy) ;

	    return ret ;
	}


	/**
	 * Split a string at the specified delimeter char. Returns a vector of the results
	 * @param str
	 * @param delimeter
	 * @return vector of strings
	 */
	static std::vector<std::string> splitStr(const std::string& str, char delimeter)
	{
		std::vector<std::string> results ;
		std::stringstream ss(str);
	    std::string item;
	    while (std::getline(ss, item, delimeter))
	    {
	    	results.push_back(item) ;
		}
	    return results ;
	}

	/**
	 * Given a string (and an optional start position) scans past any preceding whitespace then
	 * converts the next characters into an unsigned integer and returns the value. Sets 'ok' to true if conversion
	 * is successful; false otherwise
	 */
	static unsigned extractUnsigned(const std::string& string, bool& ok, std::size_t pos = 0)
	{
		std::string digits{"0123456789"} ;

		ok = false ;
		std::size_t start(string.find_first_of(digits, pos)) ;
		if (start == std::string::npos)
			return 0 ;

		std::size_t end(string.find_first_not_of(digits, start+1)) ;
		if (end == std::string::npos)
			end = string.size() ;

		std::string ustr(string.substr(start, end-start)) ;
		unsigned uval( static_cast<unsigned>(strtoul(ustr.c_str(), nullptr, 10)) ) ;
		ok = true ;
		return uval ;
	}

};


#endif /* _STRINGFUNC_HPP_ */
