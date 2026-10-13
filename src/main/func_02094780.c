/* func_02094780 @ 0x02094780, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *obj, int a, int b, int c);
extern void func_0203423c(void *obj);
extern int func_02094cf8(int a1, int a2, int a3, int a4, int a5, int a6);
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern unsigned char data_020e54a8;
extern int data_020e2788;
extern int data_020e29dc;

typedef struct {
    unsigned char pad_00[0x34];
    int code;
    unsigned char tail[0xc];
} UnkStruct_02094780;

int func_02094780(int p0, int p1, unsigned short *p2, int p3)
{
    UnkStruct_02094780 obj;
    int code;
    int last;
    int first;
    int result;
    unsigned int cond;

    func_02034270(&obj, p1, 0, 0);

    code = obj.code;
    last = (int) &data_020e2788;
    result = 3;
    first = 2;

    cond = (data_020e54a8 == 1);
    if (cond != 0) {
        if (code == 9 || code == 3) {
            result = func_02094cf8(first, p0, p1, (int) p2, p3, last);
        }
    } else {
        if (code == 0x16) {
            first = 0x21;
            if (p2 != 0) {
                *p2 = 0;
            }
            last = (int) &data_020e29dc;
        } else if (func_020ba4e4() == 1) {
            first = 0x20;
            if (p2 != 0) {
                *p2 = 0;
            }
            last = (int) &data_020e29dc;
        } else {
            if (code == 3) {
                goto L_func;
            }
            if (code == 0x13) {
                first = 0x17;
                goto L_after;
            }
            goto L_after;
        L_func:
            if (func_020b6598() != 0) {
                first = 0x18;
                last = 0;
            }
        L_after:;
        }
        result = func_02094cf8(first, p0, p1, (int) p2, p3, last);
    }

    func_0203423c(&obj);
    return result;
}
