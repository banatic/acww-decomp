/* func_02017258 @ 0x02017258, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019de4(void *param1, void *param2);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern void func_02012444(int a, unsigned short b, int c);
extern void func_02091230(int a, void *b, int c, int d);
extern void func_0200442c(void *a, int b, int c, int d);
extern void func_02019af0(void *a, int b);
extern volatile unsigned short data_020c80f8;

int func_02017258(void *param1, char *param2)
{
    unsigned short color;
    int obj;

    func_02019de4(param1, param2);
    color = data_020c80f8;
    func_02016764(param2 + 0x334, param2, 6, data_020c80f8, 1, 0x1000, 0, 0);
    obj = *(int *) (param2 + 0x628);
    if (obj) {
        func_02012444(obj, color, 0);
    }
    func_02091230(0x61, param2 + 0x5c, 0, 0);
    func_0200442c(param2 + 0x514, 0x76, 0x7f, 0);
    func_02019af0(param1, 0);
    return 1;
}
