/* model_cache: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056318 @ 0x02056318, 0x78 bytes, Thumb
 * func_02056310 @ 0x02056310, 0x8 bytes, Thumb
 * func_020562cc @ 0x020562cc, 0x44 bytes, Thumb
 * func_02056294 @ 0x02056294, 0x38 bytes, Thumb
 * func_02056268 @ 0x02056268, 0x2c bytes, Thumb
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} Entry;

struct entry {
    int value;
    int key;
};

struct Entry {
    unsigned int value;
    unsigned int key;
};

typedef struct {
    int unk_00;
} UnkStruct_02056268;

extern unsigned int data_021c8ca4;
extern unsigned int data_021c8ca8;
extern unsigned char data_020e54a8;
extern void func_0205cb34(int arg1, int arg2);
extern Entry data_021c8cac[60];
extern Entry data_021c8e8c[150];
extern void func_0205cb18(void);
extern int func_020e9948(int a, int b);
extern void MI_CpuCopy8(UnkStruct_02056268 *a, int b, int c);

void func_02056318(void)
{
    int i;
    unsigned int flag;
    int param;

    for (i = 0; i < 150; i++) {
        data_021c8e8c[i].a = 0;
        data_021c8e8c[i].b = 0x4e554c4c;
    }
    for (i = 0; i < 60; i++) {
        data_021c8cac[i].a = 0;
        data_021c8cac[i].b = 0x4e554c4c;
    }
    data_021c8ca8 = 0;
    data_021c8ca4 = 0;
    flag = (data_020e54a8 == 0);
    if (flag > 0) {
        param = 0x7800;
    } else {
        param = 0x10400;
    }
    func_0205cb34(param, 0);
}

void func_02056310(void)
{
    func_0205cb18();
}

int func_020562cc(int key)
{
    int i;
    if (key == 0x4e554c4c) {
        return 0;
    }
    for (i = 0; i < (*(int *) &data_021c8ca8); i++) {
        if (key == ((struct entry *) data_021c8e8c)[i].key) {
            return ((struct entry *) data_021c8e8c)[i].value;
        }
    }
    return 0;
}

unsigned int func_02056294(unsigned int param)
{
    int i;
    if (param == 0x4e554c4c) {
        return 0;
    }
    for (i = 0; i < 60; i++) {
        if (param == ((struct Entry *) data_021c8cac)[i].key) {
            return ((struct Entry *) data_021c8cac)[i].value;
        }
    }
    return 0;
}

int func_02056268(UnkStruct_02056268 *p, int key)
{
    int ret;
    ret = func_020e9948(key, p->unk_00);
    if (ret == 0) {
        return 0;
    }
    MI_CpuCopy8(p, ret, p->unk_00);
    return ret;
}
