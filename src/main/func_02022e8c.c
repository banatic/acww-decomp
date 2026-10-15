/* func_02022e8c @ 0x02022e8c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(int);
extern int func_020036e8(unsigned char *);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

struct Data_020c8db0 {
    int unk_00;
    unsigned char unk_04;
};
extern struct Data_020c8db0 data_020c8db0;

int func_02022e8c(void *arg)
{
    int v1, v2, v3, v4, v5;

    v1 = func_020036e8((unsigned char *) func_0208150c(*(int *) ((char *) *(int *) ((char *) arg + 0x100) + 0x830)));
    v2 = data_020c8db0.unk_00;
    v3 = data_020c8db0.unk_04;
    v4 = 0;
    v5 = 0;
    func_0202da38(arg, (char *) arg + 0x104, (char *) arg + 0x122, 0x1e, v1, v2, v3, v4, v5);
    return 1;
}
