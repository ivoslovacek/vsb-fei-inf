select rating, length, count(*)
from film
group by rating, length

select first_name + ' ' +  last_name , count(*)  pocet
from actor
group by first_name + ' ' +  last_name
order by pocet desc

select year(payment_date) payment_year, month(payment_date) payment_day, sum(amount) amount_sum
from payment
group by year(payment_date), month(payment_date)
having sum(amount) > 20000

select rating
from film
where length < 50
group by rating
having sum(length) > 250
order by rating desc

select film.language_id, language.name, count(film.film_id)
from  film
right join language on film.language_id = language.language_id
group by film.language_id, language.name

select sum(payment.amount)
from payment
right join rental on rental.rental_id = payment.rental_id
group by payment.amount
having sum(payment.amount) > 100

select customer.customer_id, address.address_id, count(distinct film_actor.actor_id) actor_count
from customer
join rental on customer.customer_id = rental.customer_id
join inventory on rental.inventory_id = inventory.inventory_id
join film on inventory.film_id = film.film_id
join film_actor on film.film_id = film_actor.film_id
join address on customer.address_id = address.address_id
group by customer.customer_id, address.address_id
having count(distinct film_actor.actor_id) > 40

select film.title
from film
join inventory on film.film_id = inventory.film_id
join rental on inventory.inventory_id = rental.inventory_id
join customer on rental.customer_id = customer.customer_id
where film.length > 50 and customer.last_name = 'BELL'
group by rental.customer_id, film.title
having count(film.film_id) = 1
