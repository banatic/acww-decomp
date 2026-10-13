/* func_020257f0 @ 0x020257f0, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d9c4(void *, void *);
extern int func_0209bc40(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(char *, char *, char *, int, int, int, int, int, int);
extern char data_020c8b58;
extern char data_020c8a58;
typedef struct {
    int unk_00;
    int unk_04;
} Pair;
extern Pair data_020d9398;
void func_020257f0(char *a, char *b)
{
    char *p;
    int local0;
    int val;
    p = &data_020c8b58;
    if (func_0209bc40(func_0202d9c4(a, b)) == 1) {
        p = &data_020c8a58;
    }
    local0 = func_020036e8(func_0208150c(*((int *) ((*((char **) (a + 0x100))) + 0x830))));
    val = 0x122;
    func_0202da38(a, a + 0x104, a + val, 0x1e, local0, *((int *) p), *((unsigned char *) (p + 4)), 0, 0);
    *((void **) b) = a + 0x104;
    *((unsigned char *) (b + 4)) = *((unsigned char *) (a + val));
    *(Pair *) (a + 0xc8) = data_020d9398;
}
