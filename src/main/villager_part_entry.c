/* villager_part_entry: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209b23c @ 0x0209b23c, 0x16 bytes, Thumb
 * func_0209b218 @ 0x0209b218, 0x24 bytes, Thumb
 * func_0209b1f0 @ 0x0209b1f0, 0x26 bytes, Thumb
 * func_0209b184 @ 0x0209b184, 0x6c bytes, Thumb
 * func_0209b160 @ 0x0209b160, 0x24 bytes, Thumb
 * func_0209b0f4 @ 0x0209b0f4, 0x6c bytes, Thumb
 * func_0209b0f0 @ 0x0209b0f0, 0x2 bytes, Thumb
 * func_0209b0c4 @ 0x0209b0c4, 0x2c bytes, Thumb
 * func_0209b044 @ 0x0209b044, 0x80 bytes, Thumb
 * func_0209af80 @ 0x0209af80, 0xc4 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[12];
    unsigned char index;
} UnkStruct_0209b0c4;

typedef struct {
    char pad_00[0xc];
    unsigned char unk_0C;
    unsigned char unk_0D;
} UnkStruct_0209b044;

typedef struct {
    unsigned char pad_00[0xc];
    unsigned char unk_0C;
} Func_0209af80_ObjA;

typedef struct {
    unsigned short h;
} Func_0209af80_ObjB;

extern void func_0209bd5c(void *param);
extern int func_020ad7a4(void);
extern int func_020af950(void *p);
extern int func_020644cc(int x);
extern int data_021f395c;
extern void func_0209bd30(unsigned char *, int, unsigned short *, int);
extern unsigned short data_020d1a28[];
extern unsigned short data_020d1a54[];
extern int func_02082438(void *arg, unsigned short *val);
extern void func_0209bb90(UnkStruct_0209b044 *, int);
extern void func_0209bb68(UnkStruct_0209b044 *, unsigned short *);
extern int func_020984e8(void);
extern int func_02099870(int);
extern int func_02094ffc(int);
extern int func_0209bd44(Func_0209af80_ObjA *);
extern int func_0209bba0(Func_0209af80_ObjA *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);

void func_0209b23c(void *param)
{
    unsigned char *ptr = (unsigned char *) param;
    func_0209bd5c(param);
    ptr[0xc] = 5;
    ptr[0xd] = 0;
}

unsigned char func_0209b218(int unused, int param)
{
    unsigned char count = 0;
    int i = 0;
    do {
        if ((param >> i) & 1) {
            count++;
        }
        i++;
    } while (i < 5);
    return count;
}

unsigned char func_0209b1f0(int a, int b)
{
    unsigned char res;
    res = func_0209b218(a, b);
    if (((b >> 2) & 1) && ((b >> 3) & 1)) {
        res--;
    }
    return res;
}

int func_0209b184(int a, int b)
{
    int i;
    int r;

    if (func_020ad7a4() == 0) {
        b = (unsigned char) (b & ~3);
    } else {
        if (func_020af950(&data_021f395c) != 0) {
            b = (unsigned char) (b & ~1);
        }
    }

    r = (int) func_0209b218(a, b);
    if (r > 0) {
        r = func_020644cc(r);
        for (i = 0; i < 5; i++) {
            if ((b >> i) & 1) {
                if (r == 0) {
                    return i;
                }
                r--;
            }
        }
    }
    return -1;
}

void func_0209b160(unsigned char *r0, int r1)
{
    if ((unsigned int) (r1 - 2) <= 1) {
        r0[0xd] &= ~4;
        r0[0xd] &= ~8;
    } else {
        r0[0xd] &= ~(1 << r1);
    }
}

void func_0209b0f4(unsigned char *p)
{
    unsigned short local;
    unsigned int tmp;
    int i;
    tmp = func_020644cc(10) & 1;
    func_0209b23c((void *) p);
    local = data_020d1a28[tmp];
    func_0209bd30(p, 20, &local, 0);
    for (i = 0; i < 5; i++) {
        p[13] |= 1 << i;
    }
    tmp = (unsigned int) func_0209b184((int) p, (unsigned char) p[13]);
    if (tmp < 5) {
        func_0209b160(p, tmp);
        p[12] = (unsigned char) tmp;
    }
}

void *func_0209b0f0(void *record)
{
    return record;
}

int func_0209b0c4(UnkStruct_0209b0c4 *s, void *arg)
{
    if (s->index < 5) {
        unsigned short val = data_020d1a54[s->index];
        return func_02082438(arg, &val);
    } else {
        return 0;
    }
}

int func_0209b044(UnkStruct_0209b044 *obj)
{
    unsigned int r;
    unsigned short v;

    if (obj->unk_0D != 0) {
        r = (unsigned int) func_0209b184((int) obj, obj->unk_0D);
        if (r < 5) {
            func_0209b160((unsigned char *) obj, r);
            obj->unk_0C = r;
            func_0209bb90(obj, 0);
            v = ((const unsigned short *) data_020d1a28)[func_020644cc(10) & 1];
            func_0209bb68(obj, &v);
            r = (unsigned int) func_0209b1f0((int) obj, obj->unk_0D);
            if ((r == 2 && (func_020644cc(10) & 1) != 0) || r == 1) {
                obj->unk_0D = 0;
            }
            return 1;
        }
        obj->unk_0D = 0;
    }
    return 0;
}

int func_0209af80(Func_0209af80_ObjA *a, Func_0209af80_ObjB *b)
{
    int v;
    int range;
    int ret;
    unsigned short t;
    unsigned short tmp;

    if (a->unk_0C >= 5) {
        goto fail;
    }

    v = func_020984e8();
    if (v == 0) {
        goto fail;
    }

    if (func_02094ffc(func_02099870(func_020984e8())) != 0) {
        goto fail;
    }

    if (((b->h & 0xF000) >> 12) != 0xD) {
        goto fail;
    }

    if (func_0209bd44(a) == 0) {
        goto fail;
    }

    if (func_0209bba0(a) != 0) {
        goto fail;
    }

    range = 0;
    if (b->h >= 0xD019 && b->h <= 0xD01C) {
        range = 1;
    }

    if (range != 0) {
        if (a->unk_0C != 0) {
            goto fail;
        }
        return 1;
    }

    t = data_020d1a54[a->unk_0C];

    if (func_0204bcdc(b) != 0) {
        tmp = t;
        ret = (func_0204bc64(b) == func_0204bc64(&tmp));
    } else {
        ret = (b->h == t);
    }

    if (ret == 0) {
        goto fail;
    }
    return 1;

fail:
    return 0;
}
