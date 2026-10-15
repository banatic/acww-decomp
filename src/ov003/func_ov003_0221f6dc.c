/* func_ov003_0221f6dc @ 0x0221f6dc, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_0221efec(void *, const void *);
extern void *func_ov003_0221ef94(void *);
extern int func_ov003_0221ef90(void *);
extern void func_ov003_0221ef44(void *, void *, unsigned short);
extern void func_ov003_0221efc0(void *);
extern unsigned char data_ov003_0223cad0;
extern void *data_021c67a4;
extern unsigned int data_021c67d0[3];

void func_ov003_0221f6dc(void *self)
{
    unsigned int tmp[3];
    unsigned char local[0x1c];
    void *ptr;
    int result;
    int id;

    data_ov003_0223cad0 = 0;
    if (data_021c67a4 == 0) {
        return;
    }

    tmp[0] = data_021c67d0[0];
    tmp[1] = data_021c67d0[1];
    tmp[2] = data_021c67d0[2];

    func_ov003_0221efec(local, tmp);
    ptr = func_ov003_0221ef94(local);
    if (ptr != 0) {
        id = 0x80d;
        result = func_ov003_0221ef90(local);
        switch (result) {
            case 0x11:
                id = 0x80b;
                break;
            case 0x12:
                data_ov003_0223cad0 = 1;
                break;
            case 5:
                id = 0x80e;
                break;
            case 0xf:
                id = 0x80c;
                break;
            default:
                break;
        }
        func_ov003_0221ef44((unsigned char *) self + 0x310, ptr, id);
    }
    func_ov003_0221efc0(local);
}
