/* func_0204cb90 @ 0x0204cb90, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    char pad_02[10];
} Entry;

extern Entry *func_0204cc04(int, int);

int func_0204cb90(int a, int b)
{
    int result = -1;
    int i;
    Entry *p;

    p = func_0204cc04(0, b);
    for (i = 0; i < 4; i++) {
        if (b == p->unk_00) {
            result = i;
            break;
        }
        p++;
    }
    return result;
}
