/* func_ov110_0229c7f0 @ 0x0229c7f0, 0x104 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xf5];
    unsigned char unk_F5;
} UnkStruct_0229c7f0;

extern int func_ov002_022088ac(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088bc(void *);
extern void func_ov110_0229c2b8(UnkStruct_0229c7f0 *, int);

void func_ov110_0229c7f0(UnkStruct_0229c7f0 *p, void *q, int mode)
{
    int r4;
    int r6;

    r4 = p->unk_F5;
    r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(q)) {
        if (func_ov002_022088cc(q) && r6 != 0) {
            goto later;
        }
        if (r4 == 0) {
            if (mode == 1) {
                p->unk_F5 += 4;
            } else {
                p->unk_F5 = 30;
            }
            func_ov110_0229c2b8(p, 16);
            goto end;
        } else {
            p->unk_F5--;
            r4--;
            goto later;
        }
    } else {
        if (func_ov002_0220889c(q) == 0 || func_ov002_022088bc(q) != 0) {
            goto later;
        }
        if (r4 == 4) {
            if (mode == 1) {
                p->unk_F5 -= 4;
                func_ov110_0229c2b8(p, 32);
                goto end;
            } else {
                p->unk_F5 = 30;
                goto end;
            }
        } else {
            p->unk_F5++;
            r4++;
        }
    }

later:
    if (func_ov002_022088cc(q)) {
        if (r6 > 0) {
            p->unk_F5 -= 5;
        } else {
            r4 += 25;
            p->unk_F5 = r4;
        }
    } else {
        if (func_ov002_022088bc(q) && r6 < 2) {
            p->unk_F5 += 5;
        }
    }

end:
    return;
}
