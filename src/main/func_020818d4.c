/* func_020818d4 @ 0x020818d4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7c];
    unsigned short field0 : 13;
    unsigned short field1 : 1;
} UnkStruct_020818d4;

unsigned int func_020818d4(UnkStruct_020818d4 *p)
{
    if (p->field1) {
        return 1;
    } else {
        return 0;
    }
}
