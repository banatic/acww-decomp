/* villager_house_2: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221d704 @ 0x0221d704, 0x68 bytes, Thumb
 * func_ov003_0221d6dc @ 0x0221d6dc, 0x28 bytes, Thumb
 * func_ov003_0221d69c @ 0x0221d69c, 0x40 bytes, Thumb
 * func_ov003_0221d64c @ 0x0221d64c, 0x50 bytes, Thumb
 * func_ov003_0221d5f4 @ 0x0221d5f4, 0x58 bytes, Thumb
 * func_ov003_0221d5cc @ 0x0221d5cc, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int data[12];
} Chunk;

struct UnkStruct_0221d704 {
    char pad_00[0x1a0];
    Chunk left;
    char pad1[0x235 - (0x1a0 + sizeof(Chunk))];
    unsigned char flag;
    char pad_236[0x318 - (0x235 + 1)];
    Chunk right;
    char pad3[0x36c - (0x318 + sizeof(Chunk))];
    char unk_36C;
    char pad_36D[0x374 - (0x36c + 1)];
    int unk_374;
    char pad_378[0x384 - (0x374 + 4)];
    int *unk_384;
};

struct UnkStruct_0221d64c {
    char pad_00[0x136];
    unsigned short code;
};

typedef struct {
    unsigned char b : 5;
} Low5;

struct Param {
    u8 pad_00[0x136];
    u16 unk_136;
};

struct UnkStruct_0221d5f4 {
    unsigned char b : 5;
};

extern int func_ov003_022203b8(void);
extern int func_ov003_0221fe9c(void *argument0);
extern void func_02056ffc(void *ptr);
extern void func_0205510c(char *p, int v);
extern int data_ov003_0223c928[];
extern char data_021e5a2c[];
extern void *func_0207cec0(void *p, int n);
extern void *func_02080b64(void *p);
extern int func_02064328(void *, void *, int, int);
extern int data_ov003_0223c914;
extern int data_ov003_022390b8;

int func_ov003_0221d704(struct UnkStruct_0221d704 *self)
{

    if (func_ov003_0221fe9c((void *) func_ov003_022203b8())) {
        self->right = self->left;
        if ((self->flag & 1) == 0) {
            func_02056ffc(&self->unk_36C);
            *self->unk_384 = self->unk_374;
        }
    }
    return 1;
}

int func_ov003_0221d6dc(void *self)
{

    if (func_ov003_0221fe9c((void *) func_ov003_022203b8())) {
        func_0205510c((char *) self + 0x2b4, 0);
    }
    return 1;
}

int func_ov003_0221d69c(void *obj)
{
    int in_range = 0;
    unsigned int val;
    int idx;

    val = *(unsigned short *) ((char *) obj + 0x136);
    if ((val >= 0x5001) && (val <= 0x5008)) {
        in_range = 1;
    }
    if (in_range) {
        idx = val - 0x5001;
    } else {
        idx = -1;
    }
    data_ov003_0223c928[idx] = 0;
    return 1;
}

unsigned char func_ov003_0221d64c(struct UnkStruct_0221d64c *obj)
{
    void *base;
    int flag;
    unsigned short val;
    int offset;
    void *tmp;

    base = data_021e5a2c;
    flag = 0;
    val = obj->code;
    if (val >= 0x5001 && val <= 0x5008) {
        flag = 1;
    }
    if (flag) {
        offset = val - 0x5001;
    } else {
        offset = -1;
    }
    tmp = func_0207cec0(base, offset);
    tmp = func_02080b64(tmp);
    return ((Low5 *) tmp)->b;
}

u8 func_ov003_0221d5f4(struct Param *p)
{
    void *base = (void *) ((int *) data_021e5a2c);
    int flag = 0;
    u16 val = p->unk_136;
    int idx;

    if (val >= 0x5001 && val <= 0x5008) {
        flag = 1;
    }

    if (flag) {
        idx = val - 0x5001;
    } else {
        idx = -1;
    }

    return (u8) (((struct UnkStruct_0221d5f4 *) func_02080b64(func_0207cec0(base, idx)))->b & 3);
}

int *func_ov003_0221d5cc(void *argument0)
{
    int x = (int) func_ov003_0221d64c((struct UnkStruct_0221d64c *) argument0);
    func_02064328(&data_ov003_0223c914, &data_ov003_022390b8, x >> 2, x & 3);
    return &data_ov003_0223c914;
}
