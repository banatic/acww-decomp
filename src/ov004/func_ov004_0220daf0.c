/* func_ov004_0220daf0 @ 0x0220daf0, 0x56 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223cd50(void);
extern char *func_ov004_0220db5c(void *list, unsigned i);
extern unsigned func_ov004_0220db68(void *list);
extern void *func_ov004_0223cc10(void *a, int b, int c, int d);
extern int func_ov004_0220da70(void *self, void *p);
void func_ov004_0220daf0(void *self, void *list, int flag)
{
    unsigned i;
    void *t;
    char *a;
    char *b;
    void *r;
    if (flag == 0) {
        for (i = 0; i < func_ov004_0220db68(list); i++) {
            t = func_ov004_0223cd50();
            a = func_ov004_0220db5c(list, i);
            b = func_ov004_0220db5c(list, i);
            r = func_ov004_0223cc10(t, *(int *) a, *(int *) (b + 4), 1);
            if (r != 0) {
                func_ov004_0220da70(self, r);
            }
        }
    }
}
