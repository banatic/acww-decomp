/* func_0207d148 @ 0x0207d148, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern int func_02003704(void);
extern unsigned char *func_0207f270(unsigned char *param);

void func_0207d148(unsigned char *param)
{
    unsigned char *ptr;
    unsigned char val;

    func_0208150c();
    if (func_02003704() != 0) {
        ptr = func_0207f270(param);
        val = ptr[0x1e];
        val = (unsigned char) (val >> 1);
        ptr[0x1e] = val;
    }
}
