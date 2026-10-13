/* func_ov071_02279290 @ 0x02279290, 0x50 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern void func_02013c04(void *p);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;

typedef struct {
    unsigned char pad_00[0x72c];
    int unk_72C;
} UnkStruct_02279290;

int func_ov071_02279290(UnkStruct_02279290 *self)
{
    func_02013c04((char *) self + 0x558);
    func_02019d0c((char *) self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    self->unk_72C = 0x28;
    return 1;
}
