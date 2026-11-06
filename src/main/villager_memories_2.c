/* villager_memories_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020807dc @ 0x020807dc, 0x2c bytes, Thumb
 * func_020807c0 @ 0x020807c0, 0x1c bytes, Thumb
 * func_020807a8 @ 0x020807a8, 0x16 bytes, Thumb
 * func_02080758 @ 0x02080758, 0x50 bytes, Thumb
 * func_02080728 @ 0x02080728, 0x30 bytes, Thumb
 * func_020806f8 @ 0x020806f8, 0x30 bytes, Thumb
 * func_02080684 @ 0x02080684, 0x74 bytes, Thumb
 * func_020805bc @ 0x020805bc, 0xc8 bytes, Thumb
 * func_02080578 @ 0x02080578, 0x44 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x80];
} UnkStruct_020805bc;

extern int func_02081d28(void *src, void *dst);
extern int func_02080808(int, unsigned int);
extern int data_021d1240;
extern int data_021d12f0;
extern int data_021d125c;
extern void *func_0209529c(int *);
extern void func_02095238(int *);
extern int func_0209526c(void *);
extern __arm void __register_global_object(void *, void *, void *);
extern int func_02081d60(void *);
extern int func_0209518c(int, int);
extern int func_02081edc(void *object);
extern int func_02081d20(char *);
extern int func_02081e10(char *p);
extern int func_0209e3ac(int a, int b, int c);
extern int func_0209e350(int a, int b);
extern int func_02064294(void *s);
extern int func_02081cd8(UnkStruct_020805bc *p);
extern unsigned char data_021dc7aa[];
extern unsigned char data_021dc7bc[];
extern unsigned short *func_02095040(void *);
extern int func_0209871c(void *, void *);
extern int memcmp(const void *, const void *, unsigned int);

int func_020807dc(void *param0, void *param1)
{
    int i;
    int result;

    i = 0;
    while (i < 8) {
        if (func_02081d28((char *) param0 + (i << 7), param1)) {
            return i;
        }
        i++;
    }
    return -1;
}

int func_020807c0(int param1, int param2)
{
    int result;
    int temp;

    result = 0;
    temp = func_02080808(param1, param2);
    if (temp != 0) {
        result = param1 + (param2 << 7);
    }
    return result;
}

int func_020807a8(int arg, void *argument1)
{
    return func_020807c0(arg, func_020807dc((void *) arg, (void *) argument1));
}

int func_02080758(int arg)
{
    if ((data_021d1240 & 1) == 0) {
        func_0209529c(&data_021d12f0);
        __register_global_object((void *) (&data_021d12f0), (((void *) func_0209526c)), (void *) (&data_021d125c));
        data_021d1240 |= 1;
    }
    func_02095238(&data_021d12f0);
    return func_020807dc((void *) arg, (void *) (&data_021d12f0));
}

int func_02080728(void *arr, int val)
{
    int i = 0;
    while (i < 8) {
        if (func_0209518c(func_02081d60((char *) arr + (i << 7)), val)) {
            return i;
        }
        i++;
    }
    return -1;
}

int func_020806f8(char *p)
{
    int max = -128;
    int i = 0;
    do {
        if (func_02081edc(p)) {
            int ret = func_02081d20(p);
            if (ret > max) {
                max = ret;
            }
        }
        p += 0x80;
        i++;
    } while (i < 8);
    return max;
}

int func_02080684(char *a, int b)
{
    int min = 0x7fffffff;
    int locals[3];
    int i;
    locals[1] = 0;
    for (i = 0; i < 8; a += 0x80, i++) {
        int res;
        int candidate;
        if (!func_02081edc((void *) a)) {
            continue;
        }
        locals[0] = func_02081e10(a);
        res = func_0209e3ac(b, locals[0], 0x3f);
        if (res == 1) {
            candidate = func_0209e350(locals[0], b);
            if (candidate < min) {
                min = candidate;
            }
        } else if (res == ~locals[1]) {
            candidate = func_0209e350(b, locals[0]);
            if (candidate < min) {
                min = candidate;
            }
        } else {
            return 0;
        }
    }
    return min;
}

int func_020805bc(UnkStruct_020805bc *p, int (*cb)(void *, void *, void *))
{
    UnkStruct_020805bc *sel;
    int i;
    int best = -1;

    if (func_02064294(data_021dc7aa) != 0) {
        sel = 0;
        for (i = 0; i < 8; p++, i++) {
            if (func_02081edc((void *) p) == 0) {
                continue;
            }
            if (cb((void *) func_02081d60((void *) p), data_021dc7aa, data_021dc7bc) == 0) {
                continue;
            }
            if (sel != 0) {
                if (func_02081cd8(sel) == func_02081cd8(p)) {
                    if (func_02081d20((char *) sel) > func_02081d20((char *) p)) {
                        sel = p;
                        best = i;
                    } else if (func_02081d20((char *) sel) == func_02081d20((char *) p)) {
                        if (func_0209e3ac((int) ((void *) func_02081e10((char *) sel)),
                                          (int) ((void *) func_02081e10((char *) p)), 0x3f) == 1) {
                            sel = p;
                            best = i;
                        }
                    }
                } else if (func_02081cd8(p) == 0) {
                    sel = p;
                    best = i;
                }
            } else {
                sel = p;
                best = i;
            }
        }
    }
    return best;
}

int func_02080578(unsigned short *a, unsigned short *b, void *c)
{
    int flag = 0;
    unsigned short *p = func_02095040((void *) a);
    if (*b == *p) {
        if (memcmp((char *) b + 2, (char *) p + 2, 12) == 0) {
            if (func_0209871c(c, a) == ~flag) {
                flag = 1;
            }
        }
    }
    return flag;
}
