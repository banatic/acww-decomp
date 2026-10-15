/* func_ov053_022612a4 @ 0x022612a4, 0x10c bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x618];
    char unk_618;
    char pad_619[0x654 - 0x619];
    int unk_654;
    char unk_658;
    char pad_659[0x71b - 0x659];
    char unk_71B;
} UnkStruct_022612a4;

extern int func_020e8858(void *p);
extern void func_02035624(int a);
extern int func_02014868(void *p);
extern void func_0208b514(unsigned int context);
extern int func_ov053_02260ba8(void *p);
extern void func_ov053_02261524(UnkStruct_022612a4 *self, int a);
extern int func_ov053_02260488(void *receiver);
extern void func_ov053_02260bb0(void *p, int a);
extern int func_020960f8(int a, int b);
extern int func_ov004_0222c070(int a);
extern int func_0203e020(UnkStruct_022612a4 *self);
extern void *func_020b5e10(void);
extern int func_020b6098(void *h, int a);
extern int func_0203b144(void);

int func_ov053_022612a4(UnkStruct_022612a4 *self)
{
    int old;

    if (func_020e8858(&self->unk_71B) == 1) {
        func_02035624(0xe);
    }
    if (func_02014868(&self->unk_618) == 0) {
        old = self->unk_654;
        func_0208b514(0x654);
        if (func_ov053_02260ba8(&self->unk_658) == 4 || func_ov053_02260ba8(&self->unk_658) == 3) {
            func_ov053_02261524(self, 7);
        } else if (func_ov053_02260ba8(&self->unk_658) == 5 && func_ov053_02260488(self) != 0) {
            func_ov053_02260bb0(&self->unk_658, 9);
            func_ov053_02261524(self, 6);
            return 1;
        } else if (func_020960f8(0x28, 4) != 0) {
            if (func_ov004_0222c070(0) != 0) {
                func_0203e020(self);
                func_ov053_02261524(self, 3);
            }
        } else if (func_ov053_02260ba8(&self->unk_658) == 0xa) {
            if (func_02014868(&self->unk_618) == 0) {
                func_020b6098(func_020b5e10(), 0);
                func_ov053_02261524(self, 3);
            }
        } else {
            func_0203e020(self);
            func_ov053_02261524(self, 3);
        }
        if (old != self->unk_654 && func_ov053_02260ba8(&self->unk_658) == 5) {
            func_0203b144();
        }
    }
    return 1;
}
