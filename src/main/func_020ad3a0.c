/* func_020ad3a0 @ 0x020ad3a0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020acea4(void *dst, unsigned int src);
extern unsigned int data_021f47d0;
extern unsigned int data_021f49a0[];
extern unsigned int data_021c9b24;
extern unsigned int data_021f4904;
extern unsigned int data_021f4938;
extern unsigned int data_021f496c;
extern unsigned int data_021f489c;
extern unsigned int data_021f48d0;

void func_020ad3a0(void)
{
    unsigned int *p;
    unsigned int v;
    unsigned int i;

    data_021f47d0 = 0;
    p = data_021f49a0;
    for (i = 0; i < 3; i++) {
        *p = 0;
        p += 6;
    }
    v = data_021c9b24;
    func_020acea4(&data_021f4904, v);
    func_020acea4(&data_021f4938, v);
    func_020acea4(&data_021f496c, v);
    func_020acea4(&data_021f489c, v);
    func_020acea4(&data_021f48d0, v);
}
