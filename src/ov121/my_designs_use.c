/* my_designs_use: 5 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_02299bd4 @ 0x02299bd4, 0x3c bytes, Thumb
 * func_ov121_02299b20 @ 0x02299b20, 0xb4 bytes, Thumb
 * func_ov121_02299ad8 @ 0x02299ad8, 0x48 bytes, Thumb
 * func_ov121_02299aac @ 0x02299aac, 0x2c bytes, Thumb
 * func_ov121_02299a70 @ 0x02299a70, 0x3c bytes, Thumb
 */

struct UnkStruct_02299a70 {
    unsigned char pad_00[0x64];
    unsigned int unk_64;
};

extern int func_020984e8(void);
extern unsigned short *func_02099710(unsigned int object);
extern unsigned short *func_020996f8(int object);
extern unsigned short *func_02099728(unsigned int object);
extern void func_02099704(void *, volatile unsigned short *);
extern void func_020996ec(void *, volatile unsigned short *);
extern int func_02095b9c(unsigned short *);
extern int func_02095b84(unsigned short *);
extern int func_02095b1c(unsigned short *);
extern int func_02095f4c(void);
extern int func_02095f58(void);
extern int func_02073d90(struct UnkStruct_02299a70 *p);
extern unsigned int func_020b2300(void);
extern struct UnkStruct_02299a70 *data_020ccf94;

unsigned short func_ov121_02299bd4(int a, int b)
{
    unsigned short result;
    int object = func_020984e8();
    switch (b) {
        case 0:
            result = *func_02099710((unsigned int) object);
            break;
        case 1:
            result = *func_020996f8(object);
            break;
        case 2:
            result = *func_02099728((unsigned int) object);
            break;
        default:
            result = 0xfff1;
            break;
    }
    return result;
}

unsigned short func_ov121_02299b20(void *obj, int mode, unsigned short arg)
{
    volatile unsigned short h;
    unsigned short id;
    unsigned short v0, v1;
    unsigned int hit;
    void *g;

    id = func_ov121_02299bd4((int) obj, mode);
    g = (void *) func_020984e8();
    h = arg;
    switch (mode) {
        case 0:
            func_02099704(g, &h);
            h = id;
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x11a8 && v0 <= 0x12a7) {
                hit = 1;
            }
            if (hit == 0) {
                id = 0xfff1;
            }
            break;
        case 1:
            func_020996ec(g, &h);
            h = id;
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x1429 && v0 <= 0x1430) {
                hit = 1;
            }
            if (hit > 0) {
                id = 0xfff1;
            }
            break;
        case 2:
            h = id;
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x13a0 && v0 <= 0x13a7) {
                hit = 1;
            }
            if (hit > 0) {
                id = 0xfff1;
            }
            break;
    }
    return id;
}

int func_ov121_02299ad8(int unused, int sel, int val)
{
    unsigned short v = (unsigned short) val;
    switch (sel) {
        case 0:
            if (func_02095b9c(&v)) {
                return 1;
            }
            break;
        case 1:
            if (func_02095b84(&v)) {
                return 1;
            }
            break;
        case 2:
            if (func_02095b1c(&v)) {
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

int func_ov121_02299aac(int param1, int param2)
{
    int result;

    if (param2 == 2) {
        if (func_02095f4c() == 0) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        if (func_02095f58() == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }

    return result;
}

int func_ov121_02299a70(void)
{
    struct UnkStruct_02299a70 *p = data_020ccf94;
    if (func_02073d90(p)) {
        if (p->unk_64 == 0 && func_020b2300() <= 1) {
            goto ret1;
        }
        return 0;
    }
    if (func_020b2300() <= 1) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}
