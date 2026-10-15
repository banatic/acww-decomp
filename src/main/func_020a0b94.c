/* func_020a0b94 @ 0x020a0b94, 0x82 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02090040(int);
extern void *func_020984e8(void);
extern int func_02099870(void *);
extern int func_02095040(void *);
extern void func_02064210(int, void *);
extern int func_02099688(void *);
extern void *func_02090124(void *);
extern int func_020882ec(void *);
extern int func_020882dc(void *);
extern int func_020882c4(void *);
extern void func_020882f0(void *);
extern void *func_020641c8(void *);
extern void *func_020641b0(void *);
extern void MI_CpuCopy8(void *, int, int);

void func_020a0b94(void *receiver)
{
    void *p5, *p4;
    int r6;
    char obj1[0x20];
    char obj2[0x20];

    p5 = func_02090040(4);
    p4 = func_020984e8();

    func_020641c8(obj1);
    func_02064210(func_02095040((void *) func_02099870(p4)), obj1);

    r6 = func_02099688(p4);
    p4 = func_02090124(p5);

    func_020641c8(obj2);
    func_02064210(func_020882ec(p4), obj2);

    if (func_020882dc(p4) != 0) {
        MI_CpuCopy8(p4, r6, 0x10);
        func_020882c4(p4);
    }

    func_020882f0(func_02090124(p5));

    func_020641b0(obj2);
    func_020641b0(obj1);
}
