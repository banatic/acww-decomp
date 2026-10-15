/* func_ov003_022195c8 @ 0x022195c8, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    unsigned short unk_0C;
    char pad_0E[0xe];
} LocalObj;

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_ov003_022195c8(void *p0, unsigned short p1, void *p2, void *p3)
{
    LocalObj local;
    int result;
    func_0200e92c(&local);
    func_0200e90c(&local, 6, p2, p3);
    local.unk_0C = p1;
    result = func_0200e894(p0, &local);
    func_0200e91c(&local);
    return result;
}
