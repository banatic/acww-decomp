/* func_0206053c @ 0x0206053c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xd];
    unsigned char unk_0D;
} UnkStruct_0206053c;
extern UnkStruct_0206053c *func_020606e4(void *a, int);
extern unsigned long func_020606fc(void *a, void *b);
extern int func_021077e8(unsigned int *);
extern int func_020b9eec(UnkStruct_0206053c *e, int v, int k);
int func_0206053c(void *a, void *b)
{
    UnkStruct_0206053c *e = func_020606e4(a, (int) b);
    unsigned int k = e->unk_0D;
    unsigned int t1;
    unsigned int t2;
    if (k == 2) {
        t1 = 1;
    } else {
        t1 = 0;
    }
    if (t1 > 0) {
        return 1;
    }
    if (k == 1) {
        t2 = 1;
    } else {
        t2 = 0;
    }
    if (t2 == 0) {
        func_020b9eec(e, func_021077e8((unsigned int *) func_020606fc(a, b)), 1);
    }
    return 0;
}
