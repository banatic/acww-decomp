/* bg_models: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02037858 @ 0x02037858, 0xd0 bytes, Thumb
 * func_020377d8 @ 0x020377d8, 0x80 bytes, Thumb
 * func_0203776c @ 0x0203776c, 0x6c bytes, Thumb
 * func_02037608 @ 0x02037608, 0x164 bytes, Thumb
 * func_020375a0 @ 0x020375a0, 0x68 bytes, Thumb
 * func_02037594 @ 0x02037594, 0xc bytes, Thumb
 * func_02037588 @ 0x02037588, 0xc bytes, Thumb
 * func_0203757c @ 0x0203757c, 0xc bytes, Thumb
 * func_02037570 @ 0x02037570, 0xc bytes, Thumb
 * func_02037564 @ 0x02037564, 0xc bytes, Thumb
 * func_02037558 @ 0x02037558, 0xc bytes, Thumb
 * func_0203754c @ 0x0203754c, 0xc bytes, Thumb
 * func_02037544 @ 0x02037544, 0x6 bytes, Thumb
 * func_02037514 @ 0x02037514, 0x2e bytes, Thumb
 * func_0203750c @ 0x0203750c, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02037858_2 {
    unsigned char pad_00[0x634];
    int unk_634;
    int unk_638;
    int unk_63C;
    int unk_640;
    int unk_644;
    int unk_648;
} UnkStruct_02037858;

typedef struct {
    int key;
    int pad_04;
    int pad_08;
    int value;
    char pad_10[32];
} BigEntry;

typedef struct {
    int key;
    int value;
} SmallEntry;

typedef struct {
    BigEntry big[31];
    SmallEntry small[9];
} Cache;

typedef struct UnkStruct_02037608 {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    int unk_2C;
} UnkStruct_02037608;

typedef struct UnkStruct_020375a0 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_020375a0;

typedef struct UnkStruct_020375a0_2 {
    int a;
    int b;
} UnkStruct_020375a0_2;

typedef struct UnkStruct_020375a0_3 {
    UnkStruct_020375a0 a[31];
    UnkStruct_020375a0_2 b[9];
    u8 unk_618;
    u8 pad_619[3];
    int unk_61C;
    u8 pad_620[0x10];
    int unk_630;
} UnkStruct_020375a0_3;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02037514;

extern int func_02037af8(const char *a, int b);
extern int NNS_FndMountArchive(void *buf, const char *data, int param);
extern int NNS_FndGetArchiveFileByName(const char *name);
extern int NNS_G3dGetMatCAnmSet(int a);
extern int func_02107b80(int a, int b);
extern int NNS_G3dGetTexSRTAnmSet(int a);
extern int func_02107bbc(int a, int b);
extern int NNS_G3dGetTexPatAnmSet(int a);
extern int func_02107bf8(int a, int b);
extern int func_021077e8(int a);
extern int func_0210285c(void *buf);
extern char data_020da418[];
extern char data_020da390[];
extern char data_020da428[];
extern char data_020da43c[];
extern char data_020da450[];
extern char data_020da460[];
extern char data_020da474[];
extern char data_020da484[];
extern unsigned char data_020da37c[];
extern unsigned char data_020da3a4[];
extern int func_02064328(void *, void *, int, int);
extern int func_02064b2c(void *, void *, int, int);
extern int func_020e9948(void *, int);
extern void MI_CpuCopy8(void *, int, int);
extern void func_020e9898(void *);
extern int data_021c9b24;
extern void *func_02107828(void *p);
extern void *NNS_G3dGetJntAnmSet(void *resource);
extern void *func_02107b44(void *p, int a);
extern int func_02056064(int a, int b);
extern int func_020561cc(int a, unsigned int b);
extern unsigned char data_020da394[];
extern unsigned char data_020da3b4[];
extern unsigned char data_020da3c4[];
extern unsigned char data_020da3d4[];
extern unsigned char data_020da3e4[];
extern unsigned char data_020da3f4[];
extern unsigned char data_020da404[];
extern unsigned char data_021fbe94[];
extern void func_0205cab0(void);
extern int data_021c52c0;

void func_02037858(UnkStruct_02037858 *self)
{
    char buf[0x68];
    if (NNS_FndMountArchive(buf, data_020da390, func_02037af8(data_020da418, 0)) != 0) {
        self->unk_634 = func_02107b80(NNS_G3dGetMatCAnmSet(NNS_FndGetArchiveFileByName(data_020da428)), 0);
        self->unk_638 = func_02107bbc(NNS_G3dGetTexSRTAnmSet(NNS_FndGetArchiveFileByName(data_020da43c)), 0);
        self->unk_63C = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_020da450)), 0);
        self->unk_640 = func_021077e8(NNS_FndGetArchiveFileByName(data_020da460));
        self->unk_644 = func_02107bf8(NNS_G3dGetTexPatAnmSet(NNS_FndGetArchiveFileByName(data_020da474)), 0);
        self->unk_648 = func_021077e8(NNS_FndGetArchiveFileByName(data_020da484));
        func_0210285c(buf);
    }
}

void *func_020377d8(int p0, void *p1)
{
    unsigned char buf[0x8c];
    int r5;
    void *r4;

    func_02064328(buf, data_020da37c, p0 >> 4, p0);
    r5 = func_02064b2c(buf, (*(void * *) data_021fbe94), -4, 0);
    r4 = 0;

    if (NNS_FndMountArchive(buf + 0x20, (const char *) (((unsigned char *) data_020da390)), r5) != 0) {
        void *r7 = (void *) NNS_FndGetArchiveFileByName((const char *) data_020da3a4);
        func_0210285c(buf + 0x20);
        r4 = (void *) func_020e9948(p1, 0x180);
        MI_CpuCopy8(r7, (int) r4, 0x180);
    }

    if (r5 != 0) {
        func_020e9898((void *) r5);
    }

    return r4;
}

int func_0203776c(Cache *cache, int key)
{
    unsigned int i, j;
    int v = 0;
    int val;
    BigEntry *b;
    SmallEntry *e;

    b = cache->big;
    for (i = 0; i < 31; b++, i++) {
        if (b->key == key) {
            v = b->value;
            break;
        }
    }

    e = cache->small;
    for (j = 0; j < 9; e++, j++) {
        val = e->value;
        if (val == 0) {
            if (v != 0) {
                e->key = key;
                e->value = v;
            } else {
                e->value = (int) func_020377d8(key, (void *) data_021c9b24);
                e->key = key;
            }
            return e->value;
        } else {
            if (e->key == key) {
                return val;
            }
        }
    }
    return 0;
}

UnkStruct_02037608 *func_02037608(UnkStruct_02037608 *arr, int key)
{
    unsigned int global;
    unsigned int i;
    int shift;
    int temp;
    char buf1[0x20];
    char buf2[0x68];

    global = (*(unsigned int *) &data_021c9b24);
    for (i = 0; i < 0x1f; arr++, i++) {
        if (arr->unk_04 == 0) {
            shift = key >> 4;
            func_02064328((void *) buf1, (void *) ((const char *) data_020da37c), shift, key);
            arr->unk_04 = func_02037af8(buf1, (int) (&arr->unk_24));
            if (NNS_FndMountArchive((void *) buf2, (const char *) ((unsigned char *) data_020da390), arr->unk_04) != 0) {
                void *p, *q, *animation;
                unsigned short off;
                unsigned int val;

                p = (void *) NNS_FndGetArchiveFileByName((const char *) data_020da394);
                q = func_02107828(p);
                off = *(unsigned short *) ((char *) q + 0xe);
                val = *(unsigned int *) ((char *) ((char *) q + off) + 0xc);
                arr->unk_08 = (unsigned int) q + val;

                arr->unk_0C = (unsigned int) NNS_FndGetArchiveFileByName((const char *) data_020da3a4);
                arr->unk_10 = (unsigned int) NNS_FndGetArchiveFileByName((const char *) data_020da3b4);

                if ((animation = (void *) NNS_FndGetArchiveFileByName((const char *) data_020da3c4)) != 0) {
                    void *r = NNS_G3dGetJntAnmSet(animation);
                    arr->unk_14 = (unsigned int) func_02107b44(r, 0);
                }
                if ((animation = (void *) NNS_FndGetArchiveFileByName((const char *) data_020da3d4)) != 0) {
                    void *r = (void *) NNS_G3dGetMatCAnmSet((int) animation);
                    arr->unk_18 = (unsigned int) func_02107b80((int) r, 0);
                }
                if ((animation = (void *) NNS_FndGetArchiveFileByName((const char *) data_020da3e4)) != 0) {
                    void *r = (void *) NNS_G3dGetTexSRTAnmSet((int) animation);
                    arr->unk_1C = (unsigned int) func_02107bbc((int) r, 0);
                }
                {
                    void *r = (void *) NNS_FndGetArchiveFileByName((const char *) data_020da3f4);
                    if (r != 0) {
                        arr->unk_28 = (unsigned int) r + 2;
                        arr->unk_2C = *(short *) r;
                    }
                }
                func_0210285c(buf2);
            }
            if (((key & 0xF000) >> 12) == 1) {
                func_02064328((void *) buf1, (void *) ((const char *) data_020da404), shift, key);
                shift = func_02064b2c(buf1, *(void **) data_021fbe94, ~3, 0);
                if (shift != 0) {
                    temp = func_021077e8((int) ((unsigned int *) shift));
                    func_02056064(temp, 0);
                    arr->unk_20 = func_020561cc(temp, global);
                    if (shift != 0) {
                        func_020e9898((void *) shift);
                    }
                }
            }
            arr->unk_00 = (unsigned int) key;
            return arr;
        } else {
            if (arr->unk_00 == (unsigned int) key) {
                return arr;
            }
        }
    }
    return 0;
}

int func_020375a0(UnkStruct_020375a0_3 *s)
{
    UnkStruct_020375a0 *p;
    UnkStruct_020375a0_2 *q;
    u32 i;
    u32 j;

    // Walks with pointers rather than indexing s->a[i].
    p = s->a;
    for (i = 0; i < 31; i++) {
        p->unk_00 = 0xffff;
        p->unk_04 = 0;
        p->unk_08 = 0;
        p->unk_0C = 0;
        p->unk_14 = 0;
        p->unk_18 = 0;
        p->unk_1C = 0;
        p->unk_10 = 0;
        p->unk_28 = 0;
        p->unk_2C = 0;
        p->unk_20 = 0;
        p++;
    }
    q = s->b;
    for (j = 0; j < 9; j++) {
        q->a = 0xffff;
        q->b = 0;
        q++;
    }
    s->unk_630 = 0;
    s->unk_618 = 0;
    s->unk_61C = 0;
    func_0205cab0();
    return 1;
}

unsigned int func_02037594(unsigned int *r0)
{
    return r0[0x630 / 4];
}

unsigned int func_02037588(void *arg0)
{
    return *(unsigned int *) ((char *) arg0 + 0x634);
}

unsigned int func_0203757c(void *ptr)
{
    return *(unsigned int *) ((char *) ptr + 0x638);
}

int func_02037570(int *r0)
{
    return r0[0x18F];
}

unsigned int func_02037564(unsigned int *param0)
{
    return param0[0x190];
}

unsigned int func_02037558(void *arg0)
{
    return *(unsigned int *) ((char *) arg0 + 0x644);
}

unsigned int func_0203754c(void *ptr)
{
    return *(unsigned int *) ((char *) ptr + 0x648);
}

int func_02037544(short *p)
{
    return p[0];
}

void func_02037514(UnkStruct_02037514 *out, const unsigned char *data, int index)
{
    UnkStruct_02037514 tmp;
    unsigned char *p = (unsigned char *) data + 2;
    int off = index * 6;
    tmp.unk_00 = p[off];
    p += off;
    tmp.unk_04 = (*(signed short *) (p + 2)) << 12;
    tmp.unk_08 = (*(signed short *) (p + 4)) << 12;
    *out = tmp;
}

int func_0203750c(void)
{
    return (int) &data_021c52c0;
}
