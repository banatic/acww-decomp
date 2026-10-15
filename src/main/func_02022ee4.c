/* func_02022ee4 @ 0x02022ee4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int scale, int, int);
struct UnkStruct_02022ee4 {
    unsigned int a;
    unsigned char b;
};
extern struct UnkStruct_02022ee4 data_020c8dc0;

int func_02022ee4(void *p)
{
    int A, B, D, E;
    unsigned char C;
    A = func_020036e8(func_0208150c(*(int *) (*(int *) ((char *) p + 0x100) + 0x830)));
    B = data_020c8dc0.a;
    C = data_020c8dc0.b;
    D = 0;
    E = 0;
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 30, A, B, C, D, E);
    return 1;
}
