/*
 * Copyright (C) 2019-2021, HENSOLDT Cyber GmbH
 */

#include <camkes.h>
#include <sel4/sel4.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#include <camkes/msgqueue.h>
#include <camkes/msgqueue_template.h>


#include "message.h"

int
run(void)
{
    camkes_msgqueue_sender_t sender = {0};

    printf("Sender init %d\n", camkes_msgqueue_sender_init(1, &sender));

    Msg a, b;

    a.handle = 5;
    a.status = 22;

    printf("Sender send %d\n", camkes_msgqueue_send(&sender, &a, sizeof(a)));

    b.handle = 8;
    b.status = 42;

    printf("Sender send %d\n", camkes_msgqueue_send(&sender, &b, sizeof(b)));

    printf("Sender hello!\n");
    return 0;
}
