/* func_ov144_0229a328 @ 0x0229a328, 0x50 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060a34(unsigned short key);

struct Work {
    unsigned char pad_00[0xb8];
    short count;
    unsigned char pad_BA[0x7b2];
    unsigned short table[0x46];
};

void func_ov144_0229a328(struct Work *p)
{
    int i;
    unsigned short key = 0x1323;

    p->count = 0;
    for (i = 0; i < 0x46; i++) {
        if (func_02060a34(key)) {
            p->table[p->count] = key;
            p->count++;
        }
        key++;
    }
}
