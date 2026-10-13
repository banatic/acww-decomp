/* func_ov115_0229e384 @ 0x0229e384, 0x24 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1428];
    unsigned short unk_1428;
} Func225E384Struct;

extern void func_ov114_0229d8d0(void *p, int a, int b, int c, int d);

void func_ov115_0229e384(Func225E384Struct *obj)
{
    obj->unk_1428 = 0;
    func_ov114_0229d8d0((char *) obj + 0xf8, 3, 6, 4, 0);
}
