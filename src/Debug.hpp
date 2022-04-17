/*
 *  This file is part of NoSqlDB.
 *  Copyright (C) 2020 Marek Zalewski aka Drwalin
 *
 *  ICon3 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ICon3 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <cstdio>
#include <chrono>
#include <ctime>
#include <cmath>
#include <cstdlib>

#ifndef RELEASE_BUILD
#define DEBUG {fprintf(stderr, " DEBUG %s:%i\n", __FILE__, __LINE__); fflush(stderr);}
#else
#define DEBUG
#endif

extern bool enableMessages;
#define PRINTF(...) {if(enableMessages) { \
	fprintf(stderr, " PRINT %s:%i", __FILE__, __LINE__); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "\n"); \
	fflush(stderr);}}

extern std::chrono::high_resolution_clock::time_point beg, end;

inline void PrintTime(const char* name, uint64_t count, float seconds) {
	double ns = (seconds*(double)(1000llu*1000llu*1000llu))/count;
	double cycles = ns * 4.3;
	printf(" %s elements %lu in time %.2f s -> %.2f kops -> %.1f ns -> %.1f cycles\n",
			name, count, seconds, count/(seconds*1000.0f), ns, cycles);
}

#define Time() std::chrono::high_resolution_clock::now()
#define DeltaTime() (std::chrono::duration<double>(end-beg).count())
#define Start() (beg = Time())
#define End() (end = Time())
#define Rand16() ((uint64_t)rand())
#define Rand32() ((Rand16()<<16) | Rand16())
#define Rand64() ((Rand32()<<32) | Rand32())
#define RandMinMax(MIN, MAX) ((Rand64()%(MAX-MIN+1))+MIN)

#endif

