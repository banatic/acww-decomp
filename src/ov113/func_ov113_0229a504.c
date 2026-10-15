/* func_ov113_0229a504 @ 0x0229a504, 0x8a bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov113_02299c44(void *self, int a);
extern int func_ov113_02299da4(void *self, int a);
extern void func_02002708(int a);
extern void func_ov002_02207ee8(char *, int, int, int, int);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int a);
extern void func_ov113_02299df4(void *self, int a);

struct UnkStruct_0229a504 {
    unsigned char pad_00[0x9a];
    unsigned char unk_9A;
    unsigned char unk_9B;
};

void func_ov113_0229a504(struct UnkStruct_0229a504 *self)
{
    int v;

    switch (self->unk_9B) {
        case 1:
            func_ov113_02299c44(self, 0);
            // fall through
        case 4:
            v = 3;
            break;
        case 0:
            func_ov113_02299c44(self, 0);
            // fall through
        case 5:
            v = 2;
            break;
        default:
            if (func_ov113_02299da4(self, 0x40) == 0) {
                v = 2;
            } else {
                v = 3;
            }
            break;
    }

    func_ov002_02207ee8((char *) (self), 8, 6, v, 0x30);
    func_02002708(2);
    func_ov002_02207e80(self, 2, 0, 0);
    func_ov002_02208090(self, 8);
    func_ov113_02299df4(self, self->unk_9A);
}
