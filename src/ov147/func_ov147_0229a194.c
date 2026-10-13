/* func_ov147_0229a194 @ 0x0229a194, 0x38 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov147_0229a6e4(void *);
extern void func_ov147_02299ad0(void *);
extern void func_020ee62c(void *);
extern void func_020edf54(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_ov147_0229aa28[];

void *func_ov147_0229a194(void *p)
{
    *(void **) p = (void *) data_ov147_0229aa28;
    func_ov147_0229a6e4((char *) p + 0xb0);
    func_ov147_02299ad0((char *) p + 0x54);
    *(void **) p = (void *) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
