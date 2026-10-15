/* func_020861dc @ 0x020861dc, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern volatile u8 data_020e54a8;
extern void *data_021c80bc;
extern u8 data_021e5a2c[];

extern int func_020867a0(void *);
extern void func_02003738(unsigned char *);
extern void *func_020867e0(void *record);
extern void func_02095238(void *record);
extern void *func_0207cec0(u8 *, int);
extern int func_0208150c(void *);
extern int func_02003704(int);
extern int func_0208642c(void *, void *);
extern int func_020862ec(void *, void *);
extern int func_020644cc(int);
extern int func_020984e8(void);
extern int func_02099870(int);
extern void func_020867e4(void *, int);
extern int func_0207cc54(int, int, int);
extern void func_020867a4(void *, int);

void func_020861dc(void *a0)
{
    int t;
    u8 mask;
    void *ptr;
    int best;
    int cnt;
    int i;
    void *obj;
    void *o2;
    int v;

    t = (data_020e54a8 == 0);
    if (t) {
        ptr = data_021c80bc;
        func_02003738((unsigned char *) func_020867a0(a0));
        func_02095238(func_020867e0(a0));
        if (ptr != 0) {
            mask = 0;
            best = -1;
            cnt = 0;
            for (i = 0; i < 8; i++) {
                obj = func_0207cec0(data_021e5a2c, i);
                if (obj != 0 && func_02003704(func_0208150c(obj))) {
                    v = func_0208642c(obj, ptr);
                    if (v > best) {
                        mask = 1 << i;
                        cnt = 1;
                        best = v;
                    } else if (v == best) {
                        mask |= 1 << i;
                        cnt++;
                    }
                }
            }
            v = func_020862ec(a0, ptr);
            if (cnt == 0 || v > best || (v > 0 && v == best && func_020644cc(2) == 0)) {
                func_020867e4(a0, func_02099870((int) func_020984e8()));
            } else {
                o2 = func_0207cec0(data_021e5a2c, func_0207cc54(mask, cnt, 8));
                if (o2 != 0 && func_02003704(func_0208150c(o2))) {
                    func_020867a4(a0, func_0208150c(o2));
                }
            }
        }
    }
}
