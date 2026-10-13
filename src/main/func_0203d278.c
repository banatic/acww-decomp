/* func_0203d278 @ 0x0203d278, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203d278 {
    unsigned char pad_00;
    unsigned char flag : 1;
};
int func_0203d278(struct UnkStruct_0203d278 *p)
{
    if (p->flag) {
        return 1;
    } else {
        return 0;
    }
}
