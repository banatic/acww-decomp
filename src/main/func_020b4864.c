/* func_020b4864 @ 0x020b4864, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b4950_unk(int a, int b, int c);

void func_020b4864(char *p, int b, int c)
{
    int i;
    int end;
    i = func_020b4950_unk((int) p, b, c);
    end = c * 2;
    for (; i < end; i += 2) {
        p[i] = 0;
        p[i + 1] = 0x30;
    }
}
