/* func_ov110_0229da50 @ 0x0229da50, 0x48 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229ccb0(void *p, unsigned char c);
extern int func_ov110_0229c2b8(void *p, int n);
extern int func_ov110_0229ce44(void *p);
extern int func_ov002_02209f70(void *p);
extern int func_ov002_02208098(void *p, int n);

void func_ov110_0229da50(void *p)
{
    if (func_ov002_02209f70((char *) p + 0x22e0) == 0) {
        func_ov110_0229ccb0(p, *(unsigned char *) ((char *) p + 0xf7));
        func_ov110_0229c2b8(p, 0x40);
        func_ov002_02208098(p, 0xf);
        func_ov110_0229ce44(p);
    } else {
        func_ov002_02208098(p, 4);
    }
}
