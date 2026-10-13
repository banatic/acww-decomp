/* func_02060de4 @ 0x02060de4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x15a0];
    struct {
        unsigned int : 10;
        unsigned int nibble : 4;
        unsigned int : 18;
    } unk_15A0;
} UnkStruct_02060de4;

int func_02060de4(UnkStruct_02060de4 *s, unsigned char val)
{
    s->unk_15A0.nibble = (unsigned char) (val & 0xF);
    return 1;
}
