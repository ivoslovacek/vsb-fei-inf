# Práce s textem

Tento týden si zkusíte napsat program, který načte sadu řádků se slovy. Pro každé slovo ve vstupu poté spočítá několik údajů a vypíše slovo v několika upravených verzích.

Program by se měl chovat takto:

1.  Načte ze vstupu jedno číslo `n`, které udává, kolik řádků se slovy bude ve vstupu následovat.
2.  Dále načte ze vstupu postupně `n` řádků.
    *   Každý řádek bude mít maximálně `100` znaků (včetně znaku odřádkování).
    *   Řádky budou obsahovat slova oddělená mezerou.
    *   Každé slovo se skládá pouze z písmen malé a velké anglické abecedy (`a-z`, `A-Z`).
    *   Každý řádek bude obsahovat alespoň jedno slovo.
3.  Pro každé slovo `s` vypíše na výstup jeden řádek (viz příklad níže a testy). Tento řádek bude obsahovat následující informace (v tomto pořadí):
    *   Pořadí slova ve vstupu (počítáno od nuly).
    *   Slovo `s`.
    *   Slovo `s`, ale všechna malá písmena budou změněna na velká a všechna velká písmena na malá.
    *   Počet malých písmen v `s`.
    *   Počet velkých písmen v `s`.
    *   Slovo `s`, ale všechna písmena budou změněna na malá.
    *   Slovo `s`, ale všechna písmena budou změněna na velká.
    *   `1`, pokud je `s` [palindromem](https://cs.wikipedia.org/wiki/Palindrom), případně `0`, pokud `s` není palindromem. Při výpočtu palindromu respektujte velikost písmen, tj. `uwu` je palindrom, ale `uwU` není.

Poznámky:

*   Nemusíte si všechny řádky ukládat do pole, stačí je zpracovávat postupně, jeden po druhém.
*   Pro veškeré načítání vstupních dat (i čísla `n`) používejte funkci [`fgets`](https://mrlvsb.github.io/upr-skripta/c/text/vstup.html#na%C4%8Dten%C3%AD-%C5%99%C3%A1dku). Pokud budete kombinovat `scanf` a `fgets`, [**budete narážet na problémy**](https://mrlvsb.github.io/upr-skripta/c/text/vstup.html#na%C4%8Dten%C3%AD-%C5%99%C3%A1dku). Proto raději vše načítejte funkcí `fgets` a pro převod na číslo využijte např. funkci [`atoi`](https://devdocs.io/c/string/byte/atoi).
*   Dávejte si u funkce `fgets` pozor na to, že znak odřádkování je také součástí vstupu! Viz [skripta](https://mrlvsb.github.io/upr-skripta/c/text/vstup.html#na%C4%8Dten%C3%AD-%C5%99%C3%A1dku).
*   Při práci s řetězci budete narážet na paměťové chyby. Používejte Address sanitizer! Při řešení této úlohy bude velmi užitečné využít [debugger](https://mrlvsb.github.io/upr-skripta/prostredi/ladeni.html#krokov%C3%A1n%C3%AD) VSCode. I při ladění/krokování si můžete na vstup programu [přesměrovat](https://code.visualstudio.com/docs/editor/debugging#_redirect-inputoutput-tofrom-the-debug-target) soubor, abyste nemuseli vstup neustále psát ručně.

Příklad vstupu:

    3
    uwu wRiTE
    HoW uNIveRsITY brittle
    Heleh

Odpovídající výstup:

    Slovo 0: uwu UWU 3 0 uwu UWU 1
    Slovo 1: wRiTE WrIte 2 3 write WRITE 0
    Slovo 2: HoW hOw 1 2 how HOW 0
    Slovo 3: uNIveRsITY UniVErSity 4 6 university UNIVERSITY 0
    Slovo 4: brittle BRITTLE 7 0 brittle BRITTLE 0
    Slovo 5: Heleh hELEH 4 1 heleh HELEH 0

Délka referenčního řešení: ~100 řádků

### Užitečné funkce

*   [`fgets`](https://devdocs.io/c/io/fgets) - načtení řádku ze vstupu do řetězce (pole znaků)
*   [`atoi`](https://devdocs.io/c/string/byte/atoi) - převedení řetězce obsahujícího číslice na číslo (`int`)
*   [`strlen`](https://devdocs.io/c/string/byte/strlen) - zjištění délky řetězce
*   [`strtok`](https://devdocs.io/c/string/byte/strtok) - rozdělení řetězce např. podle mezer. _Tato funkce je trochu komplikovaná, může být pro vás jednodušší si rozdělení podle mezer naprogramovat “ručně”._

### Bonusové úkoly

*   Pro převod řetězce na číslo nepoužívejte `atoi` ani `strtol`, ale naprogramujte si pro to vlastní funkci.
*   Naprogramujte si sami všechny nutné funkce pro práci s řetězci. Kromě funkce `fgets` tedy nepoužívejte nic ze standardní knihovny - `strlen`, `tolower`, `islower`, `isdigit`, `atoi` atd.
