/* func_0209b9cc @ 0x0209b9cc, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209b91c(unsigned int);
extern void func_0209bb90(int, int);
extern void func_0209bb68(int, unsigned short *);
extern int func_0209bc40(int);
extern int func_0209b914(unsigned int);
extern int func_020535f0(unsigned short *);
extern void func_0209b8a4(unsigned int, unsigned char);
extern int func_0209b908(unsigned int);
extern void func_0209525c(int, unsigned int);
extern void *func_0209bc20(void *record);
extern void func_0209e474(int);
extern void func_0209bb74(int, int);
extern void func_02095238(int);
extern int func_0209bac0(unsigned int, unsigned int, unsigned short *);

void func_0209b9cc(unsigned int r0, unsigned int r1, unsigned short *r2, unsigned int r3, unsigned char stackbyte)
{
    if (stackbyte != 0) {
        func_0209bac0(r0, r1, r2);
    } else {
        func_0209bb90(func_0209b91c(r0), 0);
        func_0209bb68(func_0209b91c(r0), r2);
        if (func_0209bc40(func_0209b91c(r0)) == 2) {
            if (func_0209b914(r0) == 2) {
                unsigned short v = *r2;
                int flag = 0;
                if ((unsigned int) v >= 0x450cU && (unsigned int) v <= 0x45dbU) {
                    flag = 1;
                }
                if (flag != 0) {
                    func_0209b8a4(r0, (unsigned char) func_020535f0(r2));
                }
            }
        }
    }
    if (r3 != 0) {
        func_0209525c(func_0209b908(r0), r3);
        func_0209e474((int) func_0209bc20((void *) func_0209b91c(r0)));
        func_0209bb74(func_0209b91c(r0), 0);
    } else {
        func_02095238(func_0209b908(r0));
    }
}
