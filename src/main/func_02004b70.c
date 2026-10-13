/* func_02004b70 @ 0x02004b70, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f23b4(void *, void *, unsigned int, void *, int);
extern void func_0206e904(void);
extern int data_0213fff0;

extern unsigned char data_020d72e0[];
extern unsigned char data_0213fff4[];
extern unsigned char data_021fd1bc[];

void func_02004b70(void)
{
    data_0213fff0 = 0;
    func_020f23b4((void *) data_021fd1bc, (void *) data_0213fff4, 0x00080000u, (void *) data_020d72e0, 1);
    func_0206e904();
}
