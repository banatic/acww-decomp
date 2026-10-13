/* func_02055444 @ 0x02055444, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct _func_02055444_struct {
    int *unk_00;
    int unk_04;
    int unk_08;
};
extern int data_020dd04c;

void func_02055444(struct _func_02055444_struct *obj)
{
    obj->unk_00 = &data_020dd04c;
    obj->unk_04 = 0;
    obj->unk_08 = 0;
}
