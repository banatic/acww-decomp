/* func_0205d084 @ 0x0205d084, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_0205d084 *func_0205cfac(void *);
extern void func_020b9ec4(struct UnkStruct_0205d084 *);
extern void func_020ba004(struct UnkStruct_0205d084 *);

struct UnkStruct_0205d084 {
    char pad_00[0xD];
    unsigned char unk_0D;
};

void func_0205d084(void *arg)
{
    int cond = (func_0205cfac(arg)->unk_0D == 1);
    if (cond) {
        func_020b9ec4(func_0205cfac(arg));
    } else {
        func_020ba004(func_0205cfac(arg));
    }
}
