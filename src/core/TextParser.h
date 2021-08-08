#pragma once
#include "hook.h"

#define MAX_DELIM_SIZE 8

class TextParser {
	HOOKED_CONSTRUCTOR_CLASS(TextParser)

	char const *m_str;
	char m_delim[MAX_DELIM_SIZE];
	char const *m_copyStr;
	int m_size;
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

	static void InjectHooks();
};