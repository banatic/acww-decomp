/* func_02050588 @ 0x02050588, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dcd78;
extern struct Param *data_021c8184;
extern void func_0209d180(void *p, int a, int b, int c, int d, int e, int f, int g);
extern void func_0205c8f8(void);
extern void func_0205c8dc(void);
extern int data_020dcef0;

struct Param {
    int unk_00;
    int unk_04;
    int state;
};

int func_02050588(struct Param *param)
{
    if (param->state == 0) {
        data_020dcd78 = 4;
    } else if (param->state == 1) {
        data_020dcd78 = 1;
    }
    func_0209d180((char *) param + 0x600, data_020dcd78, 0x800, 0x80, 0x134c, (int) func_0205c8f8, (int) func_0205c8dc,
                  (int) &data_020dcef0);
    data_021c8184 = param;
    return 1;
}
