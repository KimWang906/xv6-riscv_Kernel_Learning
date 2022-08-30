#include <stdio.h>

struct object
{
    int ref;
};

struct object* object_new(void)
{
    struct object* p=malloc(sizeof(struct object));
    p->ref=1;
    return p;
}

int object_ref(struct object* p)
{
    return (p->ref++);
}

int object_unref(struct object* p)
{
    if ((p->ref--)!=0)
        return p->ref;
    else
    {
        free(p);
        return 0;
    }
}
