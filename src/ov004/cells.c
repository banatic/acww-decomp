/* cells: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220db90 @ 0x0220db90, 0x2 bytes, Thumb
 * func_ov004_0220db6c @ 0x0220db6c, 0x22 bytes, Thumb
 * func_ov004_0220db68 @ 0x0220db68, 0x4 bytes, Thumb
 * func_ov004_0220db5c @ 0x0220db5c, 0xc bytes, Thumb
 * func_ov004_0220db48 @ 0x0220db48, 0x14 bytes, Thumb
 * func_ov004_0220daf0 @ 0x0220daf0, 0x56 bytes, Thumb
 * func_ov004_0220dad0 @ 0x0220dad0, 0x1e bytes, Thumb
 * func_ov004_0220dac0 @ 0x0220dac0, 0x10 bytes, Thumb
 * func_ov004_0220dabc @ 0x0220dabc, 0x4 bytes, Thumb
 * func_ov004_0220dab0 @ 0x0220dab0, 0xc bytes, Thumb
 * func_ov004_0220da70 @ 0x0220da70, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int count;
    struct {
        int a;
        int b;
    } e[4];
} UnkStruct_0220db6c;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0220db68;

typedef struct {
    int a, b;
} UnkStruct_0220db5c;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0220dabc;

struct List {
    u32 count;
    void *ent[4];
};

extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *a, int b, int c, int d);

int func_ov004_0220da70(struct List *self, void *p);

void func_ov004_0220db90(void *object) {}

int func_ov004_0220db6c(UnkStruct_0220db6c *s, int a, int b)
{
    if (s->count < 4) {
        s->e[s->count].a = a;
        s->e[s->count].b = b;
        s->count = s->count + 1;
        return 1;
    }
    return 0;
}

unsigned long func_ov004_0220db68(UnkStruct_0220db68 *p)
{
    return p->unk_00;
}

UnkStruct_0220db5c *func_ov004_0220db5c(char *self, int i)
{
    return (UnkStruct_0220db5c *) (self + 4) + (i & 3);
}

void func_ov004_0220db48(char *self)
{
    // DECLS
    u32 i;
    // ENDDECLS
    *(void **) (self) = 0x0;
    for (i = 0; i < 0x4; i++) {
        *(void **) (self + (i << 2) + 0x4) = 0x0;
    }
}

void func_ov004_0220daf0(void *self, void *list, int flag)
{
    unsigned i;
    void *t;
    char *a;
    char *b;
    void *r;
    if (flag == 0) {
        for (i = 0; i < (unsigned) func_ov004_0220db68((UnkStruct_0220db68 *) list); i++) {
            t = func_ov004_0223cd50();
            a = (char *) func_ov004_0220db5c((char *) list, i);
            b = (char *) func_ov004_0220db5c((char *) list, i);
            r = func_ov004_0223cc10(t, *(int *) a, *(int *) (b + 4), 1);
            if (r != 0) {
                func_ov004_0220da70((struct List *) self, r);
            }
        }
    }
}

void *func_ov004_0220dad0(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220db48((char *) self);
    func_ov004_0220daf0(self, (void *) a1, a2);
    return self;
}

int func_ov004_0220dac0(int arg)
{
    func_ov004_0220db48((char *) arg);
    return arg;
}

unsigned long func_ov004_0220dabc(UnkStruct_0220dabc *p)
{
    return p->unk_00;
}

int func_ov004_0220dab0(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 3) << 2) + 0x4);
}

int func_ov004_0220da70(struct List *self, void *p)
{
    u32 i;
    u32 n;

    if (p == 0) {
        return 0;
    }
    n = self->count;
    if (n >= 4) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (self->ent[i] == p) {
            return 0;
        }
    }
    self->count++;
    self->ent[n] = p;
    return 1;
}
