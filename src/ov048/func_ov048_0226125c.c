/* func_ov048_0226125c @ 0x0226125c, 0x124 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_02260e78(void *);
extern int func_02074308(void);
extern int func_020ec148(int);
extern int func_020730c8(void);
extern void *func_020eb92c(int);
extern void func_020641c8(void *);
extern void func_02064170(void *);
extern void func_02094fd4(void *);
extern void func_02094f7c(void *);
extern int func_020eb998(void *);
extern void *func_020eb9c4(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_020a8874(void *, void *, int);
extern void func_020a8a70(void *, void *, int, int);
extern void func_02068404(void *, int, void *);
extern void func_0206844c(void *, void *, void *);
extern void func_ov048_02262378(void *);
extern void func_ov048_022616b8(void *, int);
extern void func_02094f64(void *);
extern void func_02094fbc(void *);
extern void func_02064158(void *);
extern void func_020641b0(void *);
extern void *data_ov048_02263d20;

void func_ov048_0226125c(void *param)
{
    int n;
    void **arr;
    int val;
    unsigned char buf[0x1c];
    unsigned char buf1[0x20];
    unsigned char buf2[0x1c];
    unsigned char buf3[0x20];
    unsigned char buf4[0x20];
    void *elem;
    void *target;
    unsigned char i;

    if (func_ov048_02260e78(param) != 0) {
        return;
    }

    n = func_020ec148(func_02074308());
    if (n <= 0) {
        return;
    }

    arr = func_020eb92c(func_020730c8());

    func_020641c8(buf1);
    func_02064170(buf2);
    func_02094fd4(buf3);
    func_02094f7c(buf4);

    target = *(void **) ((char *) param + 0x40);

    for (i = 0; i < n; i++) {
        elem = arr[i];

        if (elem == 0) {
            continue;
        }

        func_020730c8();
        val = func_020eb998(elem);
        if (val != 0x1a) {
            continue;
        }

        func_020730c8();
        MI_CpuCopy8(func_020eb9c4(elem), &buf[2], val);
        if (buf[0x1a] != 0) {
            continue;
        }

        MI_CpuCopy8(elem, (char *) param + 0x30c, 0xe0);

        func_020a8874(buf2, &buf[2], 6);
        func_020a8a70(buf1, buf2, 0, 0);
        func_020a8874(buf4, &buf[0xe], 6);
        func_020a8a70(buf3, buf4, 0, 0);

        func_02068404(target, 3, buf1);
        func_02068404(target, 4, buf3);

        buf[0] = 0x57;
        func_0206844c(target, buf, data_ov048_02263d20);

        func_ov048_02262378(param);
        func_ov048_022616b8(param, 0);

        break;
    }

    func_02094f64(buf4);
    func_02094fbc(buf3);
    func_02064158(buf2);
    func_020641b0(buf1);
}
