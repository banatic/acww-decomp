/* func_ov104_0229dec0 @ 0x0229dec0, 0x50 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229dec0 {
    char pad_00[0x23b8];
    char unk_23B8[1];
    char pad_23B9[0x24a0 - 0x23b8 - 1];
    char unk_24A0[1];
    char pad_24A1[0x2504 - 0x24a0 - 1];
    char unk_2504[1];
} UnkStruct_0229dec0;

extern int func_ov002_0220909c(void *p);
extern void func_ov002_022096d8(void *p, int a);
extern int func_ov002_02207d24(void *p, int a);
extern int func_0208e4bc(void *p);
extern void func_ov104_0229d1b8(UnkStruct_0229dec0 *self);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov104_0229dec0(UnkStruct_0229dec0 *self)
{
    if (func_ov002_0220909c(&self->unk_2504[0]) != 0) {
        func_ov002_022096d8(&self->unk_2504[0], 0);
        func_ov002_02207d24(&self->unk_23B8[0], 1);
        if (func_0208e4bc(&self->unk_24A0[0]) != 0) {
            func_ov104_0229d1b8(self);
        }
        func_ov002_02208098((void *) (self), 0x18);
    }
}
