/* func_020127ac @ 0x020127ac, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_020127ac {
    char pad_00[4];
    int unk_04;
    char pad_08[4];
    volatile int unk_0C;
    volatile int unk_10;
};
struct UnkStruct_020127ac_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

extern void func_0204f818(int *a, int *b, struct UnkStruct_020127ac_2 *obj);
extern void func_0204f794(struct UnkStruct_020127ac_2 *obj, int a, int b);
extern int func_020644cc(int);
extern void func_02012a98(struct UnkStruct_020127ac *self, struct UnkStruct_020127ac_2 *obj);
extern void func_02013910(struct UnkStruct_020127ac *self);
extern int func_02013518(struct UnkStruct_020127ac *self, struct UnkStruct_020127ac_2 *obj);

int func_020127ac(struct UnkStruct_020127ac *self, struct UnkStruct_020127ac_2 *obj)
{
    int a = 0;
    int b = 0;
    int fc;
    int f10;
    int g10;
    int x;

    func_0204f818(&a, &b, obj);
    fc = self->unk_0C;
    x = a;
    if (x == fc) {
        f10 = self->unk_10;
        if (b >= f10) {
            f10 = f10 + 1;
            if (b <= f10) {
                func_0204f794(obj, self->unk_0C, self->unk_10);
                goto done;
            }
        }
    }
    if (x >= fc - 3 && x <= fc + 4) {
        g10 = self->unk_10;
        if (b >= g10) {
            g10 = g10 + 5;
            if (b <= g10) {
                a = fc;
                b = self->unk_10 + func_020644cc(2);
                func_0204f794(obj, a, b);
                goto done;
            }
        }
    }
    func_02012a98(self, obj);
done:
    func_02013910(self);
    if (func_02013518(self, obj) != 0) {
        self->unk_04 = 2;
        return 1;
    }
    return 0;
}
