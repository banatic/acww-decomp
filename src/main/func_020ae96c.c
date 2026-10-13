/* func_020ae96c @ 0x020ae96c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aea28(void);
extern void func_02063ce0(void *, int, int, int);
extern void func_020ae834(int, int *);
extern void func_020ae814(int, int *);
extern void func_020ae7b4(int, int *);
extern void func_020ae798(int, int *);
extern void func_020ae794(int);

extern unsigned char data_021f4a80[];

void func_020ae96c(int a0, int a1, int a2, int a3)
{
    int local;

    func_020aea28();
    func_02063ce0((void *) data_021f4a80, a1, a2, a3);
    local = 0;
    func_020ae834(a0, &local);
    func_020ae814(a0, &local);
    func_020ae7b4(a0, &local);
    func_020ae798(a0, &local);
    func_020ae794(a0);
}
