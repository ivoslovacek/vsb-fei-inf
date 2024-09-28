from django.contrib.auth.decorators import login_required
from django.contrib.staticfiles import finders
from django.shortcuts import render
from .models import Osoba


@login_required
def user_profile(request):
    ctx = {}

    try:
        osoba = Osoba.objects.get(id_user=request.user.id)
        ctx["osoba"] = osoba

    except Osoba.DoesNotExist:
        ctx["osoba"] = None

    return render(request, "user/user_profile.html", ctx)


@login_required
def user_books_current(request):
    ctx = {}

    try:
        books = Osoba.objects.raw(
            f"""
                select k.id_knihy as id_knihy, k.nazev as nazev,
                       k.edice as edice, fk.id_fknihy as id_fknihy,
                       v.od_d as od_d,
                       oa.jmeno as jmeno, oa.prijmeni as prijmeni,
                       ou.id_osoba
                from osoba ou
                join vypujcky v on v.id_osoba = ou.id_osoba
                join fyzicka_kniha fk on fk.id_fknihy = v.id_fknihy
                join kniha k on k.id_knihy = fk.id_knihy
                left join autori on autori.id_knihy = k.id_knihy
                left join osoba oa on oa.id_osoba = autori.id_osoba
                where ou.id_user_id = {request.user.id} and
                      v.do_d is null
                order by v.od_d asc
                """)

        ctx['books'] = books

        if books:
            for book in books:
                book.cover_url = f"{
                    book.id_knihy}.png" if finders.find(
                    f'covers/{book.id_knihy}.png') is not None else 'default.png'

    except Osoba.DoesNotExist:
        pass

    return render(request, "user/user_books_current.html", ctx)


@login_required
def user_books_history(request):
    ctx = {}

    try:
        books = Osoba.objects.raw(
            f"""
                select k.id_knihy as id_knihy, k.nazev as nazev,
                       k.edice as edice, fk.id_fknihy as id_fknihy,
                       v.od_d as od_d, v.do_d as do_d,
                       oa.jmeno as jmeno, oa.prijmeni as prijmeni,
                       ou.id_osoba
                from osoba ou
                join vypujcky v on v.id_osoba = ou.id_osoba
                join fyzicka_kniha fk on fk.id_fknihy = v.id_fknihy
                join kniha k on k.id_knihy = fk.id_knihy
                left join autori on autori.id_knihy = k.id_knihy
                left join osoba oa on oa.id_osoba = autori.id_osoba
                where ou.id_user_id = {request.user.id}
                order by v.od_d desc
                """)

        ctx['books'] = books

        if books:
            for book in books:
                book.cover_url = f"{
                    book.id_knihy}.png" if finders.find(
                    f'covers/{book.id_knihy}.png') is not None else 'default.png'

    except Osoba.DoesNotExist:
        pass

    return render(request, "user/user_books_history.html", ctx)
