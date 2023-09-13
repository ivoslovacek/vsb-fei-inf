# Funkce

Úloha na tento týden bude trochu speciální. Vyzkoušíme si, jak vykreslit barevnou grafiku do terminálu (ne pouze klasický text) pomocí tzv. [ANSI escape sekvencí](https://en.wikipedia.org/wiki/ANSI_escape_code).

Pokud na výstup programu vypíšete určité speciální sekvence bytů, a použijete pro jejich vykreslení terminál, který je podporuje, můžete pomocí těchto sekvencí terminál ovládat, např. pohybovat kurzorem, nastavovat barvu pozadí vykreslovaného textu, vyčistit obsah terminálu atd.

**Nachystali jsme pro vás [šablonu](/task/UPR/2022W/BER0134/ex03_functions/asset/template/drawing.c)**, ve které máte k dispozici sadu předpřipravených funkcí určených pro kreslení do terminálu. Využijte tyto funkce v úlohách popsaných níže.

**Tento úkol s největší pravděpodobností bude vyžadovat použití Linuxu nebo WSL.** Jednak šablona používá specifickou Linux funkci na uspání programu, a také samotné ANSI sekvence obvykle na Windows nemají zrovna skvělou podporu.

Tím, že váš program bude vypisovat ANSI sekvence, které upravují stav terminálu, je možné, že se váš terminál občas dostane do dost zvláštního stavu. V takovém případě buď spusťte váš program znovu nebo terminál vypněte a spusťte jej znovu. Před spuštěním programu je také vhodné vyčistit obsah terminálu (obvykle se toho dá dosáhnout pomocí klávesové zkratky `Ctrl + L`).

Cílem cvičení je vytvořit program, ve kterém si procvičíte využití funkcí (v pozdějších úlohách budete funkce používat už automaticky v podstatě neustále). Snažte se tedy svůj kód rozumně rozdělit do funkcí, abyste kód, který se dá znovu využít, neměli v programu zkopírovaný. Identifikujte často se opakující kusy kódu (vykreslení čáry, vykreslení čtverce atd.) a udělejte z nich funkce.

Na rozdělení programu do funkcí budeme brát ohled při hodnocení úlohy (to ale neznamená, že čím více funkcí = tím více bodů :) Musí to dávat smysl.).

### Seznam úloh

Každou z úloh níže vložte do samostatné funkce a tyto funkce poté volejte ve funkci `main`. Pro vykreslování používejte buď funkci `draw_pixel` (vykreslí tečku) v kombinaci s `set_xxx_color` nebo `fill_pixel` (vykreslí vyplněnou buňku) v kombinaci s `set_xxx_bg_color`.

*   **Vykreslení domu** Napište funkci, která vykreslí dům o zadaném rozměru (počet pixelů, které bude zabírat strana čtverce domu) na současné pozici kurzoru. To, jak bude dům vypadat je na vás, můžete nakreslit např. čtverec a nad ním “stříšku” z trojúhelníku. Na stříšku můžete zkusit vykreslit komín (vertikální čáru). Fantazii se meze nekladou :)
    
*   **Vykreslení vesnice** Napište funkci, která vykreslí vesnici obsahující `n` domů (`n` bude parametr funkce) se zadaným rozměrem každého domu. Domy můžete vykreslit buď vedle sebe, nebo je můžete např. umístit do mřížky. Při tvorbě této funkce využijte funkci z předchozí úlohy na vykreslení domu.
    
*   **Přerušovaná čára** Napište funkci, která vykreslí přerušovanou čáru o zadané délce `n`. Čára bude vždy obsahovat vyplněný “pixel”, poté prázdné místo, pixel, prázdné místo atd. Délka `n` bude udávat počet vyplněných pixelů.
    
*   **Schody** Napište funkci, která vykreslí “schody”, tj. střídající se horizontální a vertikální čáry. Parametrem funkce bude počet schodů.
    
*   **Animace** Použijte funkci `animace`, abyste vytvořili dojem animovaného vykreslení. Můžete třeba rozanimovat vykreslování schodů nebo vesnice. Případně, pokud v cyklu vždycky vyčistíte obrazovku, poté něco vykreslíte, a poté zavoláte funkci `animate`, můžete vykreslit pohybující se obrazce. Zkuste vymyslet nějako zajímavou animaci a vykreslit ji.
    

Při kreslení si musíte vždycky uvědomovat, na jaké pozici máte kurzor v terminálu. Pokud byste to chtěli vizuálně odladit, tak zakomentujte volání funkce `hide_cursor` ve funkci `clear_screen` a použijte funkci `animate`, aby kurzor začal blikat.
