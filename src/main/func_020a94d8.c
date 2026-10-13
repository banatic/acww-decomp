/* func_020a94d8 @ 0x020a94d8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a92d8(int a, int b);

struct UnkStruct_020a94d8 {
    int a;
    int b;
    int c;
};

int func_020a94d8(struct UnkStruct_020a94d8 *p)
{
    int result = 0;
    if (p->b != 0) {
        p->c = func_020a92d8(p->a, result);
        if (p->c != 0) {
            result = 1;
        } else {
            p->b = result;
        }
    }
    return result;
}
