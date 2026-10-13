/* func_ov145_02299e08 @ 0x02299e08, 0x24 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *);
extern void func_ov002_02208098(void *, int);

void func_ov145_02299e08(void *self)
{
    unsigned char b;

    func_ov002_0220a164((char *) self + 0xc8);
    b = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0xc3) = b;
    func_ov002_02208098(self, 8);
}
