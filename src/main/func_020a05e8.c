/* func_020a05e8 @ 0x020a05e8, 0x260 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xef];
    unsigned char arr[4];
    unsigned char pad_F3[0x10e - 0xf3];
    unsigned char lo : 4;
    unsigned char hi : 4;
} UnkStruct_020a05e8;

extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a238c(UnkStruct_020a05e8 *s);
extern void func_0209fb54(void *p);
extern void func_020a2468(UnkStruct_020a05e8 *s);
extern void func_020a0b94(void *receiver);
extern void func_02088368(void);
extern int func_020a2120(UnkStruct_020a05e8 *s, int n);
extern int func_02073dd4(void *g, int i);
extern int func_02073918(void *g, int i);
extern void func_020a1224(UnkStruct_020a05e8 *s);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern unsigned short func_020740dc(void);
extern int func_02075aa4(int a, unsigned short b);
extern void func_0209fb4c(void *p);
extern void *data_020ccf94;
extern char data_021f3ba0[];

int func_020a05e8(UnkStruct_020a05e8 *self, unsigned char *state, int p2, int base, unsigned char p4, unsigned char p5, int p6,
                  unsigned char p7, int p8)
{
    unsigned char st;
    int r;
    void *gb;
    void *ga;

    st = *state;
    if (st == base) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a238c(self);
        if (r == 1) {
            *state = p4;
            goto end;
        }
        if (r == 3) {
            goto end;
        }
        func_0209fb54(data_021f3ba0);
        if (p7 != 0) {
            func_020a2468(self);
            func_020a0b94(self);
            func_02088368();
        }
        *state = base + 1;
        goto end;
    }
    if (st == base + 1) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120(self, self->hi);
        if (r == 1) {
            *state = p4;
            goto end;
        }
        if (r != 0) {
            goto end;
        }
        *state = base + 2;
        goto end;
    }
    if (st == base + 2) {
        int f;
        int i;
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        f = 1;
        i = 3;
        ga = data_020ccf94;
        for (; i >= 0; i--) {
            if (func_02073dd4(ga, i) == 0) {
                continue;
            }
            if (func_02073918(ga, i) != 0) {
                continue;
            }
            if (self->arr[i] == 0) {
                f = 0;
                break;
            }
            if (self->arr[i] == 2) {
                f = 2;
                break;
            }
        }
        if (f != 0) {
            if (p2 == 0) {
                f = 0;
            } else if (p2 == 2) {
                f = 2;
            }
        }
        if (f == 1) {
            func_020a1224(self);
            *state = base + 3;
            goto end;
        }
        if (f == 2) {
            *state = p5;
        }
        goto end;
    }
    if (st == base + 3) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        if ((func_02073044(), func_020ebf70()) == 0) {
            goto end;
        }
        if (func_02075aa4(1, func_020740dc()) == 0) {
            goto end;
        }
        func_0209fb4c(data_021f3ba0);
        *state = base + 4;
        goto end;
    }
    if (st == base + 4) {
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        r = func_020a2120(self, self->hi);
        if (r == 1) {
            *state = p4;
            goto end;
        }
        if (r != 0) {
            goto end;
        }
        *state = base + 5;
        goto end;
    }
    if (st == base + 5) {
        int f;
        int i;
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        f = 1;
        i = 3;
        gb = data_020ccf94;
        for (; i >= 0; i--) {
            if (func_02073dd4(gb, i) == 0) {
                continue;
            }
            if (func_02073918(gb, i) != 0) {
                continue;
            }
            if (self->arr[i] == 0) {
                f = 0;
                break;
            }
            if (self->arr[i] == 2) {
                f = 2;
                break;
            }
        }
        if (f == 1) {
            *state = base + 6;
            goto end;
        }
        if (f == 2) {
            *state = p5;
        }
        goto end;
    }
    if (st == base + 6) {
        unsigned short m;
        if (func_02073fdc(p8) != 0) {
            func_02074078();
            return 0x20;
        }
        m = func_020740dc();
        if (p6 < 4) {
            m = (unsigned short) (m | (1 << p6));
        }
        if (func_02075aa4(1, m) != 0) {
            *state = base + 7;
        }
    }
end:
    return 0x20;
}
