/* func_0203f490 @ 0x0203f490, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern void func_02073820(void *);
extern void func_020737f0(void *, int *, int);
extern void func_02073770(void *, int, int);

void func_0203f490(int a, int b)
{
    void *obj = data_020ccf94;
    func_02073820(obj);
    func_020737f0(obj, &a, 1);
    func_02073770(obj, 23, b);
}
