/* func_0203b4b4 @ 0x0203b4b4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GStruct;

extern GStruct *data_021f6948;
extern void func_0203caa4(int *p, int a, int b);
extern void func_0203c99c(int *p, int a);
extern void func_0203ad58(void);

int func_0203b4b4(int *p)
{
    if (data_021f6948->unk_04 == 0) {
        func_0203caa4(p, 13, 0);
    } else {
        func_0203caa4(p, 12, 0);
    }
    func_0203c99c(p, 0);
    func_0203ad58();
    *((int *) ((char *) p + 0x1e4)) = 0x1000;
    return 1;
}
