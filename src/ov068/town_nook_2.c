/* town_nook_2: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226e570 @ 0x0226e570, 0x28 bytes, Thumb
 * func_ov068_0226e44c @ 0x0226e44c, 0x124 bytes, Thumb
 * func_ov068_0226e448 @ 0x0226e448, 0x2 bytes, Thumb
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_ov068;

typedef struct UnkStruct_0226e44c UnkStruct_0226e44c;

struct UnkStruct_0226e44c {
    unsigned char pad_00[0x14];
    int unk_14;
};

typedef struct Param0 Param0;

struct Param0 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    UnkStruct_0226e44c *unk_40;
};

extern int func_020984e8(void);
extern void func_02098fd0(int, int);
extern int data_ov068_0227733c;
extern volatile unsigned char data_021f43ec;
extern void func_0206844c(void *dst, const void *src, unsigned int size);
extern void func_ov068_0226e3a4(Param0 *param0, int a);
extern int func_02060d3c(const void *ptr);
extern void func_02015fb0(Param0 *param0, int a, int b, int c, int d, int e);
extern int func_020a12d4(void);
extern int func_02098880(const void *ptr);
extern int func_020a12c0(void);
extern unsigned char data_021dc7bc[];
extern unsigned char data_021ebcd4[];
extern unsigned char data_021f43e8[];

void func_ov068_0226e570(int arg0, UnkStruct_ov068 *arg1)
{
    int ret;
    ret = func_020984e8();
    if (ret != 0) {
        func_02098fd0(ret, 0x23);
    }
    arg1->unk_00 = data_ov068_0227733c;
    arg1->unk_04 = 0x22;
}

void func_ov068_0226e44c(Param0 *param0)
{
    UnkStruct_0226e44c *obj;
    unsigned char result;
    int v;

    obj = param0->unk_40;
    result = data_021f43ec;
    result = 0;

    switch (param0->unk_1E) {
        case 0x22:
            func_0206844c(obj, (const void *) data_021f43e8, 0);
            obj->unk_14 = 0;
            func_ov068_0226e3a4(param0, 1);
            break;

        case 0xa:
        case 0xd:
            v = func_02060d3c((const void *) data_021ebcd4);
            if (v == 0) {
                result = 0xf;
            } else {
                func_02015fb0(param0, v, 1, 10, 0, 0);
                if (func_020a12d4() != 0) {
                    result = 0x1c;
                } else if (func_02098880((const void *) data_021dc7bc) <= 1) {
                    result = 0x27;
                } else {
                    result = 0xb;
                }
            }
            break;

        case 0x1c:
        case 0x27:
        case 0xb:
            if (func_020a12c0() == 0 && func_020a12d4() == 0) {
                result = 0xe;
            } else {
                result = 0xc;
            }
            break;

        case 0xf:
            if (func_020a12c0() == 0 && func_020a12d4() == 0) {
                result = 0x10;
            } else {
                result = 0x11;
            }
            break;
    }

    if (result != 0) {
        func_0206844c(obj, &result, (*(unsigned int *) &data_ov068_0227733c));
    }
}

void func_ov068_0226e448(void) {}
