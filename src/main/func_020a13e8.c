/* func_020a13e8 @ 0x020a13e8, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    char pad_00[0x68];
    volatile int unk_68;
} UnkStruct_020a13e8;

extern UnkStruct_020a13e8 *data_020ccf94;

extern int func_020a1298(void);
extern int func_020a12d4(void);
extern int func_020a12ac(void);
extern void func_0209ef7c(const void *);
extern int func_0209877c(const void *);
extern void func_020962a4(int, int);
extern void func_0203d394(void);
extern void *func_020985cc(const void *, const void *, int, int);

extern unsigned char data_020e3a68[];
extern unsigned char data_021dc7a8[];
extern unsigned char data_021dc7bc[];

void func_020a13e8(void)
{
    if (func_020a1298() != 0) {
        return;
    }
    if (func_020a12d4() != 0) {
        func_0209ef7c((const void *) data_021dc7a8);
    }
    if (func_020a12ac() != 0) {
        UnkStruct_020a13e8 *p = data_020ccf94;
        p->unk_68 = 0;
        func_020962a4(p->unk_68, 0);
        func_0203d394();
        return;
    } else {
        const void *s = (const void *) data_021dc7bc;
        int a = func_0209877c(s);
        UnkStruct_020a13e8 *p = data_020ccf94;
        p->unk_68 = 0;
        func_020962a4(p->unk_68, a);
        func_020985cc(s, (const void *) data_020e3a68, 0, a);
    }
}
