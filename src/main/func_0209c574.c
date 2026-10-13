/* func_0209c574 @ 0x0209c574, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209cfe0(void *);
extern void func_0209cec0(void *, void *);
extern void func_0209ce00(void *, void *);
extern void func_0209cfb8(void *);
extern void *data_020e35d4;

void func_0209c574(void *param)
{
    char sp[0x140];
    void *ptr;

    func_0209cfe0(sp);
    ptr = data_020e35d4;
    func_0209cec0(sp, ptr);
    func_0209ce00(sp, param);
    func_0209cfb8(sp);
}
