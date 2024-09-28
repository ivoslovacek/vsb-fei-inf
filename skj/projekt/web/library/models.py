# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models
from django.contrib.auth.models import User


class Autori(models.Model):
    # The composite primary key (id_knihy, id_osoba) found, that is not supported. The first column is selected.
    id_knihy = models.OneToOneField(
        'Kniha', models.DO_NOTHING, db_column='id_knihy', primary_key=True)
    id_osoba = models.ForeignKey(
        'Osoba', models.DO_NOTHING, db_column='id_osoba')

    class Meta:
        managed = False
        db_table = 'autori'
        unique_together = (('id_knihy', 'id_osoba'),)


class FyzickaKniha(models.Model):
    id_fknihy = models.AutoField(primary_key=True)
    id_knihy = models.ForeignKey(
        'Kniha', models.DO_NOTHING, db_column='id_knihy')

    class Meta:
        managed = False
        db_table = 'fyzicka_Kniha'


class Jazyk(models.Model):
    id_jazyku = models.AutoField(primary_key=True)
    nazev = models.CharField(
        max_length=150, db_collation='SQL_Latin1_General_CP1_CS_AS')
    id_osoba = models.ForeignKey(
        'Osoba', models.DO_NOTHING, db_column='id_osoba', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'jazyk'


class Kniha(models.Model):
    id_knihy = models.BigIntegerField(primary_key=True)
    nazev = models.CharField(
        max_length=150, db_collation='SQL_Latin1_General_CP1_CS_AS')
    rok_vydani = models.SmallIntegerField(blank=True, null=True)
    edice = models.SmallIntegerField()
    last_update = models.DateField()
    id_zanru = models.ForeignKey(
        'Zanr', models.DO_NOTHING, db_column='id_zanru', blank=True, null=True)
    id_jazyku = models.ForeignKey(
        Jazyk, models.DO_NOTHING, db_column='id_jazyku', blank=True, null=True)
    id_originalu = models.ForeignKey(
        'self', models.DO_NOTHING, db_column='id_originalu', blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'kniha'


class Osoba(models.Model):
    id_osoba = models.AutoField(primary_key=True)
    id_user = models.ForeignKey(User, on_delete=models.SET_NULL, null=True)
    jmeno = models.CharField(
        max_length=150, db_collation='SQL_Latin1_General_CP1_CS_AS')
    prijmeni = models.CharField(
        max_length=150, db_collation='SQL_Latin1_General_CP1_CS_AS')
    datum_narozeni = models.DateField()
    datum_umrti = models.DateField(blank=True, null=True)

    class Meta:
        managed = True
        db_table = 'osoba'


class Vypujcky(models.Model):
    id_vypujcky = models.AutoField(primary_key=True)
    od_d = models.DateField()
    do_d = models.DateField(blank=True, null=True)
    id_fknihy = models.ForeignKey(
        FyzickaKniha, models.DO_NOTHING, db_column='id_fknihy')
    id_osoba = models.ForeignKey(
        Osoba, models.DO_NOTHING, db_column='id_osoba')

    class Meta:
        managed = False
        db_table = 'vypujcky'


class Zanr(models.Model):
    id_zanru = models.AutoField(primary_key=True)
    nazev = models.CharField(unique=True, max_length=150,
                             db_collation='SQL_Latin1_General_CP1_CS_AS')

    class Meta:
        managed = False
        db_table = 'zanr'
