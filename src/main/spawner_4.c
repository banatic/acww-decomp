/* spawner_4: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020848d0 @ 0x020848d0, 0x9c bytes, Thumb
 * func_02084890 @ 0x02084890, 0x40 bytes, Thumb
 * func_02084840 @ 0x02084840, 0x50 bytes, Thumb
 * func_02084834 @ 0x02084834, 0xc bytes, Thumb
 * func_020847e4 @ 0x020847e4, 0x4e bytes, Thumb
 * func_020846cc @ 0x020846cc, 0x118 bytes, Thumb
 * func_020846c0 @ 0x020846c0, 0xc bytes, Thumb
 * func_02084630 @ 0x02084630, 0x90 bytes, Thumb
 * func_02084598 @ 0x02084598, 0x98 bytes, Thumb
 * func_02084590 @ 0x02084590, 0x8 bytes, Thumb
 * func_02084560 @ 0x02084560, 0x30 bytes, Thumb
 * func_02084554 @ 0x02084554, 0xc bytes, Thumb
 * func_020844c4 @ 0x020844c4, 0x90 bytes, Thumb
 * func_020844b8 @ 0x020844b8, 0xc bytes, Thumb
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
} UnkStruct_020848d0;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02084890;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_020846cc;

typedef struct {
    char pad_00[2];
    short unk_02;
} UnkStruct_02084630;

typedef struct {
    char pad_00[2];
    short unk_02;
} UnkStruct_02084598;

extern void *data_021c80bc;
extern int func_0204f490(void *g, int *a, int *b, int *c, int *d, unsigned short *e1, unsigned short *e2, int n, int zero);
extern void func_0204f778(Vec3i *pos, int a, int b, int c, int d);
extern int func_02073dd4(void *p, int arg);
extern int func_0208602c(void);
extern int func_02086108(int a, int b);
extern int func_02084ad0(void);
extern int func_02084af0(void);
extern int func_020b65c4(void);
extern int func_02084d34(unsigned int, unsigned int, unsigned int);
extern unsigned char data_020e54a8;
extern unsigned int data_020e1b84;
extern unsigned int data_020e1d8c;
extern unsigned int data_020d0644;
extern int func_020984e8(void);
extern int func_02099640(int object);
extern int func_0209ad9c(int, int);
extern void *func_0209b4d4(int);
extern int func_0209bd44(void *);
extern int func_0209bba8(unsigned char *);
extern int func_02084b14(void *p, int n);
extern int func_02041608(void);
extern int func_02084d5c(unsigned short *p, unsigned int q, unsigned int r);
extern void *data_020ccf94;
extern unsigned int data_020e1b88;
extern int data_020d0664[];
extern UnkStruct_020846cc data_020d06a4[];
extern void func_0204f800(int *, int *, int, int, int, int);
extern void func_0204f794(void *, int, int);
extern int func_020644cc(int);
extern int func_0209fa30(void *p);
extern int func_02085d2c(int a, int b);
extern char data_021f3b85[];

int func_020848d0(int unused, Vec3i *pos, UnkStruct_020848d0 *out)
{
    void *g = data_021c80bc;
    int a = 0, b = 0, c = 0, d = 0;
    unsigned short e1, e2;

    if (g != 0) {
        e1 = 0x5014;
        e2 = 0x501a;
        if (func_0204f490(g, &a, &b, &c, &d, &e1, &e2, 1, 0) != 0) {
            out->unk_00 = 0;
            out->unk_02 = 0x4000;
            out->unk_04 = 0;
            func_0204f778(pos, a, b, c, d);
            pos->x -= 0x8000;
            pos->z += 0x6000;
            pos->y = 0;
            return 1;
        }
    }
    return 0;
}

int func_02084890(void)
{
    if (func_02073dd4((*(UnkStruct_02084890 * *) &data_020ccf94), (*(UnkStruct_02084890 * *) &data_020ccf94)->unk_64) == 0 && func_02086108(func_0208602c(), 8) != 0 &&
        func_02084ad0() == 0 && func_02084af0() == 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_02084840(void *param)
{
    if (func_02084890() != 0) {
        if (param != 0) {
            unsigned int ok = (data_020e54a8 == 0) ? 1 : 0;
            if (ok == 0) {
                goto ret0;
            }
            if (func_020b65c4() == 0x2c) {
                goto ret0;
            }
        }
        return func_02084d34((unsigned int) &data_020e1b84, (unsigned int) &data_020e1d8c, data_020d0644);
    }
ret0:
    return 0;
}

void func_02084834(void)
{
    func_02084840((void *) 1);
}

int func_020847e4(void)
{
    int forwarded_value;

    int r4;
    if ((forwarded_value = (int) func_020984e8()) != 0) {
        r4 = func_0209ad9c(func_02099640((int) forwarded_value), 0);
    } else {
        r4 = 0;
    }
    if (r4 == 0) {
        goto fail;
    }
    if (func_0209bd44((void *) func_0209b4d4(r4)) == 0) {
        goto fail;
    }
    if (func_0209bba8((unsigned char *) func_0209b4d4(r4)) != 1) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}

int func_020846cc(int param0)
{
    void *obj;
    int idx;
    int t;
    int allowed;

    obj = data_020ccf94;
    if (func_02073dd4(obj, *(int *) ((char *) obj + 0x64)) != 0) {
        goto late;
    }

    allowed = 1;
    if (param0 != 0) {
        int v = 0;
        unsigned int ok = (data_020e54a8 == 0) ? 1 : 0;
        if (ok != 0) {
            if (func_020b65c4() != 0x2c) {
                v = 1;
            }
        }
        if (v == 0) {
            allowed = 0;
        }
    }

    if (func_020847e4() != 0) {
        if (allowed == 0) {
            goto ret0;
        }
        return func_02084d34((unsigned int) &data_020e1b88, (unsigned int) &data_020e1d8c, data_020d0644);
    }

    idx = -1;
    if (func_02084ad0() == 0) {
        idx = func_02084b14(data_020d06a4, 8);
    }
    if (idx != -1) {
        t = data_020d0664[idx];
        if (t != func_02041608() && t != 0x13) {
            idx = -1;
        }
    }
    if (idx != -1) {
        if (allowed == 0) {
            goto ret0;
        }
        return func_02084d34((unsigned int) &data_020d06a4[idx].unk_04, (unsigned int) &data_020e1d8c, data_020d0644);
    }
    if (func_02084890() != 0) {
        goto ret0;
    }
    if (func_020b65c4() != 9) {
        goto ret0;
    }
    {
        unsigned short loc = 0xd025;
        return func_02084d5c(&loc, (unsigned int) &data_020e1d8c, data_020d0644);
    }

late:
    if (func_020b65c4() != 9) {
        goto ret0;
    }
    {
        unsigned short loc2 = 0xd025;
        return func_02084d5c(&loc2, (unsigned int) &data_020e1d8c, data_020d0644);
    }
ret0:
    return 0;
}

int func_020846c0(void)
{
    return func_020846cc(1);
}

int func_02084630(void *unused, void *p1, UnkStruct_02084630 *p2)
{
    unsigned short h;
    int a, b, c, d;
    int e, f;
    void *ctx;

    ctx = data_021c80bc;
    if (ctx != 0) {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        h = 0x5000;
        if (func_0204f490(ctx, &a, &b, &c, &d, &h, &h, 0x200, 0) != 0) {
            e = 0;
            f = 0;
            func_0204f800(&e, &f, a, b, c, d);
            e -= 2;
            f += 3;
            func_0204f794(p1, e, f);
            p2->unk_02 = func_020644cc(0xffff);
            return 1;
        }
    }
    return 0;
}

int func_02084598(void *unused, void *p1, UnkStruct_02084598 *p2)
{
    unsigned short h[2];
    int a, b, c, d;
    int e, f;
    void *ctx;

    ctx = data_021c80bc;
    if (ctx != 0) {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        h[0] = 0x5014;
        h[1] = 0x501a;
        if (func_0204f490(ctx, &a, &b, &c, &d, &h[0], &h[1], 1, 0) != 0) {
            e = 0;
            f = 0;
            func_0204f800(&e, &f, a, b, c, d);
            e += 2;
            f += 2;
            func_0204f794(p1, e, f);
            p2->unk_02 = func_020644cc(0xffff);
            return 1;
        }
    }
    return 0;
}

void func_02084590(void *argument0, void *argument1, void *argument2)
{
    func_02084630((void *) argument0, (void *) argument1, (UnkStruct_02084630 *) ((void *) argument2));
}

int func_02084560(int r5, int r4, int r6)
{
    int result;

    func_020984e8();
    result = func_02084af0();

    if (result != 0) {
        return func_02084630((void *) r5, (void *) r4, (UnkStruct_02084630 *) r6);
    } else {
        return func_02084598((void *) r5, (void *) r4, (UnkStruct_02084598 *) r6);
    }
}

int func_02084554(int unused, int *ptr)
{
    ptr[0] = 0;
    ptr[1] = 0;
    ptr[2] = 0;
    return 1;
}

int func_020844c4(int param0)
{
    int ret;
    void *obj;

    ret = func_0209fa30(data_021f3b85);
    obj = data_020ccf94;

    if (func_02073dd4(obj, *(int *) ((char *) obj + 0x64)) != 0) {
        goto fail;
    }

    if (param0 != 0) {
        unsigned int flag = (data_020e54a8 == 0) ? 1 : 0;
        if (flag == 0) {
            goto fail;
        }
        if (func_020b65c4() == 0x2c) {
            goto fail;
        }
    }

    if (ret != 0) {
        goto fail;
    }

    if (func_02084af0() != 0) {
        goto fail;
    }
    if (func_02084ad0() != 0) {
        goto fail;
    }

    if (func_02085d2c(0x3c, 0) == 0) {
        goto fail;
    }

    {
        unsigned short local = 0xd00d;
        return func_02084d5c(&local, (unsigned int) (((char *) &data_020e1d8c)), (unsigned int) ((*(void * *) &data_020d0644)));
    }

fail:
    return 0;
}

void func_020844b8(void)
{
    func_020844c4(1);
}
