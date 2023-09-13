# Struktury

Tento týden si zkusíte napsat program, který načte sadu záznamů o hodnotách akcií. Informace a statistiky o akciích poté program vypíše na **standardní výstup** ve formě [HTML](https://en.wikipedia.org/wiki/HTML) stránky.

Program by se měl chovat takto:

1.  Program načte pomocí [parametrů příkazové řádky](https://mrlvsb.github.io/upr-skripta/ruzne/funkce_main.html#vstupn%C3%AD-parametry-funkce-main) dva parametry: název akcie (řetězec `t`) a počet řádků na vstupu (číslo `n`). Např.:
    
        $ ./program AAPL 50
    
    *   Pokud na vstupu programu nebudou oba dva tyto parametry, vypište řádek s hláškou `Wrong parameters` a ukončete program s kódem `1`.
    *   `n` bude vždy kladné číslo (větší než nula).
2.  Dále program načte ze vstupu postupně `n` řádků. Každý řádek bude obsahovat **záznam** o hodnotě akcie konkrétní firmy v konkrétní den. Na řádku bude pět údajů oddělených čárkou:
    
    *   Index dne (celé číslo)
    *   Název akcie (řetězec obsahující pouze velká písmena anglické abecedy)
    *   Hodnota akcie na začátku daného dne (desetinné číslo)
    *   Hodnota akcie na konci daného dne (desetinné číslo)
    *   Počet provedených obchodů v daný den (celé číslo)
    
    Příklad _záznamu_:
    
        1,NVDA,134.23,135.64,51234158
    
    *   Každý řádek bude mít maximálně `100` znaků (včetně znaku odřádkování).
3.  Nalezněte mezi zadanými údaji všechny _záznamy_ akcie `t`. V nich vyhledejte _záznam_, který dosáhl nejvyššího počtu provedených obchodů.
    
    *   Pokud takový _záznam_ existuje, vypište o něm dostupné informace ve formátu HTML (viz příklad níže a testy).
    *   Pokud takový _záznam_ neexistuje, vypište informaci ve formátu HTML, že daná akcie nebyla nalezena (viz testy).
    *   Pokud by _záznamů_ s nejvyšším počtem obchodů bylo více, vypište ten, který se ve vstupu vyskytoval dříve.
4.  Dále vypište HTML seznam s veškerými načtenými vstupními _záznamy_, v opačném pořadí, než byly zadány na vstupu (tj. nejprve poslední, poté předposlední atd.). _Záznamy_ obsahující informace o akcii `t` vypište tučně (obalené v HTML tagu `<b></b>`). Příklad vypsaného záznamu:
    
        <li>Day: 3, ticker: AMD, start: 749.48, end: 745.39, diff: -4.09, volume: 51760557</li>
    
    Údaj `diff` bude obsahovat rozdíl mezi cenou na začátku a na konci daného dne pro danou akcii.
    
    Plný formát seznamu si můžete prohlédnout v záložce [Tests](#tests).
    

### Poznámky

*   **Použití [VLA](https://mrlvsb.github.io/upr-skripta/c/pole/staticka_pole.html#konstantn%C3%AD-velikost-statick%C3%A9ho-pole) je zakázáno**.
*   **V implementaci úlohy vhodně využijte struktury a nadefinujte si vlastní datový(é) typ(y)!**
*   Pro reprezentaci desetinných čísel používejte datový typ `float`.
*   Veškerá desetinná čísla vypisujte s přesností na dvě desetinná místa. Jak toho dosáhnout se můžete dozvědět v [dokumentaci](https://devdocs.io/c/io/fprintf) funkce `printf` (hledejte _precision_). Případně to můžete vygooglit.
*   Dávejte si u funkce `fgets` pozor na to, že znak odřádkování je také součástí vstupu! Viz [skripta](https://mrlvsb.github.io/upr-skripta/c/text/vstup.html#na%C4%8Dten%C3%AD-%C5%99%C3%A1dku).
*   Při práci s řetězci budete narážet na paměťové chyby. Používejte [Address sanitizer](#address-sanitizer)! Při řešení této úlohy bude velmi užitečné využít [debugger](https://mrlvsb.github.io/upr-skripta/prostredi/ladeni.html#krokov%C3%A1n%C3%AD) VSCode. I při ladění/krokování si můžete na vstup programu [přesměrovat](https://code.visualstudio.com/docs/editor/debugging#_redirect-inputoutput-tofrom-the-debug-target) soubor, abyste nemuseli vstup neustále psát ručně.

Pokud si výstup programu přesměrujete do souboru s koncovkou `.html`, tak si jej poté můžete otevřít ve webovém prohlížeči:

    $ ./main TSLA 5 < test-small.stdin > output.html

Délka referenčního řešení: ~120 řádků

### Příklad

*   Spuštění programu:
    
        $ ./main TSLA 5
    
*   Vstup:
    
        1,TSLA,662.56,664.63,73576275
        2,AMD,745.26,749.48,27373290
        2,TSLA,664.63,665.66,78968627
        3,AMD,749.48,745.39,51760557
        3,TSLA,665.66,663.08,24778442
    
*   Odpovídající výstup:
    
        <html>
        <body>
        <div>
        <h1>TSLA: highest volume</h1>
        <div>Day: 2</div>
        <div>Start price: 664.63</div>
        <div>End price: 665.66</div>
        <div>Volume: 78968627</div>
        </div>
        <ul>
        <li><b>Day: 3, ticker: TSLA, start: 665.66, end: 663.08, diff: -2.58, volume: 24778442</b></li>
        <li>Day: 3, ticker: AMD, start: 749.48, end: 745.39, diff: -4.09, volume: 51760557</li>
        <li><b>Day: 2, ticker: TSLA, start: 664.63, end: 665.66, diff: 1.03, volume: 78968627</b></li>
        <li>Day: 2, ticker: AMD, start: 745.26, end: 749.48, diff: 4.22, volume: 27373290</li>
        <li><b>Day: 1, ticker: TSLA, start: 662.56, end: 664.63, diff: 2.07, volume: 73576275</b></li>
        </ul>
        </body>
        </html>
    

### Užitečné funkce

*   [`fgets`](https://devdocs.io/c/io/fgets) - načtení řádku ze vstupu do řetězce (pole znaků).
*   [`atoi`](https://devdocs.io/c/string/byte/atoi) - převedení řetězce obsahujícího číslice na celé číslo (`int`).
*   [`atof`](https://devdocs.io/c/string/byte/atof) - převedení řetězce obsahujícího číslice na desetinní číslo (`float`).
*   [`strlen`](https://devdocs.io/c/string/byte/strlen) - zjištění délky řetězce.
*   [`strtok`](https://devdocs.io/c/string/byte/strtok) - rozdělení řetězce např. podle mezer. _Tato funkce je trochu komplikovaná, může být pro vás jednodušší si rozdělení podle mezer naprogramovat “ručně”._

### Bonusový úkol (+1b)

Vykreslete graf (např. jednoduchý svíčkový, nebo sloupcový) ve formátu SVG, který bude znázorňovat vývoj hodnoty akcie `t` v čase. Příklad:

Pokud budete bonusový úkol implementovat, nechejte ho v kódu zakomentovaný, ať projdou testy na Kelvinovi, a přidejte do Kelvina komentář pro svého cvičícího, že máte bonus hotový.
