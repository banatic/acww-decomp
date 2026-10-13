/* func_ov050_02264210 @ 0x02264210, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov050_022609d8(void *);
extern void *func_0200338c(void *, int);
extern void func_ov050_02264834(void *, int);

typedef struct {
    char pad_00[0x654];
    int state;
    char pad_658[0xE8];
    unsigned char flag;
} UnkStruct_02264210;

int func_ov050_02264210(void *param)
{
    UnkStruct_02264210 *p;
    int state;

    p = func_0200338c(func_ov050_022609d8(param), 0);
    state = p->state;
    if (state != 0 && (state == 1 || p->flag == 0)) {
        func_ov050_02264834(param, 1);
    }
    return 1;
}
