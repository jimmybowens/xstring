#ifndef com_vincyapps_xstring_h
#define com_vincyapps_xstring_h
struct xstring
{
  char * value;
};
struct xstring_array
{
  struct xstring **value;
  unsigned int len;
};
typedef struct xstring string;
typedef struct xstring_array string_array;
typedef unsigned int string_t;
int isValidString(string *input);
string * makeString(char *input);
string * makeEmptyString(string_t size);
string_array * makeStringArray(string_t size);
string_array * addStringAtIndex(string_array *array, int index, string *data);
string_array * addStringNext(string_array *array, string *data);
string * copyString(string *input);
string * concatString(string *s1, string *s2);
string * cutString(string *strInput, int from, int to);
string * resizeString(string *input, int size);
string * replaceChars(string *strInput, string *strDelim, char replValue);
string * delinString(string *input,char delim);
string * delinString2 (string *input, string *delimeters);
string * stripString(string *input, char delim, int count);
string * stripString2(string *input, string *delimeters, int count);
string * stripString3(string *input, string * delimeters, int count, int from, int to);
string * stripStringFront(string *input, string *delimeters);
string * stripStringBack(string *input, string *delimiters);
string_array * splitString(string *strInput, char delim);
string_array * splitString2(string *strInput, string *strDelim);
int findIndexOfChar(string *input, char c, int count);
int findIndexOfChar2(string *strInput, string *strDelim, int count);
int findIndexOfString(string *input, string *term, int count );
string_t getStringLength(string *input);
string_t getWordCount(string *input, char delim);
void printStringLn(string *input);
void printStringArray(string_array *array);
string * deleteString(string *input);
string_array * deleteStringArray(string_array *array);
#endif

