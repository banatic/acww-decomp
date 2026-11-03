/* object_actors: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02220268 @ 0x02220268, 0x2c bytes, Thumb
 * func_ov003_02220240 @ 0x02220240, 0x28 bytes, Thumb
 * func_ov003_022201fc @ 0x022201fc, 0x44 bytes, Thumb
 * func_ov003_022201e4 @ 0x022201e4, 0x18 bytes, Thumb
 * func_ov003_02220174 @ 0x02220174, 0x70 bytes, Thumb
 * func_ov003_02220150 @ 0x02220150, 0x24 bytes, Thumb
 * func_ov003_02220138 @ 0x02220138, 0x18 bytes, Thumb
 * func_ov003_02220120 @ 0x02220120, 0x18 bytes, Thumb
 */

struct UnkStruct_022201fc {
    unsigned char pad_00[0x22c];
    unsigned int unk_22C;
    unsigned int unk_230;
};

extern unsigned int data_ov003_0223cef0[];
extern void *func_ov009_02262fcc(void *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);

int func_ov003_02220150(int x);

int func_ov003_02220268(unsigned int value)
{
    unsigned int i;
    for (i = 0; i < 0x20; i++) {
        if (data_ov003_0223cef0[i] == 0) {
            data_ov003_0223cef0[i] = value;
            return 1;
        }
    }
    return 0;
}

int func_ov003_02220240(int argument0)
{
    int result;
    int i;
    int val;

    result = func_ov003_02220150(argument0);
    i = 0;
    val = -1;
    if (result != val) {
        ((int *) data_ov003_0223cef0)[result] = i;
        return 1;
    }
    return i;
}

struct UnkStruct_022201fc *func_ov003_022201fc(unsigned int a, unsigned int b)
{
    unsigned int i = 0;
    while (i < 32) {
        struct UnkStruct_022201fc *p = ((struct UnkStruct_022201fc * *) data_ov003_0223cef0)[i];
        if (p != 0 && p->unk_22C == a && p->unk_230 == b) {
            return p;
        }
        i++;
    }
    return 0;
}

int func_ov003_022201e4(int index)
{
    if (index >= 0 && (unsigned) index < 0x20) {
        return ((int *) data_ov003_0223cef0)[index];
    }
    return 0;
}

static __inline int predA(void *q, unsigned short key)
{
    unsigned short tmp;
    tmp = key;
    if (func_0204bc64(q) == func_0204bc64(&tmp)) {
        return 1;
    }
    return 0;
}

static __inline int predB(void *q, unsigned short key)
{
    if (*(unsigned short *) q == key) {
        return 1;
    }
    return 0;
}

void *func_ov003_02220174(unsigned short key)
{
    unsigned int i;
    void *e;
    void *q;
    int v;
    for (i = 0; i < 0x20; i++) {
        e = ((void * *) data_ov003_0223cef0)[i];
        if (e != 0) {
            q = func_ov009_02262fcc(e);
            if (func_0204bcdc(q) != 0) {
                v = predA(q, key);
            } else {
                v = predB(q, key);
            }
            if (v != 0) {
                return e;
            }
        }
    }
    return 0;
}

int func_ov003_02220150(int x)
{
    unsigned int i;
    for (i = 0; i < 32; i++) {
        if (((int *) data_ov003_0223cef0)[i] == x) {
            return (int) i;
        }
    }
    return -1;
}

void func_ov003_02220138(void)
{
    unsigned int i;
    for (i = 0; i < 32; i++) {
        ((int *) data_ov003_0223cef0)[i] = 0;
    }
}

void func_ov003_02220120(void)
{
    unsigned int i;
    unsigned int *p;

    i = 0;
    do {
        p = &data_ov003_0223cef0[i];
        *p = 0;
        i++;
    } while (i < 0x20);
}
