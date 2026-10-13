/* func_ov132_0229af54 @ 0x0229af54, 0x34 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220b9b8(void *a, void *b, int c, int d);
extern void func_ov002_02208098(void *a, int b);
extern void func_0208e5c4(void *a);

void func_ov132_0229af54(void *r0, unsigned char r1)
{
    unsigned char local;
    void *r4 = r0;

    local = r1;
    func_ov002_0220b9b8((char *) r4 + 0x3e4, &local, 1, 0);
    func_ov002_02208098(r4, 7);
    func_0208e5c4((char *) r4 + 0x94);
}
