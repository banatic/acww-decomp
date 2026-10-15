/* func_0203e258 @ 0x0203e258, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203e258 {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
};

extern int func_0203e4c0(unsigned char);
extern struct UnkStruct_0203e258 *data_021c72b8;

int func_0203e258(unsigned char argument0)
{
    if (func_0203e4c0((unsigned char) argument0) && data_021c72b8->unk_16 != 6) {
        return 1;
    } else {
        return 0;
    }
}
