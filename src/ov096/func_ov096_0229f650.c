/* func_ov096_0229f650 @ 0x0229f650, 0x10c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f820(void *, int);
extern int func_ov096_0229f150(void *, int);
extern int func_ov096_0229f830(void *, int);
extern unsigned short func_ov096_0229f0dc(void *, int);
extern int func_ov096_0229f088(void *, int);
extern void func_ov096_0229defc(void *, void *, unsigned char, unsigned short *, int);
extern void func_ov096_0229f5e0(void *, unsigned char, unsigned short, int);
extern void func_ov096_0229e898(void *, int, int);
extern int func_ov096_0229e71c(void *);
extern void func_ov096_0229e29c(void *);
extern void func_ov096_0229e67c(void *);
extern int func_ov096_0229e1ec(void *);
extern void func_ov096_0229c348(void *);

typedef struct {
    unsigned char pad_00[0xac];
    unsigned char unk_AC;
    unsigned char pad_AD[3];
    unsigned char unk_B0;
    unsigned char pad_B1[3];
    unsigned char unk_B4;
    unsigned char pad_B5[11];
    unsigned char unk_C0;
} UnkStruct_0229f650;

int func_ov096_0229f650(UnkStruct_0229f650 *self, int arg)
{
    unsigned short tmp;

    if (func_ov096_0229f820(self, arg) != 0 && func_ov096_0229f150(self, arg) != 0) {
        return 0;
    }

    if (func_ov096_0229f830(self, arg) != 0 || func_ov096_0229f820(self, arg) != 0) {
        tmp = func_ov096_0229f0dc(self, arg);
        func_ov096_0229defc(self, &self->unk_AC, self->unk_B0, &tmp, func_ov096_0229f088(self, arg));

        if (tmp != 0xfff1) {
            func_ov096_0229f5e0(self, self->unk_B4, tmp, func_ov096_0229f088(self, arg));
        }
        func_ov096_0229e898(self, arg, 1);
        return 1;
    }

    if ((unsigned char) (arg + 0xde) <= 1) {
        if (func_ov096_0229e71c(self) != 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (arg == 0x24) {
            if (self->unk_C0 < 1) {
                func_ov096_0229e29c(self);
                return 0;
            } else {
                func_ov096_0229e67c(self);
                return 1;
            }
        } else if (arg == 0x25) {
            if (func_ov096_0229e1ec(self) == 0) {
                func_ov096_0229e898(self, self->unk_B4, 1);
            }
            return 1;
        } else if (arg == 0x21) {
            func_ov096_0229c348(self);
            return 1;
        } else {
            return 0;
        }
    }
}
