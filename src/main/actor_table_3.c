/* actor_table_3: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02082808 @ 0x02082808, 0x4c bytes, Thumb
 * func_020827dc @ 0x020827dc, 0x2c bytes, Thumb
 * func_02082798 @ 0x02082798, 0x44 bytes, Thumb
 * func_02082740 @ 0x02082740, 0x56 bytes, Thumb
 * func_0208270c @ 0x0208270c, 0x34 bytes, Thumb
 * func_020826e0 @ 0x020826e0, 0x2c bytes, Thumb
 * func_020826d0 @ 0x020826d0, 0x10 bytes, Thumb
 * func_020826cc @ 0x020826cc, 0x4 bytes, Thumb
 * func_020826a8 @ 0x020826a8, 0x24 bytes, Thumb
 * func_02082664 @ 0x02082664, 0x44 bytes, Thumb
 * func_02082654 @ 0x02082654, 0x10 bytes, Thumb
 */

typedef struct {
    void *ptr;
    int pad_04;
} Elem;

typedef struct Entry {
    int value;
    int pad_04;
} Entry;

typedef struct UnkStruct_020826e0 {
    char pad_00[0x40];
    Entry entries[4];
} UnkStruct_020826e0;

extern int func_02082854(void *p, void *q);
extern int func_020828c0(void *base, Elem *elem);
extern void func_0204f818(int *a, int *b, void *data);
extern void func_02082ba0(unsigned int);
extern int func_0207cf74(unsigned int);
extern int func_0208298c(int, int);
extern unsigned char data_021d1d4c[];
extern int func_02082a44(void *ptr, int value);

int func_02082808(void *base, int val, unsigned short *src)
{
    unsigned short local;
    int idx;

    if (func_02082854(base, src) != -1) {
        goto fail;
    }

    local = 0xfff1;
    idx = func_02082854(base, &local);
    if (idx < 0 || idx >= 4) {
        goto fail;
    }

    {
        char *p = (char *) base + (idx << 3);
        *(unsigned int *) (p + 0x40) = val;
        *(unsigned short *) (p + 0x44) = *src;
    }
    return 1;

fail:
    return 0;
}

int func_020827dc(void *param, char *p)
{
    int idx;
    int ret;

    idx = func_02082854(param, p);
    ret = 0;
    if (idx >= 0 && idx < 4) {
        p = (char *) param + idx * 8;
        *(unsigned int *) (p + 0x40) = 0;
        *(unsigned short *) (p + 0x44) = 0xFFF1;
        ret = 1;
    }
    return ret;
}

int func_02082798(void *self, unsigned short key)
{
    unsigned short tmp = 0xfff1;
    int res = 0;
    int idx;

    tmp = (unsigned short) ((key & 0xfff) | 0xd000);
    idx = func_02082854(self, (void *) (&tmp));
    if (idx >= 0 && idx < 4) {
        res = *(unsigned int *) ((unsigned char *) self + (idx << 3) + 0x40);
    }
    return res;
}

void *func_02082740(void *base, int param1, int param2)
{
    Elem *elem;
    int i;
    int a, b;
    void *result = 0;

    elem = (Elem *) ((char *) base + 0x40);
    a = 0;
    b = 0;
    for (i = 0; i < 4; i++) {
        if (func_020828c0(base, elem)) {
            func_0204f818(&a, &b, (char *) elem->ptr + 0x5c);
            if (a == param1 && b == param2) {
                result = elem->ptr;
                break;
            }
        }
        elem = (Elem *) ((char *) elem + 8);
    }
    return result;
}

int func_0208270c(void *base, unsigned short *key)
{
    int result = 0;
    int index;
    unsigned short val;

    val = *key;
    if (((val & 0xf000) >> 12) == 0xd) {
        index = func_02082854(base, (void *) key);
        if (index >= 0 && index < 4) {
            result = *(int *) ((unsigned char *) base + (index * 8) + 0x40);
        }
    }
    return result;
}

int func_020826e0(UnkStruct_020826e0 *base, int index)
{
    int result = 0;

    if (index >= 0 && index < 4) {
        Entry *p = &base->entries[index];
        if (func_020828c0((void *) base, (Elem *) p)) {
            result = p->value;
        }
    }

    return result;
}

void func_020826d0(void)
{
    func_02082ba0((unsigned int) ((unsigned int *) data_021d1d4c));
}

int func_020826cc(void)
{
    return 12;
}

int func_020826a8(int arg0)
{
    int result;
    int local_4;

    local_4 = arg0;
    if (func_0207cf74(arg0) != 0) {
        result = func_0208298c((unsigned int) data_021d1d4c, local_4);
    } else {
        result = 0;
    }
    return result;
}

int func_02082664(int r0)
{
    int r4;
    int r5 = r0;
    r4 = 0;
    if (r5 < 0) {
        goto end;
    }
    if (func_0207cf74(r0) != 0) {
        r4 = func_0208298c((int) ((int *) data_021d1d4c), r5);
        goto end;
    }
    if (r5 >= func_020826cc()) {
        goto end;
    }
    r5 -= 8;
    r4 = func_020826e0((UnkStruct_020826e0 *) ((int) ((int *) data_021d1d4c)), r5);
end:
    return r4;
}

int func_02082654(int param)
{
    return func_02082a44(((int *) data_021d1d4c), param);
}
