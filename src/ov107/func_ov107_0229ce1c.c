/* func_ov107_0229ce1c @ 0x0229ce1c, 0x74 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229c2b4(int a, int b);
extern int func_ov107_0229cec4(int a);
extern int func_ov107_0229ceb4(int a);
extern void func_ov107_0229c294(int a, int b);
extern void func_ov002_0220a0b4(int a, int b, int c);
extern void func_ov002_0220a05c(int a, int b, int c, int d, int e);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov107_0229ce1c(int r4)
{
    int r5;
    int r2;
    int r0;
    int r1;

    if (func_ov107_0229c2b4(r4, 4) != 0) {
        r5 = func_ov107_0229cec4(r4);
        r2 = func_ov107_0229ceb4(r4);
        func_ov002_0220a0b4(r4 + 0x22b4, r5, r2);
        func_ov107_0229c294(r4, 4);
    } else {
        r5 = func_ov107_0229cec4(r4);
        r2 = func_ov107_0229ceb4(r4);
        func_ov002_0220a05c(r4 + 0x22b4, r5, r2, 3, 1);
        r1 = *(unsigned char *) (r4 + 0x8d);
        *(unsigned char *) (r4 + 0xbb) = r1;
        func_ov002_02208098((void *) (r4), 8);
    }
}
