/* scene_motion_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02017590 @ 0x02017590, 0x42 bytes, Thumb
 * func_02017574 @ 0x02017574, 0x1a bytes, Thumb
 * func_02017550 @ 0x02017550, 0x24 bytes, Thumb
 */

extern int func_02057bd4(void);
extern int func_02057d0c(int a, int b);
extern int func_02057b90(int a, int b);
extern void func_02019af0(void *, unsigned long);
extern int func_02095380(int n);
extern int func_02057bf0(int);

int func_02017590(void *s, int v)
{
    if (func_02057bd4() && func_02057d0c(8, v)) {
        func_02057b90(8, v);
        ((char *) s)[0x98] = 0;
        func_02019af0(s, 0);
        func_02095380(0x72);
    }
    return 1;
}

void func_02017574(unsigned char *p, int event)
{
    if (func_02057bf0(8)) {
        p[0x98] = 1;
    }
}

void func_02017550(unsigned char *obj, int event)
{
    if (func_02057bf0(8) == 0) {
        obj[0x98] = 2;
        func_02019af0(obj, 1);
    }
}
