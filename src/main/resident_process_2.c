/* resident_process_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209db24 @ 0x0209db24, 0x2c bytes, Thumb
 * func_0209dae8 @ 0x0209dae8, 0x3c bytes, Thumb
 */

extern void *func_020edf70(int size);
extern void *func_020ee660(void *);
extern unsigned int data_020da13c;
extern unsigned int data_020e360c;
extern void func_020a53c4(void);
extern int func_0202f12c(int, int, int);
extern int func_0202f134(int, int, int, int);
extern unsigned short data_020d1adc[8];

void *func_0209db24(void)
{
    void *r4;
    void *r0;

    r4 = func_020edf70(0x50);
    if (r4 != 0) {
        func_020ee660(r4);
        *(unsigned int *) r4 = (unsigned int) &data_020da13c;
        *(unsigned int *) r4 = (unsigned int) &data_020e360c;
    }
    return r4;
}

void func_0209dae8(void)
{
    int r5;
    int r4;
    int r7;
    int r0;
    int r1;
    int r2;
    int r3;

    func_020a53c4();
    r5 = func_0202f12c(0, 0, 1);
    r4 = 0;
    r7 = 0;
    while (r4 < 7) {
        r0 = data_020d1adc[r4];
        r1 = r5;
        r2 = r7;
        r3 = r7;
        func_0202f134(r0, r1, r2, r3);
        r4++;
    }
}
