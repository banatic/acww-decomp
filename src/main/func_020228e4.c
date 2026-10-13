/* func_020228e4 @ 0x020228e4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202e118(void *dst, unsigned int src);
extern void func_02022bbc(void *p, int n, void *data);
extern unsigned char data_020c8a68[];

struct UnkStruct_020228e4 {
    unsigned char pad_00[0x100];
    unsigned int unk_100;
};

int func_020228e4(struct UnkStruct_020228e4 *obj)
{
    unsigned short result;
    unsigned short b;
    unsigned short a;

    func_0202e118(&result, obj->unk_100);
    b = *(volatile unsigned short *) &result;
    a = *(volatile unsigned short *) &result;

    if (a == 0xfff1 || (b >= 0x1380 && b <= 0x139f)) {
        func_02022bbc(obj, 4, data_020c8a68);
        return 1;
    }
    return 0;
}
