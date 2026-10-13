/* func_ov114_0229c410 @ 0x0229c410, 0x1e4 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1280];
    int unk_1280;
    unsigned char pad_1284[0x1294 - 0x1284];
    int unk_1294;
    unsigned char pad_1298[0x12bc - 0x1298];
    unsigned char st;
    unsigned char unk_12BD;
} UnkStruct_0229c410;

extern const unsigned char data_ov114_0229da8c[];
extern const unsigned char data_ov114_0229da90[];

extern int func_ov002_0220889c(void *in);
extern int func_ov002_022088ac(void *in);
extern int func_ov002_022088bc(void *in);
extern int func_ov002_022088cc(void *in);
extern int func_ov114_0229c60c(UnkStruct_0229c410 *o);
extern int func_ov114_0229c370(UnkStruct_0229c410 *o);
extern int func_ov114_0229c690(UnkStruct_0229c410 *o);

int func_ov114_0229c410(UnkStruct_0229c410 *o, void *in)
{
    unsigned int st;
    unsigned int st2;
    int n;
    int v;

    if (in == 0) {
        return 0;
    }
    st = o->st;
    if (func_ov114_0229c60c(o) != -1) {
        if (func_ov002_022088bc(in) != 0) {
            o->st = 0;
        } else if (func_ov002_022088ac(in) != 0) {
            if (o->st > 5) {
                o->st = o->st - 1;
            }
        } else if (func_ov002_0220889c(in) != 0) {
            if (o->st < 0xc) {
                o->st = o->st + 1;
            }
        }
    } else {
        st2 = o->st;
        if (st2 <= 1) {
            if (func_ov002_022088cc(in) != 0) {
                o->st = o->unk_12BD;
            } else if (func_ov002_022088bc(in) != 0) {
                o->st = func_ov114_0229c370(o);
            } else if (func_ov002_022088ac(in) != 0) {
                o->st = 1;
            } else if (func_ov002_0220889c(in) != 0) {
                o->st = 0;
            }
        } else if (st2 >= 0xd) {
            n = st2 - 0xd;
            if (func_ov002_022088cc(in) != 0) {
                if (func_ov114_0229c690(o) < 0x48) {
                    o->st = 1;
                } else {
                    o->st = 0;
                }
            } else if (func_ov002_022088bc(in) != 0) {
                v = func_ov114_0229c690(o);
                if (v < 0x40) {
                    o->st = 2;
                } else if (v >= 0xc0) {
                    o->st = 3;
                } else {
                    o->st = 4;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                if (n < o->unk_1294 - 1) {
                    o->st = o->st + 1;
                    v = func_ov114_0229c690(o);
                    if (v > 0xe0) {
                        o->unk_1280 = v - 0xe0;
                    }
                }
            } else if (func_ov002_022088ac(in) != 0) {
                if (n > 0) {
                    o->st = o->st - 1;
                    v = func_ov114_0229c690(o);
                    if (v < 0x20) {
                        o->unk_1280 = v - 0x20;
                    }
                }
            }
        } else {
            n = st2 - 2;
            if (func_ov002_022088cc(in) != 0) {
                o->st = func_ov114_0229c370(o);
            } else if (func_ov002_022088ac(in) != 0) {
                o->st = data_ov114_0229da90[n];
            } else if (func_ov002_0220889c(in) != 0) {
                o->st = data_ov114_0229da8c[n];
            }
        }
    }
    if (st != o->st) {
        return 1;
    }
    return 0;
}
