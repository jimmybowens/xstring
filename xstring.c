#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "xstring.h"
string *cutString(string *strInput, int from, int to)
{
  if( ! isValidString(strInput) )
  {
    return NULL;
  }

  string_t len = getStringLength(strInput);
  if( from < 0)
  {
    from = 0;
  }

  if( from > 0 )
  {
    from = ( from - 1);
  }

  if( ( to > len ) || ( to < 0) )
  {
    to = len;
  }

  int range = ( to - from);

  if( range < 0)
  {
    return copyString(strInput);
  }
  int idx = 0;
  string * result = makeEmptyString(range);
  char *ptr = &strInput->value[from];
  while( *ptr != '\0')
  {
    if( idx < range)
    {
      result->value[idx++] = *ptr++;
    }else
    {
      break;
    }
  }

  return result;
}

int isValidString(string *input)
{
  if( input == NULL || input->value == NULL || input->value == '\0')
  {
    return 0;
  }
  return 1;
}
void printStringLn(string *input)
{
  if( input != NULL )
  {
    if( input->value != NULL || input->value != '\0')
    {
      printf("%s\n", input->value);
    }
    else
    {
      printf("NULL\n");
    }
  }else
  {
    printf("NULL\n");
  }
}
void printStringArray(string_array *array)
{
  if( array != NULL )
  {
    if( array->value != NULL )
    {
      for( string_t i = 0; i < array->len; i++)
      {
	printStringLn(array->value[i]);
      }
    }else
    {
      printf("NULL\n");
    }
  }else
  {
    printf("NULL\n");
  }
}

string * makeString(char *input)
{
  if( input == NULL || input == '\0')
  {
    return NULL;
  }
  string * result = NULL;
  result = ( string *) malloc ( sizeof( string ));
  if( result == NULL)
  {
    fprintf(stderr, "An error has occured: %s\n", "out of memory");
    exit ( EXIT_FAILURE);
  }
  result->value = NULL;
  int len = 0;
  char *ptr = &input[0];
  while( *ptr++ != '\0')
  {
    len++;
  }
  result->value = (char *) malloc ( ( len + 1) * sizeof( char ));
  if( result->value == NULL)
  {
    fprintf(stderr, "An error has occured: %s\n", "out of memory");
    exit ( EXIT_FAILURE);
  }
  int idx = 0;
  ptr = &input[0];
  while( *ptr != '\0')
  {
    result->value[idx++] = *ptr++;
  }
  result->value[len] = '\0';
  return result;
}

string * makeEmptyString(string_t size)
{
  string *result = NULL;
  result = (string *) malloc(sizeof( string));
  int errnum = 0;
  if( result == NULL )
  {
    errnum = errno;
    fprintf(stderr, "An error has occured: %s\n", "out of memory");
    exit ( EXIT_FAILURE);
  }
  result->value = NULL;
  result->value = (char *) malloc ( ( size + 1) * sizeof( char ));
  if( result->value == NULL)
  {
    errnum = errno;
    fprintf(stderr, "An error has occured: %s\n", "out of memory");
    exit ( EXIT_FAILURE);
  }
  for( string_t i = 0; i < size; i++)
  {
    result->value[i] = '\x20';
  }
  result->value[size] = '\0';
  return result;
}

string * deleteString(string *input)
{
  if( input == NULL)
  {
    return NULL;
  }
  if( input->value != NULL)
  {
    free(input->value);
    input->value = NULL;
  }
  free(input);
  input = NULL;
  return NULL;
}

string *copyString(string *input)
{
  if( input == NULL || input->value == NULL || input->value == '\0')
  {
    return NULL;
  }
  string *result = makeEmptyString ( getStringLength ( input ));
  char *ptr = &input->value[0];
  int idx = 0;
  while( *ptr != '\0')
  {
    result->value[idx++] = *ptr++;
  }
  return result;
}
string *concatString(string *sone, string *stwo)
{
  if( !isValidString(sone) || !isValidString(stwo))
  {
    return NULL;
  }
  string_t sonel = getStringLength(sone);
  string_t stwol = getStringLength(stwo);
  string_t totall = ( sonel + stwol);
  string * result = makeEmptyString(totall);
  char *soneptr = &sone->value[0];
  char *stwoptr = &stwo->value[0];
  int idx = 0;
  while( *soneptr != '\0')
  {
    result->value[idx++] = *soneptr++;
  }
  soneptr = &sone->value[0];
  stwoptr = &stwo->value[0];
  while( *stwoptr != '\0')
  {
    result->value[idx++] = *stwoptr++;
  }
  return result;
}

string *resizeString(string *input, int size)
{
  if( !isValidString(input))
  {
    return NULL;
  }
  if( size < 0)
  {
    return copyString(input);
  }
  string_t len = getStringLength(input);
  string_t resizedlen = ( len + size );
  string * result = makeEmptyString(resizedlen);
  int idx = 0;
  char *ptr = &input->value[0];
  while( *ptr != '\0' || idx != resizedlen)
  {
    result->value[idx++] = *ptr++;
  }
  return result;
}

string *delinString2( string *input, string *delimiters)
{
  if( !isValidString(input))
  {
    return NULL;
  }
  if( !isValidString(delimiters))
  {
    return copyString(input);
  }

  string *result = copyString(input);
  string *result_bk = NULL;
  char *delim = &delimiters->value[0];
  while( *delim != '\0')
  {
    result_bk = result;//pointer to old result
    result = delinString(result,*delim++);//generate new result
    result_bk = deleteString(result_bk);//delete old result
  }
  return result;
}

string *delinString(string *input, char delim)
{
  if( !isValidString(input))
  {
    return NULL;
  }
  string *result = NULL;
  string_t inputLen = getStringLength(input);
  string_t start = 0;
  string_t end = inputLen;
  char *ptr = &input->value[0];
  int idx = 0;
  int insertIdx = 0;
  string_t resultLen = 0;
  while( *ptr != '\0')
  {
    if( *ptr++ == delim)
    {
      start++;
    }else
    {
      break;
    }
  }
  ptr = &input->value[inputLen];
  while(end >= start)
  {
    if( *ptr == delim || *ptr == '\0')
    {
      end--;
    }else
    {
      break;
    }
    ptr--;
  }
  ptr = &input->value[0];
  idx = 0;
  while( *ptr != '\0')
  {
    if( idx < start || idx > end)
    {
      ptr++;
      idx++;
      continue;
    }
    if( resultLen == 0)
    {
      ptr++;
      idx++;
      resultLen++;
      continue;
    }
    if( *ptr == delim && * ( ptr - 1) == delim )
    {
      ptr++;
      idx++;
      continue;
    }
    resultLen++;
    ptr++;
    idx++;
  }
  ptr = &input->value[0];
  idx = 0;
  insertIdx = 0;
  result = makeEmptyString(resultLen);
  while( *ptr != '\0')
  {
    if( idx < start || idx > end)
    {
      ptr++;
      idx++;
      continue;
    }
    if( insertIdx == 0)
    {
      result->value[insertIdx++] = *ptr;
      idx++;
      ptr++;
      continue;
    }
    if( *ptr == delim && * ( ptr - 1) == delim)
    {
      ptr++;
      idx++;
      continue;
    }
    result->value[insertIdx++] = *ptr;
    ptr++;
    idx++;
  }
  return result;
}

string * stripString2( string *input, string *delimeters, int count )
{
  if( !isValidString(input))
  {
    return NULL;
  }
  if( !isValidString(delimeters))
  {
    return copyString(input);
  }
  string *result = NULL;
  string *result_bk = NULL;
  char *delim = &delimeters->value[0];
  while( *delim != '\0')
  {
    result_bk = result;
    if( result_bk == NULL)
    {
      result = stripString(input,*delim++, count);
    }else
    {
      result = stripString(result_bk, *delim++,count);
    }
    result_bk = deleteString(result_bk);
  }
  return result;
}

string * stripString(string *input, char delim, int count)
{
  if( !isValidString(input))
  {
    return NULL;
  }
  string *result = NULL;
  int idx = 0;
  string_t delimCount = 0;
  char *ptr = &input->value[0];
  string_t resultLen = 0;
  while( *ptr != '\0')
  {
    if( delimCount == count)
    {
      break;
    }
    if( *ptr++ == delim)
    {
      delimCount++;
    }
  }
  resultLen = ( getStringLength(input) - delimCount);
  result = makeEmptyString(resultLen);
  ptr = &input->value[0];
  idx = 0;
  int skipped = 0;
  while( *ptr != '\0')
  {
    if( skipped < count)
    {
      if( *ptr == delim)
      {
	skipped++;
	ptr++;
	continue;
      }
    }
    if( *ptr == delim)
    {
      result->value[idx++] = *ptr;
      ptr++;
      skipped++;
      continue;
    }
    result->value[idx++] = *ptr;
    ptr++;
  }
  return result;
}

string_t getStringLength(string *input)
{
  if( input == NULL || input->value == NULL || input->value == '\0')
  {
    return 0;
  }
  string_t len = 0;
  char *ptr = &input->value[0];
  while( *ptr++ != '\0')
  {
    len++;
  }
  return len;
}

string_t getWordCount(string *input, char delim)
{
  if( !isValidString( input ))
  {
    return 0;
  }
  string *source = delinString( input, delim );
  string_t count = 0;
  char *ptr = &source->value[0];
  while( *ptr != '\0')
  {
    if( *ptr++ == delim)
    {
      count++;
    }
  }
  deleteString(source);
  return ( count == 0 ) ? 1 : ( count + 1);
}

int findIndexOfChar( string *input, char c, int count)
{
  if( !isValidString(input))
  {
    return -1;
  }
  if( count < 0)
  {
    count = getStringLength(input);
  }
  int idx = 0;
  char *ptr = &input->value[0];
  int findCount = 0;
  int found = 0;
  int lastFound = 0;
  while( *ptr != '\0')
  {
    if( *ptr++ == c)
    {
      found = 1;
      if( findCount == count)
      {
	return lastFound;
      }
      lastFound = idx;
      findCount++;
    }
    idx++;
  }
  return ( found > 0 ) ? lastFound : -1;
}
int findIndexOfChar2(string *strInput, string *strDelim, int count)
{
  if( ! isValidString(strInput) || ! isValidString(strDelim) )
  {
    return -1;
  }
  char *inputptr = &strInput->value[0];
  char *delimptr = &strDelim->value[0];
  int index = -1;
  int lastFound = -1;
  while( *inputptr != '\0')
  {
    while( *delimptr != '\0')
    {
      index = findIndexOfChar(strInput, *delimptr++, 1);
      printf("%d\n",index);
      if( index != -1)
      {
	lastFound = index;
      }
    }
    inputptr++;
  }
  return lastFound;
}

int findIndexOfString ( string *input, string *term, int count)
{
  if( ! isValidString ( input ) || ! isValidString ( term ) )
  {
    return -1;
  }
  string_t i = 0;
  string_t j = 0;
  int chunkLen = 0;
  string_t inputLen = getStringLength(input);
  string_t termLen = getStringLength(term);
  char *inputptr = &input->value[0];
  char *termptr = &term->value[0];
  int match = 0;
  int timesFound = 0;
  int lastIdx = 0;
  if( count < 1)
  {
    count = 1;
  }
  if( count > inputLen)
  {
    count = ( termLen == 0 ) ? inputLen : ( inputLen / termLen);
  }
  for( i = 0; i < inputLen; i++)
  {
    chunkLen = ( inputLen - i);
    if( chunkLen >= termLen)
    {
      match = 0;
      for( j = 0; j < termLen;j++)
      {
	if( *inputptr == *termptr)
	{
	  match++;
	}
      }
      termptr = &term->value[0];
      inputptr = &input->value[i + 1];
    }
    if( match == termLen)
    {
      timesFound++;
      if( timesFound == count )
      {
	return i;
      }else
      {
	lastIdx = ( i - termLen ) + 1 ;
      }
    }
  }
  return ( timesFound > 0 ) ? lastIdx : -1;
}

string * stripStringFront(string *strInput, string *strDelim)
{
  if( ! isValidString( strInput))
  {
    return NULL;
  }
  if( ! isValidString( strDelim))
  {
    return copyString( strInput );
  }
  char *inputptr = &strInput->value[0];
  char *delimptr = NULL;
  int idx = 0;
  int index = -1;
  int start = 0;
  int stop = 0;
  int range = 0;
  string_t len = getStringLength(strInput);
  while( *inputptr != '\0')
  {
    if( stop > 0)
    {
      break;
    }
    delimptr = &strDelim->value[0];
    while( *delimptr != '\0')
    {
      index = findIndexOfChar(strDelim, *inputptr, 1);
      if( index == -1)
      {
	stop = 1;
	start = idx;
	break;
      }
      delimptr++;
    }
    inputptr++;
    idx++;
  }
  range = (len - start);
  if( range < 0)
  {
    return copyString( strInput );
  }
  return cutString(strInput, (start + 1), len);
}

string * stripStringBack(string *strInput, string *strDelim)
{
  if( ! isValidString(strInput))
  {
    return NULL;
  }
  if( ! isValidString(strDelim))
  {
    return copyString(strInput);
  }
  string_t len = getStringLength(strInput);
  char *inputptr = &strInput->value[len];
  char *delimptr = NULL;
  int idx = len;
  int end = len;
  int stop = 0;
  int index = -1;
  while(idx >= 0 )
  {
    if( stop > 0 )
    {
      break;
    }
    if( *inputptr == '\0')
    {
      inputptr--;
      idx--;
      continue;
    }
    delimptr = &strDelim->value[0];
    while( *delimptr != '\0')
    {
      index = findIndexOfChar(strDelim, *inputptr, 1);
      if( index == -1)
      {
	stop = 1;
	end = idx;
	break;
      }
      delimptr++;
    }
    inputptr--;
    idx--;
  }
  return cutString(strInput, 0, (end + 1));
}

string_array * makeStringArray(string_t size)
{
  string_array * array = NULL;
  array = ( string_array *) malloc ( sizeof( string_array ));
  if( array == NULL )
  {
    fprintf(stderr, "An error has occured: %s\n", "out of memory");
    exit ( EXIT_FAILURE );
  }
  array->value = NULL;
  array->value = ( string **) malloc ( size * sizeof( string ));
  if( array->value == NULL )
  {
    fprintf(stderr, "An error has occured: %s\n", "out of memory");
    exit ( EXIT_FAILURE );
  }
  for( unsigned int i = 0; i < size; i++)
  {
    array->value[i] = NULL;
  }
  array->len = size;
  return array;
}

string_array * deleteStringArray(string_array *array)
{
  if( array == NULL)
  {
    return NULL;
  }
  if( array->value != NULL)
  {
    for( unsigned int i = 0; i < array->len; i++)
    {
      deleteString(array->value[i]);
    }
    free(array->value);
  }
  free(array);
  array = NULL;
  return NULL;
}

string_array * addStringNext(string_array *array, string *data)
{
  if( array == NULL )
  {
    return NULL;
  }

  if( array->value == NULL)
  {
    return array;
  }

  if( ! isValidString( data ) )
  {
    return array;
  }

  for( string_t i = 0; i < array->len; i++)
  {
    if( array->value[i] == NULL )
    {
      array->value[i] = copyString(data);
      break;
    }
  }
  return array;
}

string_array * addStringAtIndex(string_array *array, int index, string *data)
{
  if( array == NULL )
  {
    return NULL;
  }

  if( array->value == NULL)
  {
    return array;
  }

  if( ! isValidString( data ) )
  {
    return array;
  }

  for( string_t i = 0; i < array->len; i++)
  {
    if(i == index)
    {
      array->value[i] = deleteString(array->value[i]);
      array->value[i] = copyString(data);
      break;
    }
  }
  return array;
}

string_array * splitString(string *strInput, char delim)
{
  if( !isValidString( strInput ))
  {
    return NULL; //maybe return and empty array;
  }
  string * strDelim = makeString(&delim);
  string * strippedFront = stripStringFront(strInput, strDelim);
  string * strippedBack = stripStringBack(strippedFront, strDelim);
  string * strDelin = delinString(strippedBack,delim);
  string_t wordCount = getWordCount(strDelin, delim);
  string_array * array = NULL;
  if( wordCount == 1 )
  {
    array = makeStringArray(wordCount);
    addStringNext(array,copyString(strInput));
    return array;
  }
  array = makeStringArray(wordCount);
  int cutStart = 0;
  int cutEnd = 0;
  int idx = 0;
  int last = 0;
  char *ptr = &strDelin->value[0];

  while( *ptr != '\0')
  {
    if( *ptr == delim )
    {
      cutStart = last;
      cutEnd = idx;
      addStringNext(array,cutString(strDelin, cutStart, cutEnd));
      last = (idx + 2);
    }
    idx++;
    ptr++;
  }
  addStringNext(array, cutString(strDelin, findIndexOfChar(strDelin, delim, -1) + 2, -1) );
  deleteString(strDelin);
  deleteString(strDelim);
  deleteString(strippedFront);
  deleteString(strippedBack);
  return array;
}

string_array * splitString2(string *strInput, string *strDelim)
{
  if( !isValidString( strInput))
  {
    return NULL;
  }
  if( !isValidString( strDelim ))
  {
    return splitString ( strInput, ' ');
  }
  string *source = replaceChars(strInput,strDelim,' ');
  string_array * array = splitString ( source, ' ');
  source = deleteString(source);
  return array;
}

string * replaceChars(string *strInput, string *strDelim, char replValue)
{
  if( ! isValidString( strInput ))
  {
    return NULL;
  }
  if( ! isValidString( strDelim ))
  {
    return copyString(strInput);
  }
  string *source = copyString( strInput );
  char *inputptr = &source->value[0];
  char *delimptr = NULL;
  int idx = 0;
  while( *inputptr != '\0')
  {
    delimptr = &strDelim->value[0];
    while( *delimptr != '\0')
    {
      if( *delimptr == *inputptr)
      {
	source->value[idx] = replValue;
      }
      delimptr++;
    }
    idx++;
    inputptr++;
  }
  return source;
}
