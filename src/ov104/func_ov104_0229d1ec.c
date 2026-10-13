/* func_ov104_0229d1ec @ 0x0229d1ec, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
} ObjB;
typedef struct {
    char pad_00[1];
} ObjA;

typedef struct {
    char pad_00[0xBD];
    unsigned char flag;
    char pad_BE[0x23E2];
    ObjB objB;
    ObjA objA;
} UnkStruct_0229d1ec;

extern int func_ov104_0229c364(void *self, int val);
extern int func_ov002_02208ae4(ObjA *a);
extern int func_ov002_02208ad8(ObjA *a, unsigned char b);
extern void func_ov002_0220a0b4(ObjB *a, int b, int c);
extern void func_ov002_0220a374(ObjB *a, int b);

void func_ov104_0229d1ec(UnkStruct_0229d1ec *self)
{
    int r4, r2;
    if (func_ov104_0229c364(self, 0x8000) != 0) {
        self->flag = 1;
    } else {
        self->flag = 0;
    }
    r4 = func_ov002_02208ae4(&self->objA);
    r2 = func_ov002_02208ad8(&self->objA, self->flag);
    func_ov002_0220a0b4(&self->objB, r4, r2);
    func_ov002_0220a374(&self->objB, 7);
}
