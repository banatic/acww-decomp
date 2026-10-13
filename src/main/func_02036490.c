/* func_02036490 @ 0x02036490, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020041cc(void);
extern void func_02036560(void *);

void func_02036490(void *arg0)
{
    void *r5;
    int r4;
    void *r6;
    int r0;

    r5 = arg0;
    r0 = *(int *) ((char *) r5 + 0x30);
    r0 -= 8;
    if ((unsigned int) r0 <= 1) {
        func_020041cc();
    }
    r4 = 0;
    r6 = (char *) r5 + 4;
    do {
        func_02036560((char *) r6 + (r4 << 4));
        r4++;
    } while (r4 < 8);
    r0 = 0;
    *(int *) ((char *) r5 + 0x84) = r0;
}
