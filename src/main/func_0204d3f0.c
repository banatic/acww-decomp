/* func_0204d3f0 @ 0x0204d3f0, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b67d4(void);
extern int func_020b6804(void);
extern int func_020b6680(void);
extern int func_020b66b0(void);
extern int func_0204e8c4(const void *, int);
extern int func_02060eac(const void *, int, int);
extern int func_0204d858(int, int);
extern void func_0204d530(void *, void *, int);
extern int func_0204dc34(int, int, int);
extern void *func_0204f86c(int, int);
extern int func_0204d4bc(void *, int, int, int);
extern int data_021e9aac;
extern int data_021ebcd4;
typedef struct {
    int key;
    int result;
    int pad_08;
    int pad_0C;
} Elem;
Elem *func_0204d3f0(void *p0, int *p1, int p2, int p3)
{
    Elem *r5 = 0;
    int r4;
    if (((func_020b65c4() == 0) || (func_020b65c4() == 0x31)) || (func_020b65c4() == 0x2c)) {
        r5 = (Elem *) func_0204e8c4(&data_021e9aac, p3);
        goto end;
    }
    if (func_020b67d4() != 0) {
        r5 = (Elem *) func_02060eac(&data_021ebcd4, func_020b6804(), p3);
        goto end;
    }
    if (func_020b6680() != 0) {
        int r4_tmp;
        r4_tmp = func_020b66b0();
        r4 = func_0204d858(p3, 4);
        r5 = (Elem *) r4;
        func_0204d530(p0, r5, 0);
        r5 = (Elem *) func_0204dc34((int) r5, r4_tmp, p3);
        goto end;
    }
    if (p1 == 0) {
        goto end;
    }
    if (p2 <= 0) {
        goto end;
    }
    r5 = (Elem *) func_0204f86c(p2, p3);
    if (r5 == 0) {
        goto end;
    }
    r4 = 0;
    while (r4 < p2) {
        Elem *elem;
        elem = &r5[r4];
        elem->key = *p1;
        elem->result = func_0204d4bc(p0, elem->key, r4, p3);
        p1++;
        r4++;
    }

end:
    return r5;
}
