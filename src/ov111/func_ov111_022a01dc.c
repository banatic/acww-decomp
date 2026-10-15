/* func_ov111_022a01dc @ 0x022a01dc, 0x28 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

void func_ov111_022a01dc(void *r0)
{
    extern void func_ov002_02207fc0(void *);
    extern void func_ov111_0229f1fc(void *);
    extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
    extern void func_ov111_0229fd08(void *);
    extern void func_ov111_0229efec(void *);

    void *r4 = r0;
    func_ov002_02207fc0(r4);
    func_ov111_0229f1fc(r4);
    func_ov002_02208098((void *) (r4), 3);
    func_ov111_0229fd08(r4);
    func_ov111_0229efec(r4);
}
