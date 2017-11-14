case 0x00: /**** halt ****/
    ;;CYCLES += 8;break;
case 0x01: /**** xae ****/
    T8 = AC;AC = E;E = T8;CYCLES += 7;break;
case 0x02: /**** ccl ****/
    CARRY = 0;CYCLES += 5;break;
case 0x03: /**** scl ****/
    CARRY = 1;CYCLES += 5;break;
case 0x04: /**** dint ****/
    STATUS &= 0xF7;CYCLES += 6;break;
case 0x05: /**** ien ****/
    STATUS |= 0x08;CYCLES += 6;break;
case 0x06: /**** csa ****/
    UPDATESASB();UPDATEOVCY();AC = STATUS;CYCLES += 5;break;
case 0x07: /**** cas ****/
    STATUS = AC;OVERFLOW = (AC >> 6) & 1;CARRY = (AC >> 7) & 1;UPDATESASB();FLAGS(AC & 7);CYCLES += 6;break;
case 0x08: /**** nop ****/
    ;;CYCLES += 5;break;
case 0x09: /**** db 09 ****/
    break;
case 0x0a: /**** db 0a ****/
    break;
case 0x0b: /**** db 0b ****/
    break;
case 0x0c: /**** db 0c ****/
    break;
case 0x0d: /**** db 0d ****/
    break;
case 0x0e: /**** db 0e ****/
    break;
case 0x0f: /**** db 0f ****/
    break;
case 0x10: /**** db 10 ****/
    break;
case 0x11: /**** db 11 ****/
    break;
case 0x12: /**** db 12 ****/
    break;
case 0x13: /**** db 13 ****/
    break;
case 0x14: /**** db 14 ****/
    break;
case 0x15: /**** db 15 ****/
    break;
case 0x16: /**** db 16 ****/
    break;
case 0x17: /**** db 17 ****/
    break;
case 0x18: /**** db 18 ****/
    break;
case 0x19: /**** sio ****/
    SOUT(E&1);E = (E >> 1) | (SIN() ? 0x80:0x00);CYCLES += 5;break;
case 0x1a: /**** db 1a ****/
    break;
case 0x1b: /**** db 1b ****/
    break;
case 0x1c: /**** sr ****/
    AC = AC >> 1;CYCLES += 5;break;
case 0x1d: /**** srl ****/
    AC = (AC >> 1)|(CARRY << 7);CYCLES += 5;break;
case 0x1e: /**** rr ****/
    AC = (AC >> 1)|(AC << 7);CYCLES += 5;break;
case 0x1f: /**** rrl ****/
    T16 = AC|(CARRY << 8);CARRY = T16 & 1;AC = T16 >> 1;CYCLES += 5;break;
case 0x20: /**** db 20 ****/
    break;
case 0x21: /**** db 21 ****/
    break;
case 0x22: /**** db 22 ****/
    break;
case 0x23: /**** db 23 ****/
    break;
case 0x24: /**** db 24 ****/
    break;
case 0x25: /**** db 25 ****/
    break;
case 0x26: /**** db 26 ****/
    break;
case 0x27: /**** db 27 ****/
    break;
case 0x28: /**** db 28 ****/
    break;
case 0x29: /**** db 29 ****/
    break;
case 0x2a: /**** db 2a ****/
    break;
case 0x2b: /**** db 2b ****/
    break;
case 0x2c: /**** db 2c ****/
    break;
case 0x2d: /**** db 2d ****/
    break;
case 0x2e: /**** db 2e ****/
    break;
case 0x2f: /**** db 2f ****/
    break;
case 0x30: /**** xpal p0 ****/
    T8 = P0;P0 = ((P0 & 0xFF00)|AC);AC = T8;CYCLES += 8;break;
case 0x31: /**** xpal p1 ****/
    T8 = P1;P1 = ((P1 & 0xFF00)|AC);AC = T8;CYCLES += 8;break;
case 0x32: /**** xpal p2 ****/
    T8 = P2;P2 = ((P2 & 0xFF00)|AC);AC = T8;CYCLES += 8;break;
case 0x33: /**** xpal p3 ****/
    T8 = P3;P3 = ((P3 & 0xFF00)|AC);AC = T8;CYCLES += 8;break;
case 0x34: /**** xpah p0 ****/
    T8 = (P0 >> 8);P0 = ((P0 & 0x00FF)|(AC << 8));AC = T8;CYCLES += 8;break;
case 0x35: /**** xpah p1 ****/
    T8 = (P1 >> 8);P1 = ((P1 & 0x00FF)|(AC << 8));AC = T8;CYCLES += 8;break;
case 0x36: /**** xpah p2 ****/
    T8 = (P2 >> 8);P2 = ((P2 & 0x00FF)|(AC << 8));AC = T8;CYCLES += 8;break;
case 0x37: /**** xpah p3 ****/
    T8 = (P3 >> 8);P3 = ((P3 & 0x00FF)|(AC << 8));AC = T8;CYCLES += 8;break;
case 0x38: /**** db 38 ****/
    break;
case 0x39: /**** db 39 ****/
    break;
case 0x3a: /**** db 3a ****/
    break;
case 0x3b: /**** db 3b ****/
    break;
case 0x3c: /**** xppc p0 ****/
    T16 = P0;P0 = P0;P0 = T16;CYCLES += 7;break;
case 0x3d: /**** xppc p1 ****/
    T16 = P0;P0 = P1;P1 = T16;CYCLES += 7;break;
case 0x3e: /**** xppc p2 ****/
    T16 = P0;P0 = P2;P2 = T16;CYCLES += 7;break;
case 0x3f: /**** xppc p3 ****/
    T16 = P0;P0 = P3;P3 = T16;CYCLES += 7;break;
case 0x40: /**** lde ****/
    AC = E;CYCLES += 6;break;
case 0x41: /**** db 41 ****/
    break;
case 0x42: /**** db 42 ****/
    break;
case 0x43: /**** db 43 ****/
    break;
case 0x44: /**** db 44 ****/
    break;
case 0x45: /**** db 45 ****/
    break;
case 0x46: /**** db 46 ****/
    break;
case 0x47: /**** db 47 ****/
    break;
case 0x48: /**** db 48 ****/
    break;
case 0x49: /**** db 49 ****/
    break;
case 0x4a: /**** db 4a ****/
    break;
case 0x4b: /**** db 4b ****/
    break;
case 0x4c: /**** db 4c ****/
    break;
case 0x4d: /**** db 4d ****/
    break;
case 0x4e: /**** db 4e ****/
    break;
case 0x4f: /**** db 4f ****/
    break;
case 0x50: /**** ane ****/
    AC &= E;CYCLES += 6;break;
case 0x51: /**** db 51 ****/
    break;
case 0x52: /**** db 52 ****/
    break;
case 0x53: /**** db 53 ****/
    break;
case 0x54: /**** db 54 ****/
    break;
case 0x55: /**** db 55 ****/
    break;
case 0x56: /**** db 56 ****/
    break;
case 0x57: /**** db 57 ****/
    break;
case 0x58: /**** ore ****/
    AC |= E;CYCLES += 6;break;
case 0x59: /**** db 59 ****/
    break;
case 0x5a: /**** db 5a ****/
    break;
case 0x5b: /**** db 5b ****/
    break;
case 0x5c: /**** db 5c ****/
    break;
case 0x5d: /**** db 5d ****/
    break;
case 0x5e: /**** db 5e ****/
    break;
case 0x5f: /**** db 5f ****/
    break;
case 0x60: /**** xre ****/
    AC ^= E;CYCLES += 6;break;
case 0x61: /**** db 61 ****/
    break;
case 0x62: /**** db 62 ****/
    break;
case 0x63: /**** db 63 ****/
    break;
case 0x64: /**** db 64 ****/
    break;
case 0x65: /**** db 65 ****/
    break;
case 0x66: /**** db 66 ****/
    break;
case 0x67: /**** db 67 ****/
    break;
case 0x68: /**** dae ****/
    T8 = E;_decimalAdd();CYCLES += 11;break;
case 0x69: /**** db 69 ****/
    break;
case 0x6a: /**** db 6a ****/
    break;
case 0x6b: /**** db 6b ****/
    break;
case 0x6c: /**** db 6c ****/
    break;
case 0x6d: /**** db 6d ****/
    break;
case 0x6e: /**** db 6e ****/
    break;
case 0x6f: /**** db 6f ****/
    break;
case 0x70: /**** ade ****/
    T8 = E;BINARYADD();CYCLES += 7;break;
case 0x71: /**** db 71 ****/
    break;
case 0x72: /**** db 72 ****/
    break;
case 0x73: /**** db 73 ****/
    break;
case 0x74: /**** db 74 ****/
    break;
case 0x75: /**** db 75 ****/
    break;
case 0x76: /**** db 76 ****/
    break;
case 0x77: /**** db 77 ****/
    break;
case 0x78: /**** cae ****/
    T8 = E ^ 0xFF;BINARYADD();CYCLES += 8;break;
case 0x79: /**** db 79 ****/
    break;
case 0x7a: /**** db 7a ****/
    break;
case 0x7b: /**** db 7b ****/
    break;
case 0x7c: /**** db 7c ****/
    break;
case 0x7d: /**** db 7d ****/
    break;
case 0x7e: /**** db 7e ****/
    break;
case 0x7f: /**** db 7f ****/
    break;
case 0x80: /**** db 80 ****/
    break;
case 0x81: /**** db 81 ****/
    break;
case 0x82: /**** db 82 ****/
    break;
case 0x83: /**** db 83 ****/
    break;
case 0x84: /**** db 84 ****/
    break;
case 0x85: /**** db 85 ****/
    break;
case 0x86: /**** db 86 ****/
    break;
case 0x87: /**** db 87 ****/
    break;
case 0x88: /**** db 88 ****/
    break;
case 0x89: /**** db 89 ****/
    break;
case 0x8a: /**** db 8a ****/
    break;
case 0x8b: /**** db 8b ****/
    break;
case 0x8c: /**** db 8c ****/
    break;
case 0x8d: /**** db 8d ****/
    break;
case 0x8e: /**** db 8e ****/
    break;
case 0x8f: /**** dly %c ****/
    T8 = FETCH();DELAY4CYCLES = AC / 2 + T8 / 2 + T8 * 128;AC = 0xFF;CYCLES += 13;break;
case 0x90: /**** jmp %a(p0) ****/
    P0 = EACIXNOE(P0);CYCLES += 10;break;
case 0x91: /**** jmp %a(p1) ****/
    P0 = EACIXNOE(P1);CYCLES += 10;break;
case 0x92: /**** jmp %a(p2) ****/
    P0 = EACIXNOE(P2);CYCLES += 10;break;
case 0x93: /**** jmp %a(p3) ****/
    P0 = EACIXNOE(P3);CYCLES += 10;break;
case 0x94: /**** jp %a(p0) ****/
    T16 = EACIXNOE(P0);if ((AC & 0x80) == 0) P0 = T16;CYCLES += 10;break;
case 0x95: /**** jp %a(p1) ****/
    T16 = EACIXNOE(P1);if ((AC & 0x80) == 0) P0 = T16;CYCLES += 10;break;
case 0x96: /**** jp %a(p2) ****/
    T16 = EACIXNOE(P2);if ((AC & 0x80) == 0) P0 = T16;CYCLES += 10;break;
case 0x97: /**** jp %a(p3) ****/
    T16 = EACIXNOE(P3);if ((AC & 0x80) == 0) P0 = T16;CYCLES += 10;break;
case 0x98: /**** jz %a(p0) ****/
    T16 = EACIXNOE(P0);if (AC == 0) P0 = T16;CYCLES += 10;break;
case 0x99: /**** jz %a(p1) ****/
    T16 = EACIXNOE(P1);if (AC == 0) P0 = T16;CYCLES += 10;break;
case 0x9a: /**** jz %a(p2) ****/
    T16 = EACIXNOE(P2);if (AC == 0) P0 = T16;CYCLES += 10;break;
case 0x9b: /**** jz %a(p3) ****/
    T16 = EACIXNOE(P3);if (AC == 0) P0 = T16;CYCLES += 10;break;
case 0x9c: /**** jnz %a(p0) ****/
    T16 = EACIXNOE(P0);if (AC != 0) P0 = T16;CYCLES += 10;break;
case 0x9d: /**** jnz %a(p1) ****/
    T16 = EACIXNOE(P1);if (AC != 0) P0 = T16;CYCLES += 10;break;
case 0x9e: /**** jnz %a(p2) ****/
    T16 = EACIXNOE(P2);if (AC != 0) P0 = T16;CYCLES += 10;break;
case 0x9f: /**** jnz %a(p3) ****/
    T16 = EACIXNOE(P3);if (AC != 0) P0 = T16;CYCLES += 10;break;
case 0xa0: /**** db a0 ****/
    break;
case 0xa1: /**** db a1 ****/
    break;
case 0xa2: /**** db a2 ****/
    break;
case 0xa3: /**** db a3 ****/
    break;
case 0xa4: /**** db a4 ****/
    break;
case 0xa5: /**** db a5 ****/
    break;
case 0xa6: /**** db a6 ****/
    break;
case 0xa7: /**** db a7 ****/
    break;
case 0xa8: /**** ild %d(p0) ****/
    T16 = EACIXNOE(P0);AC = READ(T16)+1;WRITE(T16);CYCLES += 22;break;
case 0xa9: /**** ild %d(p1) ****/
    T16 = EACIXNOE(P1);AC = READ(T16)+1;WRITE(T16);CYCLES += 22;break;
case 0xaa: /**** ild %d(p2) ****/
    T16 = EACIXNOE(P2);AC = READ(T16)+1;WRITE(T16);CYCLES += 22;break;
case 0xab: /**** ild %d(p3) ****/
    T16 = EACIXNOE(P3);AC = READ(T16)+1;WRITE(T16);CYCLES += 22;break;
case 0xac: /**** db ac ****/
    break;
case 0xad: /**** db ad ****/
    break;
case 0xae: /**** db ae ****/
    break;
case 0xaf: /**** db af ****/
    break;
case 0xb0: /**** db b0 ****/
    break;
case 0xb1: /**** db b1 ****/
    break;
case 0xb2: /**** db b2 ****/
    break;
case 0xb3: /**** db b3 ****/
    break;
case 0xb4: /**** db b4 ****/
    break;
case 0xb5: /**** db b5 ****/
    break;
case 0xb6: /**** db b6 ****/
    break;
case 0xb7: /**** db b7 ****/
    break;
case 0xb8: /**** dld %d(p0) ****/
    T16 = EACIXNOE(P0);AC = READ(T16)-1;WRITE(T16);CYCLES += 22;break;
case 0xb9: /**** dld %d(p1) ****/
    T16 = EACIXNOE(P1);AC = READ(T16)-1;WRITE(T16);CYCLES += 22;break;
case 0xba: /**** dld %d(p2) ****/
    T16 = EACIXNOE(P2);AC = READ(T16)-1;WRITE(T16);CYCLES += 22;break;
case 0xbb: /**** dld %d(p3) ****/
    T16 = EACIXNOE(P3);AC = READ(T16)-1;WRITE(T16);CYCLES += 22;break;
case 0xbc: /**** db bc ****/
    break;
case 0xbd: /**** db bd ****/
    break;
case 0xbe: /**** db be ****/
    break;
case 0xbf: /**** db bf ****/
    break;
case 0xc0: /**** ld %d(p0) ****/
    AC = READ(EACIX(P0));CYCLES += 18;break;
case 0xc1: /**** ld %d(p1) ****/
    AC = READ(EACIX(P1));CYCLES += 18;break;
case 0xc2: /**** ld %d(p2) ****/
    AC = READ(EACIX(P2));CYCLES += 18;break;
case 0xc3: /**** ld %d(p3) ****/
    AC = READ(EACIX(P3));CYCLES += 18;break;
case 0xc4: /**** ldi %c ****/
    AC = FETCH();CYCLES += 10;break;
case 0xc5: /**** ld @%d(p1) ****/
    AC = READ(EACAIX(P1));CYCLES += 18;break;
case 0xc6: /**** ld @%d(p2) ****/
    AC = READ(EACAIX(P2));CYCLES += 18;break;
case 0xc7: /**** ld @%d(p3) ****/
    AC = READ(EACAIX(P3));CYCLES += 18;break;
case 0xc8: /**** st %d(p0) ****/
    WRITE(EACIX(P0));CYCLES += 18;break;
case 0xc9: /**** st %d(p1) ****/
    WRITE(EACIX(P1));CYCLES += 18;break;
case 0xca: /**** st %d(p2) ****/
    WRITE(EACIX(P2));CYCLES += 18;break;
case 0xcb: /**** st %d(p3) ****/
    WRITE(EACIX(P3));CYCLES += 18;break;
case 0xcc: /**** db cc ****/
    break;
case 0xcd: /**** st @%d(p1) ****/
    WRITE(EACAIX(P1));CYCLES += 18;break;
case 0xce: /**** st @%d(p2) ****/
    WRITE(EACAIX(P2));CYCLES += 18;break;
case 0xcf: /**** st @%d(p3) ****/
    WRITE(EACAIX(P3));CYCLES += 18;break;
case 0xd0: /**** and %d(p0) ****/
    AC &= READ(EACIX(P0));CYCLES += 18;break;
case 0xd1: /**** and %d(p1) ****/
    AC &= READ(EACIX(P1));CYCLES += 18;break;
case 0xd2: /**** and %d(p2) ****/
    AC &= READ(EACIX(P2));CYCLES += 18;break;
case 0xd3: /**** and %d(p3) ****/
    AC &= READ(EACIX(P3));CYCLES += 18;break;
case 0xd4: /**** ani %c ****/
    AC &= FETCH();CYCLES += 10;break;
case 0xd5: /**** and @%d(p1) ****/
    AC &= READ(EACAIX(P1));CYCLES += 18;break;
case 0xd6: /**** and @%d(p2) ****/
    AC &= READ(EACAIX(P2));CYCLES += 18;break;
case 0xd7: /**** and @%d(p3) ****/
    AC &= READ(EACAIX(P3));CYCLES += 18;break;
case 0xd8: /**** or %d(p0) ****/
    AC |= READ(EACIX(P0));CYCLES += 18;break;
case 0xd9: /**** or %d(p1) ****/
    AC |= READ(EACIX(P1));CYCLES += 18;break;
case 0xda: /**** or %d(p2) ****/
    AC |= READ(EACIX(P2));CYCLES += 18;break;
case 0xdb: /**** or %d(p3) ****/
    AC |= READ(EACIX(P3));CYCLES += 18;break;
case 0xdc: /**** ori %c ****/
    AC |= FETCH();CYCLES += 10;break;
case 0xdd: /**** or @%d(p1) ****/
    AC |= READ(EACAIX(P1));CYCLES += 18;break;
case 0xde: /**** or @%d(p2) ****/
    AC |= READ(EACAIX(P2));CYCLES += 18;break;
case 0xdf: /**** or @%d(p3) ****/
    AC |= READ(EACAIX(P3));CYCLES += 18;break;
case 0xe0: /**** xor %d(p0) ****/
    AC ^= READ(EACIX(P0));CYCLES += 18;break;
case 0xe1: /**** xor %d(p1) ****/
    AC ^= READ(EACIX(P1));CYCLES += 18;break;
case 0xe2: /**** xor %d(p2) ****/
    AC ^= READ(EACIX(P2));CYCLES += 18;break;
case 0xe3: /**** xor %d(p3) ****/
    AC ^= READ(EACIX(P3));CYCLES += 18;break;
case 0xe4: /**** xri %c ****/
    AC ^= FETCH();CYCLES += 10;break;
case 0xe5: /**** xor @%d(p1) ****/
    AC ^= READ(EACAIX(P1));CYCLES += 18;break;
case 0xe6: /**** xor @%d(p2) ****/
    AC ^= READ(EACAIX(P2));CYCLES += 18;break;
case 0xe7: /**** xor @%d(p3) ****/
    AC ^= READ(EACAIX(P3));CYCLES += 18;break;
case 0xe8: /**** dad %d(p0) ****/
    T8 = READ(EACIX(P0));_decimalAdd();CYCLES += 23;break;
case 0xe9: /**** dad %d(p1) ****/
    T8 = READ(EACIX(P1));_decimalAdd();CYCLES += 23;break;
case 0xea: /**** dad %d(p2) ****/
    T8 = READ(EACIX(P2));_decimalAdd();CYCLES += 23;break;
case 0xeb: /**** dad %d(p3) ****/
    T8 = READ(EACIX(P3));_decimalAdd();CYCLES += 23;break;
case 0xec: /**** dai %c ****/
    T8 = FETCH();_decimalAdd();CYCLES += 15;break;
case 0xed: /**** dad @%d(p1) ****/
    T8 = READ(EACAIX(P1));_decimalAdd();CYCLES += 23;break;
case 0xee: /**** dad @%d(p2) ****/
    T8 = READ(EACAIX(P2));_decimalAdd();CYCLES += 23;break;
case 0xef: /**** dad @%d(p3) ****/
    T8 = READ(EACAIX(P3));_decimalAdd();CYCLES += 23;break;
case 0xf0: /**** add %d(p0) ****/
    T8 = READ(EACIX(P0));BINARYADD();CYCLES += 19;break;
case 0xf1: /**** add %d(p1) ****/
    T8 = READ(EACIX(P1));BINARYADD();CYCLES += 19;break;
case 0xf2: /**** add %d(p2) ****/
    T8 = READ(EACIX(P2));BINARYADD();CYCLES += 19;break;
case 0xf3: /**** add %d(p3) ****/
    T8 = READ(EACIX(P3));BINARYADD();CYCLES += 19;break;
case 0xf4: /**** adi %c ****/
    T8 = FETCH();BINARYADD();CYCLES += 11;break;
case 0xf5: /**** add @%d(p1) ****/
    T8 = READ(EACAIX(P1));BINARYADD();CYCLES += 19;break;
case 0xf6: /**** add @%d(p2) ****/
    T8 = READ(EACAIX(P2));BINARYADD();CYCLES += 19;break;
case 0xf7: /**** add @%d(p3) ****/
    T8 = READ(EACAIX(P3));BINARYADD();CYCLES += 19;break;
case 0xf8: /**** cad %d(p0) ****/
    T8 = READ(EACIX(P0)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
case 0xf9: /**** cad %d(p1) ****/
    T8 = READ(EACIX(P1)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
case 0xfa: /**** cad %d(p2) ****/
    T8 = READ(EACIX(P2)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
case 0xfb: /**** cad %d(p3) ****/
    T8 = READ(EACIX(P3)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
case 0xfc: /**** cai %c ****/
    T8 = FETCH() ^ 0xFF;BINARYADD();CYCLES += 12;break;
case 0xfd: /**** cad @%d(p1) ****/
    T8 = READ(EACAIX(P1)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
case 0xfe: /**** cad @%d(p2) ****/
    T8 = READ(EACAIX(P2)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
case 0xff: /**** cad @%d(p3) ****/
    T8 = READ(EACAIX(P3)) ^ 0xFF;BINARYADD();CYCLES += 20;break;
