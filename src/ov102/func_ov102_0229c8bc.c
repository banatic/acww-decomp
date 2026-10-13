/* func_ov102_0229c8bc @ 0x0229c8bc, 0xf4 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c8bc {
    unsigned char pad_00[0x25a5];
    unsigned char unk_25A5;
};

extern void func_ov102_0229c298(struct UnkStruct_0229c8bc *, int);
extern int func_ov002_022088ac(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088bc(void *);

void func_ov102_0229c8bc(struct UnkStruct_0229c8bc *a, void *b, int c)
{
    int f;
    int cnt;

    f = a->unk_25A5;
    cnt = 0;
    while (f >= 5) {
        f -= 5;
        cnt++;
    }

    if (func_ov002_022088ac(b) == 0) {
        goto L922;
    }
    if (func_ov002_022088cc(b) != 0) {
        if (cnt != 0) {
            goto L968;
        }
    }
    if (f != 0) {
        goto L914;
    }

    if (c == 1) {
        a->unk_25A5 += 4;
    } else {
        a->unk_25A5 = 0x24;
    }
    func_ov102_0229c298(a, 0x10);
    return;

L914:
    a->unk_25A5--;
    f--;
    goto L968;

L922:
    if (func_ov002_0220889c(b) == 0) {
        goto L968;
    }
    if (func_ov002_022088bc(b) != 0) {
        goto L968;
    }
    if (f != 4) {
        goto L95c;
    }
    if (c == 1) {
        a->unk_25A5 -= 4;
        func_ov102_0229c298(a, 0x20);
        return;
    } else {
        a->unk_25A5 = 0x24;
        return;
    }

L95c:
    a->unk_25A5++;
    f++;
    goto L968;

L968:
    if (func_ov002_022088cc(b) == 0) {
        goto L98a;
    }
    if (cnt > 0) {
        a->unk_25A5 -= 5;
        return;
    } else {
        f += 25;
        a->unk_25A5 = f;
        return;
    }

L98a:
    if (func_ov002_022088bc(b) == 0) {
        return;
    }
    if (cnt >= 2) {
        return;
    }
    a->unk_25A5 += 5;
}
