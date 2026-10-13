/* func_ov068_022726a0 @ 0x022726a0, 0x22 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022726a0 {
    int unk_00;
    int unk_04;
};

extern struct UnkStruct_022726a0 *func_020682e0(int);
extern void func_02068320(struct UnkStruct_022726a0 *);
extern void func_ov068_02272a7c(void *, int);

void func_ov068_022726a0(void *arg0)
{
    struct UnkStruct_022726a0 *p;
    p = func_020682e0(0);
    if (p->unk_04 == 0) {
        func_02068320(p);
        func_ov068_02272a7c(arg0, 6);
    }
}
