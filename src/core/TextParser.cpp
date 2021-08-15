#include "TextParser.h"
#include <string.h>
#include <cctype>

void TextParser::InjectHooks() {
	using namespace memory::hook;

	inject_hook(0x61A470, &TextParser::Constructor<char const*, char const*>);
	inject_hook(0x61A310, &TextParser::MatchCurrentToken);
	inject_hook(0x61A350, &TextParser::MatchCurrentTokenCaseInsensitive);
	inject_hook(0x61A450, &TextParser::PushReadPosition);
	inject_hook(0x61A460, &TextParser::PopReadPosition);
	inject_hook(0x61A590, &TextParser::GetTokenAsInt);
	inject_hook(0x61A5C0, &TextParser::GetTokenAsFloat);
	//inject_hook(0x61A3B0, &TextParser::copyTokenToBuffer);
}

TextParser::TextParser(char const *str, char const *delim) {
	m_str = str;
	m_copyStr = str;
	m_size = 0;
	
	memset(&m_delim[0], 0, sizeof(m_delim[0]) * MAX_DELIM_SIZE);
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
	*((int*)&m_pData + m_size++) = m_pos;
}

void TextParser::PopReadPosition() {
	m_size--;
	m_pos = *((int*)&m_pData + m_size);
}

int TextParser::GetTokenAsInt() {
	char buffer[16];
	if (copyTokenToBuffer(m_str, buffer, sizeof(buffer), NULL, true)) {
		return atoi(buffer);
	}
	else {
		return 0;
	}
}

float TextParser::GetTokenAsFloat() {
	char buffer[16];
	if (copyTokenToBuffer(m_str, buffer, sizeof(buffer), NULL, true)) {
		return static_cast<float>(atof(buffer));
	}
	else {
		return 0.0f;
	}
}

//TODO: fix this one
char* TextParser::copyTokenToBuffer(char const *token, char *buf, unsigned long size, char sym, bool bFlag) {
	XCALL(0x61A3B0);

	/*char* copy = const_cast<char*>(token);
	if (!bFlag) {
		do {
			if (isSeparator(*copy)) {
				break;
			}
			copy++;
		} while (sym != *copy);
	}

	if (size <= 0)
		return nullptr;

	memcpy(buf, token, size);
	buf[size] = '\0';

	return buf;*/
}