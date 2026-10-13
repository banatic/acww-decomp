/* func_02066934 @ 0x02066934, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8bb8(void *);

void func_02066934(void *r0, int r1, int r2)
{
    void *r4 = r0;
    int r5 = r2;
    func_020a8bb8((char *) r0 + 0x20);
    *(int *) ((char *) r4 + 0x2c) = r5;
    *(unsigned char *) ((char *) r4 + 0x44) = 0;
}
