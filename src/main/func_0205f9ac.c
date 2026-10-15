/* func_0205f9ac @ 0x0205f9ac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0205c610(int);
extern void func_0205f910(void *);
extern int func_020e9abc(void *);

extern unsigned char data_021c9ae0[];
extern unsigned char data_021cacec[];

void func_0205f9ac(int argument0)
{
    void *p;

    func_0205c610((int) argument0);
    func_0205f910((void *) data_021cacec);
    p = *(void **) data_021c9ae0;
    if (p) {
        func_020e9abc(p);
    }
}
