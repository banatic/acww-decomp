/* func_020c34e4 @ 0x020c34e4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de8(void *ptr);
extern int func_02019e00(void *ptr);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;

struct UnkStruct_020c34e4 {
    char pad_00[0x564];
    char unk_564;
};

int func_020c34e4(struct UnkStruct_020c34e4 *self)
{
    if (func_02019de8(&self->unk_564) == 0) {
        goto done;
    }
    if (func_02019e00(&self->unk_564) != 2) {
        goto done;
    }
    func_02019d0c(&self->unk_564, 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
done:
    return 1;
}
