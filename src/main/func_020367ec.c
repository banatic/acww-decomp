/* func_020367ec @ 0x020367ec, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020366c0(void *param1);
extern void func_0203665c(void *param1);

void func_020367ec(void *param1)
{
    void *r4 = param1;
    func_020366c0(r4);
    *(unsigned char *) ((char *) r4 + 8) = 0x3f;
    func_0203665c(r4);
    *(unsigned char *) ((char *) r4 + 0x10) = 0;
    *(unsigned char *) ((char *) r4 + 0xf) = 0;
}
