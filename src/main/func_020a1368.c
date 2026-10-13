/* func_020a1368 @ 0x020a1368, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc4];
    int value;
} UnkStruct_020a1368;

extern UnkStruct_020a1368 *data_021f3c3c;

int func_020a1368(void)
{
    if (data_021f3c3c == 0) {
        return 0;
    }
    return data_021f3c3c->value;
}
