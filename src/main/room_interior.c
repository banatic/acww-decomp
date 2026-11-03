/* room_interior: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02034a48 @ 0x02034a48, 0x2c bytes, Thumb
 * func_02034a18 @ 0x02034a18, 0x30 bytes, Thumb
 * func_02034a00 @ 0x02034a00, 0x18 bytes, Thumb
 * func_020349e8 @ 0x020349e8, 0x18 bytes, Thumb
 * func_020349d0 @ 0x020349d0, 0x18 bytes, Thumb
 * func_020349b8 @ 0x020349b8, 0x18 bytes, Thumb
 * func_020348fc @ 0x020348fc, 0xbc bytes, Thumb
 */

typedef struct {
    unsigned short unk_00;
    unsigned short f0 : 6;
    unsigned short b6 : 1;
    unsigned short b7 : 1;
    unsigned short b8 : 1;
} UnkStruct_020348fc;

extern int func_02034b80(int p1, int p2, int p3, int p4);
extern int func_02034b04(int p1, int p2, int p3, int p4);
extern unsigned short data_021c5204[];
extern unsigned short data_021c519c[];
extern unsigned short data_021c5174[];
extern char data_021ebcd4[];
extern int func_020b65c4(void);
extern int func_020b67e8(int id);
extern void *func_02060f04(char *g, int id);
extern void func_020611bc(void *p, unsigned short *q, int a);
extern void func_02061194(void *p, unsigned short *q, int a);

int func_02034a48(int a1, int a2, int a3, int a4, unsigned char a5)
{
    if (a3) {
        return func_02034b80(a1, a2, a4, a5);
    } else {
        return func_02034b04(a1, a2, a4, a5);
    }
}

void func_02034a18(void)
{
    unsigned int i;
    for (i = 0; i < 51; i++) {
        data_021c5204[i] = 0xfff1;
        data_021c519c[i] = data_021c5204[i];
    }
}

int func_02034a00(unsigned int idx, unsigned short *src)
{
    if (idx >= 0x33) {
        goto fail;
    }
    data_021c519c[idx] = *src;
    return 1;
fail:
    return 0;
}

unsigned short *func_020349e8(unsigned int r0)
{
    unsigned short *result;

    if (r0 < 0x33) {
        result = &data_021c519c[r0];
    } else {
        result = data_021c5174;
    }
    return result;
}

int func_020349d0(unsigned int idx, unsigned short *src)
{
    if (idx < 0x33) {
        data_021c5204[idx] = *src;
        return 1;
    }
    return 0;
}

unsigned short *func_020349b8(unsigned int index)
{
    if (index < 0x33) {
        return &data_021c5204[index];
    }
    return data_021c5174;
}

void func_020348fc(UnkStruct_020348fc *self)
{
    int f8;
    unsigned short loc;
    unsigned char id;
    int b7;
    int b6;
    void *p;

    loc = self->unk_00;
    id = (unsigned char) self->f0;
    b7 = self->b7;
    if (self->b6) {
        b6 = 1;
    } else {
        b6 = 0;
    }
    if (self->b8) {
        f8 = 1;
    } else {
        f8 = 0;
    }
    if (self->f0 == func_020b65c4()) {
        func_02034a48((int) (&loc), b7, b6, f8, 0);
        return;
    }
    if (func_020b67e8(id) != 0) {
        p = func_02060f04(data_021ebcd4, id);
        if (p == 0) {
            return;
        }
        if (b6 != 0) {
            func_020611bc(p, &loc, b7);
            func_02034a00(id, &loc);
        } else {
            func_02061194(p, &loc, b7);
            func_020349d0(id, &loc);
        }
    } else {
        if (b6 != 0) {
            func_02034a00(id, &loc);
        } else {
            func_020349d0(id, &loc);
        }
    }
}
