/* func_ov003_0220d410 @ 0x0220d410, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_0220d484(void *a, unsigned char *b, unsigned char *c);
extern int func_ov003_0220d498(void *a, unsigned char *b, int c, int d, int e);

void func_ov003_0220d410(void *p, int param2)
{
    unsigned char local[2];
    func_ov003_0220d484((char *) p + 0x8f0, &local[0], &local[1]);
    func_ov003_0220d498(p, &local[0], local[1], 6, param2);
}
