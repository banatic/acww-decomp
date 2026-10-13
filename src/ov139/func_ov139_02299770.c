/* func_ov139_02299770 @ 0x02299770, 0x28 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070b84(void *);

void func_ov139_02299770(char *arg0)
{
    int i;
    char *base;

    i = 0;
    arg0[0x9a3] = 0;
    base = arg0 + 0xcc;
    do {
        func_02070b84(base + i * 0x6c);
        i++;
    } while (i < 0x14);
}
