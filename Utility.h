#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// GLOBALS
const std::string ALPHA_NUMERIC = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Lower-cases a string.
inline void lower(std::string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

// Splits a string into a vector of string, using non-alpha-numerics as delimiters.
inline std::vector<std::string> split(const std::string &src)
{
	std::vector<std::string> results;
	size_t pos, prev = 0;
	while ((pos = src.find_first_not_of(ALPHA_NUMERIC, prev)) != std::string::npos)
	{
		if (pos > prev)
			results.push_back(src.substr(prev, pos - prev));
		prev = pos + 1;
	}
	if (prev < src.length())
		results.push_back(src.substr(prev));
	return results;
}

// Converts a string into a unique integer. Useful as a hashing function.
inline int hashString(const std::string &s)
{
	int size = s.length(), result = 0;
	for (int i = 0; i < size; ++i)
		result += (i + 1) * s[i];
	return result;
}

#endif // UTILITY_H