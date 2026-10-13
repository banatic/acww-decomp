/* func_02062cbc @ 0x02062cbc, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cb5c0;
extern char data_020de5b0;
extern char data_020de5c8;
extern char data_020de5e0;
extern char data_020de5f4;

extern int func_0206e73c(void *, void *, int, void *, int, void *, int, int);
extern void func_02062c0c(void);
extern void func_02062b98(void);
extern void func_02062b18(void);
extern int func_0206e890(void *, void *, int, int);
extern void func_0206e854(void *);

int func_02062cbc(void *ptr)
{
    int flag, result;

    data_021cb5c0 = 0;

    result = func_0206e73c(ptr, &data_020de5b0, 12, &data_020de5c8, 4, &data_020de5e0, 0x18, 0x600);

    flag = 1;
    if ((result | flag) == 0) {
        flag = 0;
    }

    if (flag) {
        func_02062c0c();
        func_02062b98();
        func_02062b18();
    }

    result = func_0206e890((char *) ptr + 0x54, &data_020de5f4, 0x18, 0x80);

    flag = (flag | result) ? 1 : 0;

    if (flag) {
        func_0206e854((char *) ptr + 0x54);
    }

    return flag;
}
