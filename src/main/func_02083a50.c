/* func_02083a50 @ 0x02083a50, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct some_struct {
    int unk_00;
    char unk_04;
};

extern void func_02078a90(void *);
extern void func_02083cb4(struct some_struct *);

struct some_struct *func_02083a50(struct some_struct *param)
{
    func_02078a90(&param->unk_04);
    func_02083cb4(param);
    return param;
}
