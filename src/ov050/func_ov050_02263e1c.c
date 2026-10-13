/* func_ov050_02263e1c @ 0x02263e1c, 0x58 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c0e0(void *);
extern int func_0201c040(void *, int *, int *);
extern int func_020a7278(void);
extern int func_0201c054(void *, int, int, int);
extern void func_ov050_02264834(void *, int);

typedef struct {
    unsigned char pad_00[0x64];
    int unk_64;
} Data_020ccf94;

extern Data_020ccf94 *data_020ccf94;

int func_ov050_02263e1c(void *p)
{
    int a, b;
    if (func_0201c0e0(p) && (a = 4, b = 4, func_0201c040(p, &a, &b)) && a == 4 && func_020a7278()) {
        func_0201c054(p, 1, data_020ccf94->unk_64, 4);
        func_ov050_02264834(p, 13);
    }
    return 1;
}
