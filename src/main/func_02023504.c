/* func_02023504 @ 0x02023504, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *p);
extern int func_020036e8(int v);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

struct GlobalData {
    unsigned int unk_00;
    unsigned char unk_04;
};
extern struct GlobalData data_020c8bd0;

void func_02023504(void *self, void *out)
{
    int arg4;
    int arg5;
    int arg6;

    arg4 = func_020036e8(func_0208150c(*(void **) ((char *) (*(void **) ((char *) self + 0x100)) + 0x830)));
    arg5 = data_020c8bd0.unk_00;
    arg6 = data_020c8bd0.unk_04;

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, arg4, arg5, arg6, 0, 0);

    *(void **) out = (char *) self + 0x104;
    *(unsigned char *) ((char *) out + 4) = *(unsigned char *) ((char *) self + 0x122);
}
