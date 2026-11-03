/* text_walker_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9228 @ 0x020a9228, 0x4 bytes, Thumb
 * func_020a9220 @ 0x020a9220, 0x6 bytes, Thumb
 * func_020a9218 @ 0x020a9218, 0x8 bytes, Thumb
 * func_020a9210 @ 0x020a9210, 0x8 bytes, Thumb
 * func_020a91f0 @ 0x020a91f0, 0x20 bytes, Thumb
 * func_020a91d8 @ 0x020a91d8, 0x18 bytes, Thumb
 * func_020a91b8 @ 0x020a91b8, 0x20 bytes, Thumb
 * func_020a91a4 @ 0x020a91a4, 0x14 bytes, Thumb
 * func_020a9190 @ 0x020a9190, 0x14 bytes, Thumb
 * func_020a9164 @ 0x020a9164, 0x2a bytes, Thumb
 * func_020a9080 @ 0x020a9080, 0xe2 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[36];
    unsigned long unk_24;
} UnkStruct_020a9220;

struct UnkStruct_020a91f0 {
    void *unk_00;
    char pad_04[0x28];
    int unk_2C;
};

struct UnkStruct_020a9164 {
    char pad_00[4];
    int unk_04;
    char pad_08[0x1c];
    int unk_24;
    char pad_28[4];
    int unk_2C;
};

typedef struct {
    unsigned char pad_00[0x24];
    int unk_24;
    unsigned char pad_28[4];
    int unk_2C;
} UnkStruct_020a9080;

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[16];
} Info_020a9080;

extern void *func_020a92b0(void *obj, int arg);
extern char data_020e3dc4;
extern void *func_020a9260(void *obj);
extern void func_020edb3c(void *obj);
extern void func_020a8ecc(void *);
extern void func_020a8eac(void *);
extern void func_020a8e8c(int, int);
extern void func_020a9318(struct UnkStruct_020a9164 *);
extern void func_020a8754(void *);
extern void func_020a8764(void *, int);
extern int func_020a83ec(void *);
extern void func_020a8328(void *, int *, int *, int *);
extern int func_02068114(void);
extern void func_020a93e8(UnkStruct_020a9080 *, int);
extern void func_020a9334(UnkStruct_020a9080 *, int);
extern void func_020a8e4c(int, int);
extern int func_02050c40(void);
extern int func_02050c38(void);
extern int func_02050c30(void);
extern int func_02050c48(void);
extern int func_02050c50(void);
extern int func_02050c18(void);
extern int func_02050c10(void);

void func_020a9228(int *p0, int p1)
{
    p0[9] = p1;
}

void func_020a9220(UnkStruct_020a9220 *p)
{
    p->unk_24 = 0;
}

void func_020a9218(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (40))) + (0)) = 1;
}

void func_020a9210(int p0)
{
    *(unsigned char *) ((char *) (((int) (p0) + (40))) + (0)) = 0;
}

struct UnkStruct_020a91f0 *func_020a91f0(struct UnkStruct_020a91f0 *obj)
{
    func_020a92b0(obj, 1);
    obj->unk_00 = &data_020e3dc4;
    obj->unk_2C = 0;
    return obj;
}

void *func_020a91d8(void *obj)
{
    *(void **) obj = ((int *) &data_020e3dc4);
    func_020a9260(obj);
    return obj;
}

void *func_020a91b8(void *obj)
{
    *(void **) obj = &data_020e3dc4;
    func_020a9260(obj);
    func_020edb3c(obj);
    return obj;
}

void func_020a91a4(void *arg)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg + 0x24))) != 0) {
        func_020a8ecc(condition_value0);
    }
}

void func_020a9190(void *arg)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg + 0x24))) != 0) {
        func_020a8eac(condition_value0);
    }
}

void func_020a9164(struct UnkStruct_020a9164 *p, int argument1)
{
    if (p->unk_24) {
        func_020a8e8c(p->unk_24, (int) argument1);
    }
    if (p->unk_2C && p->unk_04 == p->unk_2C) {
        p->unk_2C = 0;
        func_020a9318(p);
    }
}

void func_020a9080(UnkStruct_020a9080 *self, int param)
{
    int v0, v1, v2;
    Info_020a9080 info;
    int cmd, val, result;

    func_020a8754(&info);
    func_020a8764(&info, param);

    cmd = info.unk_00;
    val = info.unk_04;

    if (cmd == 2) {
        func_020a93e8(self, func_020a83ec(&info));
    } else if (cmd == 0xff) {
        if (val == 2) {
            func_020a8328(&info, &v0, &v1, &v2);
            if (func_02068114() == 0) {
                func_020a93e8(self, v0 * 2);
                func_020a9334(self, v2);
                self->unk_2C = v2 + ((v1 - v2) ^ 1);
            }
        }
    } else if (cmd == 0) {
        result = 0;
        if (val == 0) {
            result = func_02050c40();
        } else if (val == 1) {
            result = func_02050c38();
        } else if (val == 6) {
            result = func_02050c30();
        } else if (val == 7) {
            result = func_02050c48();
        } else if (val == 8) {
            result = func_02050c50();
        } else if (val == 9) {
            result = func_02050c18();
        } else if (val == 10) {
            result = func_02050c10();
        }
        if (result != 0) {
            func_020a9334(self, result);
        }
    }

    if (self->unk_24 != 0) {
        func_020a8e4c(self->unk_24, param);
    }
}
