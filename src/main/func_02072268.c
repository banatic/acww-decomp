/* func_02072268 @ 0x02072268, 0xc6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e7bc(int a0, int a2);
extern void *func_02062fbc(void *);
extern int func_020a8be4(void *, void *);
extern void func_02072e64(void *, void *);
extern void func_02072f54(void *, int);
extern void func_02072e18(void *, int);
extern void *func_020641c8(void *);
extern void *func_02094fd4(void *);
extern void func_020642fc(void *);
extern void func_020641e0(void *, void *);
extern void *func_0209529c(void *);
extern void func_02095044(void *, void *);
extern void func_02095038(void *, void *);
extern void func_02072eec(void *, void *);
extern int func_0209526c(void *);
extern void func_020642f8(void *);
extern void *func_02094fbc(void *);
extern void *func_020641b0(void *);
extern void *func_02062f4c(void *);

int func_02072268(int a0, void *a1, int a2)
{
    unsigned char buf0[0x28];
    unsigned char buf1[0x20];
    unsigned char buf2[0x20];
    unsigned char buf3[0x2c];
    unsigned char *p4;
    unsigned char b1, b2;

    if (a2 < 0x32) {
        p4 = (unsigned char *) func_0206e7bc(a0, a2);
        if (p4 != 0) {
            func_02062fbc(buf0);
            func_020a8be4(buf0, p4);
            func_02072e64(a1, buf0);
            b1 = *(p4 + 0x32);
            func_02072f54(a1, b1);
            b2 = *(p4 + 0x33);
            func_02072e18(a1, b2);
            func_020641c8(buf1);
            func_020a8be4(buf1, p4 + 0x24);
            func_02094fd4(buf2);
            func_020a8be4(buf2, p4 + 0x16);
            func_020642fc(buf3);
            func_020641e0(buf3, buf1);
            func_0209529c(buf3 + 0xe);
            func_02095044(buf3 + 0xe, buf2);
            func_02095038(buf3 + 0xe, buf3);
            func_02072eec(a1, buf3 + 0xe);
            func_0209526c(buf3 + 0xe);
            func_020642f8(buf3);
            func_02094fbc(buf2);
            func_020641b0(buf1);
            func_02062f4c(buf0);
            return 1;
        }
    }
    return 0;
}
