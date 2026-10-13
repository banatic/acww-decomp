/* func_0205dc58 @ 0x0205dc58, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c4fc(void);
extern void func_0205dbb8(void *ptr);
extern void func_020e9abc(void);

extern unsigned char data_021c9ad4[];
extern unsigned char data_021c9df4[];

void func_0205dc58(void)
{
    void *ptr;
    int *global_ptr;

    func_0205c4fc();
    func_0205dbb8((void *) data_021c9df4);
    global_ptr = (int *) data_021c9ad4;
    if (*global_ptr != 0) {
        func_020e9abc();
    }
}
