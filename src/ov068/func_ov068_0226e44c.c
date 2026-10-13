/* func_ov068_0226e44c @ 0x0226e44c, 0x124 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

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

extern volatile unsigned char data_021f43ec;
extern unsigned int data_ov068_0227733c;
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
        func_0206844c(obj, &result, data_ov068_0227733c);
    }
}
