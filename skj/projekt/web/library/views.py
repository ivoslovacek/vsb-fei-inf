from django.http import HttpResponse, HttpResponseServerError
from django.shortcuts import render
from django.contrib.staticfiles import finders
from .models import Vypujcky, Kniha, FyzickaKniha


def index(request):
    available_books = Kniha.objects.raw(
        """
                select k.id_knihy as id_knihy, k.nazev as nazev,
                        k.edice as edice,
                        o.jmeno as jmeno, o.prijmeni as prijmeni
                from kniha k
                left join autori on autori.id_knihy = k.id_knihy
                left join osoba o on o.id_osoba = autori.id_osoba
                where k.id_knihy in (select fk.id_knihy
                                       from fyzicka_kniha fk
                                       left join vypujcky v on v.id_fknihy = fk.id_fknihy
                                       where v.id_fknihy is null or v.do_d is not null)
                order by k.nazev, k.edice asc
            """

    )

    for book in available_books:
        book.cover_url = f"{
            book.id_knihy}.png" if finders.find(
            f'covers/{book.id_knihy}.png') is not None else 'default.png'

    context = {"books": available_books}

    return render(request, 'index.html', context)


def books(request):
    context = {}

    if request.method == "POST":
        search_input = request.POST.get('search_input')

        if search_input:
            book = None

            try:
                isbn = int(search_input)

                books = Kniha.objects.raw(
                    f"""
                        select kniha.id_knihy as id_knihy, kniha.nazev as nazev,
                        kniha.edice as edice,
                        o.jmeno as jmeno, o.prijmeni as prijmeni
                        from kniha kniha
                        left join autori on autori.id_knihy = kniha.id_knihy
                        left join osoba o on o.id_osoba = autori.id_osoba
                        where kniha.id_knihy = {isbn}
                        order by kniha.nazev, kniha.edice asc
                        """
                )
            except ValueError:
                books = Kniha.objects.raw(
                    """
                        select kniha.id_knihy as id_knihy, kniha.nazev as nazev,
                        kniha.edice as edice,
                        o.jmeno as jmeno, o.prijmeni as prijmeni
                        from kniha kniha
                        left join autori on autori.id_knihy = kniha.id_knihy
                        left join osoba o on o.id_osoba = autori.id_osoba
                        where convert(varchar, lower(kniha.nazev),150)
                                like convert(varchar, lower(%s), 150)
                        order by kniha.nazev, kniha.edice asc
                    """, ["%{}%".format(search_input)]
                )

            for book in books:
                book.cover_url = f"{
                    book.id_knihy}.png" if finders.find(
                    f'covers/{book.id_knihy}.png') is not None else 'default.png'

            context["books"] = books
    else:
        books = Kniha.objects.raw(
            """
                    select kniha.id_knihy as id_knihy, kniha.nazev as nazev,
                    kniha.edice as edice,
                    o.jmeno as jmeno, o.prijmeni as prijmeni
                    from kniha kniha
                    left join autori on autori.id_knihy = kniha.id_knihy
                    left join osoba o on o.id_osoba = autori.id_osoba
                    order by kniha.nazev, kniha.edice asc
                """
        )

        for book in books:
            book.cover_url = f"{
                book.id_knihy}.png" if finders.find(
                f'covers/{book.id_knihy}.png') is not None else 'default.png'

        context = {"books": books}

    return render(request, 'books.html', context)


def book_detail(request):
    isbn_parameter = request.GET.get('isbn')

    try:
        isbn = int(isbn_parameter)

        query_results = Kniha.objects.raw(
            f"""
                    select top 1 k.id_knihy as id_knihy, k.nazev as title,
                        k.rok_vydani as yop, k.edice as edition,
                        oa.jmeno as a_name, oa.prijmeni as a_surname,
                        oa.id_osoba as a_id,
                        z.nazev as genre, j.nazev as language,
                        ot.jmeno as t_name, ot.prijmeni as t_surname
                    from kniha k
                    left join autori on autori.id_knihy = k.id_knihy
                    left join osoba oa on oa.id_osoba = autori.id_osoba
                    left join zanr z on z.id_zanru = k.id_zanru
                    left join jazyk j on j.id_jazyku = k.id_jazyku
                    left join osoba ot on ot.id_osoba = j.id_osoba
                    where k.id_knihy = {isbn}
                """
        )

        if query_results:
            book_copies = FyzickaKniha.objects.raw(
                f"""
                    select fk.id_fknihy as id_fknihy
                    from fyzicka_kniha fk
                    left join vypujcky v on v.id_fknihy = fk.id_fknihy
                    where fk.id_knihy = {query_results[0].id_knihy}
                    group by fk.id_fknihy
                    except
                    select v2.id_fknihy
                    from vypujcky v2
                    where v2.do_d is null
                    """
            )

            for book in query_results:
                book.cover_url = f"{
                    book.id_knihy}.png" if finders.find(
                    f'covers/{book.id_knihy}.png') is not None else 'default.png'

            book = query_results[0]
            book.copies = str([book.id_fknihy for book in book_copies])

            return render(request, "book_detail.html", {"book": book})
        else:
            response = render(request, "httperror.html",
                              {"error": f"404 Not Found {isbn}"})
            response.status_code = 404
            return response

    except ValueError:
        response = render(request, "httperror.html", {
                          "error": "500 Internal Server Error"})
        response.status_code = 500
        return response
