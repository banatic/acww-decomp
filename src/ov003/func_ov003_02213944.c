/* func_ov003_02213944 @ 0x02213944, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02213a90(void *p, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                                unsigned char *e);
extern void func_ov003_02213ae4(void *p, unsigned char a, unsigned char b, unsigned char c, int d, int e);

void func_ov003_02213944(void *p1, int p2)
{
    unsigned char buf[5];
    func_ov003_02213a90((char *) p1 + 0x8f0, &buf[0], &buf[1], &buf[2], &buf[3], &buf[4]);
    func_ov003_02213ae4(p1, buf[3], buf[1], buf[2], 6, p2);
}
