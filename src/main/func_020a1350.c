/* func_020a1350 @ 0x020a1350, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xC8];
    int value;
} UnkStruct_021f3c3c;

extern UnkStruct_021f3c3c *data_021f3c3c;

int func_020a1350(void)
{
    if (data_021f3c3c == 0) {
        return 0;
    }
    return data_021f3c3c->value;
}
