/* func_02087e0c @ 0x02087e0c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
} TestStruct;

int func_02087e0c(TestStruct *p)
{
    if (p->bit1) {
        return 1;
    } else {
        return 0;
    }
}
