/* func_020983c8 @ 0x020983c8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Func020983C8Data {
    char pad_00[0x40];
    unsigned int value;
};

extern struct Func020983C8Data data_021ef8a8;

void func_020983c8(int arg)
{
    if (arg > 0x3b9ac9ff) {
        arg = 0x3b9ac9ff;
    }
    data_021ef8a8.value = arg;
}
