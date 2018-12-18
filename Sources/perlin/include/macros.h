//
//  macros.h
//  linux
//
//  Created by menangen on 18/12/2018.
//

#define CPU_SSE2 __builtin_cpu_supports("sse2")
#define CPU_SSE3 __builtin_cpu_supports("sse3")

#define CPU_SSE41 __builtin_cpu_supports("sse4.1")
#define CPU_SSE42 __builtin_cpu_supports("sse4.2")

#define CPU_AVX __builtin_cpu_supports("avx")
#define CPU_AVX2 __builtin_cpu_supports("avx2")

#define CPU_AVX512 __builtin_cpu_supports("avx512f")
