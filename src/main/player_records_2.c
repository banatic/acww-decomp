/* player_records_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02098904 @ 0x02098904, 0x2c bytes, Thumb
 * func_020988e4 @ 0x020988e4, 0x20 bytes, Thumb
 * func_020988d8 @ 0x020988d8, 0xc bytes, Thumb
 * func_020988a4 @ 0x020988a4, 0x34 bytes, Thumb
 * func_02098880 @ 0x02098880, 0x24 bytes, Thumb
 * func_02098868 @ 0x02098868, 0x16 bytes, Thumb
 * func_02098844 @ 0x02098844, 0x24 bytes, Thumb
 * func_020987ac @ 0x020987ac, 0x98 bytes, Thumb
 * func_02098788 @ 0x02098788, 0x24 bytes, Thumb
 * func_0209877c @ 0x0209877c, 0xc bytes, Thumb
 * func_0209871c @ 0x0209871c, 0x60 bytes, Thumb
 */

typedef struct {
    unsigned short id;
    char data[0xc];
} Key;

typedef struct {
    char pad_00[0x249c];
} Elem;

typedef struct {
    unsigned short tag;
    unsigned char data[12];
} TaggedData;

typedef struct {
    char pad_00[0x249c];
} Slot;

extern void *func_02099ad0(void *);
extern void *func_02099bc8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int func_02099a28(int);
extern int func_020644cc(int);
extern Key *func_02099870(Elem *);
extern int memcmp(const void *, const void *, int);
extern int func_0209518c(Key *, Key *);
extern void func_02099a38(void *);
extern int func_02099314(int a, int b);
extern int func_020951bc(const TaggedData *key);

int func_02098844(int r0, int r1);
int func_0209871c(Slot *slots, TaggedData *key);

void *func_02098904(void *ptr)
{
    __cxa_vec_ctor((void *) (ptr), 4, 0x249c, (((void (*)(void *)) func_02099bc8)), (((void (*)(void *)) func_02099ad0)));
    return ptr;
}

int func_020988e4(int arg)
{
    __cxa_vec_cleanup((void *) (arg), 4, 0x249c, (((void (*)(void *)) func_02099ad0)));
    return arg;
}

int func_020988d8(unsigned int arg)
{
    if (arg < 4) {
        return 1;
    } else {
        return 0;
    }
}

int func_020988a4(int r5, int r4)
{
    int r0;
    int r1;

    r1 = r4;
    r0 = func_020988d8(r1);
    if (r0 != 0) {
        r4 = r4 * 0x249c;
        r0 = r5 + r4;
        r0 = func_02099a28(r0);
        if (r0 != 0) {
            return 1;
        }
    }
    return 0;
}

int func_02098880(int param)
{
    int i;
    int count = 0;
    int j = 0;
    for (i = 0; i < 4; i++) {
        if (func_020988a4(param, i)) {
            count++;
        }
    }
    return count;
}

void *func_02098868(void *arg, void *argument1)
{
    return (void *) func_02098844((int) arg,
                                  (int) ((void *) func_0209871c((Slot *) arg, (TaggedData *) ((void *) argument1))));
}

int func_02098844(int r0, int r1)
{
    int r4 = 0;
    int r5 = r0;
    int r6 = r1;

    if (func_020988d8(r6) != 0) {
        r4 = r5 + r6 * 0x249c;
    }

    return r4;
}

void *func_020987ac(void *p0, Key *p1)
{
    void *result;
    int n, k, i;
    Elem *e;
    Key *q;

    if (p1 == 0 || (int) func_02098868(p0, p1) == 0) {
        n = func_02098880((int) p0);
    } else {
        n = func_02098880((int) p0) - 1;
    }
    result = 0;
    if (n > 0) {
        k = func_020644cc(n);
        for (i = 0; i < 4; i++) {
            e = (Elem *) ((char *) p0 + i * 0x249c);
            if (func_02099a28((int) e) == 1) {
                if (p1 != 0) {
                    q = func_02099870(e);
                    if (p1->id == q->id && memcmp(p1->data, q->data, 0xc) == 0 && func_0209518c(p1, q) != 0) {
                        continue;
                    }
                }
                if (k == 0) {
                    result = e;
                    break;
                }
                k--;
            }
        }
    }
    return result;
}

void func_02098788(void *arg0)
{
    int i;
    void *ptr;

    for (i = 0; i < 4; i++) {
        ptr = (void *) ((int) arg0 + i * 0x249c);
        func_02099a38(ptr);
    }
}

int func_0209877c(int a)
{
    return func_02099314(a, 4);
}

int func_0209871c(Slot *slots, TaggedData *key)
{
    int i;
    TaggedData *info;

    if (func_020951bc(key) != 1) {
        goto fail;
    }
    i = 0;
    while (i < 4) {
        info = (TaggedData *) func_02099870((Elem *) (&slots[i]));
        if (key->tag == info->tag) {
            if (memcmp(key->data, info->data, 12) == 0) {
                if (func_0209518c((Key *) key, (Key *) info) != 0) {
                    return i;
                }
            }
        }
        i++;
    }
fail:
    return -1;
}
