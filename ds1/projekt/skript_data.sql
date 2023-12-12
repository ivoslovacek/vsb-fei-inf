declare @counter int = 0;

insert into Jazyk (nazev)
values ('Němčina')

insert into Zanr
values ('Válečný román')

insert into Osoba (jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Erich Maria', 'Remarque', '1898-6-22', '1970-9-25')


insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9783462046335, 'Im Westen Nichts Neues', 2014, 24,
        (select Zanr.id_zanru
         from Zanr
         where Zanr.nazev = 'Válečný román'),
        (select id_jazyku
         from Jazyk
         where nazev = 'Němčina'
           and id_osoba is null))

set @counter = 0;
while @counter < 1
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9783462046335)

        SET @counter = @counter + 1;
    end

insert into Autori(id_knihy, id_osoba)
values (9783462046335, (select id_osoba
                        from Osoba
                        where Osoba.jmeno = 'Erich Maria'
                          and Osoba.prijmeni = 'Remarque'))

insert into Osoba (jmeno, prijmeni, datum_narozeni)
values ('Ivana', 'Parkmanová', '1991-1-2')

insert into Jazyk (nazev, id_osoba)
values ('Čeština', (select id_osoba
                    from Osoba
                    where jmeno = 'Ivana'
                      and prijmeni = 'Parkmanová'))

insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku, id_originalu)
values (9788024942230, 'Na západní frontě klid', 2020, 11,
        (select Zanr.id_zanru
         from Zanr
         where Zanr.nazev = 'Válečný román'),
        (select id_jazyku
         from Jazyk
                  join dbo.Osoba O on Jazyk.id_osoba = O.id_osoba
         where Jazyk.nazev = 'Čeština'
           and jmeno = 'Ivana'
           and prijmeni = 'Parkmanová'),
        9783462046335)

set @counter = 0;
while @counter < 5
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9788024942230)

        SET @counter = @counter + 1;
    end

insert into Autori(id_knihy, id_osoba)
values (9788024942230, (select id_osoba
                        from Osoba
                        where Osoba.jmeno = 'Erich Maria'
                          and Osoba.prijmeni = 'Remarque'))

insert into Osoba(jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Arthur Wesley', 'Wheen', '1897-2-9', '1971-3-15')

insert into Jazyk(nazev, id_osoba)
values ('Angličtina', (select id_osoba
                       from Osoba
                       where jmeno = 'Arthur Wesley'
                         and prijmeni = 'Wheen'))

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku, id_originalu)
values (9780449213940, 'All Quiet on the Western Front', 1987, 0, (select Zanr.id_zanru
                                                                   from Zanr
                                                                   where Zanr.nazev = 'Válečný román'),
        (select id_jazyku
         from Jazyk
                  join Osoba on Jazyk.id_osoba = Osoba.id_osoba
         where Jazyk.nazev = 'Angličtina'
           and jmeno = 'Arthur Wesley'
           and prijmeni = 'Wheen'), 9783462046335)

set @counter = 0;
while @counter < 3
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9780449213940)

        SET @counter = @counter + 1;
    end

insert into Autori(id_knihy, id_osoba)
values (9780449213940, (select id_osoba
                        from Osoba
                        where Osoba.jmeno = 'Erich Maria'
                          and Osoba.prijmeni = 'Remarque'))

insert into Osoba(jmeno, prijmeni, datum_narozeni)
values ('Karin', 'Lednická', '1969-2-5')

insert into Zanr
values ('Románová kronika')

insert into Jazyk(nazev)
values ('Čeština')

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788088362005, 'Šikmý kostel', 2020, 1, (select id_zanru
                                                 from Zanr
                                                 where nazev = 'Románová kronika'), (select id_jazyku
                                                                                     from Jazyk
                                                                                     where Jazyk.nazev = 'Čeština'
                                                                                       and Jazyk.id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9788088362005, (select id_osoba
                        from Osoba
                        where jmeno = 'Karin'
                          and prijmeni = 'Lednická'))

set @counter = 0;
while @counter < 4
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9788088362005)

        SET @counter = @counter + 1;
    end

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788088362043, 'Šikmý kostel 2', 2021, 1, (select id_zanru
                                                   from Zanr
                                                   where nazev = 'Románová kronika'), (select id_jazyku
                                                                                       from Jazyk
                                                                                       where Jazyk.nazev = 'Čeština'
                                                                                         and Jazyk.id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9788088362043, (select id_osoba
                        from Osoba
                        where jmeno = 'Karin'
                          and prijmeni = 'Lednická'))

set @counter = 0;
while @counter < 3
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9788088362043)

        SET @counter = @counter + 1;
    end

insert into Osoba(jmeno, prijmeni, datum_narozeni)
values ('Adrian', 'Newey', '1958-12-26')

insert into Jazyk(nazev)
values ('Angličtina')

insert into Zanr(nazev)
values ('Životopis')

insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9780008196806, 'How to Build a Car : The Autobiography of the World''s Greatest Formula 1 Designer', 2017, 1,
        (select id_zanru
         from Zanr
         where Zanr.nazev = 'Životopis'),
        (select id_jazyku
         from Jazyk
         where nazev = 'Angličtina'
           and id_osoba is null))


insert into Fyzicka_Kniha(id_knihy)
values (9780008196806)

insert into Autori(id_knihy, id_osoba)
values (9780008196806, (select id_osoba
                        from Osoba
                        where jmeno = 'Adrian'
                          and prijmeni = 'Newey'))

insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku, id_originalu)
values (9788081990182, 'Jak postavit monopost F1', 2020, 1,
        (select id_zanru
         from Zanr
         where Zanr.nazev = 'Životopis'),
        (select id_jazyku
         from Jazyk
         where nazev = 'Čeština'
           and id_osoba is null),
        9780008196806)

insert into Autori(id_knihy, id_osoba)
values (9788081990182, (select id_osoba
                        from Osoba
                        where jmeno = 'Adrian'
                          and prijmeni = 'Newey'))

set @counter = 0;
while @counter < 3
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9788081990182)

        SET @counter = @counter + 1;
    end

insert into Osoba(jmeno, prijmeni, datum_narozeni)
values ('Michal', 'Viewegh', '1962-3-31')

insert into Zanr
values ('Autobiografický román')

insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788085247893, 'Báječná léta pod psa', 1997, 5,
        (select id_zanru
         from Zanr
         where nazev = 'Autobiografický román'),
        (select id_jazyku
         from Jazyk
         where Jazyk.nazev = 'Čeština'
           and id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9788085247893, (select id_osoba
                        from Osoba
                        where jmeno = 'Michal'
                          and prijmeni = 'Viewegh'))

insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku, id_originalu)
values (9788024936802, 'Báječná léta pod psa', 2018, 7,
        (select id_zanru
         from Zanr
         where nazev = 'Autobiografický román'),
        (select id_jazyku
         from Jazyk
         where Jazyk.nazev = 'Čeština'
           and id_osoba is null),
        9788085247893)

insert into Autori(id_knihy, id_osoba)
values (9788024936802, (select id_osoba
                        from Osoba
                        where jmeno = 'Michal'
                          and prijmeni = 'Viewegh'))

set @counter = 0;
while @counter < 3
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9788024936802)

        SET @counter = @counter + 1;
    end

insert into Zanr
values ('Román')

insert into Kniha (id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788020205070, 'Výchova Dívek V Čechách', 1994, 1,
        (select id_zanru
         from Zanr
         where nazev = 'Román'),
        (select id_jazyku
         from Jazyk
         where Jazyk.nazev = 'Čeština'
           and id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9788020205070, (select id_osoba
                        from Osoba
                        where jmeno = 'Michal'
                          and prijmeni = 'Viewegh'))

insert into Fyzicka_Kniha
values (9788020205070)

insert into Osoba(jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Josef', 'Škvorecký', '1924-9-27', '2012-1-3')

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788085204032, 'Tankový prapor: fragment z doby kultů', 1990, 3,
        (select id_zanru
         from Zanr
         where nazev = 'Román'),
        (select id_jazyku
         from Jazyk
         where Jazyk.nazev = 'Čeština'
           and id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9788085204032, (select id_osoba
                        from Osoba
                        where jmeno = 'Josef'
                          and prijmeni = 'Škvorecký'))

set @counter = 0;
while @counter < 4
    begin
        insert into Fyzicka_Kniha(id_knihy)
        values (9788085204032)

        SET @counter = @counter + 1;
    end

insert into Osoba (jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Bohumil', 'Hrabal', '1914-3-28', '1997-2-3')

insert into Zanr
values ('Novela')

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788020421142, 'Ostře sledované vlaky', 2009, 9,
        (select id_zanru
         from Zanr
         where nazev = 'Novela'),
        (select id_jazyku
         from Jazyk
         where Jazyk.nazev = 'Čeština'
           and id_osoba is null))

insert into Fyzicka_Kniha
values (9788020421142)

select count(*) as Pocet_fyzickych_knih, nazev
from Fyzicka_Kniha
         join dbo.Kniha K on Fyzicka_Kniha.id_knihy = K.id_knihy
group by K.id_knihy, K.nazev
order by count(*) desc

insert into Autori(id_knihy, id_osoba)
values (9788020421142, (select id_osoba
                        from Osoba
                        where jmeno = 'Bohumil'
                          and prijmeni = 'Hrabal'))

insert into osoba(jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Francis Scott', 'Key Fitzgerald', '1896-9-24', '1940-12-21')

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9780370005287, 'The Great Gatsby, The Last Tycoon', 1977, 0,
        (select id_zanru
         from Zanr
         where nazev = 'Román'),
        (select id_jazyku
         from Jazyk
         where nazev = 'Angličtina'
           and id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9780370005287, (select id_osoba
                        from Osoba
                        where jmeno = 'Francis Scott'
                          and prijmeni = 'Key Fitzgerald'))

insert into osoba(jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Lubomír', 'Dorůžka', '1924-3-18', '2013-12-16')

insert into Jazyk (nazev, id_osoba)
values ('Čeština', (select id_osoba
                    from Osoba
                    where jmeno = 'Lubomír'
                      and prijmeni = 'Dorůžka'))

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku, id_originalu)
values (9788020710819, 'Velký Gatsby, Poslední magnát', 2000, 2,
        (select id_zanru
         from Zanr
         where nazev = 'Román'),
        (select J.id_jazyku
         from Jazyk J
                  join dbo.Osoba O on O.id_osoba = J.id_osoba
         where J.nazev = 'Čeština'
           and O.jmeno = 'Lubomír'
           and O.prijmeni = 'Dorůžka'),
        9780370005287)

insert into Autori(id_knihy, id_osoba)
values (9788020710819, (select id_osoba
                        from Osoba
                        where jmeno = 'Francis Scott'
                          and prijmeni = 'Key Fitzgerald'))

insert into Fyzicka_Kniha
values (9788020710819)

insert into Osoba(jmeno, prijmeni, datum_narozeni, datum_umrti)
values ('Jan', 'Werich', '1905-2-6', '1980-10-31')

insert into Zanr
values ('Soubor pohádek')

insert into Kniha(id_knihy, nazev, rok_vydani, edice, id_zanru, id_jazyku)
values (9788000001937, 'Fimfarum', 1992, 8,
        (select id_zanru
         from Zanr
         where nazev = 'Soubor pohádek'),
        (select id_jazyku
         from Jazyk
         where nazev = 'Čeština'
           and id_osoba is null))

insert into Autori(id_knihy, id_osoba)
values (9788000001937, (select id_osoba
                        from Osoba
                        where jmeno = 'Jan'
                          and prijmeni = 'Werich'))

insert into Fyzicka_Kniha
values (9788000001937)

insert into Osoba(jmeno, prijmeni, datum_narozeni)
values ('Jakub', 'Novák', '1990-01-15'),
       ('Eva', 'Svobodová', '1985-07-22'),
       ('Petr', 'Dvořák', '1978-03-10'),
       ('Tereza', 'Kovářová', '1995-09-05'),
       ('Jan', 'Procházka', '1982-11-30'),
       ('Karolína', 'Moravcová', '1998-04-18'),
       ('Lukáš', 'Kučera', '1973-06-25'),
       ('Barbora', 'Marešová', '1989-12-12'),
       ('Martin', 'Šimáček', '1992-08-08'),
       ('Zuzana', 'Havlíčková', '1980-02-20'),
       ('Michal', 'Novotný', '1993-05-14'),
       ('Kateřina', 'Křížová', '1975-09-28'),
       ('Adam', 'Urban', '1987-10-03'),
       ('Lucie', 'Pospíšilová', '1986-11-25'),
       ('Tomáš', 'Richter', '1991-08-17'),
       ('Adéla', 'Janků', '1983-04-05'),
       ('Ondřej', 'Černý', '1996-02-12'),
       ('Nela', 'Kolářová', '1979-07-30'),
       ('Filip', 'Žižka', '1984-09-22');

insert into Vypujcky(od_d, do_d, id_fknihy, id_osoba)
values ('2020-1-15', '2020-2-16', 2, 12),
       ('2020-1-16', '2020-2-18', 3, 15),
       ('2021-3-3', '2021-4-8', 3, 18),
       ('2022-4-8', '2022-5-7', 7, 29),
       ('2022-5-8', '2022-6-7', 7, 17),
       ('2022-6-14', '2022-7-11', 7, 29),
       ('2020-3-6', '2020-4-1', 10, 13),
       ('2020-4-3', '2020-5-7', 11, 17),
       ('2020-5-7', '2020-6-2', 14, 17),
       ('2020-8-18', '2020-9-2', 14, 17),
       ('2022-1-18', '2022-3-2', 18, 24),
       ('2022-3-14', '2022-3-30', 18, 14),
       ('2021-6-14', '2021-7-2', 25, 26),
       ('2021-8-9', '2021-9-15', 25, 19),
       ('2023-4-2', null, 25, 19),
       ('2023-3-6', null, 29, 14),
       ('2023-4-9', null, 21, 28)