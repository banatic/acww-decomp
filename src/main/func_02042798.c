/* func_02042798 @ 0x02042798, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094fd4(void *);
extern int func_02094fbc(void *);
extern int func_0207cec0(const void *, int);
extern unsigned int func_0208150c(unsigned int object);
extern int func_02003648(unsigned char *item);
extern int func_0208249c(char *out, int value);
extern int func_0203d7c4(int, void *);
extern int func_020644cc(int);
extern void MI_CpuCopy8(const unsigned char *, void *, unsigned int);
extern int func_0203fcb4(int, void *, int);
extern void *func_02077f3c(int, const void *, unsigned char, unsigned char, unsigned char);
extern unsigned int data_020cb5c0[];
extern const unsigned char data_020db864[];

extern unsigned char data_021e5a2c[];

void func_02042798(int unused, unsigned char *p, unsigned char *q)
{
    int i;
    int r5;
    int c;
    int v10;
    int v14;
    char buf18[8];
    char buf20[36];

    func_02094fd4(buf20);
    i = 0;
    v10 = 0;
    c = 0;
    r5 = -1;
    v14 = i;

    for (i = 0; i < 7; i++) {
        int code;
        unsigned int record;
        unsigned int item;
        r5 = -1;
        code = *(unsigned short *) p;
        switch (code) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                if ((record = func_0207cec0((const void *) data_021e5a2c, code)) != 0 && (item = func_0208150c(record)) != 0) {
                    func_0208249c(buf20, func_02003648((unsigned char *) item));
                    func_0203d7c4(c, buf20);
                    r5 = func_020644cc(3) + 0x1e;
                }
                break;
            default:
                if (code >= 0x1c && code < 0x3a) {
                    int ret;
                    MI_CpuCopy8(q, buf18, 8);
                    ret = func_0203fcb4(code, buf18, v10);
                    switch (ret) {
                        case 2:
                        case 3:
                            r5 = data_020cb5c0[code - 0x1c];
                            break;
                        default:
                            break;
                    }
                }
                break;
        }
        if (r5 != ~v14) {
            func_02077f3c(r5, data_020db864, q[5], q[4], q[3]);
        }
        p += 12;
    }

    func_02094fbc(buf20);
}
