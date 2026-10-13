/* func_ov105_0229c9ac @ 0x0229c9ac, 0xe0 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern void func_ov105_0229c330(void *, int);
extern int func_ov105_0229c340(void *, int);
extern int func_ov105_0229d76c(void *, unsigned char);
extern void func_ov002_0220a314(void *);

void func_ov105_0229c9ac(unsigned char *self, void *other, int param)
{
    int t = self[0x2ba] - 0x1a;
    int k = t >> 1;

    if (!func_ov002_022088ac(other)) {
        goto L3;
    }

    // func_022088ac succeeded
    if ((t & 1) <= 0) {
        goto L2;
    }
    self[0x2ba] -= 1;
    goto Lcommon;

L2:
    self[0x2ba] = (unsigned char) (k * 5 + 0x28);
    goto Lend;

L3:
    if (!func_ov002_0220889c(other)) {
        goto Lcommon;
    }
    if ((t & 1) >= 1) {
        goto L4;
    }
    self[0x2ba] += 1;
    goto Lcommon;

L4:
    self[0x2ba] = (unsigned char) (k * 5 + 0x24);
    func_ov105_0229c330(self, 0x20);
    goto Lend;

Lcommon:
    if (func_ov105_0229d76c(self, self[0x2ba]) == 0) {
        goto Lend;
    }
    if (func_ov105_0229c340(self, 0x30) != 0) {
        goto Lend;
    }
    if (func_ov002_022088cc(other) != 0) {
        if (k <= 0) {
            goto Lend;
        }
        self[0x2ba] -= 2;
        goto Lend;
    } else {
        if (func_ov002_022088bc(other) == 0) {
            goto Lend;
        }
        if (k >= 4) {
            goto L5;
        }
        self[0x2ba] += 2;
        goto Lend;
    }
L5:
    if (param != 0) {
        goto Lend;
    }
    self[0x2ba] = 0x3d;
    func_ov002_0220a314(self + 0x24a4);
Lend:
    return;
}
