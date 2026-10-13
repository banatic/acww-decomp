/* func_020ef9dc @ 0x020ef9dc, 0x54 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern void func_020ef8d0(void *p, int a, int b);
extern void func_020efa30(void *p, int x, int y);

struct UnkStruct_020ef9dc {
    char pad_00[6];
    unsigned short h;
    unsigned char b;
};

void func_020ef9dc(struct UnkStruct_020ef9dc *s, unsigned char b, unsigned short h, int x, signed short y)
{
    if (s == 0) {
        OS_Terminate();
    }
    s->b = b;
    s->h = h;
    func_020ef8d0(s, 1, 1);
    func_020efa30(s, x, y);
}
