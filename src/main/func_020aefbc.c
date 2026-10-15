/* func_020aefbc @ 0x020aefbc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1e28[];

int func_020af028(unsigned short *);

unsigned char func_020aefbc(unsigned short *argument0)
{
    unsigned char result;
    int index;

    index = func_020af028((unsigned short *) argument0);
    result = data_020d1e28[index];
    return result;
}
