/* func_ov109_0229c330 @ 0x0229c330, 0xe8 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct Other Other;

struct UnkStruct_0229c330 {
    unsigned char pad_00[0x29d3];
    unsigned char unk_29D3;
};

extern int func_ov002_022088ac(Other *p);
extern int func_ov002_022088cc(Other *p);
extern int func_ov002_0220889c(Other *p);
extern int func_ov002_022088bc(Other *p);
extern void func_ov109_0229c29c(struct UnkStruct_0229c330 *s, int mode);
extern int func_ov109_0229c2ac(struct UnkStruct_0229c330 *s, int mode);
extern void func_ov002_0220a314(void *addr);

void func_ov109_0229c330(struct UnkStruct_0229c330 *self, Other *other)
{
    int field;
    int count;

    field = self->unk_29D3;
    count = 0;
    while (field >= 5) {
        field -= 5;
        count++;
    }

    if (func_ov002_022088ac(other)) {
        if (func_ov002_022088cc(other) && count != 0) {
            goto out;
        }
        if (field == 0) {
            self->unk_29D3 += 4;
            func_ov109_0229c29c(self, 8);
        } else {
            self->unk_29D3 -= 1;
        }
    } else if (func_ov002_0220889c(other) && !func_ov002_022088bc(other)) {
        if (field == 4) {
            self->unk_29D3 -= 4;
            func_ov109_0229c29c(self, 0x10);
        } else {
            self->unk_29D3 += 1;
        }
    }

out:
    if (func_ov109_0229c2ac(self, 0x18) != 0) {
        return;
    }

    if (func_ov002_022088cc(other)) {
        if (count > 0) {
            self->unk_29D3 -= 5;
        }
        return;
    }

    if (func_ov002_022088bc(other)) {
        if (count < 2) {
            self->unk_29D3 += 5;
        } else {
            self->unk_29D3 = 15;
            func_ov002_0220a314((char *) self + 0x2274);
        }
        return;
    }
}
