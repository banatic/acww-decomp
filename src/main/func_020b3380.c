/* func_020b3380 @ 0x020b3380, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b3720(void *param1, void *param2);
extern void func_020b3634(void *param1, void *param2);
extern void func_020b3504(void *param1, void *param2);
extern void func_020b35c0(void *param1, void *param2);

void func_020b3380(void *param1, void *param2, void *param3)
{
    void *r5 = param1;
    void *r4 = param2;
    void *r1 = param3;

    func_020b3720(r5, r1);

    if (r4 != 0) {
        func_020b3634((char *) r5 + 0x14, r4);
        func_020b3504((char *) r5 + 0x18, r4);
        func_020b35c0((char *) r5 + 0x34, r4);
    }
}
