/* func_ov118_0229a8b4 @ 0x0229a8b4, 0x78 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(char *p, int a);
extern int func_ov118_0229a9ac(char *p);
extern int func_ov118_0229a950(char *p);
extern void func_ov002_0220a0b4(char *p, int a, int b);
extern void func_ov118_0229a440(char *p, int a);
extern void func_ov002_0220a05c(char *p, int a, int b, int c, int d);
extern void func_ov002_02208098(char *p, int a);

void func_ov118_0229a8b4(char *p)
{
    if (func_ov118_0229a460(p, 0x4000) != 0) {
        int v1 = func_ov118_0229a9ac(p);
        int v2 = func_ov118_0229a950(p);
        func_ov002_0220a0b4(p + 0x6c0, v1, v2);
        func_ov118_0229a440(p, 0x4000);
    } else {
        int v1 = func_ov118_0229a9ac(p);
        int v2 = func_ov118_0229a950(p);
        func_ov002_0220a05c(p + 0x6c0, v1, v2, 3, 1);
        *(unsigned char *) (p + 0xab) = *(unsigned char *) (p + 0x8d);
        func_ov002_02208098(p, 4);
    }
}
