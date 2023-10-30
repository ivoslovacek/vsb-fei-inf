select film.film_id,
       film.title,
       count(fa.actor_id) actor_count,
       count(fc.category_id) category_count
from film
left join dbo.film_actor fa on film.film_id = fa.film_id
left join dbo.film_category fc on film.film_id = fc.film_id
group by film.film_id, film.title

SELECT first_name, last_name,
       (select count(*)
        from rental
        where rental.customer_id = customer.customer_id
            and DATEDIFF(day, rental.rental_date, rental.return_date) < 5
        ) less_then_5,
       (select count(*)
        from rental
        where rental.customer_id = customer.customer_id
          and DATEDIFF(day, rental.rental_date, rental.return_date) < 7
       ) less_then_7
from customer

SELECT first_name, last_name
FROM customer
WHERE
(
    SELECT COUNT(*)
    FROM
    rental
    JOIN inventory ON rental.inventory_id = inventory.inventory_id
    WHERE rental.customer_id = customer.customer_id AND film_id IN
    (
        SELECT film_id
        FROM
        actor
        JOIN film_actor ON actor.actor_id = film_actor.actor_id
        WHERE actor.first_name = 'TOM' AND actor.last_name = 'MCKELLEN'
    )
)
>
(
    SELECT COUNT(*)
    FROM
    rental
    JOIN inventory ON rental.inventory_id = inventory.inventory_id
    WHERE rental.customer_id = customer.customer_id AND film_id IN
    (
    SELECT film_id
    FROM
    actor
    JOIN film_actor ON actor.actor_id = film_actor.actor_id
    WHERE actor.first_name = 'GROUCHO' AND actor.last_name = 'SINATRA'
    )
)