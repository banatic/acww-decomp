/* func_020a91d8 @ 0x020a91d8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9260(void *obj);
extern int data_020e3dc4;

void *func_020a91d8(void *obj)
{
    *(void **) obj = &data_020e3dc4;
    func_020a9260(obj);
    return obj;
}
