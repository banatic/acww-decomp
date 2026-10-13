/* func_02022e34 @ 0x02022e34, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, char *, char *, int, int, int, int, int, int);

struct UnkStruct_02022e34 {
    int a;
    unsigned char b;
};
extern struct UnkStruct_02022e34 data_020c8b70;

struct UnkStruct_02022e34_2 {
    char pad_00[0x100];
    void *ptr;
};

int func_02022e34(struct UnkStruct_02022e34_2 *o)
{
    int res;
    int d0;
    unsigned char d1;

    res = func_020036e8(func_0208150c(*(int *) ((char *) o->ptr + 0x830)));
    d0 = data_020c8b70.a;
    d1 = data_020c8b70.b;

    func_0202da38(o, (char *) o + 0x104, (char *) o + 0x122, 0x1e, res, d0, d1, 0, 0);

    return 1;
}
