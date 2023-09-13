# Cykly a podmínky

Vytvořte program, který bude umět vypisovat různé geometrické tvary na výstup. Při spuštění se vypíšou všechny tvary definované níže na výstup, oddělené prázdným řádkem.

Pro tisk znaků na výstup použijte `printf`:

    printf("x");  // výpis jednoho znaku
    printf("\n"); // výpis odřádkování

Snažte se psát kód tak, aby šly vlastnosti (parametry) jednotlivých tvarů jednoduše v kódu změnit, ideálně změnou hodnoty jedné proměnné. Parametry jednotlivých tvarů, které by měly jít v kódu jednoduše upravit, jsou popsány níže.

**Pro výpis tvarů použijte cykly a podmínky, smyslem úlohy není “natvrdo” vypsat konkrétní tvar, ale napsat kód, který umí tvar vypsat obecně, v závislosti na hodnotě vstupních parametrů, které budou určeny proměnnými na začátku programu.**

Pokud byste měli k úloze jakékoliv dotazy, napište mi prosím na Discordu, rád vám vše vysvětlím :)

Tvary, které by váš program měl umět vypsat:

*   Řádek o délce `n` (`n` je parametr).
    
    Příklad pro `n=3`:
    
        xxx
    
*   Sloupec o výšce `n` (`n` je parametr).
    
    Příklad pro `n=4`:
    
        x
        x
        x
        x
    
*   Čtverec o straně `n` (`n` je parametr).
    
    Příklad pro `n=3`:
    
        xxx
        xxx
        xxx
    
*   Obdélník o šířce `w` a výšce `h` (`w` a `h` jsou parametry).
    
    Příklad pro `w=3` a `h=4`:
    
        xxx
        xxx
        xxx
        xxx
    
*   “Žebřík” s `n` stupni a šířkou `w` (`n` a `w` jsou parametry). Žebřík s `n` stupni je tvořen `n` řádky obsahujícími `w` znaků `'x'` a `n-1` prázdnými řádky.
    
    Příklad pro `n=3` a `w=4`:
    
        xxxx
        
        xxxx
        
        xxxx
    
*   Dutý čtverec o straně `n` (`n` je parametr). Dutý čtverec obsahuje znaky `'x'` po svém obvodu, ale uvnitř je prázdný (vypište znak mezery `' '`).
    
    Příklad pro `n=4`:
    
        xxxx
        x  x
        x  x
        xxxx
    
    Aby dutý čtverec vypadal v terminálu trochu lépe, můžete zkusit vypsat mezery mezi jednotlivými sloupci:
    
        x x x x
        x     x
        x     x
        x x x x
    
*   Pravotočivá diagonála s výškou `n` (`n` je parametr).
    
    Příklad pro `n=5`:
    
        x
         x
          x
           x
            x
    
*   Levotočivá diagonála s výškou `n` (`n` je parametr).
    
    Příklad pro `n=4`:
    
           x
          x
         x
        x
    
*   Trojúhelník s výškou `n` (`n` je parametr).
    
    Příklad pro `n=5`:
    
            x
           x x
          x   x
         x     x
        xxxxxxxxx
    
    Příklad pro `n=3`:
    
          x  
         x x
        xxxxx
    
*   Obdélník vyplněný čísly o šířce `w` a výšce `h` . Vypište dutý obdélník, který bude mít uvnitř čísla `0-9`, která se budou postupně zvyšovat, zleva doprava a shora dolů. Jakmile by číslo dosáhlo hodnoty `10`, tak opět vypište nulu, místo čísla `11` vypište opět jedničku atd.
    
    Příklad pro `w=5` a `h=5`:
    
        xxxxx
        x012x
        x345x
        x678x
        xxxxx
    
    Příklad pro `w=8` a `h=4`:
    
        xxxxxxxx
        x012345x
        x678901x
        xxxxxxxx

