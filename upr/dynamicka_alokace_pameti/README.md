# Dynamická alokace paměti

Tento týden si zkusíte napsat program, který vytvoří dvourozměrné plátno/mřížku/obrázek, na kterém se bude pohybovat a kreslit želvička. Uživatel aplikace bude příkazy ovládat, jak se bude želvička pohybovat, a bude jí také dával povel, kdy má nakreslit “pixel”.

Program by se měl chovat takto:

1.  Načtěte ze vstupu dvě čísla oddělená mezerou, `rows` a `cols`.
2.  Vytvořte 2D mřížku (pole) znaků o rozměrech `rows` řádků a `cols` sloupců. Znaky ve mřížce inicializujte na znak `'.'` (tečka).
3.  Umístěte želvičku na pozici `(0, 0)` - nultý řádek a nultý sloupec (vlevo nahoře).
4.  Načítejte postupně znaky ze vstupu programu. Znaky budou oddělené bílým znakem (mezerou či odřádkováním).
    *   Pokud narazíte na znak `'x'`, vypište mřížku na výstup programu a ukončete program.
    *   Pokud narazíte na znaky `'<'`, `'>'`, `'^'`, `'v'`, posuňte želvičku v odpovídajícím směru (doleva, doprava, nahoru, dolů).
    *   Pokud narazíte na znak `'o'`, zapište do mřížky znak `'o'` na současné pozici želvičky.

Poznámky:

*   Pokud by želvička měla provést posun, který by ji vyvedl ven z mřížky (např. na pozici `(0, 0)` by dostala příkaz jít doleva), tak želvičku “teleportujte” na opačnou stranu mřížky. Např.:
    
        z..
        ...
        ...
    
    V `3x3` mřížce výše je pozice želvičky `(0, 0)` znázorněna znakem `z`.
    
    *   Pokud by zde želvička dostala příkaz `<`, přesune se na pozici `(0, 2)`, tj. úplně doprava nahoru.
    *   Pokud by zde želvička dostala příkaz `^`, přesune se na pozici `(2, 0)`, tj. úplně doleva dolů.
*   Pro vytvoření mřížky využijte dynamickou alokaci paměti. Stačí naalokovat jedno pole, nepoužívejte [zubatá pole](https://mrlvsb.github.io/upr-skripta/c/pole/zubata_pole.html). Nezapomeňte pole uvolnit, jakmile už jej nebudete potřebovat.
    
*   Želvička nebude na mřížce nijak znázorněna, v mřížce se budou objevovat pouze znaky `'o'`, které želvička bude kreslit, případně “prázdná místa” znázorněná znakem `'.'`.
    

Příklad vstupu:

    3 3
    o
    >
    v
    o
    >
    v
    o
    x

Odpovídající výstup:

    o..
    .o.
    ..o

### Bonusové úkoly

*   Vygenerujte na mřížce po jejím vytvoření na několika náhodných místech překážky (znázorněné znakem `'#'`). Pokud želvička narazí na překážku, tak přes ni nebude moct přejít. O generování náhodných čísel si můžete přečíst [zde](https://mrlvsb.github.io/upr-skripta/ruzne/nahodna_cisla.html).
*   Vytvořte z programu animaci, viz zadání minulé úlohy. Po každém pohybu želvičky nebo vykreslení pixelu vykreslete celou mřížku. Pozici želvičky znázorněte znakem `z`. Aby animace vypadala pěkně, tak před vykreslením mřížky vyčistěte obrazovku terminálu. Můžete pro to použít ANSI sekvenci `printf("\x1b[2J");`. Aby animace více vynikla, použijte mezeru místo tečky pro prázdné místo na mřížce.

Pokud budete implementovat bonusové úkoly, tak vám nebudou procházet testy v Kelvinovi. Odevzdávejte v tom případě řešení v takové podobě, aby testy prošly, bonusový kód nechte zakomentovaný, a v Kelvinu přidejte komentář (tlačítko `+` u čísla nějakého řádku odevzdaného kódu, anebo větší tlačítko `+` úplně nahoře v záložce `Source code`) s informací, že jste implementovali bonus.
