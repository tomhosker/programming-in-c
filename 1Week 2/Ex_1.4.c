#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int is_vowel(int a);

int is_alternating(int a, int b, int c);

int is_prime(int n);

int sum_is_prime(int a, int b, int c);

int main(void)
{
  int name[3] = {'a', 'a', 'a'};
  int count = 1;
  
  while(!(name[0] == 'z' && name[1] == 'z' && name[2] == 'z'))
  {
    if(is_alternating(name[0], name[1], name[2]) == TRUE && sum_is_prime(name[0], name[1], name[2]) == TRUE && name[0] == name[2])
    {
      printf("%d ", count);
      printf("%c%c%c\n", name[0], name[1], name[2]);
      count++;
    }
    
    if(name[2] != 'z')
    {
      name[2]++;
    }
    else
    {
      if(name[1] != 'z')
      {
        name[2] = 'a';
        name[1]++;
      }
      else
      {
        name[0]++;
        name[1] = 'a';
        name[2] = 'a';
      }
    }
  }
  
  return(0);
}

int is_vowel(int a)
{
  if(a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u')
  {
    return(TRUE);
  }
  else
  {
    return(FALSE);
  }
}

int is_alternating(int a, int b, int c)
{
  if(is_vowel(a) == TRUE)
  {
    if(is_vowel(b) == FALSE)
    {
      if(is_vowel(c) == TRUE)
      {
        return(TRUE);
      }
      else
      {
        return(FALSE);
      }
    }
    else
    {
      return(FALSE);
    }
  }
  else
  {
    if(is_vowel(b) == TRUE)
    {
      if(is_vowel(c) == FALSE)
      {
        return(TRUE);
      }
      else
      {
        return(FALSE);
      }
    }
    else
    {
      return(FALSE);
    }
  }
}

int is_prime(int n)
{
  if(n == 1)
  {
    return(FALSE);
  }
  else
  {
    if(n == 2)
    {
      return(TRUE);
    }
    else
    {
      for(int i = 2; i <= sqrt(n); i++)
      {
        if(n%i == 0)
        {
          return(FALSE);
        }
      }
      return(TRUE);
    }
  }
}

int sum_is_prime(int a, int b, int c)
{
  if(is_prime((a-'a'+1)+(b-'a'+1)+(c-'a'+1)) == TRUE)
  {
    return(TRUE);
  }
  else
  {
    return(FALSE);
  }
}