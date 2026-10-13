/* func_0207d608 @ 0x0207d608, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207ffa0(void *p, int shift);

struct UnkStruct_0207d608 {
    char pad_00[0x7d0];
    unsigned short unk_7D0;
};

int func_0207d608(void *p, int shift)
{
    if (func_0207ffa0(p, shift) && (((struct UnkStruct_0207d608 *) p)->unk_7D0 >> shift) & 1) {
        return 1;
    } else {
        return 0;
    }
}
