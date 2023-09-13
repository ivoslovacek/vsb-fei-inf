# Modularizace

Tento týden si zkusíte napsat program, který bude překládat text z jednoho souboru do druhého souboru, podle jednoduchého slovníku zadaného v třetím souboru.

Program by se měl chovat takto:

1.  Program načte pomocí [parametrů příkazové řádky](https://mrlvsb.github.io/upr-skripta/ruzne/funkce_main.html#vstupn%C3%AD-parametry-funkce-main) tři parametry:
    
    *   Cestu ke slovníku (`dict-path`)
    *   Cestu ke vstupnímu souboru (`input-path`)
    *   Cestu k výstupnímu souboru (`output-path`)
    
    Např.:
    
        $ ./upr-translator dictionary-en-cs.csv input.txt translated.txt
    
    *   Pokud na vstupu programu nebudou všechny tři parametry, vypište řádek s hláškou `Wrong parameters` a ukončete program s kódem `1`.
2.  Program načte ze souboru na cestě `dict-path` slovník. Slovník je ve formátu CSV, na každém řádku je dvojice ASCII **slov** oddělena čárkou. Dvojice slov udává překlad ze zdrojového na cílové slovo.
    
    Např. tento soubor:
    
        hello,ahoj
        house,dum
        car,auto
    
    říká, že slovo `hello` má být přeloženo na slovo `ahoj`, slovo `house` má být přeloženo na slovo `dum` a slovo `car` má být přeloženo na slovo `auto`.
    
    *   Žádné zdrojové slovo se ve slovníku nebude opakovat.
    *   Každé slovo bude obsahovat pouze znaky malé a velké anglické abecedy, případně mezeru. Nebude obsahovat čárku ani další jiné znaky.
    *   Slovník načtěte do nějaké struktury v paměti a dále jej používejte ve funkci pro překlad souboru.
    *   Pokud při načtení dojde k chybě, vypište řádek s hláškou `Could not load dictionary` a ukončete program s kódem `1`.
3.  Program otevře soubor na cestě `input-path` a vytvoří soubor na cestě `output-path`. Procházejte postupně slova ze vstupního souboru. Slova ve vstupním souboru jsou oddělena mezerou, a na každém řádku se může vyskytovat více slov. Každé slovo přeložte a poté jej zapište do výstupního souboru. Pokud pro dané slovo nenaleznete ve slovníku žádný překlad, tak do výstupního souboru vypište slovo `<unknown>`. Zachovejte ve výstupním souboru stejné mezery a odřádkování, jako byly ve vstupním souboru.
    
    Příklad:
    
    *   Slovník (`dictionary.csv`)
    
        hello,ahoj
        your,tvoje
        my,moje
        what,co
        name,jmeno
        is,je
        mike,michal
    
    *   Vstupní soubor (`input.txt`)
    
        hello my name
        is mike
        what is
        your real
        name
    
    *   Spuštění programu
    
        $ ./upr-translator dictionary.csv input.txt output.txt
    
    *   Očekávaný obsah souboru `output.txt` po spuštění programu:
    
        ahoj moje jmeno
        je michal
        co je
        tvoje <unknown>
        jmeno
    
    *   Můžete předpokládat, že každý řádek vstupního souboru bude mít max. `255` znaků (včetně znaku odřádkování). Řádek může být také prázdný.
    *   Váš program musí fungovat i pro velké soubory, které se nevlezou do paměti počítače! Nenačítejte celý vstupní soubor do paměti, ale procházejte ho postupně po řádcích a rovnou zapisujte do výstupního souboru.
    *   Pokud se nepodaří otevřít vstupní soubor, vypište řádek s hláškou `Could not open input file` a ukončete program s kódem `1`.
    *   Pokud se nepodaří otevřít výstupní soubor, vypište řádek s hláškou `Could not open output file` a ukončete program s kódem `1`.

Pokud byste si chtěli např. přeložit něco z angličtiny do češtiny, tak [zde](/task/UPR/2022W/BER0134/ex09_translator/asset/template/dictionary-en-cs.csv) je k dispozici slovník necelých 1000 slov spolu s jejich překladem.

### Poznámky

*   **Použití [VLA](https://mrlvsb.github.io/upr-skripta/c/pole/staticka_pole.html#konstantn%C3%AD-velikost-statick%C3%A9ho-pole) je zakázáno**.
*   V implementaci úlohy si vhodně nadefinujte vlastní datové typy, např. pro reprezentaci slovníku. **Rozdělte také program tak, aby byl ve více zdrojových souborech. Použijte hlavičkový soubor pro deklarace struktur a funkcí a zdrojový soubor pro jejich definici. V souboru `main.c` poté mějte pouze jednu (`main`) funkci, ve které budete používat struktury a funkce z hlavičkového souboru.**
*   Při práci s řetězci budete narážet na paměťové chyby. Používejte [Address sanitizer](#address-sanitizer)! Při řešení této úlohy bude velmi užitečné využít [debugger](https://mrlvsb.github.io/upr-skripta/prostredi/ladeni.html#krokov%C3%A1n%C3%AD) VSCode.

Délka referenčního řešení: ~150 řádků

### Užitečné funkce

*   [`fgets`](https://devdocs.io/c/io/fgets) - načtení řádku ze vstupu do řetězce (pole znaků).
*   [`strdup`](https://devdocs.io/c/string/byte/strdup) - zkopírování řetězce na haldu. **Takto vytvořený řetězec je nutné později uvolnit funkcí `free`!**

### Bonusový úkol (+1b)

Naimplementujte opačnou transformaci, která vezme slovník, a přeloží soubor zpět do původního jazyka. Přidejte na vstup programu parametr, který rozliší, jestli má jít o překlad ze zdrojového do cílového jazyka či naopak.
