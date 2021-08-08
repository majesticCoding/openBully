#include "TextParser.h"
#include <string.h>
#include <cctype>

void TextParser::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x61A470, &TextParser::Constructor<char const*, char const*>);
	inject_hook(0x61A310, &TextParser::MatchCurrentToken);
	inject_hook(0x61A350, &TextParser::MatchCurrentTokenCaseInsensitive);
	//inject_hook(0x61A450, &TextParser::PushReadPosition);
	//inject_hook(0x61A460, &TextParser::PopReadPosition);
}

TextParser::TextParser(char const *str, char const *delim) {
	m_str = str;
	m_copyStr = str;
	m_size = 0;
	
	memset(&m_delim[0], 0, sizeof(m_delim[0])* MAX_DELIM_SIZE);
	strncpy_s(m_delim, delim, strlen(delim));
	advanceToToken();
}

bool TextParser::isSeparator(char symbol) {
	for (size_t i = 0; i < MAX_DELIM_SIZE; i++) {
		if (m_delim[i] == symbol)
			return true;
	}

	return false;
}

void TextParser::advanceToToken(void) {
	while (*m_str && isSeparator(*m_str))
		++m_str;
}

void TextParser::advanceToToken(char const *token) {
	while (*m_str && !TextParser::MatchCurrentToken(token))
		++m_str;
}

void TextParser::advanceToSeparator(void) {
	while (*m_str && !isSeparator(*m_str))
		++m_str;
}

void TextParser::GetNextToken(void) {
	if (!isSeparator(*m_str))
		advanceToSeparator();
	
	advanceToToken();
}

bool TextParser::MatchCurrentToken(char const *token) {
	const char *copy = m_str;
	while (*token) {
		if (*token != *copy) {
			return false;
		}

		++token; ++copy;
	}

	return isSeparator(*copy);
}

bool TextParser::MatchCurrentTokenCaseInsensitive(char const* token) {
	const char *copy = m_str;
	while (*token) {
		if (tolower(*token) != tolower(*copy))
			return false;

		token++; copy++;
	}

	return isSeparator(*copy);
}

void TextParser::PushReadPosition() {

}

void TextParser::PopReadPosition() {

}