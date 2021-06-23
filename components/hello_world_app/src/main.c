/*
 * Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 */

#include <stdio.h>

static int testFunc(int i);

int run()
{
    printf("hello world!\n");

    int i = 0;

    while (i<10)
    {
        int value = testFunc(i);

        if (value > 0)
        {
            i++;
        }
    }

    return 0;
}

int testFunc(int i)
{
    if (i % 2 == 0)
    {
        return i;
    }
    else
    {
        return 0;
    }

    return -1;
}
