/* func_ov101_0229c330 @ 0x0229c330, 0xfc bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c330 {
    unsigned char pad_00[0xb3];
    unsigned char unk_B3;
} UnkStruct_0229c330;

typedef struct Object Object;

extern int func_ov002_022088ac(Object *obj);
extern int func_ov002_022088cc(Object *obj);
extern int func_ov002_0220889c(Object *obj);
extern int func_ov002_022088bc(Object *obj);
extern void func_ov002_0220a314(void *ptr);
extern void func_ov101_0229c29c(UnkStruct_0229c330 *self, int param);
extern int func_ov101_0229c2ac(UnkStruct_0229c330 *self, int param);

void func_ov101_0229c330(UnkStruct_0229c330 *self, Object *obj)
{
    int r4 = self->unk_B3;
    int r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(obj) != 0) {
        if (func_ov002_022088cc(obj) != 0) {
            if (r6 != 0) {
                goto common;
            }
        }
        // fall through to check_r4
    } else {
        goto else_branch;
    }

check_r4:
    if (r4 == 0) {
        self->unk_B3 = self->unk_B3 + 4;
        func_ov101_0229c29c(self, 8);
        goto common;
    } else {
        self->unk_B3 = self->unk_B3 - 1;
        goto common;
    }

else_branch:
    if (func_ov002_0220889c(obj) == 0) {
        goto common;
    }
    if (func_ov002_022088bc(obj) != 0) {
        goto common;
    }
    if (r4 == 4) {
        self->unk_B3 = self->unk_B3 - 4;
        func_ov101_0229c29c(self, 0x10);
        goto common;
    } else {
        self->unk_B3 = self->unk_B3 + 1;
    }

common:
    if (func_ov101_0229c2ac(self, 0x18) == 0) {
        if (func_ov002_022088cc(obj) != 0) {
            if (r6 > 0) {
                self->unk_B3 = self->unk_B3 - 5;
            }
        } else if (func_ov002_022088bc(obj) != 0) {
            if (r6 < 2) {
                self->unk_B3 = self->unk_B3 + 5;
            } else {
                self->unk_B3 = 0xf;
                func_ov002_0220a314((char *) self + 0x229c);
            }
        }
    }
}
