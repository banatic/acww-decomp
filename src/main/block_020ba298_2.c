/* block_020ba298_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba9d8 @ 0x020ba9d8, 0x50 bytes, Thumb
 * func_020ba9b4 @ 0x020ba9b4, 0x24 bytes, Thumb
 * func_020ba8d8 @ 0x020ba8d8, 0xdc bytes, Thumb
 */

extern int func_0206fea4(void);
extern void func_020b1800(void *arg);
extern void func_020bc388(void *arg);
extern void func_020bc380(void *arg);
extern void func_020bb6d8(void *arg);
extern void func_020bbe94(void *arg);
extern int data_021f6cd8;
extern char data_021f7280;
extern void func_020bc1bc(int *);
extern int data_021f8b48;
extern int func_0205bfdc(void *);
extern void GX_LoadBGPltt(void *, int, int);
extern void GXS_LoadBGPltt(void *, int, int);
extern void func_020e9898(void *);
extern void func_020bc4dc(void *);
extern void func_020b1774(void *);
extern void func_020bbe8c(void *);
extern int data_021f6d2c;
extern int data_021f6cc0;
extern void *data_021f8b2c;
extern void *data_021f8b34;
extern char data_021f75b0[];
extern void *data_021f8b14[3];

int func_020ba9d8(void *p)
{
    if (data_021f6cd8) {
        if (func_0206fea4() == 0) {
            func_020b1800(&data_021f7280);
        }
        func_020bc388(((char *) &data_021f8b48));
    } else {
        func_020bc380(((char *) &data_021f8b48));
    }

    func_020bb6d8(((char *) data_021f75b0));
    p = (void *) ((char *) p + 0x50);
    func_020bbe94(p);
    return 1;
}

int func_020ba9b4(void)
{
    if (data_021f6cd8 != 0) {
        func_020bc1bc(&data_021f8b48);
    }
    return 1;
}

int func_020ba8d8(char *p)
{
    int ret;
    int i, j, k;
    void **q;
    void *v;

    ret = func_0205bfdc(&data_021f6d2c);
    GX_LoadBGPltt(&data_021f6cc0, 0, 2);
    GXS_LoadBGPltt(&data_021f6cc0, 0, 2);
    q = &data_021f8b2c;
    v = *q;
    if (v != 0) {
        func_020e9898(v);
    }
    *q = 0;
    q = &data_021f8b34;
    v = *q;
    if (v != 0) {
        func_020e9898(v);
    }
    *q = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            q = (void **) (data_021f75b0 + i * 8 + j * 4 + 0x1544);
            v = *(void **) (data_021f75b0 + i * 8 + j * 4 + 0x1544);
            if (v != 0) {
                func_020e9898(v);
            }
            *q = 0;
        }
    }
    q = data_021f8b14;
    for (k = 0; k < 3; k++) {
        v = *q;
        if (v != 0) {
            func_020e9898(v);
            *q = 0;
        }
        q++;
    }
    if (data_021f6cd8 != 0) {
        func_020bc4dc(&data_021f8b48);
    }
    func_020b1774(((int *) &data_021f7280));
    p += 0x50;
    func_020bbe8c(p);
    return ret;
}
