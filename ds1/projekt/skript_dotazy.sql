/* 1;1;17;Délka výpujčky ve dnech*/
select id_vypujcky, datediff(day, od_d, do_d) as delka_vypujcky
from Vypujcky

/* 1;2;15;Staří vydání v rocích*/
select id_knihy,
       nazev,
       rok_vydani,
       datediff(year, datefromparts(rok_vydani, 1, 1), current_timestamp) as stari_vydani_v_rocich
from Kniha

/* 1;3;15;Sestupně seřazené knihy podle roku vydání*/
select id_knihy, nazev, rok_vydani, edice
from Kniha
order by rok_vydani desc

/* 1;4;30;Vek osob podle data narozeni*/
select id_osoba, jmeno, prijmeni, datediff(year, datum_narozeni, current_timestamp) as vek
from osoba
order by datediff(year, datum_narozeni, current_timestamp)

/* 2;1;5;Výpis prvních nebo neznámých edic knih bez staršího evidovaného vydání*/
select id_knihy, nazev, rok_vydani, edice
from Kniha
where id_originalu is null
  and (edice = 1 or edice = 0)

/* 2;2;14;Výpis dokončených výpůjček*/
select id_vypujcky, id_osoba, do_d, do_d
from Vypujcky
where do_d is not null

/* 2;3;4;Výpis všech žánrů obsahující slovo román*/
select id_zanru, nazev
from Zanr
where nazev like '%román%'

/* 2;4;3;Výpis všech lidí kteří se dožili více jak 80 let*/
select id_osoba, jmeno, prijmeni, datediff(year, datum_narozeni, datum_umrti) as vek
from Osoba
where datediff(year, datum_narozeni, datum_umrti) > 80

/* 3;1;12;Vydání knih s v originálním jazyce nebo neznámým překladatelem*/
select id_knihy, nazev, rok_vydani, edice
from Kniha
where id_jazyku in (select id_jazyku
                    from Jazyk
                    where id_osoba is null)

/* 3;2;12;Vydání knih s v originálním jazyce nebo neznámým překladatelem*/
select id_knihy, nazev, rok_vydani, edice
from Kniha
where exists (select id_jazyku
              from Jazyk
              where Kniha.id_jazyku = Jazyk.id_jazyku
                and id_osoba is null)

/* 3;3;12;Vydání knih s v originálním jazyce nebo neznámým překladatelem*/
select id_knihy, nazev, rok_vydani, edice
from Kniha
where id_jazyku = any (select id_jazyku
                       from Jazyk
                       where Kniha.id_jazyku = Jazyk.id_jazyku
                         and id_osoba is null)

/* 4;1;8;Počet evidovaných vydání knih dle autora*/
select count(id_knihy) as pocet_knih, id_osoba
from Autori
group by id_osoba

/* 4;2;13;Počet kopii u knih s alepsoň jednou kopii*/
select id_knihy, count(id_fknihy) as pocet_kopii_knih
from Fyzicka_Kniha
group by id_knihy

/* 4;3;1;Rok s největším počtem vydaných knih*/
select top 1 count(*) pocet_vydanych_knih, rok_vydani
from Kniha
group by rok_vydani
order by count(*) desc

/* 4;4;4;ID osob s více jak 4mi výpůjčkami*/
select id_osoba
from Vypujcky
group by id_osoba
having count(id_osoba) >= 2

/* 5;1;11;Výpis ISBN knihy, názvu knihy a roku vydaní knih v českém jazyce*/
select K.id_knihy, K.nazev, K.rok_vydani
from Kniha K
         join Jazyk J on K.id_jazyku = J.id_jazyku
where J.nazev = 'Čeština'

/* 5;2;11;Výpis ISBN knihy, názvu knihy a roku vydaní knih v českém jazyce*/
select K.id_knihy,
       K.nazev,
       K.rok_vydani
from Kniha K
where id_jazyku is not null
  and K.id_jazyku in (select J.id_jazyku
                      from Jazyk J
                      where J.nazev = 'Čeština')

/* 5;3;7;Pocet osob, které si vypůjčili daný žánr*/
select count(O.id_osoba) as pocet_osob, K.id_zanru, Z.nazev
from Kniha K
         left join Fyzicka_Kniha on K.id_knihy = Fyzicka_Kniha.id_knihy
         left join dbo.Vypujcky V on Fyzicka_Kniha.id_fknihy = V.id_fknihy
         left join dbo.Osoba O on V.id_osoba = O.id_osoba
         right join dbo.Zanr Z on K.id_zanru = Z.id_zanru
group by K.id_zanru, Z.nazev
order by K.id_zanru

/* 5;4;15;Pocet aktualně vypůjčených kopií pro jednotlivé vydání knih*/
select K.id_knihy,
       K.nazev,
       K.edice,
       count(V.id_vypujcky) as pocet_vypujcenych_kopii
from Kniha K
         left join dbo.Fyzicka_Kniha FK on K.id_knihy = FK.id_knihy
         left join dbo.Vypujcky V on FK.id_fknihy = V.id_fknihy
where V.do_d is null
group by K.id_knihy, K.nazev, K.edice

/* 6;1;12;Knihy, které nejsou aktuálně zapůjčené*/
SELECT K.id_knihy, K.nazev
FROM Kniha K
WHERE NOT EXISTS (SELECT distinct FK.id_knihy
                  FROM Fyzicka_Kniha FK
                           JOIN Vypujcky V ON FK.id_fknihy = V.id_fknihy
                  WHERE FK.id_knihy = K.id_knihy
                    AND V.do_d IS NULL)