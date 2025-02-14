#include "../../includes/shellinho.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
