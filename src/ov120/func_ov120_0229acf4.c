/* func_ov120_0229acf4 @ 0x0229acf4, 0x68 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229acf4 {
    unsigned char pad_00[0xa1];
    unsigned char count;
    unsigned char pad_A2[0x2720 - 0xa2];
    unsigned char table[0x100];
} UnkStruct_0229acf4;

unsigned char func_ov120_0229acf4(UnkStruct_0229acf4 *self, unsigned int key)
{
    if (key == 9) {
        return 13;
    }
    if (key >= 1 && key < 9) {
        unsigned int target = key + 5;
        int i = 0;
        int n = self->count;
        while (i < n) {
            if (self->table[i] == target) {
                return (unsigned char) i;
            }
            i++;
        }
        return 14;
    }
    if (key < 15 && key >= 10) {
        return (unsigned char) (key - 10);
    }
    if (key < 28 && key >= 15) {
        return (unsigned char) (key - 15);
    }
    return 14;
}
