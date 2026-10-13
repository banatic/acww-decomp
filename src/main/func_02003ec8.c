/* func_02003ec8 @ 0x02003ec8, 0x174 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e9948(void *heap, unsigned int size);

extern unsigned char data_0213f0b0[];
extern unsigned char data_0213f0d0[];
extern unsigned char data_0213f0f0[];
extern unsigned char data_0213f110[];
extern unsigned char data_0213f130[];
extern unsigned char data_0213f150[];
extern unsigned char data_0213f170[];
extern unsigned char data_0213f190[];
extern unsigned char data_0213f1b0[];
extern unsigned char data_0213f1d0[];
extern unsigned char data_0213f1f0[];
extern unsigned char data_0213f210[];
extern unsigned char data_0213f230[];

void func_02003ec8(void *heap, int kind)
{
    void *obj;

    switch (kind) {
        case 0:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0b0;
            }
            break;
        case 1:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0d0;
            }
            break;
        case 2:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0f0;
            }
            break;
        case 3:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f110;
            }
            break;
        case 4:
            obj = func_020e9948(heap, 0x14);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f230;
            }
            break;
        case 5:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f130;
            }
            break;
        case 6:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f1b0;
            }
            break;
        case 7:
            obj = func_020e9948(heap, 0x18);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f1d0;
            }
            break;
        case 8:
            obj = func_020e9948(heap, 0x14);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f1f0;
            }
            break;
        case 9:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f150;
            }
            break;
        case 10:
            obj = func_020e9948(heap, 0x14);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f210;
            }
            break;
        case 255:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f170;
            }
            break;
        default:
            obj = func_020e9948(heap, 0x10);
            if (obj) {
                *(unsigned int *) obj = (unsigned int) data_0213f190;
                *(unsigned int *) obj = (unsigned int) data_0213f0b0;
            }
            break;
    }
}
