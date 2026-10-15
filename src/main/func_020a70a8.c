/* func_020a70a8 @ 0x020a70a8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a75d4(void);
extern void *data_020ccf94;
extern void func_02073820(void *);
extern int func_02073424(void *);
extern int func_020733f8(void *);
extern void func_020737f0(void *, int, int);
extern void func_02073770(void *, int, int);
extern void func_02073410(void *);

void func_020a70a8(int arg)
{
    void *obj;
    int r6;

    func_020a75d4();
    obj = data_020ccf94;
    func_02073820(obj);
    r6 = func_02073424(obj);
    func_020737f0(obj, r6, func_020733f8(obj));
    func_02073770(obj, 15, arg);
    func_02073410(obj);
}
