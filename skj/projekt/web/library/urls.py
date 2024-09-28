from django.urls import path

from . import views, views_auth, views_user, views_staff

urlpatterns = [
    path('', views.index, name="index"),
    path('books', views.books, name='books'),
    path('book', views.book_detail, name='book_detail'),
    path('login', views_auth.login_user, name='login_page'),
    path('logout', views_auth.logout_user, name='logout_page'),
    path('create_account', views_auth.create_user, name='create_user'),
    path('profile', views_user.user_profile, name='user_profile'),
    path('profile/books', views_user.user_books_current, name='user_books_current'),
    path('profile/books/history', views_user.user_books_history,
         name='user_books_history'),
    path('profile/delete', views_auth.delete_user, name='delete_user'),
    path('staff/manage/borrow', views_staff.staff_borrow_book, name='borrow_book'),
    path('staff/manage/return', views_staff.staff_return_book, name='return_book'),
]
