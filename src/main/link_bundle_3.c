/* link_bundle_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a7680 @ 0x020a7680, 0x2 bytes, Thumb
 * func_020a7660 @ 0x020a7660, 0x20 bytes, Thumb
 */

extern unsigned int data_020ccf94;
void func_020733d0(unsigned int, char *, int);

void func_020a7680(void) {}

void func_020a7660(void)
{
    char local = 1;
    func_020733d0(data_020ccf94, &local, 1);
}
