/* func_ov082_022791b0 @ 0x022791b0, 0x54 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

typedef struct Pair {
    int a;
    int b;
} Pair;

extern Pair data_ov082_02279710;
extern Pair data_ov082_02279708;

void func_ov082_022791b0(int unused, Pair *out, int index)
{
    static int init_flag;
    static Pair table[2];

    if (!(init_flag & 1)) {
        table[0] = data_ov082_02279710;
        table[1] = data_ov082_02279708;
        init_flag |= 1;
    }

    *out = table[index];
}
