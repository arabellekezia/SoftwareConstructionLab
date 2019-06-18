Name: Arabelle Siahaan
UID: xxxxxxxxx

Compare the performance of sfrob and sfrobu using time.

1. First, create a huge file to test on our programs. Reusing the
frobnicated examples from Assignment 4, I wrote a C program to
aid in writing the big file.

#include <stdio.h>
int main()
{
  int i;
  for (i = 0 ; i <= 100000; i++)
    {
      printf("*~BO *{_CIA *hXE]D *LER #@_GZY #E\\OX #^BO #FKPS #NEM\4\n");
    }
}

Then I compile the C program, run it and write the output in a file called
bigfile.txt using the commands:
$ gcc -o writebig write_bigfile.c
$ ./writebig > bigfile.txt

2. Then, I want to test sfrob first using different number of lines:
10, 100, 1000, 10000 and 100000

To do this I used these commands:

$ time ./sfrob < <(head -10 bigfile.txt)
Output:
real	0m0.005s
user	0m0.000s
sys	0m0.002s

$ time ./sfrob < <(head -100 bigfile.txt)
Output:
real	0m0.006s
user	0m0.001s
sys	0m0.002s

$ time ./sfrob < <(head -1000 bigfile.txt)
Output:
real	0m0.014s
user	0m0.008s
sys	0m0.004s

$ time ./sfrob < <(head -10000 bigfile.txt)
Output:
real	0m0.119s
user	0m0.091s
sys	0m0.020s

$ time ./sfrob < <(head -100000 bigfile.txt)
Output:
real	0m1.419s
user	0m1.016s
sys	0m0.202s

3. Next, do the same tests in 2 but with sfrobu this time.

$ time ./sfrobu < <(head -10 bigfile.txt)
Output:
real	0m0.006s
user	0m0.000s
sys	0m0.003s

$ time ./sfrobu < <(head -100 bigfile.txt)
Output:
real	0m0.014s
user	0m0.001s
sys	0m0.011s

$ time ./sfrobu < <(head -1000 bigfile.txt)
Output:
real	0m0.106s
user	0m0.020s
sys	0m0.084s

$ time ./sfrobu < <(head -10000 bigfile.txt)
Output:
real	0m1.039s
user	0m0.192s
sys	0m0.841s

$ time ./sfrobu < <(head -100000 bigfile.txt)
Output:
real	0m10.442s
user	0m2.112s
sys	0m8.289s

4. Analysis:
After looking at the output, we can see that sfrobu always take longer
time compared to sfrob. Also notice that as the line number increases,
the performance time difference between sfrob and sfrobu also increase.
In other words, the performance of sfrobu decreases faster than sfrob,
or the time grow faster than sfrob.

Using the strace command, I can also estimate the number of comparisons
as a function of input lines. For sfrobu, I can see that there is a 2:1
ration between comparison and input line. This is because, for every character
both read and write functions must be called. For sfrob, I notice
that, for big files especially, there is 1 comparison every ~4000 characters.

5. Finally, compare performance between sfrob, sfrobu, sfrobs, sfrobu -f and
sfrobs -f using the time command:

$ time ./sfrob < testfile.txt
Output:
real	0m0.020s
user	0m0.013s
sys	0m0.005s

$ time ./sfrobu < testfile.txt
Output:
real	0m0.164s
user	0m0.035s
sys	0m0.127s

$ time ./sfrobu -f < testfile.txt
Output:
real	0m1.300s
user	0m1.173s
sys	0m0.125s

$ time ./sfrobs < testfile.txt
Output:
real	0m0.012s
user	0m0.006s
sys	0m0.010s

$ time ./sfrobs -f < testfile.txt
Output:
real	0m0.013s
user	0m0.007s
sys	0m0.010s

6. Analysis:
We can see that the shell script sfrobs is faster out of all five.
From earlier, we have also deduced that the unbuffered version is
slower than the buffered ones, because it is calling many different
syscalls. Also notice that the -f flag decreases the performance,
which is expected because it has more syscalls to make.
