/* func_02091358 @ 0x02091358, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int (*func)(int, int, int, int, int);
    int pad_04;
} Entry;

extern Entry data_020e2c1c[];

struct UnkStruct_02091358 {
    unsigned char pad_00[0x39c];
    unsigned short counter;
};

int func_02091358(struct UnkStruct_02091358 *obj, unsigned int idx, int a, int b, int c, int d)
{
    int result = -1;
    if (idx < 0x66) {
        int (*fn)(int, int, int, int, int) = data_020e2c1c[idx].func;
        if (fn != 0) {
            int r = fn(idx, a, b, c, d);
            if (r == 0) {
                unsigned short old = obj->counter;
                obj->counter = old + 1;
                result = old;
            } else if (r == 2) {
                obj->counter++;
            }
        }
    }
    return result;
}
