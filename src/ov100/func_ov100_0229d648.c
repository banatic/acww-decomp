/* func_ov100_0229d648 @ 0x0229d648, 0x34 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d648 {
    char pad_00[0x28DC];
    unsigned short array[15];
};

unsigned char func_ov100_0229d648(struct UnkStruct_0229d648 *obj)
{
    int i;
    for (i = 0; i < 15; i++) {
        if (obj->array[i] == 0xFFF1) {
            i += 15;
            return (unsigned char) i;
        }
    }
    return 0x20;
}
