/* func_ov135_0229ca3c @ 0x0229ca3c, 0x1c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov135_0229c7fc(void *);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov135_0229ca3c(void *r0)
{
    void *r4 = r0;
    func_ov135_0229c7fc(r4);
    func_ov002_02207fc0(r4);
    func_ov002_02208098((void *) (r4), 6);
}
