/* func_ov003_022130dc @ 0x022130dc, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02213178(void *a, void *b, void *c, void *d);
extern void func_ov003_022131c8(void *a, unsigned char b, unsigned char c, int d, void *e);

void func_ov003_022130dc(void *a, void *b)
{
    unsigned char local[3];
    func_ov003_02213178((char *) a + 0x8f0, &local[0], &local[1], &local[2]);
    func_ov003_022131c8(a, local[0], local[1], 6, b);
}
