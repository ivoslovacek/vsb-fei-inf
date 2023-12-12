drop table if exists Autori
drop table if exists Vypujcky
drop table if exists Fyzicka_Kniha
drop table if exists Kniha
drop table if exists Zanr
drop table if exists Jazyk
drop table if exists Osoba
drop function if exists IsValidISBN_BigInt
go

CREATE FUNCTION dbo.IsValidISBN_BigInt(@isbn BIGINT)
    RETURNS BIT
AS
BEGIN
    DECLARE @IsValid BIT = 0;

    IF (@isbn >= 1000000000 AND @isbn <= 9999999999) -- ISBN-10
        BEGIN
            DECLARE @CheckDigit INT = 0;
            DECLARE @Multiplier INT = 10;
            DECLARE @TempISBN BIGINT = @isbn / 10;

            WHILE @TempISBN > 0
                BEGIN
                    SET @CheckDigit = @CheckDigit + (@TempISBN % 10) * @Multiplier;
                    SET @Multiplier = @Multiplier - 1;
                    SET @TempISBN = @TempISBN / 10;
                END

            SET @CheckDigit = @CheckDigit % 11;
            IF (@CheckDigit = 10)
                BEGIN
                    SET @CheckDigit = 0;
                END

            IF (@CheckDigit = @isbn % 10)
                BEGIN
                    SET @IsValid = 1;
                END
        END
    ELSE
        IF (@isbn >= 1000000000000 AND @isbn <= 9999999999999) -- ISBN-13
            BEGIN
                SET @CheckDigit = 0;
                SET @Multiplier = 1;
                DECLARE @Index INT = 1;

                WHILE @Index <= 12
                    BEGIN
                        SET @CheckDigit = @CheckDigit + (@isbn % 10) * IIF(@Multiplier = 1, 1, 3);
                        SET @Multiplier = 3 - @Multiplier;
                        SET @isbn = @isbn / 10;
                        SET @Index = @Index + 1;
                    END

                SET @CheckDigit = (10 - (@CheckDigit % 10)) % 10;

                IF (@isbn % 10 = @CheckDigit)
                    BEGIN
                        SET @IsValid = 1;
                    END
            END

    RETURN @IsValid;
END;
go

create table osoba
(
    id_osoba       int primary key identity,
    jmeno          varchar(150) not null,
    prijmeni       varchar(150) not null,
    datum_narozeni date         not null check (datum_narozeni < current_timestamp),
    datum_umrti    date default null check (datum_umrti < current_timestamp),
    constraint CK_DatumUmrti check (datum_umrti is null or datum_umrti >= datum_narozeni)
)

create table jazyk
(
    id_jazyku int primary key identity,
    nazev     varchar(150) not null,
    id_osoba  int          references osoba on delete set null
)

create table zanr
(
    id_zanru int primary key identity,
    nazev    varchar(150) not null unique
)

create table kniha
(
    id_knihy     bigint primary key,
    nazev        varchar(150) not null,
    rok_vydani   smallint,
    edice        smallint     not null,
    last_update  date         not null              default current_timestamp,
    id_zanru     int          references zanr on delete set null,
    id_jazyku    int          references jazyk on delete set null,
    id_originalu bigint references kniha (id_knihy) default null,
    constraint CK_ValidISBN check (dbo.IsValidISBN_BigInt(id_knihy) = 1)
)


create table fyzicka_Kniha
(
    id_fknihy int primary key identity,
    id_knihy  bigint not null references kniha on delete cascade
)
create table vypujcky
(
    id_vypujcky int primary key identity,
    od_d        date not null default current_timestamp,
    do_d        date          default null,
    id_fknihy   int  not null references fyzicka_kniha on delete cascade,
    id_osoba    int  not null references osoba on delete cascade,
    constraint CK_DobaVypujceni check (od_d < do_d or do_d is null)
)
create table autori
(
    id_knihy bigint,
    id_osoba int,
    primary key (id_knihy, id_osoba),
    foreign key (id_knihy) references kniha on delete cascade,
    foreign key (id_osoba) references osoba on delete cascade
)
go