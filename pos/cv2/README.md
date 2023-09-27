# Úloha – hromadný chat

5-ti bodový úloha v předmětu POS

## Zadání

- Poslání zprávy na „talk“ server přes TCP/8000
- Příjem zpráv na UDP/8010 z broadcastu (nyní
kvůli on-line výuce unicastem na IP adresu z TCP spojení)
Zpráva max. 255 ASCII znaků
ukončeno <LF> (tj. \n)
- Při posílání UDP zpět je zprávě předřazeno 9
bytů :
- 4 byte - IP adresa odesílatele (int, formát lo-hi)
- 4 byte - htonl(time_t)
- 1 byte - délka následujícího řetězce (0-255).
| 127 | 0 | 0 | 1 | 0x4A | 0xAE | 0x1A | 0x30 | 3 | SSS |
