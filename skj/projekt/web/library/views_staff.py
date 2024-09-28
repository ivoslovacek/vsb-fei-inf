from django.contrib import messages
from django.contrib.auth.decorators import login_required
from django.shortcuts import render, redirect
from django.urls import reverse
from .models import Kniha, FyzickaKniha, Osoba, Vypujcky

from datetime import datetime


@login_required
def staff_borrow_book(request):
    if not request.user.is_staff:
        response = render(request, 'staff/insufficient_permissions.html')
        response.status_code = 403
        return response

    if request.method == 'POST':
        id_osoba_str = request.POST.get('id_osoba')
        id_osoba = None

        if not id_osoba_str:
            messages.error(request, ("Nebylo zadané ID uživatele!"))
            return redirect(reverse('borrow_book'))

        try:
            id_osoba = int(id_osoba_str)
        except ValueError:
            messages.error(request, ("Neplatné ID uživatele"))
            return redirect(reverse('borrow_book'))

        osoba = None

        try:
            osoba = Osoba.objects.get(pk=id_osoba)
        except osoba.DoesNotExist:
            messages.error(request, ("Neexistuje uživatel se zadaným id!"))
            return redirect(reverse('borrow_book'))

        if osoba.datum_umrti:
            messages.error(request, ("Neplatný uživatel!"))
            return redirect(reverse('borrow_book'))

        id_fknihy_str = request.POST.get('id_fknihy')
        id_fknihy = None

        if not id_fknihy_str:
            messages.error(request, ("Nebylo zadané ID kopie knihy!"))
            return redirect(reverse('borrow_book'))

        try:
            id_fknihy = int(id_fknihy_str)
        except ValueError:
            messages.error(request, ("Neplatné ID kopie knihy"))
            return redirect(reverse('borrow_book'))

        id_oq = Kniha.objects.raw(f"""
                 select k.id_knihy as id_knihy, k.id_originalu as id_o
                 from kniha k
                 join fyzicka_kniha fk on fk.id_knihy = k.id_knihy
                 where fk.id_fknihy = {id_fknihy}
                 """)

        if not id_oq:
            messages.error(request, ("Neexistuje kopie knihy se zadaným ID!"))
            return redirect(reverse('borrow_book'))

        id_originalu = id_oq[0].id_o if id_oq[0].id_o else id_oq[0].id_knihy

        borrowed_books = Vypujcky.objects.raw(
            f"""
                    select v.id_vypujcky
                    from kniha k
                    join fyzicka_kniha fk on fk.id_knihy = k.id_knihy
                    join vypujcky v on v.id_fknihy = fk.id_fknihy
                    where (k.id_originalu = {id_originalu} or
                           k.id_knihy = {id_originalu}) and
                           v.do_d is null and v.id_osoba = {id_osoba} or
                           v.id_fknihy = {id_fknihy} and v.do_d is null
                """
        )

        if borrowed_books:
            messages.error(
                request, ("Uživatel již má zapůjčenou tuhle knihu!"))
            return redirect(reverse('borrow_book'))

        Vypujcky.objects.create(
            id_osoba=osoba,
            id_fknihy=FyzickaKniha.objects.get(id_fknihy=id_fknihy),
            od_d=datetime.now().date()
        )

        messages.success(request, (f"Kopie knihy s ID: {
                         id_fknihy} byla úspěšně vypůjčena."))
        return redirect(reverse('borrow_book'))

    else:
        return render(request, 'staff/borrow_book.html')


@login_required
def staff_return_book(request):
    if not request.user.is_staff:
        response = render(request, 'staff/insufficient_permissions.html')
        response.status_code = 403
        return response

    if request.method == 'POST':
        id_fknihy_str = request.POST.get('id_fknihy')
        id_fknihy = None

        if not id_fknihy_str:
            messages.error(request, ("Nebylo zadané ID kopie knihy!"))
            return redirect(reverse('return_book'))

        try:
            id_fknihy = int(id_fknihy_str)
        except ValueError:
            messages.error(request, ("Neplatné ID kopie knihy"))
            return redirect(reverse('return_book'))

        try:
            vypujcka = Vypujcky.objects.get(id_fknihy=id_fknihy, do_d=None)
            vypujcka.do_d = datetime.now().date()
            vypujcka.save()

            messages.success(request, (f"Kopie knihy s ID: {
                             id_fknihy} byla úspěšně vrácena."))
            return redirect(reverse('return_book'))
        except Vypujcky.DoesNotExist:
            messages.error(
                request, (f"Neexistuje kopie knihy se zadaným ID: {id_fknihy}!"))
            return redirect(reverse('return_book'))
    else:
        return render(request, 'staff/return_book.html')
