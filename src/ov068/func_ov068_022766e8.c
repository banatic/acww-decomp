/* func_ov068_022766e8 @ 0x022766e8, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020edf70(unsigned int size);
extern void func_0202e8e4(void);
extern void func_0202decc(void *addr);
extern int data_ov068_02278140;
extern int data_ov068_022780b0;

struct UnkStruct_022766e8 {
    void *unk_00;
    char pad_04[0x898];
    void *unk_89C;
};

struct UnkStruct_022766e8 *func_ov068_022766e8(void)
{
    struct UnkStruct_022766e8 *p = (struct UnkStruct_022766e8 *) func_020edf70(0xa7c);
    if (p) {
        func_0202e8e4();
        p->unk_00 = &data_ov068_02278140;
        func_0202decc(&p->unk_89C);
        p->unk_89C = &data_ov068_022780b0;
    }
    return p;
}
