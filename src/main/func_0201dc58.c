/* func_0201dc58 @ 0x0201dc58, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(unsigned char *, unsigned char *, unsigned char *, int, int, int, int, int, int);

struct GlobalInfo {
    int unk_00;
    unsigned char unk_04;
};
extern struct GlobalInfo data_020c8d18;

void func_0201dc58(unsigned char *p1, unsigned char *out)
{
    int arg5 = func_020036e8(func_0208150c(*(int *) ((unsigned char *) (*(int *) (p1 + 0x100)) + 0x830)));
    int arg6 = data_020c8d18.unk_00;
    int arg7 = 1;
    int arg8 = 2;
    int arg9 = data_020c8d18.unk_04;

    func_0202da38(p1, p1 + 0x104, p1 + 0x122, 30, arg5, arg6, arg7, arg8, arg9);

    *(int *) out = (int) (p1 + 0x104);
    out[4] = p1[0x122];
}
