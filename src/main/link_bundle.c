/* link_bundle: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a70a8 @ 0x020a70a8, 0x44 bytes, Thumb
 * func_020a7064 @ 0x020a7064, 0x44 bytes, Thumb
 */

extern void func_020a75d4(void);
extern void *data_020ccf94;
extern void func_02073820(void *);
extern int func_02073424(void *);
extern int func_020733f8(void *);
extern void func_020737f0(void *, int, int);
extern void func_02073770(void *, int, int);
extern void func_02073410(void *);
extern void func_020a74bc(void);
extern int func_020733c4(int);
extern int func_02073394(int);
extern void func_020733ac(int);

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

void func_020a7064(int param)
{
    int obj;
    int tmp1;
    int tmp2;
    func_020a74bc();
    obj = (*(int *) &data_020ccf94);
    func_02073820((void *) obj);
    tmp1 = func_020733c4(obj);
    tmp2 = func_02073394(obj);
    func_020737f0((void *) obj, tmp1, tmp2);
    func_02073770((void *) obj, 0x10, param);
    func_020733ac(obj);
}
