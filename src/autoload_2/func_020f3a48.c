/* func_020f3a48 @ 0x020f3a48, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020eec60(unsigned char);
extern void func_020f4338(void *, void *);

void func_020f3a48(void *r5, void *r4)
{
    unsigned char r0;
    r0 = ((unsigned char *) r5)[0x1d];
    func_020eec60(r0);
    func_020f4338(r5, r4);
    ((unsigned char *) r5)[0x1c] = 2;
}
