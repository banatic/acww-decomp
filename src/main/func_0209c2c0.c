/* func_0209c2c0 @ 0x0209c2c0, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma pack(1)
typedef struct {
    unsigned char pad_00[0x21];
    unsigned char flag : 1;
} UnkStruct_0209c2c0;
#pragma pack()

int func_0209c2c0(UnkStruct_0209c2c0 *s)
{
    if (s->flag) {
        return 1;
    } else {
        return 0;
    }
}
