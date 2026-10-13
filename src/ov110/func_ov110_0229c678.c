/* func_ov110_0229c678 @ 0x0229c678, 0x74 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229c2b8(void *p, int v);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088cc(void *p);

void func_ov110_0229c678(void *r4, void *r5)
{
    if (func_ov002_0220889c(r5)) {
        if (func_ov002_022088cc(r5)) {
            *(unsigned char *) ((char *) r4 + 0xf5) = 0x19;
        } else {
            *(unsigned char *) ((char *) r4 + 0xf5) = 0;
        }
        func_ov110_0229c2b8(r4, 0x20);
    } else if (func_ov002_022088ac(r5)) {
        if (func_ov002_022088cc(r5)) {
            *(unsigned char *) ((char *) r4 + 0xf5) = 0x1d;
        } else {
            *(unsigned char *) ((char *) r4 + 0xf5) = 4;
        }
    } else if (func_ov002_022088cc(r5)) {
        *(unsigned char *) ((char *) r4 + 0xf5) = 0x1d;
    }
}
