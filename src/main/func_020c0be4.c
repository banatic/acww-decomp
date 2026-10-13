/* func_020c0be4 @ 0x020c0be4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020c0c58(int);
extern void func_020c0c78(int);
extern void func_020bec14(void *data_021fba00, int k, short *p);
extern int data_021fba00;
extern short data_021f6cfc[];

void func_020c0be4(int a)
{
    unsigned int i;
    void *p = &data_021fba00;

    func_020c0c58(a);
    func_020c0c78(a);
    for (i = 0; i < 5; i++) {
        func_020bec14(p, (int) (i + 10), &data_021f6cfc[i]);
    }
}
