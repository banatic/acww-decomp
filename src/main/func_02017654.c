/* func_02017654 @ 0x02017654, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bd4(void *);
extern int func_02019af0(void *, int);

void func_02017654(void *arg0)
{
    int val;
    void *pvVar2;

    val = func_02057bd4(arg0);
    if (val == 0) {
        func_02019af0(arg0, 1);
        pvVar2 = (void *) ((int) arg0 + 0x98);
        *(unsigned char *) pvVar2 = 3;
    }
    return;
}
