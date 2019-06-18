Name: Arabelle Siahaan
UID: xxxxxxxxx

In the homework bit, I am supposed to make the performance of main.c faster
by splitting it into threads. So I looked at the main function of the original
main.c file and see that there are nested loops that go through every pixel one-by-one.
I notice that this is what needs to be multithreaded.

But, I had the problem of visiting each pixel by using multithread and
make sure that each pixel is visited once and once only. I also need to make sure that
there will not be any race conditions or other multithread issues.

After some thinking, I decided to use a method in which it visits different horizontal
pixels but always visits the vertical pixels. I do this by making each thread
run (width/nthreads) pixels per loop. In my main.c, I also handled the case
in which the width and nthread does not divide equally:

the start point would be is given by (tnum) * (width/nthreads)
the end point would be is given by (tnum+1) * (width/nthreads), but for widths that
are not divisible by nthreads, the end point is given by:
(tnum == nthreads - 1) ? width : (tnum+1) * (width/nthreads)

Then I start applying multithread by first creating an array of integers that store
the thread IDs of our threads. The IDs are generated in order from 0 to nthread.
After that, I create the threads using pthread_create and then join the threads
using pthread_join.

Finally, I needed to figure out a way to ensure that data was printed in the correct
order. I removed all the original print statements and changed it to a print statement
I generated using a globaly-defined 3D array. Then, I print the RGB value of each pixel
correctly.

Now, I'm going to analyze the time performance of this multithread performance, using
different number of threads: 1, 2, 4 and 8.

(a) 1 thread
$ time ./srt 1-test.ppm > 1-out.txt
real	0m40.953s
user	0m40.871s
sys	0m0.001s

(b) 2 threads
$ time ./srt 2-test.ppm > 2-out.txt
real	0m22.046s
user	0m42.764s
sys	0m0.002s

(c) 4 threads
$ time ./srt 4-test.ppm > 4-out.txt
real	0m14.844s
user	0m43.673s
sys	0m0.003s

(d) 8 threads
$ time ./srt 8-test.ppm > 8-out.txt
real	0m9.275s
user	0m44.497s
sys	0m0.002s

From what we can see here, the amount of time taken to complete the ray-tracing
decreases as the number of threads increase. However, as I keep on increasing
the number of threads, I notice that the time taken for the program to run increases
after it reaches the optimum performance time at around 6 seconds. After this optimum
time, the time increases in a decreasing growth until this increase is negligible.

