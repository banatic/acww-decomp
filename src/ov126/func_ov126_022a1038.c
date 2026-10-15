/* func_ov126_022a1038 @ 0x022a1038, 0xd0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern unsigned char *func_ov126_022a0c1c(void *);
extern int func_ov002_02208008(void *);
extern int func_ov095_02299a54(void *, int);
extern void func_ov002_0220a2b4(void *);
extern void func_ov002_0220a254(void *);
extern void func_ov002_0220a314(void *);
extern void func_ov126_0229ff68(void *);
extern void func_ov126_0229f7b8(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov126_0229fe28(void *);
extern int func_ov126_0229fdd4(void *);
extern int func_ov126_0229fcfc(void *);
extern int func_ov126_0229fd64(void *);
extern int func_ov126_0229fcd8(void *);

void func_ov126_022a1038(char *arg)
{
    int v;

    if (func_ov002_02208014(arg)) {
        func_ov126_022a0c1c(arg);
        return;
    }

    v = func_ov002_02208008(arg);

    switch (func_ov095_02299a54(arg + 0x19c, v)) {
        case 1:
            func_ov002_0220a2b4(arg + 0x3f90);
            func_ov126_0229ff68(arg);
            break;
        case 2:
            func_ov002_0220a254(arg + 0x3f90);
            func_ov126_0229ff68(arg);
            break;
        case 3:
            func_ov002_0220a314(arg + 0x3f90);
            func_ov126_0229ff68(arg);
            break;
        case 4:
            func_ov002_0220a2b4(arg + 0x3f90);
            func_ov126_0229f7b8(arg, 0x80);
            func_ov002_02208098((void *) (arg), 6);
            func_ov126_0229ff68(arg);
            break;
        default:
            if (func_ov126_0229fe28(arg)) {
                return;
            }
            if (func_ov126_0229fdd4(arg)) {
                return;
            }
            if (func_ov126_0229fcfc(arg)) {
                return;
            }
            if (func_ov126_0229fd64(arg)) {
                return;
            }
            if (func_ov126_0229fcd8(arg)) {
                return;
            }
            break;
    }
}
