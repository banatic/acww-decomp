/* town_map: 5 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229a448 @ 0x0229a448, 0x12 bytes, Thumb
 * func_ov120_0229a438 @ 0x0229a438, 0xe bytes, Thumb
 * func_ov120_0229a428 @ 0x0229a428, 0xe bytes, Thumb
 * func_ov120_0229a424 @ 0x0229a424, 0x2 bytes, Thumb
 * func_ov120_0229a420 @ 0x0229a420, 0x2 bytes, Thumb
 */

typedef struct {
    char pad_00[0x9c];
    unsigned short flags;
} UnkStruct_0229a428;

int func_ov120_0229a448(void *self, unsigned short mask)
{
    unsigned short value;
    value = *(unsigned short *) ((char *) self + 0x9c);
    if ((value & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov120_0229a438(void *self, unsigned short value)
{
    unsigned short *p = (unsigned short *) ((char *) self + 0x9c);
    *p = (unsigned short) (*p | value);
}

void func_ov120_0229a428(UnkStruct_0229a428 *self, unsigned short mask)
{
    self->flags &= ~mask;
}

void func_ov120_0229a424(void *element) {}

void func_ov120_0229a420(void *element) {}
