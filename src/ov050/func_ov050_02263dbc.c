/* func_ov050_02263dbc @ 0x02263dbc, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c2c8(void *, int);
extern int func_020e8b4c(int, int);
extern short data_020c80f0;
extern void func_ov050_02264834(void *, int);
extern int func_ov050_02260718(void *);

struct UnkStruct_02263dbc {
    char pad_00[0x8e];
    short unk_8E;
};

int func_ov050_02263dbc(struct UnkStruct_02263dbc *p)
{
    int a, b;
    a = func_0201c2c8(p, 4);
    b = func_020e8b4c(p->unk_8E, a);
    if (b >= data_020c80f0) {
        func_ov050_02264834(p, 0xe);
    } else {
        func_ov050_02260718(p);
    }
    return 1;
}
