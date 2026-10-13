/* func_ov121_02299e80 @ 0x02299e80, 0x148 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct ObjTag {
    unsigned char pad_00[0xb1];
    unsigned char state;
} UnkStruct_02299e80;

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088bc(int);
extern void func_ov121_02299a4c(UnkStruct_02299e80 *, int);
extern int func_ov121_0229a038(UnkStruct_02299e80 *, int, int);
extern int func_ov121_0229a074(UnkStruct_02299e80 *, int, int);
extern int func_ov121_02299a5c(UnkStruct_02299e80 *, int);

int func_ov121_02299e80(UnkStruct_02299e80 *self, int p1, int p2)
{
    if (func_ov002_022088ac(p1) != 0) {
        if (self->state == 8) {
            self->state = 7;
            func_ov121_02299a4c(self, 0x20);
            goto tail;
        }
        if (self->state == 4 && p2 != 0) {
            self->state = 8;
            goto tail;
        }
        if (func_ov121_0229a038(self, 0, 3) != 0) {
            goto tail;
        }
        if (func_ov121_0229a038(self, 4, 7) != 0) {
            goto tail;
        }
        if (func_ov121_0229a038(self, 9, 11) != 0) {
            goto tail;
        }
        if (func_ov121_0229a038(self, 12, 15) != 0) {
            goto tail;
        }

        {
            unsigned char st = self->state;
            if (st > 0x10 && st <= 0x17) {
                (*(volatile unsigned char *) &self->state) = (unsigned char) ((*(volatile unsigned char *) &self->state) - 1);
            }
        }
        goto tail;
    } else {
        if (func_ov002_0220889c(p1) != 0) {
            if (self->state == 8) {
                self->state = 4;
                goto tail;
            }
            if (self->state == 7 && p2 != 0) {
                self->state = 8;
                func_ov121_02299a4c(self, 0x40);
                goto tail;
            }
            if (self->state == 0xb && func_ov002_022088bc(p1) != 0) {
                self->state = 0xf;
                return 1;
            }
            if (func_ov121_0229a074(self, 0, 3) != 0) {
                goto tail;
            }
            if (func_ov121_0229a074(self, 4, 7) != 0) {
                goto tail;
            }
            if (func_ov121_0229a074(self, 9, 11) != 0) {
                goto tail;
            }
            if (func_ov121_0229a074(self, 12, 15) != 0) {
                goto tail;
            }

            {
                unsigned char st = self->state;
                if (st >= 0x10 && st < 0x17) {
                    (*(volatile unsigned char *) &self->state) =
                        (unsigned char) ((*(volatile unsigned char *) &self->state) + 1);
                }
            }
            goto tail;
        }
    }
tail:
    return func_ov121_02299a5c(self, 0x60);
}
