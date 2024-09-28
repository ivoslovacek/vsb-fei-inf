from django.shortcuts import render, redirect
from django.urls import reverse
from django.contrib import messages
from django.contrib import auth
from django.contrib.auth.decorators import login_required
from django.core.exceptions import ValidationError
from .models import Osoba

from datetime import datetime


def login_user(request):
    if request.user.is_authenticated:
        messages.warning(request, ("Jste už přihlášen/a."))
        return redirect(reverse('index'))

    if request.method == "POST":
        username = request.POST.get('username')
        password = request.POST.get('password')

        user = auth.authenticate(request, username=username, password=password)
        print(password)

        if user:
            auth.login(request, user)
            messages.success(request, ("Přihlášení proběhlo úspěšně."))

            next = request.GET.get('next')
            if next:
                return redirect(next)
            else:
                return redirect(reverse('index'))

        else:
            messages.error(
                request, ("Chybně zadané heslo nebo uživatelské jméno!"))
            return redirect(reverse('login_page'))
    else:
        return render(request, "auth/login_page.html")


def logout_user(request):
    if request.user.is_authenticated:
        auth.logout(request)

    messages.success(request, ("Odhlášení proběhlo úspěšně"))
    return redirect(reverse('index'))


def create_user(request):
    if request.method == "POST":
        username = request.POST.get('username')
        password = request.POST.get('password')
        password_again = request.POST.get('password_again')
        first_name = request.POST.get('first_name')
        last_name = request.POST.get('last_name')

        try:
            birth_date = datetime.strptime(
                request.POST.get('birth_date'), "%Y-%m-%d").date()
        except ValueError:
            messages.error(request, ("Neplatné datum narození"))
            is_valid = False

        is_valid = True

        if len(username) <= 3:
            messages.error(
                request, ("Uživatelské jméno musí mít délku minimalně 4!"))
            is_valid = False

        if auth.models.User.objects.filter(username=username).exists():
            messages.error(request, ("Uživatelské jméno je již používáno!"))
            is_valid = False

        if not first_name:
            messages.error(
                request, ("Zadejte křestní jméno!"))
            is_valid = False

        if not last_name:
            messages.error(
                request, ("Zadejte příjmení!"))
            is_valid = False

        if birth_date >= datetime.now().date():
            messages.error(
                request, ("Uživatelské jméno musí mít délku minimalně 4!"))
            is_valid = False

        try:
            auth.password_validation.validate_password(password)

            if (password != password_again):
                messages.error(
                    request, ("Zadané hesla se neshodují"))
                is_valid = False

            user = auth.models.User.objects.create_user(
                username=username, password=password)

            if not is_valid:
                return redirect(reverse('create_user'))

            Osoba.objects.create(
                jmeno=first_name,
                prijmeni=last_name,
                datum_narozeni=birth_date,
                id_user=user
            )

            user.save()

            messages.success(request, ("Účet byl úspěšně vytvořen"))
            return redirect(reverse('login_page'))

        except ValidationError:
            messages.error(
                request, ("Zadejte silnější heslo! (Musí být 8 znaků dlouhé a \
                        obsahovat alespoň jedno číslo a jeden specialní znak!)"))
            return redirect(reverse('create_user'))
    else:
        return render(request, "auth/create_user.html")


@login_required
def delete_user(request):
    if not request.user.is_authenticated:
        request.session['previous_page'] = 'delete_user'
        return redirect(reverse('login_page'))

    if request.method == 'POST':
        confirmation = request.POST.get('confirmation')

        if confirmation != 'Chci smazat účet':
            messages.error("Potvrzovací text nebyl správně opsán")
            return redirect(reverse('user_profile'))

        user = request.user
        auth.logout(request)
        user.delete()

        return redirect(reverse('index'))

    else:
        return render(request, "auth/delete_user.html")
