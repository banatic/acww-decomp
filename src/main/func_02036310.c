/* func_02036310 @ 0x02036310, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02036310 {
    char pad_00[0xc];
    int state;
};

extern void func_02036558(struct UnkStruct_02036310 *s, int a, int b, int c);

void func_02036310(void *unused, struct UnkStruct_02036310 *s)
{
    if (s->state == 2) {
        func_02036558(s, 0x28, 5, 1);
        s->state = 5;
    } else if (s->state == 3) {
        func_02036558(s, 0x7f, 5, 1);
        s->state = 5;
    } else if (s->state == 4) {
        func_02036558(s, 0, 5, 1);
        s->state = 5;
    } else if (s->state == 5) {
    } else if (s->state == 6) {
        func_02036558(s, 0x7f, 5, 1);
        s->state = 0;
    }
}
