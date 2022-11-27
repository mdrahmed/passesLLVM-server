#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern void opensslcryptoSevpSevp_pbeDc_var_save();

static jmp_buf env;
static int ct = 0;
int abak;
int *a_ptr = &abak;
int aa = 123;

int __attribute__((always_inline)) foo(int a) { return a * 2; }

int bar(int a, int b) { return (a + foo(b) * 2); }

int fez(int a, int b, int c) { return (a + bar(a, b) * 2 + c * 3); }

// __attribute__((constructor(2))) void before_main1()
// {

//   // printf("before_main1\n");
// }

// __attribute__((constructor(1)))
void before_main2()
{
  // if (setjmp(env))
  // {
  //   printf("[*] Jump back\t Counter: %d\n", ct);
  // }
  // else
  // printf("Initializing \n");

  printf("before_main2\n");
}

__attribute__((destructor(1))) void after_main1()
{
  printf("after_main1\n");
  // __asm__(
  // "call _main"
  // );
}

__attribute__((destructor(2))) void after_main2() { printf("after_main2\n"); }

void function_exit()
{
  ct++;
  if (ct < 40)
  {
    __asm__(
        "jmp label");
    // longjmp(env, ct);
  }
  else
  {
    printf("exiting... \t Counter: %d\n", ct);
  }
}

void do_com(int input)
{
  int whatevera, whateverab;
  whatevera = 100;
  whateverab = input;
  if (whatevera > whateverab)
  {
    printf("tureeeee");
  }
  else
  {
    printf("FFFFF");
  }
  
  
}

void do_sth()
{
  static int astatic = 11;
  int ret = 0;

  a_ptr = &aa;

  ret += foo(astatic);
  ret += bar(astatic, ret);
  ret += fez(astatic, ret, 123);
  astatic++;
  printf("[*] fez ret: %d\t Counter: %d \n", ret, ct);
  abak = *a_ptr;

  char buf[100];
  memset(buf, 0, 100);
  read(0, buf, 100);

  if (buf[0] == 'y')
  {
    printf("one\n");
    if (buf[1] == 'u')
    {
      printf("two\n");
      if (buf[2] == 'z')
      {
        printf("three\n");
        if (buf[3] == 'z')
        {
          printf("four\n");
          __builtin_trap();
        }
      }
      else
      {
        printf("Bye\n");
      }
    }
  }
}

int main(int argc, char *argv[])
{
  asm("label:");
  before_main2();
  abak = 1111;
  atexit(function_exit);
  //while (__AFL_LOOP(1000))
  // {
    do_sth();
  // }
  return 0;
}

/*

$ clang Infinite_demo.c

# Clang
$  ./a.out
before_main2
[*] fez ret: 12915	 Counter: 0
before_main2
[*] fez ret: 12915	 Counter: 1
Segmentation fault

# GCC

# ./a.out
break
before_main1
before_main2
[*] fez ret: 12915       Counter: 0
[*] Jump back    Counter: 1
before_main1
break
before_main1
before_main2
[*] fez ret: 12915       Counter: 1
[*] Jump back    Counter: 2
before_main1
break
before_main1
before_main2
[*] fez ret: 12915       Counter: 2
[*] Jump back    Counter: 3
before_main1
break
before_main1
before_main2
[*] fez ret: 12915       Counter: 3
exiting... 4
after_main2
after_main1
*/
