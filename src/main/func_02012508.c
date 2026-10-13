/* func_02012508 @ 0x02012508, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082c98(void *p);
extern void func_0205eb8c(int a, void *b, int c);
extern void func_02016638(void *a, void *b, void *c, void *d, unsigned short e);

int func_02012508(void *p0, void *p1, void *p2, void *p3, unsigned short p4)
{
    int ret = func_02082c98((char *) p0 + 4);
    if (ret == 0) {
        goto fail;
    }
    func_0205eb8c(ret, p2, 0);
    func_02016638((char *) p1 + 0x334, p1, p2, p3, p4);
    *(unsigned short *) p0 = *(unsigned short *) p2;
    return 1;
fail:
    return 0;
}
