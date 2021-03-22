/**
 * Copyright (C) 2019-2020, Hensoldt Cyber GmbH
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

using namespace std;

void*
operator new(unsigned int n)
{
    void* const p = malloc(n);

    return p;
}

void
operator delete(void* p, unsigned int n)
{
    free(p);
}

template<class T>
class temp
{
    T var;

  public:
    template<class Y>
    temp(Y tmp)
    {
        var = tmp;
        printf("Constructor is %d\n", var);
    }
};

class Runner
{
  public:
    Runner() { printf("Constructor is called\n"); }
    virtual ~Runner() { printf("Destructor is called\n"); }

    void run() { printf("hello world!\n"); }
};

class Derived : public Runner
{
  public:
    Derived() { printf("Derived Constructor is called\n"); }
    ~Derived() { printf("Derived Destructor is called\n"); }

    void run() { printf("hello world!\n"); }
};

extern "C" int
run()
{
    temp<int>  a(256);
    temp<char> b(256);
    Runner     r, *s;

    s = new Runner();
    s->run();
    delete s;

    s = new Runner();
    s->run();
    delete s;

    r.run();

    auto p = new Runner();
    p->run();

    s = new Derived();

    delete s;
    delete p;

    int m = 0;
    int n = 0;
    [&, n](int a) mutable { m = ++n + a; }(4);

    printf("%d %d \n", m, n);

    etl::queue<int, 5> q;
    for (int i = 0; i < 10; i++)
    {
        if (!q.full())
            q.push(i);
    }

    printf("Queue size %d\n", q.size());
    for (int i = 0; i < 10; i++)
    {
      if(!q.empty())
      {
        printf("Got element %d\n",q.front());
        q.pop();
      }
    }

    return 0;
}
