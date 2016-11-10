#include <cstring>
extern "C" int g_utf8_get_char(const char* p)
{
	return p[0];
}

extern "C" int
g_unichar_to_utf8(int c,
	char *outbuf)
{
	if (!outbuf) return 1;
	outbuf[0] = c;
	return 1;
}

extern "C"
bool
g_utf8_validate(const char *str,
	int max_len,
	const char **end)
{
	if (end)
		*end = str + strlen(str);
	return 1;
}

extern "C"
long
g_utf8_strlen(const char *p,
	long max)
{
	return strnlen_s(p, max);
}

extern "C"
char *
g_utf8_strncpy(char *dest,
	const char *src,
	int n)
{
	return strncpy(dest, src, n);
}

extern "C"
const char *
g_utf8_offset_to_pointer(const char *str,
	long offset)
{
	return str + offset;
}

extern "C"
int
g_unichar_validate(int c)
{
	return 1;
}
static const char utf8_skip_data[256] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2,
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5,
  5, 5, 5, 6, 6, 1, 1
};
extern "C" const char *const g_utf8_skip = utf8_skip_data;
