/* func_0207a44c @ 0x0207a44c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *p);
extern int func_02003704(int x);
extern void func_0207d5bc(void *p);

typedef struct {
    char data[0x7ec];
} Entry;

void func_0207a44c(Entry *p)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(p))) {
            func_0207d5bc(p);
        }
        p++;
    }
}
