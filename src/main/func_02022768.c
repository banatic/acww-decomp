/* func_02022768 @ 0x02022768, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202e118(void *dst, unsigned int src);
extern void func_02022bbc(void *p, int n, void *data);
extern unsigned char data_020c8af8[];

struct UnkStruct_02022768 {
    unsigned char pad_00[0x100];
    unsigned int unk_100;
};

int func_02022768(struct UnkStruct_02022768 *obj)
{
    unsigned short result;
    unsigned short b;
    unsigned short a;

    func_0202e118(&result, obj->unk_100);
    b = *(volatile unsigned short *) &result;
    a = *(volatile unsigned short *) &result;

    if (a == 0xfff1 || (b >= 0x1380 && b <= 0x139f)) {
        func_02022bbc(obj, 7, data_020c8af8);
        return 1;
    }
    return 0;
}
