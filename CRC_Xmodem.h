#ifndef CRC_Xmodem_h
#define CRC_Xmodem_h

class CRCXmodem {
  public:
    void Calculate(unsigned char *FromAddr, unsigned short *ToAddr, unsigned char Size);
  
};

#endif


