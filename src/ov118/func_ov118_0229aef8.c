/* func_ov118_0229aef8 @ 0x0229aef8, 0x6c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229aef8 {
    unsigned char pad_00[0xa1];
    unsigned char count;
    unsigned char pad_A2[0x478a - 0xa2];
    unsigned char table[0x100];
} UnkStruct_0229aef8;

extern unsigned char data_ov118_0229ca98[];

unsigned char func_ov118_0229aef8(UnkStruct_0229aef8 *p, unsigned int key)
{
    if (key == 9) {
        return 13;
    }
    if (key >= 1 && key < 9) {
        unsigned int target = key + 5;
        int i = 0;
        int n = p->count;
        while (i < n) {
            if (p->table[i] == target) {
                return (unsigned char) i;
            }
            i++;
        }
        return 14;
    }
    if (key < 15 && key >= 10) {
        return data_ov118_0229ca98[key - 10];
    }
    if (key < 28 && key >= 15) {
        return (unsigned char) (key - 15);
    }
    return 14;
}
