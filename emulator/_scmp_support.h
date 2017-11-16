static inline WORD16 _eac4kix(WORD16 *p) {
 T8 = FETCH();
 if (T8 == 0x80) T8 = E;
 if (T8 & 0x80) return (T8 | 0xFF00) + *p;
 return T8 + *p;
}
static inline WORD16 _eac4kaix(WORD16 *p) {
 T8 = FETCH();
 if (T8 == 0x80) T8 = E;
 if (T8 & 0x80) {
  *p += (T8 | 0xFF00);
  return *p;
 } else {
  T16 = *p;
  *p += T8;
  return T16;
 }
}
static inline WORD16 _eac4kixnoe(WORD16 *p) {
 T8 = FETCH();
 if (T8 & 0x80) return (T8 | 0xFF00) + *p;
 return T8 + *p;
}
static void _decimalAdd() {
 T16 = (T8 & 0x0F) + (AC & 0x0F) + CARRY;
 if (T16>= 10) {
  T16 = T16 + 0x06;
 }
 T16 = T16 + (T8 & 0xF0) + (AC & 0xF0);
 CARRY = 0;
 if (T16 > 0x99) {
  T16 = T16+ 0x60;CARRY = 1;
 }
 AC = T16 & 0xFF;
}
#define BINARYADD()  T16 = CARRY+AC+T8;OVERFLOW();AC = T16 & 0xFF;CARRY = (T16 >> 8) & 1
#ifdef  USEOVERFLOW
#define OVERFLOW()  OVERFLOW = ((((AC^T8) & 0x80) == 0) && (((AC^T16) & 0x80) == 0)) ? 1 : 0
#else
#define OVERFLOW()  {}
#endif
#define UPDATESASB() STATUS = (STATUS & 0xCF) | (SENSEA() ? 0x10:0x00) | (SENSEB() ? 0x20:0x00);
#define UPDATEOVCY()   STATUS = (STATUS & 0x3F) | ((OVERFLOW!=0) ? 64:0) | ((CARRY!=0) ? 128:0x00);
static BYTE8 getStatus() {
 UPDATESASB();UPDATEOVCY();
 return STATUS;
}