/*
 * Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 */

#include <stdio.h>
#include <sys/utsname.h>
#include <camkes.h>

//------------------------------------------------------------------------------
static UNUSED void test_uname(void)
{
    struct utsname s;
    uname(&s);
    printf("sysname:    '%s'\n", s.sysname);
    printf("nodename:   '%s'\n", s.nodename);
    printf("release:    '%s'\n", s.release);
    printf("version:    '%s'\n", s.version);
    printf("machine:    '%s'\n", s.machine);
    printf("domainname: '%s'\n", s.__domainname);
}

//------------------------------------------------------------------------------
static UNUSED void test_sel4_word(void)
{
    printf("SEL4_PRIx_word: <%s>\n", SEL4_PRIx_word);
    seL4_Word foo = 0x42;
    printf("foo=0x%"SEL4_PRIx_word"\n", foo);
    printf("foo=%"SEL4_PRIu_word"\n", foo);
}

//------------------------------------------------------------------------------
static UNUSED void test_null_pointer_dereference(void)
{
    printf("cause NULL pointer dereference crash\n");
    *((volatile int *)NULL) = 0x42;
    printf("I'm a zombie?\n");
}

//------------------------------------------------------------------------------
static UNUSED void test_benchmark_trace(void)
{
#ifdef CONFIG_ENABLE_BENCHMARKS
    seL4_Error ret;
    ret = seL4_BenchmarkResetLog();
    ret = seL4_BenchmarkFinalizeLog();
    ret = seL4_BenchmarkSetLogBuffer(seL4_Word frame_cptr)

    printf("seL4_BenchmarkNullSyscall...\n");
    seL4_BenchmarkNullSyscall();

    printf("seL4_BenchmarkFlushCaches...\n");
    seL4_BenchmarkFlushCaches();

    seL4_BenchmarkFlushL1Caches(seL4_Word cache_type)
    seL4_BenchmarkGetThreadUtilisation(seL4_Word tcb_cptr)
    seL4_BenchmarkResetThreadUtilisation(seL4_Word tcb_cptr)

#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
    printf("seL4_BenchmarkResetAllThreadsUtilisation...\n");
    seL4_BenchmarkResetAllThreadsUtilisation();
    printf("seL4_Yield...\n");
    seL4_Yield();
    printf("Test\n");
    printf("seL4_Yield...\n");
    seL4_Yield();
#ifdef CONFIG_DEBUG_BUILD
    printf("seL4_BenchmarkDumpAllThreadsUtilisation...\n");
    seL4_BenchmarkDumpAllThreadsUtilisation();
#endif /* CONFIG_DEBUG_BUILD */
#endif /* CONFIG_BENCHMARK_TRACK_UTILISATION  */
#endif /* CONFIG_ENABLE_BENCHMARKS */
}

//------------------------------------------------------------------------------
int run(void)
{
    printf("CAmkES hello world enter\n");

    // test_sel4_word();
    test_uname();

    test_benchmark_trace();

#ifdef CONFIG_DEBUG_BUILD
    printf("seL4_DebugSnapshot\n");
    seL4_DebugSnapshot();
    printf("seL4_DebugDumpScheduler\n");
    seL4_DebugDumpScheduler();
#endif /* CONFIG_DEBUG_BUILD */

    // printf("hello world!\n");

    // test_null_pointer_dereference();

    return 0;
}
