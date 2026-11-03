/* process_020daae4_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e514 @ 0x0203e514, 0x48 bytes, Thumb
 * func_0203e510 @ 0x0203e510, 0x4 bytes, Thumb
 * func_0203e4e0 @ 0x0203e4e0, 0x30 bytes, Thumb
 */

extern int func_0203ec98(void);
extern void func_0203e58c(int receiver);
extern void func_0203e55c(int receiver);
extern void func_0203e5f4(int receiver);
extern void func_0203e5c0(int receiver);
extern void func_0203f568(int);
extern unsigned char data_021c72c4[];
extern void func_020a6d24(void);
extern void func_020a6ce4(void);
extern void func_020a529c(void *);
extern void func_01ffd418(int, int);
extern int data_021f42f4;

int func_0203e514(int param)
{
    if (func_0203ec98()) {
        func_0203e58c(param);
        func_0203e55c(param);
    }
    if (!func_0203ec98()) {
        func_0203e5f4(param);
    }
    if (func_0203ec98()) {
        func_0203e5c0(param);
    }
    func_0203f568((unsigned int) data_021c72c4);
    return 1;
}

int func_0203e510(void)
{
    return 1;
}

void func_0203e4e0(int a, int b)
{
    void *condition_value0;
    func_020a6d24();
    func_020a6ce4();
    if ((condition_value0 = (void *) (data_021f42f4))) {
        func_020a529c(condition_value0);
    }
    func_01ffd418(a, b);
}
