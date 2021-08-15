#pragma once
#include "hook.h"

#define MAX_DELIM_SIZE 8

class TextParser {
	HOOKED_CONSTRUCTOR_CLASS(TextParser)

	union {
		char const* m_str;
		int m_pos;
	};
	char m_delim[MAX_DELIM_SIZE];
	char const *m_copyStr;
	int m_size;
	int *m_pData;
public:
	TextParser(char const *str, char const *delim);
	bool isSeparator(char symbol);
	void advanceToToken();
	void advanceToToken(char const *token);
	void advanceToSeparator();
	void GetNextToken();
	bool MatchCurrentToken(char const *token);
	bool MatchCurrentTokenCaseInsensitive(char const *token);
	void PushReadPosition();
	void PopReadPosition();
	int GetTokenAsInt();
	float GetTokenAsFloat();
	char *copyTokenToBuffer(char const*, char*, unsigned long, char, bool);

	char const *getStr() { return m_str; }

	static void InjectHooks();
};