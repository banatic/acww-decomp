/* func_020f3cd4 @ 0x020f3cd4, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f3fe0(void *unused0);
extern void func_020f65bc(int, int);

struct UnkStruct_020f3cd4 {
    const char *vtbl;
    unsigned char flag;
};

struct UnkStruct_020f3cd4_2 {
    char pad_00[0x30];
    int flag;
};

extern const char data_0213ec40[];
extern const struct UnkStruct_020f3cd4_2 data_021fd1bc;

struct UnkStruct_020f3cd4 *func_020f3cd4(struct UnkStruct_020f3cd4 *this)
{
    int flag;

    func_020f3fe0(this);
    this->vtbl = data_0213ec40;
    flag = data_021fd1bc.flag;
    if (flag != 0) {
        func_020f65bc(flag, 0xd1);
    }
    this->flag = 3;
    return this;
}
