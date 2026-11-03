/* object_claim_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203f4ec @ 0x0203f4ec, 0x18 bytes, Thumb
 * func_0203f4c4 @ 0x0203f4c4, 0x28 bytes, Thumb
 * func_0203f490 @ 0x0203f490, 0x34 bytes, Thumb
 * func_0203f454 @ 0x0203f454, 0x3c bytes, Thumb
 * func_0203f444 @ 0x0203f444, 0x10 bytes, Thumb
 * func_0203f400 @ 0x0203f400, 0x44 bytes, Thumb
 * func_0203f394 @ 0x0203f394, 0x6c bytes, Thumb
 * func_0203f364 @ 0x0203f364, 0x30 bytes, Thumb
 * func_0203f338 @ 0x0203f338, 0x2c bytes, Thumb
 */

typedef struct UnkStruct_0203f4ec UnkStruct_0203f4ec;

struct UnkStruct_0203f4ec {
    unsigned char type;
};

typedef void (*Handler)(UnkStruct_0203f4ec *, int);

struct UnkStruct_0203f400 {
    char pad_00[0x64];
    int unk_64;
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0203f394;

extern Handler data_020dab98[];
extern int OSiHeapInfo[4];
extern int data_021c72d4;
extern char data_020dab94;
extern void *data_020ccf94;
extern void func_02073820(void *);
extern void func_020737f0(void *, int *, int);
extern void func_02073770(void *, int, int);
extern int func_02073d90(void *);
extern int func_020a7278(void);

void func_0203f4ec(UnkStruct_0203f4ec *obj, int arg)
{
    data_020dab98[obj->type](obj, arg);
}

void func_0203f4c4(void)
{
    int value = 0;
    int i;
    for (i = 0; i < 4; i++) {
        OSiHeapInfo[i] = value;
    }
    data_021c72d4 = value;
    data_020dab94 = 6;
}

void func_0203f490(int a, int b)
{
    void *obj = data_020ccf94;
    func_02073820(obj);
    func_020737f0(obj, &a, 1);
    func_02073770(obj, 23, b);
}

int func_0203f454(int a, int b)
{
    int i;
    if (OSiHeapInfo[a] != 0) {
        return 0;
    }
    if (data_021c72d4 == b) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (b == OSiHeapInfo[i]) {
            return 0;
        }
    }
    return 1;
}

int func_0203f444(int p0)
{
    *(int *) ((char *) OSiHeapInfo + ((p0 << 2))) = 0;
    return (int) OSiHeapInfo;
}

int func_0203f400(int p)
{
    struct UnkStruct_0203f400 *s = (*(struct UnkStruct_0203f400 * *) &data_020ccf94);

    if (func_02073d90(s) == 0) {
        return 2;
    }
    if (s->unk_64 == 0) {
        if (!func_0203f454((unsigned char) ((unsigned char) s->unk_64), p)) {
            return 0;
        }
        return 2;
    }
    return 1;
}

void func_0203f394(unsigned int arg)
{
    UnkStruct_0203f394 *p;
    p = (*(UnkStruct_0203f394 * *) &data_020ccf94);
    if (func_02073d90(p)) {
        int field;
        unsigned char buf[12];
        UnkStruct_0203f394 *q;
        field = p->unk_64;
        if (field == 0) {
            OSiHeapInfo[field] = arg;
        } else {
            (*(unsigned char *) &data_020dab94) = 0;
            buf[0] = 0;
            buf[1] = arg;
            buf[2] = arg >> 8;
            buf[3] = arg >> 16;
            buf[4] = arg >> 24;
            q = (*(UnkStruct_0203f394 * *) &data_020ccf94);
            func_02073820(q);
            func_020737f0(q, (int *) buf, 5);
            func_02073770(q, 23, 0);
        }
    }
}

void func_0203f364(void)
{
    void *r4;
    int r0;

    r4 = (void *) (*(unsigned int *) &data_020ccf94);
    r0 = func_02073d90(r4);
    if (r0 != 0) {
        if (*(int *) ((char *) r4 + 0x64) == 0) {
            func_0203f444(0);
        } else {
            func_0203f490(3, 0);
        }
    }
}

int func_0203f338(void)
{
    int r = func_02073d90((void *) ((*(int *) &data_020ccf94)));

    if (r == 0) {
        return 2;
    }
    if (!func_020a7278()) {
        return 1;
    }
    return 2;
}
