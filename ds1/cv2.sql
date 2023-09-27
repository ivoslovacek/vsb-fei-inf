--select *
--from city
--join country
--on city.country_id = country.country_id

--select r.customer_id
--from rental r
--join customer  c on r.customer_id = c.customer_id
--where c.last_name = 'SIMPSON'

--select concat(customer.first_name, ' ', customer.last_name), address.address, city.city
--from customer
--join address on customer.address_id = address.address_id
--join city on address.city_id = city.city_id

select concat(staff.first_name, ' ', staff.last_name) name_of_manager,
       store_ad.address store_address,
       store_c.city store_city,
       store_co.country store_country,
       staff_ad.address staff_address,
       staff_c.city staff_city,
       staff_co.country staff_country
from store
join staff on store.manager_staff_id = staff.staff_id
join address store_ad on store.address_id = store_ad.address_id
join city store_c on store_ad.city_id = store_c.city_id
join country store_co on store_c.country_id = store_co.country_id
join address staff_ad on staff.address_id = staff_ad.address_id
join city staff_c on staff_ad.city_id = staff_c.city_id
join country staff_co on staff_co.country_id = staff_c.country_id

select film.film_id, film_actor.actor_id, film_category.category_id
from film
join film_actor on film.film_id = film_actor.film_id
join film_category on film.film_id = film_category.film_id
where film.film_id = 1
order by film_actor.actor_id

select payment.payment_id, payment.amount, rental.rental_date
from payment
left join rental on payment.rental_id = rental.rental_id

select film.film_id, film.title, l.name language, ol.name original_language
from film
join language l on l.language_id = film.language_id
left join language ol on ol.language_id = film.original_language_id

select film.title
from film
left join inventory on film.film_id = inventory.film_id
where inventory.film_id is null

select film.title, language.name
from film
left join language on language.language_id = film.language_id and language.name like 'I%'