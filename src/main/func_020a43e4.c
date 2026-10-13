/* func_020a43e4 @ 0x020a43e4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_021c75b8;
typedef struct {
    int unk_00;
    int unk_04;
} some_struct;
extern some_struct *func_020682e0(int);
extern int func_02068320(some_struct *);
extern int func_0204e414(int);
extern int func_0204dfe0(int, int *, int, int);
extern int func_020b5e10(int);
extern void func_020b63f4(int, int, int *, unsigned int, int, int, int);
extern void func_020a4e94(void *, int);

void func_020a43e4(void *arg)
{
    some_struct *p;
    int local[3];
    int cond;
    int v1, v2, v3, v4;

    p = func_020682e0(0);
    cond = (data_021c75b8 == 2) ? 1 : 0;
    if (cond != 0) {
        if (p->unk_04 == 0) {
            v1 = func_02068320(p);
            v2 = func_0204e414(v1);
            v3 = func_0204dfe0(v2, local, 0, 0);
            v4 = func_020b5e10(v3);
            func_020b63f4(v4, 0, local, 0x00400000, -32768, 3, 2);
            func_020a4e94(arg, 0);
        }
    }
}
