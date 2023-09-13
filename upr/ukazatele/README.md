# Ukazatele

Tento týden si zkusíte napsat program, který bude počítat [histogram](https://cs.wikipedia.org/wiki/Histogram) čísel. Histogram bude mít `9` “košů” a bude zaznamenávat četnost jednotlivých hodnot `1` až `9`.

Program by se měl chovat takto:

1.  Načte ze vstupu znak, který bude udávat, jestli se má vykreslit vertikální (pokud na vstupu byl znak `v`) nebo horizontální (pokud na vstupu byl znak `h`) histogram.
    *   Pokud bude zadán jiný znak než `v` nebo `h`, vypište řádek `Neplatny mod vykresleni` na standardní výstup a ukončete program s chybovým kódem `1`.
2.  Načte ze vstupu nezáporné číslo (`n`), které udává, kolik dále program načte čísel. Z těchto načtených čísel poté váš program vypočítá histogram.
3.  Načte od uživatele `n` čísel oddělených mezerou a vypočítá pro ně histogram.
    *   Pokud bude číslo na vstupu mimo interval `[1, 9]`, pokládejte takové číslo za hodnotu `1`.
    *   Histogram počítá, kolikrát se jednotlivé hodnoty `1` až `9` vyskytly ve vstupu.
    *   Histogram reprezentujte polem s `9` prvky.
    *   Ideální řešení pro výpočet histogramu není mít pod sebou 9x `if` větev. Zamyslete se, jak histogram spočítat bez podmínek, jde to provést jedním řádkem.
4.  Vykreslí histogram na výstup. Podívejte se na záložku `Tests` pro vzorové ukázky vstupů a výstupů.
    *   Pokud má být histogram vertikální, tak vykreslete pod sebe čísla `1` až `9` (každé číslo na jednom řádku). Pokud se dané číslo vyskytlo na vstupu, tak za něj vykreslete mezeru a znak `#` tolikrát, kolikrát se dané číslo vyskytlo na vstupu.
    *   Pokud má být histogram horizontální, tak vykreslete čísla `1` až `9` vedle sebe. Pokud se dané číslo vyskytlo na vstupu, tak nad ním by měl být vykreslený sloupeček se znakem `#`. Sloupeček bude tak vysoký, kolikrát se daný znak vyskytl na vstupu.
    *   Poznámka: vykreslit horizontální histogram je mnohem složitější, než vykreslit vertikální. Raději tedy začněte s tím vertikálním :)

Poznámky ke kódu:

*   **Pro tuto úlohu není potřeba používat tzv. dynamickou alokaci paměti. Vše vyřešte pouze pomocí ukazatelů a statických polí. Nevyužívejte ani tzv. VLA (variable-length array):**
    
          int velikost = ...;
        
          // Pole na zásobníku, jehož velikost není konstantní (VLA).
          // Nepoužívejte tuto vlastnost C99.
          // https://stackoverflow.com/questions/12407754/what-technical-disadvantages-do-c99-style-vlas-have
          int pole[velikost];
    
*   V zadání používáme zkrácené názvy pro určité proměnné (např. `n`). V programu si proměnné pojmenujte tak, aby bylo jasné, k čemu slouží, názvy proměnných nemusí přesně odpovídat zadání.
    
*   Proměnné pojmenovávejte tak, aby šlo z jejich názvu okamžitě poznat, k čemu slouží, a vytvářejte je co nejblíže místu, kde jsou v kódu opravdu potřeba (ne všechny na začátku funkce).
    
*   Rozdělte si program do funkcí tak, aby to dávalo smysl (např. funkce na načtení histogramu, vykreslení histogramu).
    

Příklad vstupu:

    v
    9
    3 3 2 3 7 1 1 4 9

Odpovídající výstup:

    1 ##
    2 #
    3 ###
    4 #
    5
    6
    7 #
    8
    9 #

### Bonusový úkol

Udělejte z výstupu animaci. Po vykreslení každého znaku `#` program na chvíli uspěte (např. pomocí funkce `usleep`, viz minulá úloha). Aby to fungovalo, vypněte v programu [line buffering](https://stackoverflow.com/a/7876756/1107768). V základním režimu se totiž výstup programu ukáže vždy až po vypsání znaku odřádkování.

### Načítání vstupu

Pomocí funkce [`scanf`](https://devdocs.io/c/io/fscanf) můžete načíst číslo ze vstupu programu do číselné proměnné takto:

    int number;
    scanf("%d", &number);

Znak můžete načíst takto:

    char ch;
    scanf("%c", &ch);
