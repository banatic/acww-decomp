/* func_ov113_02299644 @ 0x02299644, 0x268 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9b];
    volatile unsigned char st;
    unsigned char pad_9C;
    volatile unsigned char unk_9D;
    volatile unsigned char unk_9E;
} UnkStruct_02299644;

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern void func_ov113_02299d94(UnkStruct_02299644 *o, int n);
extern int func_ov002_02209f3c(void *p);
extern void func_0200467c(int n);

int func_ov113_02299644(UnkStruct_02299644 *o, void *in)
{
    unsigned int st;
    int v;
    int n;
    int m;

    st = o->st;
    if (st <= 3) {
        if (func_ov002_022088ac(in) != 0) {
            if (o->st != 0) {
                o->st = o->st - 1;
            } else {
                o->st = 3;
                func_ov113_02299d94(o, 0x10);
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st < 3) {
                o->st = o->st + 1;
            } else {
                o->st = 0;
                func_ov113_02299d94(o, 0x20);
            }
        } else if (func_ov002_022088cc(in) != 0) {
            m = o->unk_9E + 0x44;
            v = func_ov002_02209f3c((char *) o + 0x2b20) - m;
            if (v < 0) {
                v = 0;
            }
            n = v >> 3;
            m = o->unk_9D;
            if (n >= m) {
                n = m - 1;
            }
            o->st = n + 6;
        }
    } else if (st == 5) {
        if (func_ov002_022088bc(in) != 0) {
            o->st = 6;
        } else if (func_ov002_022088ac(in) != 0) {
            o->st = 4;
            func_ov113_02299d94(o, 0x10);
        } else if (func_ov002_0220889c(in) != 0) {
            o->st = 4;
        }
    } else if (st == 4) {
        if (func_ov002_022088bc(in) != 0) {
            o->st = o->unk_9D + 5;
        } else if (func_ov002_022088ac(in) != 0) {
            o->st = 5;
        } else if (func_ov002_0220889c(in) != 0) {
            o->st = 5;
            func_ov113_02299d94(o, 0x20);
        }
    } else if (st <= 0x14) {
        if (func_ov002_022088cc(in) != 0) {
            if (func_ov002_0220889c(in) != 0 ||
                (func_ov002_02209f3c((char *) o + 0x2b20) > 0x80 && func_ov002_022088ac(in) == 0)) {
                o->st = 4;
            } else {
                o->st = 5;
            }
        } else if (func_ov002_022088bc(in) != 0) {
            if (func_ov002_0220889c(in) != 0 ||
                (func_ov002_02209f3c((char *) o + 0x2b20) > 0x80 && func_ov002_022088ac(in) == 0)) {
                o->st = 2;
            } else {
                o->st = 1;
            }
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->st > 6) {
                o->st = o->st - 1;
                func_ov113_02299d94(o, 0x80);
                func_0200467c(0xb);
            } else {
                o->st = 5;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st + 1 < o->unk_9D + 6) {
                o->st = o->st + 1;
                func_ov113_02299d94(o, 0x80);
                func_0200467c(0xb);
            } else {
                o->st = 4;
            }
        }
    }
    if (o->st != st) {
        return 1;
    }
    return 0;
}
