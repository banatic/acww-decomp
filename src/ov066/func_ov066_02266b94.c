/* func_ov066_02266b94 @ 0x02266b94, 0x60 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov066_02266b14(void *);
extern void func_ov066_02266ad4(void *);
extern void func_ov066_02266a8c(void *);
extern void func_ov066_02266a4c(void *);
extern void func_ov066_02266bf4(void);

void func_ov066_02266b94(void *p)
{
    switch (*(unsigned short *) p) {
        case 3:
            func_ov066_02266b14(p);
            break;
        case 4:
            func_ov066_02266ad4(p);
            break;
        case 5:
            func_ov066_02266a8c(p);
            break;
        case 6:
            func_ov066_02266a4c(p);
            break;
    }
    func_ov066_02266bf4();
}
