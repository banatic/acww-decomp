/* func_02072be0 @ 0x02072be0, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072bd0(void *a, int b);
extern int func_02072d4c(int a);
extern void *func_02072ee8(void *record);
extern unsigned char *func_02095040(int a);
extern int func_0209518c(int a, int b);
extern void func_02095038(int a, unsigned char *b);
extern int memcmp(const void *a, const void *b, unsigned int n);

void func_02072be0(void *local0, int param1, unsigned char *param2)
{
    unsigned char i;
    int t;
    unsigned char *p;
    int local1;

    for (i = 0; i < 8; i++) {
        t = func_02072d4c(func_02072bd0(local0, i));
        local1 = (int) func_02072ee8((void *) t);
        p = func_02095040(local1);
        if (*(unsigned short *) p == *(unsigned short *) param2) {
            if (memcmp(p + 2, param2 + 2, 12) == 0) {
                if (func_0209518c(local1, param1) != 0) {
                    t = (int) func_02072ee8((void *) t);
                    func_02095038(t, func_02095040(param1));
                }
            }
        }
    }
}
