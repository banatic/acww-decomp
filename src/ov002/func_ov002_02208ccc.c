/* func_ov002_02208ccc @ 0x02208ccc, 0x4c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8bb8(void *ptr, int param);

int func_ov002_02208ccc(char *base, unsigned char *slots, int param, unsigned char val)
{
    long i;

    for (i = 0; i < 5; i++) {
        if (slots[i] == 0xff) {
            func_020a8bb8(base + 0x28 + i * 116, param);
            slots[i + 5] = val;
            slots[10] |= 1 << i;
            slots[i] = 0xfe;
            return 1;
        }
    }
    return 0;
}
