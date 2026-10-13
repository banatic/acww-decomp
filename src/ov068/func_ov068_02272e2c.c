/* func_ov068_02272e2c @ 0x02272e2c, 0x24 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02272934(void *);
extern void func_02095f08(int);

struct _ov068_02272e2c_struct {
    char pad_00[0x2b4];
    int unk_2B4;
};

int func_ov068_02272e2c(struct _ov068_02272e2c_struct *this)
{
    func_ov068_02272934(this);
    if (this->unk_2B4 != 0) {
        func_02095f08(1);
    }
    return 1;
}
