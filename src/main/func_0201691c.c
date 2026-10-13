/* func_0201691c @ 0x0201691c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201651c(void *p, int x);
extern int func_0208308c(void *p);
extern void func_02016764(void *p, void *q, int a, int b, int c, int d, int e, int f);
extern void func_02055050(void *p);
extern void func_02055de0(void *p, void (*fp)(void), int a, int b, void *q, int c);
extern int func_02016618(void *p);
extern void func_020165f4(void *p);
extern void func_0201c6a8(void);

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    unsigned char unk_10;
    char pad_11[3];
    int unk_14;
} UnkStruct_0201691c;

int func_0201691c(UnkStruct_0201691c *param0, void *param1, int param2)
{
    func_0201651c(param0, 0);
    param0->unk_14 = param2;

    if (func_0208308c(param0) == 0) {
        return 0;
    }

    func_02016764(param0, param1, 0, 0, 0, 0x1000, 0, 0);
    func_02055050((char *) param1 + 0xec);
    func_02055de0((char *) param1 + 0xec, func_0201c6a8, 6, 1, param1, 0);
    param0->unk_0C = 2;

    if (func_02016618(param0) == 0) {
        func_020165f4(param0);
    }

    param0->unk_10 = 0;
    return 1;
}
