/* func_02012250 @ 0x02012250, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082c98(void *);
extern void *func_0205e8e4(void *);
extern void func_0205ea60(void *);

void func_02012250(char *p, char *q)
{
    void *res = func_02082c98(p + 4);
    int value;
    int *sub;

    if (res) {
        value = *(int *) (q + 0x198);
        sub = (int *) ((char *) func_0205e8e4(res) + 0x9c);
        sub[4] = value;
        func_0205ea60(res);
    }
}
