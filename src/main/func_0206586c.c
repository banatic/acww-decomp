/* func_0206586c @ 0x0206586c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x124];
    int unk_124;
    unsigned short unk_128;
} UnkStruct_0206586c;

extern UnkStruct_0206586c *data_021cd864;

short func_0206586c(void)
{
    volatile short result = 0;
    if (data_021cd864 && data_021cd864->unk_124 != 9) {
        result = data_021cd864->unk_128;
    }
    return result;
}
