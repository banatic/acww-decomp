/* func_020178a0 @ 0x020178a0, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02019de4(void *param1, void *param2);
extern void func_02057bb8(unsigned short *out);
extern int func_02057bd4(int val);
extern void func_02057cb8(void *p);
extern void func_02016764(void *a, void *b, int c, unsigned short d, int e, int f, int g, int h);
extern void func_02091230(int a, void *b, int c, int d);
extern void func_0200442c(void *a, int b, int c, int d);
extern void func_02019af0(void *a, int b);
extern void func_020199ec(void *a, void *b, void *c);
extern volatile unsigned short data_020c80f8;

int func_020178a0(void *param1, char *param2)
{
    char *r6;
    unsigned short vbuf[1];
    int val;

    r6 = (char *) func_02019de4(param1, param2);

    func_02057bb8(vbuf);
    val = vbuf[0];
    *(unsigned short *) (r6 + 0x22) = val;

    if (func_02057bd4(val) != 0) {
        func_02057cb8(param2);
    }

    func_02016764((void *) (param2 + 0x334), param2, 0x28, data_020c80f8, 1, 0x1000, 0, 0);

    func_02091230(0x61, (void *) (param2 + 0x5c), 0, 0);
    func_0200442c((void *) (param2 + 0x514), 0x76, 0x7f, 0);

    func_02019af0(param1, 0);

    *(unsigned char *) ((char *) param1 + 4) = 0x14;
    *(unsigned char *) ((char *) param1 + 5) = (unsigned char) (*(int *) ((char *) param1 + 0x14));

    func_020199ec(param1, (char *) param1 + 6, r6 + 0x22);

    return 1;
}
