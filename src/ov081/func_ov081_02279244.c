/* func_ov081_02279244 @ 0x02279244, 0x2c bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(const void *);
extern void func_0203e020(const void *);
extern void func_ov081_022792e0(const void *, int);

int func_ov081_02279244(const void *p)
{
    if (!func_02014868((const char *) p + 0x618)) {
        func_0203e020(p);
        func_ov081_022792e0(p, 2);
    }
    return 1;
}
