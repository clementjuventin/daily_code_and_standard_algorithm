# Game of life

## V1

I started from a version implemented during my daily coding journey. 
It does not focus the efficience at all, I took this version to start from something I did and thus have an extreme space for improvments.
For this V1, all I will do is making a benchmark, making some graphical functions used to debug, and also care that my code is handling every sub-cases.

This V1 will also serve as a test reference. Next algorithm will need to give the same output in order to be qualified as valid.

```
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_V1_BILOAF       297017 ns       296987 ns         2320
BM_V1_BLOCK         76646 ns        76639 ns         9145
BM_V1_BLINKER       97330 ns        97320 ns         7073
BM_V1_GLIDER       145940 ns       145925 ns         4686
BM_V1_EATER_1      137415 ns       137401 ns         5056
BM_V1_HERSCHEL     254744 ns       254724 ns         2727
```

## V1.5

The first step for me was to turn compiler optimizations on with this line:
```
target_compile_options(benchmark PRIVATE -O3)
```
This gave me a x~50 speedup.
```
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_V1_BILOAF         5984 ns         5963 ns       117776
BM_V1_BLOCK          1996 ns         1988 ns       352626
BM_V1_BLINKER        2456 ns         2449 ns       283990
BM_V1_GLIDER         3512 ns         3506 ns       198266
BM_V1_EATER_1        3180 ns         3167 ns       208959
BM_V1_HERSCHEL       5494 ns         5482 ns       124509
```

## V2

I will do easy optimizations. Such as getting out the invariants from the loops.

## V3

What seems obvious to me is that most of the cells are empty. We don't need to iterate over desert zones. I will start by finding a way to skip desert zones, I will also have to find a way to reduce the size of the array counting for the neightbours of each cells to be more local. Maybe using a hashmap.  

For this, I changed the function prototype.

```
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_V1_BILOAF         6111 ns         6111 ns       106952
BM_V1_BLOCK          2042 ns         2042 ns       343578
BM_V1_BLINKER        2515 ns         2515 ns       276891
BM_V1_GLIDER         3570 ns         3569 ns       195148
BM_V1_EATER_1        3134 ns         3133 ns       220606
BM_V1_HERSCHEL       5479 ns         5476 ns       124334
BM_V2_BILOAF         5922 ns         5921 ns       115739
BM_V2_BLOCK          1986 ns         1986 ns       358966
BM_V2_BLINKER        2522 ns         2522 ns       267728
BM_V2_GLIDER         3456 ns         3456 ns       198143
BM_V2_EATER_1        3118 ns         3118 ns       224536HERSCHEL
BM_V2_HERSCHEL       5498 ns         5497 ns       125663
BM_V3_BILOAF        15368 ns        15366 ns        45004
BM_V3_BLOCK          5089 ns         5089 ns       136550
BM_V3_BLINKER        4964 ns         4964 ns       137649
BM_V3_GLIDER         7252 ns         7251 ns        97538
BM_V3_EATER_1        8246 ns         8245 ns        82914
BM_V3_HERSCHEL      18292 ns        18291 ns        37024
```

As you can see the results was not here. But the code is so much cleaner and easy to understand now (~100->~30 lines). Also, with V1 and V2, we were scaling the game space depending on the need and never unscaling it, in V3 it does not rely on the array indexes, which I think is a good thing.

The V3 seems better but is not more efficient. At this point, I think I need to make a choice, I considered small structures and only 10 iterations. The optimization I made targets huge structures because the more we make the game space big, the more empty cells the V1 and V2 will iterate over for nothing. I made an optimization for something my benchmark can't measure.

At the same time, I wonder if it make sense to considere extra large game space. The theory behind the game of life is that the game space is infinite, which is not possible due to technical limitations. However, there is a huge difference between the maximum space that V1 and V2 can handle versus V3. For V3, because living cells are defined by coordinates, we could choose to describe these coordinates with 8, 16, 32, ..., 256 or more bytes. The growing potential is way more reduce for V1 and V2 since we need to allocate a two dimentional array to store the game state.

That's why I need to make a choice, either I decide to include extremely large state or I don't.

After some thinking, I think we should include large state. In fact, there is no point of trying to optimize on small structures such as the one in my benchmark because it's already very fast. There structures are periodic and I can generate 100k+ iterations in a second which is totally useless. Something not useless is to generate 1k+ iterations on huge spaces. At the same time, I don't need a 2^512 x 2^512 game space.

The goal now will be to find a "critical" value between the small and the extra large. It probably more rely on the human representation. And then, I will benchmark again my algorithm.