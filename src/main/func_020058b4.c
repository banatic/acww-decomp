/* func_020058b4 @ 0x020058b4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054988(void *param1, void *param2);

extern void func_02005740(void);

void func_020058b4(void *param1)
{
    void *r4 = param1;
    void *r0 = *(void **) ((char *) r4 + 4);
    void *r1 = *(void **) ((char *) r0 + 0x2c);
    if (r1 != 0) {
        func_02054988((char *) r1 + 0x234, r4);
    }
    *(void **) ((char *) r4 + 0x24) = (void *) func_02005740;
    *(unsigned char *) ((char *) r4 + 0x92) = 2;
}
