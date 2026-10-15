/* func_ov046_02260e34 @ 0x02260e34, 0x88 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int func_020b1328(int *);
extern void *func_020b1954(void *);
extern int func_020b1394(void *, int);
extern void func_02068404(int, int, void *);
extern void *func_020b193c(void *);
extern void func_020b1310(void);

void func_ov046_02260e34(void *self)
{
    int local0 = 0;
    char local1[0x24];

    if (func_020b1328(&local0) == 0) {
        if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
            *(int *) ((char *) self + 0xdc) = 0x2f;
        } else {
            *(int *) ((char *) self + 0xdc) = 0x11;
        }
    } else {
        if (func_020b1328(&local0) == 1) {
            func_020b1954(local1);
            func_020b1394(local1, local0);
            func_02068404(*(int *) ((char *) self + 0x40), 7, local1);
            *(int *) ((char *) self + 0xdc) = 0x39;
            func_020b193c(local1);
        } else {
            *(int *) ((char *) self + 0xdc) = 0x3a;
        }
        func_020b1310();
    }
}
