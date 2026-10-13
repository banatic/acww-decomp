/* func_0204226c @ 0x0204226c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x30];
    struct {
        unsigned int : 6;
        signed int bit6 : 1;
        signed int bit7 : 1;
        unsigned int : 24;
    } flags;
} UnkStruct_0204226c;

extern UnkStruct_0204226c data_021c79c4;

void func_0204226c(unsigned char *dest)
{
    if (data_021c79c4.flags.bit7) {
        dest[0] = 1;
    } else {
        dest[0] = 0;
    }
    if (data_021c79c4.flags.bit6) {
        dest[1] = 1;
    } else {
        dest[1] = 0;
    }
}
