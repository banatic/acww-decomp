/* func_0201cd5c @ 0x0201cd5c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201cd7c(void *param1);
extern void func_0200451c(void *param1);

void func_0201cd5c(void *param1)
{
    void *r4;
    unsigned char *r0;
    unsigned char *r4b;

    r4 = param1;
    func_0201cd7c(r4);
    func_0200451c(r4);
    r0 = (unsigned char *) r4 + 0x5a;
    *r0 = 1;
    r4b = (unsigned char *) r4 + 0x59;
    *r4b = 1;
}
