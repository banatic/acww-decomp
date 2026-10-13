/* func_0209cf80 @ 0x0209cf80, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e35ec[];
extern int func_0206e890(void *p1, char *p2, int p3, int p4);
extern void func_0206e854(void *p);

int func_0209cf80(void *param)
{
    if (func_0206e890((char *) param + 0x120, data_020e35ec, 0x10, 0x20c)) {
        func_0206e854((char *) param + 0x120);
        return 1;
    } else {
        return 0;
    }
}
