#include "CRC_Xmodem.h"

void CRCXmodem::Calculate(unsigned char *FromAddr, unsigned short *ToAddr, unsigned char Size) {
  int i, ByteNo;
  unsigned short C;
  *ToAddr=0;
  for(ByteNo=1; ByteNo<=Size;ByteNo++,FromAddr++) {
    C=((*ToAddr>>8)^*FromAddr)<<8;
    for(i=0;i<8;i++)
      if(C&0x8000)C=(C<<1)^0x1021;
      else C=C<<1;
     *ToAddr=C^(*ToAddr<<8);
   }
}
