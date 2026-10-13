/* func_0205dec8 @ 0x0205dec8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0205dec8 *func_0205dde8(void *p);
extern void func_020b9ec4(struct UnkStruct_0205dec8 *p);
extern void func_020ba004(struct UnkStruct_0205dec8 *p);

struct UnkStruct_0205dec8 {
    unsigned char pad_00[13];
    unsigned char unk_0D;
};

void func_0205dec8(void *p)
{
    int flag;

    flag = (func_0205dde8(p)->unk_0D == 1) ? 1 : 0;
    if (flag != 0) {
        func_020b9ec4(func_0205dde8(p));
    } else {
        func_020ba004(func_0205dde8(p));
    }
}
