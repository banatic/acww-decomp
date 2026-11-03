/* friend_roster_input_2: 11 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229b5a8 @ 0x0229b5a8, 0x220 bytes, Thumb
 * func_ov119_0229b510 @ 0x0229b510, 0x98 bytes, Thumb
 * func_ov119_0229b49c @ 0x0229b49c, 0x74 bytes, Thumb
 * func_ov119_0229b450 @ 0x0229b450, 0x4c bytes, Thumb
 * func_ov119_0229b408 @ 0x0229b408, 0x48 bytes, Thumb
 * func_ov119_0229b3dc @ 0x0229b3dc, 0x2a bytes, Thumb
 * func_ov119_0229b38c @ 0x0229b38c, 0x4e bytes, Thumb
 * func_ov119_0229b284 @ 0x0229b284, 0x108 bytes, Thumb
 * func_ov119_0229b248 @ 0x0229b248, 0x3c bytes, Thumb
 * func_ov119_0229b188 @ 0x0229b188, 0xc0 bytes, Thumb
 * func_ov119_0229b0f8 @ 0x0229b0f8, 0x90 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0xa0];
    volatile unsigned char st;
    unsigned char pad_A1[0xaf - 0xa1];
    volatile unsigned char af;
} UnkStruct_0229b5a8;

typedef struct {
    u8 pad_00[0x9a];
    u16 unk_9A;
    u8 pad_9C;
    u8 unk_9D;
    u8 pad_9E[2];
    u8 unk_A0;
    u8 pad_A1[0x0f];
    u8 unk_B0;
    u8 unk_B1;
} State;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov002_02209eec(void *p);
extern int func_ov002_02209f00(void *p);
extern struct UnkStruct_0229b510 {
    char pad_00[0x64];
    int count;
} *data_020ccf94;
extern void func_ov002_02208d30(void *addr, int val);
extern int func_02073d90(void *arg);
extern void *func_02094fd4(void *buf);
extern int func_020984fc(int idx);
extern int func_02099870(int object);
extern void *func_02095074(int a, void *buf);
extern int func_ov002_02208ccc(void *a, void *b, void *c, unsigned char d);
extern void *func_02094fbc(void *buf);
extern int func_ov002_02208d4c(void *addr, int a, int b);
extern void func_ov119_0229a50c(void *p, int flag);
extern int func_ov119_0229ae28(void *obj);
extern void *func_02077c3c(void *object);
extern int func_02077d6c(void *friend_data);
extern void func_ov119_0229a410(void *ptr, int value);
extern void func_02077c40(int x);
extern void func_ov119_0229a714(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern int func_ov119_0229ae10(void *self);
extern void func_0206fc80(unsigned char c);
extern int func_ov119_0229c608(int a, int b);
extern void func_ov119_0229c5f4(int a);
extern int func_ov119_0229ac80(void *receiver);
extern void func_ov119_0229bba8(int, int);
extern void *func_ov119_0229ae50(void *receiver);
extern int func_02099664(int arg);
extern int func_02077bc8(int arg);
extern int func_ov119_0229ac3c(void *self, int arg);
extern int func_02077ea4(int a, int b);
extern int func_020950a8(int arg);
extern int func_02077c38(char *elem);
extern void func_02051c08(int a, int b, int c);
extern int func_02095040(int arg);
extern int func_020642a4(int arg);
extern int func_02077c34(char *elem);
extern int func_020ee45c(void *self);
extern void func_ov090_02298fa4(int arg);
extern int func_ov119_0229ae68(void *receiver);
extern int func_02077d68(int arg);
extern int func_020eaf48(int a, int b);
extern void func_ov119_0229adc4(void *self);
extern int func_ov119_0229a650(void *self, void *other);
extern void func_ov119_0229a69c(void *self, int r);
extern void func_ov119_0229bbe4(void *self);
extern void func_0200467c(int cmd);
extern int func_02088d9c(u8 *p);
extern int func_02088d94(u8 *p);
extern u8 *data_ov119_0229cca8[];

void func_ov119_0229b248(void *self, void *other);

int func_ov119_0229b5a8(UnkStruct_0229b5a8 *o, void *in)
{
    unsigned int st;
    int v;
    int n;

    st = o->st;
    if (in == 0) {
        return 0;
    }
    if (st <= 7) {
        if (func_ov002_022088bc(in) != 0) {
            if (o->st + 1 < o->af) {
                o->st = o->st + 1;
            }
        } else if (func_ov002_022088cc(in) != 0) {
            if (o->st != 0) {
                o->st = o->st - 1;
            } else {
                o->st = 0x14;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            v = func_ov002_02209eec((char *) o + 0xda8);
            if (v > 0x94) {
                o->st = 0x16;
            } else {
                v = v - 0x35;
                if (v < 0) {
                    v = 0;
                }
                v = v >> 4;
                if (v >= 6) {
                    v = 5;
                }
                o->st = v + 8;
            }
        }
    } else if (st >= 0xe && st <= 0x15) {
        if (func_ov002_022088ac(in) != 0) {
            if (o->st > 0xe) {
                o->st = o->st - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st < 0x15) {
                o->st = o->st + 1;
            }
        } else if (func_ov002_022088bc(in) != 0) {
            v = func_ov002_02209f00((char *) o + 0xda8);
            if (o->af != 0 && v < 0x80) {
                o->st = 0;
            } else {
                o->st = 8;
            }
        }
    } else if (st >= 8 && st <= 0xd) {
        if (func_ov002_022088cc(in) != 0) {
            if (o->st > 8) {
                o->st = o->st - 1;
            } else {
                o->st = 0x14;
            }
        } else if (func_ov002_022088bc(in) != 0) {
            if (o->st < 0xd) {
                o->st = o->st + 1;
            } else {
                o->st = 0x16;
            }
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->af != 0) {
                v = func_ov002_02209eec((char *) o + 0xda8) - 0x30;
                if (v < 0) {
                    v = 0;
                }
                v = v >> 4;
                n = o->af;
                if (v >= n) {
                    v = n - 1;
                }
                o->st = v;
            }
        }
    } else if (st == 0x16) {
        if (func_ov002_022088cc(in) != 0) {
            o->st = 0xd;
        }
        if (func_ov002_022088ac(in) != 0) {
            n = o->af;
            if (n != 0) {
                o->st = n - 1;
            }
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}

void func_ov119_0229b510(void *p)
{
    char sp[0x24];
    int i;
    struct UnkStruct_0229b510 *ptr;
    int count;

    *(unsigned char *) ((char *) p + 0xB0) = 7;
    func_ov002_02208d30((char *) p + 0x4c4, 0xA);

    ptr = data_020ccf94;
    if (func_02073d90(ptr) != 0) {
        count = ptr->count;
        i = 0;
        func_02094fd4(sp);
        for (; i < 4; i++) {
            int object;
            if (count == i) {
                continue;
            }
            if ((object = func_020984fc(i)) == 0) {
                continue;
            }
            {
                int ret = func_02099870(object);
                func_02095074(ret, sp);
                func_ov002_02208ccc((char *) p + 0xDC, (char *) p + 0x4c4, sp, (unsigned char) (i + 6));
            }
        }
        func_02094fbc(sp);
    }

    func_ov002_02208d4c((char *) p + 0x4c4, 0xCE, 5);
    func_ov002_02208d4c((char *) p + 0x4c4, 2, 0xA);
    func_ov119_0229a50c(p, 0);
}

void func_ov119_0229b49c(void *obj)
{
    void *object;

    func_ov002_02208d30((char *) obj + 0x4c4, 0xa);
    func_ov002_02208d4c((char *) obj + 0x4c4, 0xcf, 3);
    func_ov002_02208d4c((char *) obj + 0x4c4, 0xd0, 2);
    if ((object = (void *) func_ov119_0229ae28(obj))) {
        object = func_02077c3c(object);
        if (func_02077d6c(object) == 0) {
            func_ov002_02208d4c((char *) obj + 0x4c4, 0xd1, 4);
        }
    }
    func_ov002_02208d4c((char *) obj + 0x4c4, 0xd2, 0);
    func_ov002_02208d4c((char *) obj + 0x4c4, 2, 0xa);
    func_ov119_0229a50c(obj, 0);
}

void func_ov119_0229b450(char *obj)
{
    func_ov002_02208d30(obj + 0x4c4, 0xa);
    func_ov002_02208d4c(obj + 0x4c4, 0xd3, 0xa);
    func_ov002_02208d4c(obj + 0x4c4, 4, 1);
    func_ov002_02208d4c(obj + 0x4c4, 0x13, 0xa);
    func_ov119_0229a50c(obj, 1);
    func_ov119_0229a410(obj, 0x10);
}

void func_ov119_0229b408(void *self)
{
    int r = func_ov119_0229ae28(self);
    if (r != 0) {
        func_02077c40(r);
        *(short *) ((char *) self + 0x9a) = -1;
        func_ov119_0229a410(self, 2);
        func_ov119_0229a714(self);
        *((char *) self + 0xb1) = 1;
        func_ov002_02208098(self, 9);
        *((char *) self + 0xb4) = (char) func_ov119_0229ae10(self);
    }
}

void func_ov119_0229b3dc(int a, int b)
{
    unsigned char c;
    c = (unsigned char) func_ov119_0229ae10((void *) a);
    func_0206fc80(c);
    func_ov119_0229c608(a, b);
    func_ov119_0229c5f4(a);
}

void func_ov119_0229b38c(int param)
{
    int idx = func_ov119_0229ac80((void *) param);
    if (idx == -1) {
        func_ov119_0229bba8(param, 0x13);
    } else {
        char *base;
        base = func_ov119_0229ae50((void *) param);
        func_02077c40((int) (base + 0x24 * idx));
        func_0206fc80((unsigned char) idx);
        func_ov119_0229c608(param, 0xe);
        func_ov119_0229c5f4(param);
    }
}

void func_ov119_0229b284(void *self)
{
    int tmp, sp4, sp8, spC, sp10;
    int r4;
    char *r6;
    char *r7;

    r4 = func_ov119_0229ac80((void *) self);
    if (r4 == -1) {
        func_ov119_0229bba8((int) self, 0x13);
        return;
    }

    tmp = func_020984fc(((unsigned char *) self)[0xad] - 6);
    if (func_ov119_0229ac3c(self, func_02077bc8(func_02099664(tmp)))) {
        func_ov119_0229bba8((int) self, 0x14);
        return;
    }

    r6 = func_ov119_0229ae50((void *) self);
    sp4 = func_02099870(tmp);
    r7 = r6 + r4 * 0x24;
    sp8 = (int) func_02077c3c((void *) r7);
    func_02077ea4(sp8, func_02077bc8(func_02099664(tmp)));
    spC = func_020950a8(sp4);
    func_02051c08(spC, func_02077c38(r7), 6);
    sp10 = func_020642a4(func_02095040(sp4));
    func_02051c08(sp10, func_02077c34(r7), 6);

    func_ov090_02298fa4(func_020ee45c(self));

    ((unsigned char *) self)[0xb4] = (unsigned char) r4;

    if (func_ov119_0229ae68(self) != 0) {
        if (func_020eaf48(((unsigned char *) self)[0xb4],
                          func_02077d68((int) func_02077c3c((void *) (r6 + ((unsigned char *) self)[0xb4] * 0x24)))) == 0) {
            func_ov002_02208098(self, 0x10);
            return;
        }
    }

    func_ov119_0229b248(self, (void *) r4);
}

void func_ov119_0229b248(void *self, void *other)
{
    int r;
    func_ov119_0229adc4(self);
    r = func_ov119_0229a650(self, other);
    if (r != ((unsigned char *) self)[0x9d]) {
        func_ov119_0229a69c(self, r);
    } else {
        func_ov119_0229a714(self);
    }
    func_ov119_0229bbe4(self);
}

int func_ov119_0229b188(State *p)
{
    u8 v = p->unk_A0;

    if (v >= 14 && v <= 21) {
        if (func_ov119_0229c608((int) p, v - 14) != 0) {
            return 1;
        } else {
            return 0;
        }
    }
    if (v >= 8 && v <= 13) {
        u8 r = v - 8;
        if (r != p->unk_9D) {
            p->unk_9D = r;
            func_ov002_02208098(p, 14);
            if (r == 4) {
                func_0200467c(0xf);
            } else {
                func_0200467c(0xb);
            }
            return 1;
        } else {
            return 0;
        }
    }
    if (v == 22) {
        p->unk_B0 = 8;
        p->unk_B1 = 3;
        func_ov002_02208098(p, 8);
        func_0200467c(0x2b);
        return 1;
    }
    if (v <= 7) {
        p->unk_9A = v;
        func_ov119_0229a410(p, 4);
        p->unk_B1 = 3;
        func_ov002_02208098(p, 8);
        func_0200467c(0x2b);
        return 1;
    }
    return 0;
}

int func_ov119_0229b0f8(u8 *self, int x, int y)
{
    int i;
    int t;

    t = func_02088d9c(data_ov119_0229cca8[0] + 8) + 0x83;
    if (t <= x) {
        t += 0x22;
        if (t >= x) {
            for (i = 0; i < 6; i++) {
                t = func_02088d94(data_ov119_0229cca8[i] + 8) + 0x61;
                if (t <= y) {
                    t += 0x12;
                    if (t >= y) {
                        i += 8;
                        return (u8) i;
                    }
                }
            }
        }
    }
    if (x >= 0x18 && x <= 0xc0 && y >= 0x30 && y < 0xb0) {
        int k = (y - 0x30) >> 4;
        if (k < self[0xaf]) {
            return (u8) k;
        }
    }
    if (x >= 0xc3 && x <= 0xf3 && y >= 0x9f && y <= 0xb5) {
        return 0x16;
    }
    return 0x17;
}
